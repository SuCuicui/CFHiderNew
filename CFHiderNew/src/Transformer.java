import java.io.*;
import java.util.*;
import java.util.concurrent.CopyOnWriteArrayList;

import org.omg.CORBA.PRIVATE_MEMBER;

import com.sun.java.swing.plaf.windows.WindowsTreeUI.ExpandedIcon;
import com.sun.xml.internal.ws.api.server.Invoker;

import soot.*;
import soot.JastAddJ.LongType;
import soot.JastAddJ.TypeDecl;
import soot.javaToJimple.LocalGenerator;
import soot.jbco.util.Rand;
import soot.jimple.AnyNewExpr;
import soot.jimple.ArrayRef;
import soot.jimple.AssignStmt;
import soot.jimple.BinopExpr;
import soot.jimple.CastExpr;
import soot.jimple.Constant;
import soot.jimple.DefinitionStmt;
import soot.jimple.DoubleConstant;
import soot.jimple.Expr;
import soot.jimple.FloatConstant;
import soot.jimple.IdentityStmt;
import soot.jimple.IfStmt;
import soot.jimple.InstanceInvokeExpr;
import soot.jimple.InstanceOfExpr;
import soot.jimple.IntConstant;
import soot.jimple.InvokeExpr;
import soot.jimple.InvokeStmt;
import soot.jimple.Jimple;
import soot.jimple.LongConstant;
import soot.jimple.NewArrayExpr;
import soot.jimple.NopStmt;
import soot.jimple.NullConstant;
import soot.jimple.Ref;
import soot.jimple.ReturnStmt;
import soot.jimple.SpecialInvokeExpr;
import soot.jimple.StaticInvokeExpr;
import soot.jimple.Stmt;
import soot.jimple.StringConstant;
import soot.jimple.VirtualInvokeExpr;
import soot.jimple.internal.AbstractBinopExpr;
import soot.jimple.internal.JEqExpr;
import soot.jimple.internal.JLengthExpr;
import soot.options.*;
import soot.toolkits.graph.*;
import soot.toolkits.scalar.FlowSet;
import soot.util.Numberable;
import sun.org.mozilla.javascript.internal.ast.Assignment;

/**
 * @author SuCuicui
 **/
public class Transformer
{

	static final int N=20;
	static long counter = 0;
	static Writer indexWriter=null;
    final static double ratio = 0.5;
    
	static Writer getWriter(){
		String filename = "/tmp/counter";
	    if(indexWriter==null){
			try{
				indexWriter = new PrintWriter(filename, "UTF-8");

			} catch (IOException e) {
			   // do something
			}
	    }
		return indexWriter;
	}

	static void closeWriter(){
		if(indexWriter !=null){
			try {
				indexWriter.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			indexWriter = null;
		}
	}

	public static void indexwriter(String content) {
		String file="/tmp/SGXindex";
		BufferedWriter out = null;
		try {
			out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file, true)));
			out.write(content+"\n");
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				out.close();
				} catch (IOException e) {
					e.printStackTrace();
					}
			}
		}
	
	ArrayList<Value> condVals = new ArrayList<Value>();
	ArrayList<Value> condValsInt = new ArrayList<Value>();
	ArrayList<Value> condValsDouble = new ArrayList<Value>();
	ArrayList<Value> condValsFloat = new ArrayList<Value>();
	ArrayList<Value> condValsChar = new ArrayList<Value>();
	ArrayList<Value> condValsLong = new ArrayList<Value>();
	ArrayList<Value> condValsByte = new ArrayList<Value>();
	ArrayList<Value> condValsOtherType = new ArrayList<Value>();		
//	ArrayList<Value> condValsType = new ArrayList<Value>();		
	ArrayList<Value> condValsTypeArray = new ArrayList<Value>();
    Unit lastIdentityStmt = null;
	
    @SuppressWarnings("unchecked")
	public Transformer(Body aBody)
    {
		String declaredClassName = "";
    	declaredClassName = aBody.getMethod().getDeclaringClass().toString();
		String declaredFunction = aBody.getMethod().toString();
//		G.v().out.println("start insertting at class: "+declaredClassName+"; function: "+declaredFunction);
    	G.v().out.println("start processing function: "+declaredFunction+";");
    	if(declaredClassName.contains("sgx_invoker")){
//			G.v().out.println("Encounters the sgxinvoker class ...skip...");
			return;
		}
    	PatchingChain<Unit> units = aBody.getUnits();//all statements
//    	G.v().out.println("units:"+units.toString());

        Local branchResultLocal = Jimple.v().newLocal("branchInvokeResult", BooleanType.v());
        Local sgxObjLocal = Jimple.v().newLocal("sgxInvoker", RefType.v("invoker.sgx_invoker"));//sgx object
        aBody.getLocals().add(branchResultLocal);  //1.insert local boolean branchInvokeResultLocal
        aBody.getLocals().add(sgxObjLocal); //2.insert local reftype invokerLocal
        
    	Unit currStmt = null;
    	Unit currProStmt = null;
    	Iterator<Unit> scanIt1 = units.snapshotIterator();
    	Iterator<Unit> scanIt2 = units.snapshotIterator();

        HashSet<Value> identifiedLocal = new HashSet<Value>();

        List<Local> localArray = new CopyOnWriteArrayList<Local>();//declaration valuables
        List<Local> tmpLocalArray = new CopyOnWriteArrayList<Local>();//declaration valuables
        Iterator<Local> locali = aBody.getLocals().iterator();
        while(locali.hasNext()){
        	Local tLocal = locali.next();
        	localArray.add(tLocal);
        	tmpLocalArray.add(tLocal);
        }		
    	while (scanIt1.hasNext()) {//stmt
    		currStmt = scanIt1.next();
    		if(currStmt instanceof IfStmt){//IfStmt
    			Value orgIfCondition = ((IfStmt) currStmt).getCondition();

    			Iterator<ValueBox> ubIt=orgIfCondition.getUseBoxes().iterator();
    			while(ubIt.hasNext()){
    				ValueBox vBox = (ValueBox) ubIt.next();
    				Value tValue = vBox.getValue();
    				String tValueTypeStr=tValue.getType().toString();
    				if(!(tValue instanceof Constant))
    					condVals.add(tValue);
//        			conditionValuesType.add(vBox.getValue().getType());
            	    localArray.removeAll(condVals);
	    			if(tValueTypeStr.equals("int")){
	    				condValsInt.add(tValue);
	    			}
	    			else if(tValueTypeStr.equals("double")){
	    				condValsDouble.add(tValue);
	    			}
	    			else if(tValueTypeStr.equals("float")){
	    				condValsFloat.add(tValue);
	    			}
	    			else if(tValueTypeStr.equals("char")){
	    				condValsChar.add(tValue);
	    			}
	    			else if(tValueTypeStr.equals("long")){
	    				condValsLong.add(tValue);
	    			}
	    			else if(tValueTypeStr.equals("byte")){
	    				condValsByte.add(tValue);
	    			}
	    			else {
	    				condValsOtherType.add(tValue);
	//    				condValTypeNum.add(0);
	    			}
    			}
//    	    	G.v().out.println("ValuesType in condition: "+conditionValuesType.toString()+";");
    	    	//Readin stmt transformation
    	    	//IfStmt transformation
    	    }
    		if((currStmt instanceof IdentityStmt)){
        	    G.v().out.println("IdentityStmt:"+currStmt.toString());
        		identifiedLocal.add(((IdentityStmt)currStmt).getLeftOp());
        	    G.v().out.println("identifiedLocal:"+identifiedLocal.toString());
        	}
    	}    	
    	G.v().out.println("Values in condition: "+condVals.toString()+";");
    	
    	condValsTypeArray.add(IntConstant.v(condValsInt.size()));
    	condValsTypeArray.add(IntConstant.v(condValsDouble.size()));
    	condValsTypeArray.add(IntConstant.v(condValsFloat.size()));
    	condValsTypeArray.add(IntConstant.v(condValsChar.size()));
    	condValsTypeArray.add(IntConstant.v(condValsLong.size()));
    	condValsTypeArray.add(IntConstant.v(condValsByte.size()));
    	condValsTypeArray.add(IntConstant.v(condValsOtherType.size()));
    	
//    	G.v().out.println("typeNumber of type: "+tArrayList+";");
//		G.v().out.println("current stmt is: ----------#"+currStmt+"#----------------");
    	//insertInitValueStmt(condValTypeNum);

        boolean isInitSgxInvoker = false;
//        boolean isInitValueInSgx = false;
        lastIdentityStmt = units.getFirst();
//        G.v().out.println("***++++++lastIdentityStmt is： "+lastIdentityStmt.toString()+";");

	    G.v().out.println("localArray:"+localArray.toString());
    	while(scanIt2.hasNext()){
    		currProStmt=scanIt2.next();
    		ArrayList<Value> currDefVals = new ArrayList<Value>();
    		ArrayList<Value> currUseVals = new ArrayList<Value>();

//    		G.v().out.println("current stmt is: ----------#"+currProStmt+"#----------------");
			Iterator<ValueBox> ubIt=currProStmt.getDefBoxes().iterator();
			while(ubIt.hasNext()){
				ValueBox vBox = ubIt.next();
				currDefVals.add(vBox.getValue());
			}    	    	    	
    	    currDefVals.retainAll(condVals);
//    	    G.v().out.println("currDefVals:"+currDefVals.toString());
    	    
    	    ubIt=currProStmt.getUseBoxes().iterator();
			while(ubIt.hasNext()){
				ValueBox vBox = ubIt.next();
				currUseVals.add(vBox.getValue());
			}    	    	   	
    	    currUseVals.retainAll(condVals);
//    	    G.v().out.println("currUseVals:"+currUseVals.toString()); 
    	    
//    		G.v().out.println("current stmt is: ----------#"+currProStmt+"#----------------");
//    		if(!currUseVals.isEmpty()){
//    			G.v().out.println("use: "+currProStmt.getUseBoxes()+";");
//        		G.v().out.println("current stmt type is: ----------#"+currProStmt.getClass()+"#----------------");
//    		}
    	    
			if((currProStmt instanceof IdentityStmt)){
        	    G.v().out.println("currProStmt is IdentityStmt:"+currProStmt.toString());
        		
        	    if(!currDefVals.isEmpty()){//update
        	    	if(!isInitSgxInvoker){// && isIdentityStmtOver
                	    initidentyLocal(localArray, units, currProStmt,identifiedLocal);//????why????
                		insertSgxInitStmt(aBody, sgxObjLocal, units, currProStmt, "invoker.sgx_invoker");
                		isInitSgxInvoker = true;
                	}
        	    	//DefValue transformation
//            	    G.v().out.println("***++++++currProStmt is:++++++++++"+currProStmt.toString());
        	    	lastIdentityStmt = replaceValueUpdateStmt(aBody, sgxObjLocal, units, localArray, currProStmt, currDefVals);
    	    	}
        	    else{
            	    lastIdentityStmt = currProStmt;//
        	    }
        	    continue;
        	}
        	//init sgx enclave
			if(!isInitSgxInvoker && (!condVals.isEmpty())){
        	    initidentyLocal(localArray, units, currProStmt,identifiedLocal);
        		insertSgxInitStmt(aBody, sgxObjLocal, units, currProStmt, "invoker.sgx_invoker");
        		isInitSgxInvoker = true;
        		
//        	    lastIdentityStmt = currProStmt;//
//        	    G.v().out.println("***++++++lastIdentityStmt is:++++++++++"+lastIdentityStmt.toString());
        	}
//			G.v().out.println("***++++++lastIdentityStmt is:++++++++++"+lastIdentityStmt.toString());
    		if((currProStmt instanceof AssignStmt)){
    	    	G.v().out.println("currProStmt is AssignStmt: "+currProStmt.toString()+";");
//        	    G.v().out.println("conditionValues:"+condVals.toString());
    			
    	    	if(!currDefVals.isEmpty()){//update
//            	    G.v().out.println("toBeHiddenDefValues:"+currDefVals.toString());
            	    //DefValue transformation
            	    replaceValueUpdateStmt(aBody, sgxObjLocal, units, localArray, currProStmt, currDefVals);
    	    	}
    	    	else if(!currUseVals.isEmpty()){//getLocal 
            	    replaceValueGetStmt(aBody, sgxObjLocal, units, localArray, currProStmt, currUseVals);
    	    	}
    		}

    		if(currProStmt instanceof IfStmt){
    	    	G.v().out.println("currProStmt is IfStmt: "+currProStmt.toString()+";");
//        	    G.v().out.println("conditionValues:"+condVals.toString());
        	    replaceBranchStmt(aBody, sgxObjLocal, branchResultLocal, units, localArray, currProStmt);
    		}

    		if(currProStmt instanceof ReturnStmt){
    	    	G.v().out.println("currProStmt is ReturnStmt: "+currProStmt.toString()+";");
//    	    	G.v().out.println("use: "+currUseVals+";");
    	    	
    	    	Local tmpReturnValue = Jimple.v().newLocal("tmpReturnValue"+Long.toString(counter), currUseVals.get(0).getType());
    			aBody.getLocals().add(tmpReturnValue);
    			localArray.add(tmpReturnValue);
    			G.v().out.println("tmpValue: "+tmpReturnValue.toString());    	        	
    			DefinitionStmt newAssignStmt = initAssignStmt(tmpReturnValue);
    			G.v().out.println("newAssignStmt is: "+newAssignStmt.toString());    	        	
    			G.v().out.println("lastIdentityStmt is: "+lastIdentityStmt.toString());
//    	        units.addFirst(newAssignStmt);
    			units.insertAfter(newAssignStmt, lastIdentityStmt);
    			
    			G.v().out.println("add newAssignStmt is: ++++++++++++++++++++++++++ "+newAssignStmt+"++++++++++++++++++++++");
    			
    			newAssignStmt = Jimple.v().newAssignStmt(tmpReturnValue,currUseVals.get(0));
    			G.v().out.println("newAssignStmt is: ++++++++++++++++++++++++++ "+newAssignStmt+"++++++++++++++++++++++");
    			units.insertBefore(newAssignStmt, currProStmt);
//    	        units.addFirst(newAssignStmt);
    			//
//    	    	rightOp = newAssignStmt.getRightOp();
//    	    	leftOpValue = newAssignStmt.getLeftOp();
    			replaceValueGetStmt(aBody, sgxObjLocal, units, localArray, newAssignStmt, currUseVals);
    			G.v().out.println("ReturnStmt to be replaced is: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
    			((ReturnStmt)currProStmt).setOp(tmpReturnValue);
    			G.v().out.println("new ReturnStmt is: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
    		}
    		if(currProStmt instanceof InvokeStmt){
    	    	G.v().out.println("currProStmt is InvokeStmt: "+currProStmt.toString()+";");
//    	    	G.v().out.println("use: "+currProStmt.getUseBoxes()+";");
//    	    	G.v().out.println("use: "+currUseVals+";");
//    	    	G.v().out.println("def: "+currDefVals+";");
    	    	for(Value invokeParaValue:currUseVals){
    	    		ArrayList<Value> oneValues = new ArrayList<>();
    	    		oneValues.add(invokeParaValue);
    	    		Local tmpInvoke = Jimple.v().newLocal("tmpInvoke"+Long.toString(counter), currUseVals.get(0).getType());
        			aBody.getLocals().add(tmpInvoke);
        			localArray.add(tmpInvoke);    			
        			G.v().out.println("tmpValue: "+tmpInvoke.toString());    	        	

        			DefinitionStmt newAssignStmt = initAssignStmt(tmpInvoke);
        			G.v().out.println("newAssignStmt is: "+newAssignStmt.toString());	        	
        			G.v().out.println("lastIdentityStmt is: "+lastIdentityStmt.toString());
//        	        units.addFirst(newAssignStmt);
        			units.insertAfter(newAssignStmt, lastIdentityStmt);
        			
        	        
        			newAssignStmt = Jimple.v().newAssignStmt(tmpInvoke,invokeParaValue);
        			units.insertBefore(newAssignStmt, currProStmt);
//        	    	rightOp = newAssignStmt.getRightOp();
//        	    	leftOpValue = newAssignStmt.getLeftOp();
        			replaceValueGetStmt(aBody, sgxObjLocal, units, localArray, newAssignStmt, oneValues);
        			
        			G.v().out.println("InvokeStmt to be replaced is: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");        			
        			Expr invokeExpr = ((InvokeStmt) currProStmt).getInvokeExpr();
        			int paraIndex = ((InvokeExpr)invokeExpr).getArgs().indexOf(invokeParaValue);
        			((InvokeExpr)invokeExpr).setArg(paraIndex, tmpInvoke);
        			G.v().out.println("new invokeExpr is: ++++++++++++++++++++++++++ "+invokeExpr+"++++++++++++++++++++++");
        			 ((InvokeStmt) currProStmt).setInvokeExpr(invokeExpr);
        			G.v().out.println("new InvokeStmt is: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
    	    	}
//    			
    		}
    	}
    	G.v().out.println("***++++++lastIdentityStmt is:++++++++++"+lastIdentityStmt.toString());
    }
   
    private void replaceValueGetStmt(
			Body aBody,
			Local sgxObjLocal,
			PatchingChain<Unit> units,
			List<Local> localArray,
			Unit currProStmt,
			ArrayList<Value> currUseVals) {
		// TODO Auto-generated method stub
    	Value rightOp = null;
    	Value leftOpValue = null;
    	if(currProStmt instanceof AssignStmt){
    		rightOp = ((AssignStmt)currProStmt).getRightOp();
    		leftOpValue = ((AssignStmt)currProStmt).getLeftOp();
    	}else if(currProStmt instanceof IdentityStmt){
   		 	rightOp = ((IdentityStmt)currProStmt).getRightOp();
   		 	leftOpValue = ((IdentityStmt)currProStmt).getLeftOp();
    	}else{
        	G.v().out.println(" currProStmt Type: "+currProStmt.getClass()+";");
    	}
		ArrayList<Value> variable = new ArrayList<Value>();//
		ArrayList<Value> cons = new ArrayList<Value>();//
		ArrayList<Value> values = new ArrayList<Value>();
		ArrayList<String> operator = new ArrayList<String>();
    	analyzeExp(rightOp, values, operator, cons, variable);//
    	
		boolean rightOpIsInvoke = false;
    	for(Value val:values){
    		if((val instanceof InvokeExpr)||(val instanceof ArrayRef))//ref????
    			rightOpIsInvoke = true;
    	}
    	if(rightOpIsInvoke){
        	G.v().out.println("the invokestmt rightop is: "+rightOp+";");
			for(Value invokeParaValue:currUseVals){
	    		ArrayList<Value> oneValueList = new ArrayList<>();
	    		oneValueList.add(invokeParaValue);
				Local tmpGetInvoke = Jimple.v().newLocal("tmpGetInvoke"+Long.toString(counter), leftOpValue.getType());
				aBody.getLocals().add(tmpGetInvoke);
				localArray.add(tmpGetInvoke);
    			G.v().out.println("tmpValue: "+tmpGetInvoke.toString());    	        	

				DefinitionStmt assignStmt = initAssignStmt(tmpGetInvoke);
    			G.v().out.println("newAssignStmt is: "+assignStmt.toString());
    	        G.v().out.println("lastIdentityStmt is: "+lastIdentityStmt.toString());
//    	        units.addFirst(assignStmt);
    			units.insertAfter(assignStmt, lastIdentityStmt);
				
				assignStmt = Jimple.v().newAssignStmt(tmpGetInvoke, invokeParaValue);
//				localArray.add(tmpGetInvoke);
				units.insertBefore(assignStmt, currProStmt);

    			replaceValueGetStmt(aBody, sgxObjLocal, units, localArray, assignStmt, oneValueList);
    			
    			G.v().out.println("InvokeExpr to be replaced is: ++++++++++++++++++++++++++ "+rightOp+"++++++++++++++++++++++");        			
    			int argIndex = ((InvokeExpr)rightOp).getArgs().indexOf(invokeParaValue);
    			((InvokeExpr)rightOp).setArg(argIndex, tmpGetInvoke);     			
    			G.v().out.println("new invokeExpr is: ++++++++++++++++++++++++++ "+rightOp+"++++++++++++++++++++++");
    			((AssignStmt)currProStmt).setRightOp(rightOp);
    		}
			G.v().out.println("new InvokeStmt is: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
			return;
		}
		int index=0;

		String left_index="-1";
		String right_index="-1";
		String return_index="-1";
		boolean setParam0 = false, setParam1 = false;
		String symbolString = null;
		int val_type=0;
		int pos_index=0;
		
    	for(Value local: values){
			G.v().out.println("values:********"+local+"*************");
		}			

		for(String local: operator){
			symbolString = local;
			G.v().out.println("operator:********"+local+"*************");
		}
		//insert stmt
		SootMethod toCall = Scene.v().getMethod
			      ("<invoker.sgx_invoker: void clear()>");
		Stmt newInvokeStmt = Jimple.v().newInvokeStmt(
				Jimple.v().newVirtualInvokeExpr
		           (sgxObjLocal, toCall.makeRef(), Arrays.asList()));
//		G.v().out.println("newInvokeStmt to insert is: ++++++++++++++++++++++++++ "+newInvokeStmt+"++++++++++++++++++++++");
//		G.v().out.println("start insert before currStmt: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
		units.insertBefore(newInvokeStmt, currProStmt);

		toCall = Scene.v().getMethod
			      ("<invoker.sgx_invoker: void setCounter(long)>");
		newInvokeStmt = Jimple.v().newInvokeStmt(
				Jimple.v().newVirtualInvokeExpr
		           (sgxObjLocal, toCall.makeRef(), Arrays.asList(LongConstant.v(counter))));
//		G.v().out.println("newInvokeStmt to insert is: ++++++++++++++++++++++++++ "+newInvokeStmt+"++++++++++++++++++++++");
//		G.v().out.println("start insert before currStmt: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
		units.insertBefore(newInvokeStmt, currProStmt);
		
		int returnTypeIndex = TypeIndex(leftOpValue);//return value type index
		pos_index = typeToList(returnTypeIndex).indexOf(leftOpValue);
		return_index = Integer.toString(returnTypeIndex*10+pos_index);
		
		int opTypeIndex = TypeIndex(values.get(0));
		indexwriter(Integer.toString(opTypeIndex));//tuple-0

		int list_size = 0;
		int MaxSize = (localArray.size()>N)?N:localArray.size();
		Random rand = new Random();
		
		if(values.size()==1){
			if(condVals.contains(values.get(0))){
				val_type = TypeIndex(values.get(0));//int or float
				pos_index = typeToList(val_type).indexOf(values.get(0));
				left_index = Integer.toString(val_type*10+pos_index);
			}else{
				for(Local loc:localArray){//将variable随机插入localarray
					if((loc.equals(values.get(0))) && (list_size >= MaxSize - 1)){
						int index_random = rand.nextInt(MaxSize - 1);
						localArray.remove(loc);
						localArray.add(index_random, loc);
					}
					list_size++;
				}
				for(Local loc:localArray){
					if(!isTypeCompatible(values.get(0).getType(), loc.getType()))
						continue;
					if((loc.equals(values.get(0)) || (rand.nextDouble()<=ratio)) && (index<N)){
						if(loc.equals(values.get(0))){
//							val_type = TypeIndex(values.get(0));//int or float
							left_index = Integer.toString(index);
							setParam0 = true;
						}						
						newInvokeStmt = prepareInsertStmt(loc, sgxObjLocal, "invoker.sgx_invoker");//只add类型相同的变量
						units.insertBefore(newInvokeStmt, currProStmt);
						index++;
					}
				}
				if(!setParam0){
					left_index = ((Value)(values.get(0))).getType().toString()+"_"+values.get(0);
					setParam0 = true;
				}
			}
		}else if(values.size()==2){
			if(condVals.contains(values.get(0))){
				val_type = TypeIndex(values.get(0));//int or float
				pos_index = typeToList(val_type).indexOf(values.get(0));
				left_index = Integer.toString(val_type*10+pos_index);
				setParam0 = true;
			}
			if(condVals.contains(values.get(1))){
				val_type = TypeIndex(values.get(1));//int or float
				pos_index = typeToList(val_type).indexOf(values.get(1));
				right_index = Integer.toString(val_type*10+pos_index);
				setParam1 = true;
			}
			if(!setParam0 && !setParam1){
				for(Value val: values){//variable-tobehidden;
					for(Local loc:localArray){//将variable随机插入localarray
						if((loc.equals(val)) && (list_size >= MaxSize - 1)){
							int index_random = rand.nextInt(MaxSize - 1);
							localArray.remove(loc);
							localArray.add(index_random, loc);
						}
						list_size++;
					}
				}
				for(Local loc:localArray){
					if(!isTypeCompatible(values.get(0).getType(), loc.getType()))
						continue;
//					if(isTypeCompatible(values.get(0).getType(), values.get(1).getType())){
					if((loc.equals(values.get(0))||loc.equals(values.get(1))||(rand.nextDouble()<=ratio)) && (index<N)){
						if(loc.equals(values.get(0))){
//							val_type = TypeIndex(values.get(0));//int or float
							left_index = Integer.toString(index);
							setParam0 = true;
						}
						if(loc.equals(values.get(1))){
//							val_type = TypeIndex(values.get(1));//int or float
							right_index = Integer.toString(index);
							setParam1 = true;
						}
						newInvokeStmt = prepareInsertStmt(loc, sgxObjLocal, "invoker.sgx_invoker");//只add类型相同的变量
						units.insertBefore(newInvokeStmt, currProStmt);
						index++;
					}
//					}	
				}
			}else if(!setParam0){
				for(Local loc:localArray){//将variable随机插入localarray
					if((loc.equals(values.get(0))) && (list_size >= MaxSize - 1)){
						int index_random = rand.nextInt(MaxSize - 1);
						localArray.remove(loc);
						localArray.add(index_random, loc);
					}
					list_size++;
				}
				for(Local loc:localArray){
					if(!isTypeCompatible(values.get(0).getType(), loc.getType()))
						continue;
					if((loc.equals(values.get(0)) || (rand.nextDouble()<=ratio)) && (index<N)){
						if(loc.equals(values.get(0))){
//							val_type = TypeIndex(values.get(0));//int or float
							left_index = Integer.toString(index);
							setParam0 = true;
						}
						newInvokeStmt = prepareInsertStmt(loc, sgxObjLocal, "invoker.sgx_invoker");//只add类型相同的变量
						units.insertBefore(newInvokeStmt, currProStmt);
						index++;
					}
				}
			}else if(!setParam1){
				for(Local loc:localArray){//将variable随机插入localarray
					if((loc.equals(values.get(1))) && (list_size >= MaxSize - 1)){
						int index_random = rand.nextInt(MaxSize - 1);
						localArray.remove(loc);
						localArray.add(index_random, loc);
					}
					list_size++;
				}
				for(Local loc:localArray){
					if(!isTypeCompatible(values.get(1).getType(), loc.getType()))
						continue;
					if((loc.equals(values.get(1)) || (rand.nextDouble()<=ratio)) && (index<N)){
						if(loc.equals(values.get(1))){
//							val_type = TypeIndex(values.get(1));//int or float
							right_index = Integer.toString(index);
							setParam1 = true;
						}
						
						newInvokeStmt = prepareInsertStmt(loc, sgxObjLocal, "invoker.sgx_invoker");//只add类型相同的变量
						units.insertBefore(newInvokeStmt, currProStmt);
						index++;
					}
				}
			}
			if(!setParam0){
				left_index = ((Value)(values.get(0))).getType().toString()+"_"+values.get(0);
				setParam0=true;
			}
			if(!setParam1){
				right_index = ((Value)(values.get(1))).getType().toString()+"_"+values.get(1);
				setParam1=true;
			}
		}else{
			G.v().out.println("********error: values size isnot 1 nor 2!********");
		}
		indexwriter(left_index);//tuple-1
		indexwriter(right_index);//tuple-2
		if(!operator.isEmpty()){
			if(symbolString.equals(" + "))
				indexwriter("1");
			else if(symbolString.equals(" - ") || symbolString.equals(" cmp "))
				indexwriter("2");
			else if(symbolString.equals(" * "))
				indexwriter("3");
			else if(symbolString.equals(" / "))
				indexwriter("4");
			else if(symbolString.equals(" % "))
				indexwriter("5");
			else 
				indexwriter("-1");
		}else{
			indexwriter("-1");
		}
		indexwriter(return_index);
		
		if(left_index == "-1")
			G.v().out.println("stmt has no first operand:********"+left_index+"*************");
		if(right_index == "-1")
			G.v().out.println("stmt has no second operand:********"+right_index+"*************");
		
		boolean LeftOpIsArrayRef=false;
    	if(leftOpValue instanceof ArrayRef)
    		LeftOpIsArrayRef = true;

//		G.v().out.println("start insert an un-invoke get");
//		G.v().out.println("leftOpvalue  is: "+leftOpValue+"*******");
		
    	toCall = Scene.v().getMethod (returnTypeIndexToCallFunc(returnTypeIndex));
		DefinitionStmt assignStmt=null;
		
		if(LeftOpIsArrayRef){
			Local tmpRef=Jimple.v().newLocal
					("tmpArrayRef"+String.valueOf(counter),leftOpValue.getType());				 
			aBody.getLocals().add(tmpRef);
			localArray.add(tmpRef);    			
			G.v().out.println("tmpValue: "+tmpRef.toString());    	        	

			assignStmt = initAssignStmt(tmpRef);
			G.v().out.println("newAssignStmt is: "+assignStmt.toString());	        			
			G.v().out.println("lastIdentityStmt is: "+lastIdentityStmt.toString());
//	        units.addFirst(assignStmt);
			units.insertAfter(assignStmt, lastIdentityStmt);
	        
//			localArray.add(tmpRef);
			
			assignStmt = Jimple.v().newAssignStmt(tmpRef,
					Jimple.v().newVirtualInvokeExpr
				          (sgxObjLocal, toCall.makeRef(), Arrays.asList()));
			((AssignStmt)currProStmt).setRightOp(tmpRef);
		}
		else{
			assignStmt = Jimple.v().newAssignStmt(leftOpValue,
					Jimple.v().newVirtualInvokeExpr
				          (sgxObjLocal, toCall.makeRef(), Arrays.asList()));
			units.insertBefore(assignStmt, currProStmt);
			units.remove(currProStmt);
		}
//		G.v().out.println("rightOpvalueOfAssignment is:++++++"+rightOp+"++++++++");
//		G.v().out.println("currProStmt units is: ++++ "+currProStmt.getUseBoxes()+"++++++++++++");
		counter++;
	}
    
    private String returnTypeIndexToCallFunc(int returnTypeIndex){
    	String funcString=new String();
    	switch (returnTypeIndex) {
		case 1:
			funcString =  "<invoker.sgx_invoker: int getIntValue()>";//getIntValue
			break;
		case 2:
			funcString = "<invoker.sgx_invoker: double getDoubleValue()>";
			break;
		case 3:
			funcString = "<invoker.sgx_invoker: char getCharValue()>";
			break;
		case 4:
			funcString = "<invoker.sgx_invoker: long getLongValue()>";
			break;
		case 5:
			funcString = "<invoker.sgx_invoker: byte getByteValue()>";
			break;
			
		default:
			break;
		}
    	return funcString;
    }
    
	@SuppressWarnings("unused")
	private void replaceBranchStmt(
			Body aBody,
			Local sgxObjLocal,
			Local branchResultLocal,
			PatchingChain<Unit> units,
			List<Local> localArray,
			Unit currProStmt) {
		
    	Value ifCondition = ((IfStmt)currProStmt).getCondition();
//    	G.v().out.println(" curr pro Unit: "+ifCondition+";");
		ArrayList<Value> variable = new ArrayList<Value>();//
		ArrayList<Value> values = new ArrayList<Value>();
    	ArrayList<Value> cons= new ArrayList<Value>();
		ArrayList<String> operator = new ArrayList<String>();

		analyzeExp(ifCondition, values, operator, cons, variable);
		
		int index=0;
		String left_index="-1";
		String right_index="-1";
		String return_index="-1";
		boolean setParam0 = false, setParam1 = false;
		String symbolString = null;
		int val_type=0;
		int pos_index=0;
		
//    	for(Value local: values){
//			G.v().out.println("values:********"+local+"*************");
//		}			
//		for(Value local: variable){
//			G.v().out.println("variable:********"+local+"*************");//parameter non-constant
//		}
//		for(Value local: cons){
//			G.v().out.println("cons:********"+local+"*************");//constant
//		}
		for(String local: operator){
			symbolString = local;
//			G.v().out.println("operator:********"+local+"*************");
		}
		SootMethod toCall = Scene.v().getMethod
			      ("<invoker.sgx_invoker: void clear()>");
		Stmt newInvokeStmt = Jimple.v().newInvokeStmt(
				Jimple.v().newVirtualInvokeExpr
		           (sgxObjLocal, toCall.makeRef(), Arrays.asList()));
//		G.v().out.println("newInvokeStmt to insert is: ++++++++++++++++++++++++++ "+newInvokeStmt+"++++++++++++++++++++++");
//		G.v().out.println("start insert before currStmt: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
		units.insertBefore(newInvokeStmt, currProStmt);
		
		toCall = Scene.v().getMethod
			      ("<invoker.sgx_invoker: void setCounter(long)>");
		newInvokeStmt = Jimple.v().newInvokeStmt(
				Jimple.v().newVirtualInvokeExpr
		           (sgxObjLocal, toCall.makeRef(), Arrays.asList(LongConstant.v(counter))));
//		G.v().out.println("newInvokeStmt to insert is: ++++++++++++++++++++++++++ "+newInvokeStmt+"++++++++++++++++++++++");
//		G.v().out.println("start insert before currStmt: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
		units.insertBefore(newInvokeStmt, currProStmt);
		
		int opTypeIndex = TypeIndex(values.get(0));//op value type index
		indexwriter(Integer.toString(opTypeIndex));//tuple-0

		int list_size = 0;
		int MaxSize = (localArray.size()>N)?N:localArray.size();
		Random rand = new Random();
		
		if(values.size()==1){
			G.v().out.println("there is only one para in condition values!!!++++++++++++++++++++++++++++++++");
		}else if(values.size()==2){
			if(condVals.contains(values.get(0))){
//				G.v().out.println("values0 is in condvals!");
				val_type = TypeIndex(values.get(0));//int or float
				pos_index = typeToList(val_type).indexOf(values.get(0));
				left_index = Integer.toString(val_type*10+pos_index);
				setParam0 = true;
			}
			if(condVals.contains(values.get(1))){
//				G.v().out.println("values1 is in condvals!");
				val_type = TypeIndex(values.get(1));//int or float
				pos_index = typeToList(val_type).indexOf(values.get(1));
				right_index = Integer.toString(val_type*10+pos_index);
				setParam1 = true;
			}
			if(!setParam0){
//				G.v().out.println("values0 is constant!");
				left_index = ((Value)(values.get(0))).getType().toString()+"_"+values.get(0);
				setParam0=true;
			}
			if(!setParam1){
				right_index = ((Value)(values.get(1))).getType().toString()+"_"+values.get(1);
				setParam1=true;
			}
		}else{
			G.v().out.println("********error: values size is not 1 nor 2!********");
		}
		if(!setParam0 || !setParam1)
			G.v().out.println("values are not in hidden list!!!!!********");
		
		indexwriter(left_index);//tuple-1
		indexwriter(right_index);//tuple-2
		if(!operator.isEmpty()){
			if(symbolString.equals(" == "))
				indexwriter("6");
			else if(symbolString.equals(" != ") || symbolString.equals(" cmp "))
				indexwriter("7");
			else if(symbolString.equals(" > "))
				indexwriter("8");
			else if(symbolString.equals(" < "))
				indexwriter("9");
			else if(symbolString.equals(" >= "))
				indexwriter("10");
			else if(symbolString.equals(" <= "))
				indexwriter("11");
			else 
				indexwriter("-1");
		}else{
			indexwriter("-1");
		}
		indexwriter(return_index);
		
		if(left_index == "-1")
			G.v().out.println("stmt has no first operand:********"+left_index+"*************");
		if(right_index == "-1")
			G.v().out.println("stmt has no second operand:********"+right_index+"*************");

		toCall = Scene.v().getMethod ("<invoker.sgx_invoker: boolean getBooleanValue()>");
//		toCall = Scene.v().getMethod (returnTypeIndexToCallFunc(1));//返回值为int类型
		DefinitionStmt assignStmt = Jimple.v().newAssignStmt(branchResultLocal,
				Jimple.v().newVirtualInvokeExpr
		           (sgxObjLocal, toCall.makeRef(), Arrays.asList()));//IntConstant.v(1)));//返回值为int类型
		units.insertBefore(assignStmt, currProStmt);
		((IfStmt)currProStmt).setCondition(new JEqExpr(branchResultLocal, IntConstant.v(1)));

//		G.v().out.println("assignStmt to insert is: ++++++++++++++++++++++++++ "+assignStmt+"++++++++++++++++++++++");
//		G.v().out.println("start insert before currStmt: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
		counter++;
    }
    
	@SuppressWarnings("unused")
    private Unit replaceValueUpdateStmt(
			Body aBody,
			Local sgxObjLocal,
			PatchingChain<Unit> units,
			List<Local> localArray,
			Unit currProStmt,
			ArrayList<Value> currDefVals) {
		// TODO Auto-generated method stub
    	Value rightOp = null;
    	Value leftOpValue = null;
    	if(currProStmt instanceof AssignStmt){
    		rightOp = ((AssignStmt)currProStmt).getRightOp();
    		leftOpValue = ((AssignStmt)currProStmt).getLeftOp();
//            G.v().out.println(" curr pro Unit: "+rightOp+";");
    	}else if(currProStmt instanceof IdentityStmt){
   		 	rightOp = ((IdentityStmt)currProStmt).getRightOp();
   		 	leftOpValue = ((IdentityStmt)currProStmt).getLeftOp();
//            G.v().out.println(" curr pro Unit: "+rightOp+";");
    	}else{

            G.v().out.println(" currProStmt Type: "+currProStmt.getClass()+";");
        }
//    	G.v().out.println(" curr pro Unit: "+rightOp+";");
    	
		ArrayList<Value> variable = new ArrayList<Value>();//
		ArrayList<Value> cons = new ArrayList<Value>();//
		ArrayList<Value> values = new ArrayList<Value>();
		ArrayList<String> operator = new ArrayList<String>();
		boolean RightOpIsInvoke = false;
		boolean isRightOpInCondVal = false;
    	analyzeExp(rightOp, values, operator, cons, variable);//
    	for(Value val:values){
    		if((val instanceof JLengthExpr)||(val instanceof InstanceInvokeExpr)||(val instanceof ArrayRef))
    			RightOpIsInvoke = true;
    		if(condVals.contains(val))
    			isRightOpInCondVal=true;
    	}
    	//to process stmt like x=invoke(temp1) or x=invoke(y)
		if(RightOpIsInvoke){
//			G.v().out.println("start insert an invoke tmp");
			Local tmpValue = Jimple.v().newLocal("tmpResult"+Long.toString(counter), leftOpValue.getType());
			aBody.getLocals().add(tmpValue);
			localArray.add(tmpValue);
			G.v().out.println("tmpValue: "+tmpValue.toString());    	        	

			DefinitionStmt assignStmt = initAssignStmt(tmpValue);
			G.v().out.println("newAssignStmt is: "+assignStmt.toString());	        			
			G.v().out.println("lastIdentityStmt is: "+lastIdentityStmt.toString());
//	        units.addFirst(assignStmt);
			units.insertAfter(assignStmt, lastIdentityStmt);
			
			assignStmt = Jimple.v().newAssignStmt(tmpValue,rightOp);
			if(isRightOpInCondVal){
//				rightOp = assignStmt.getRightOp();
//    	    	leftOpValue = assignStmt.getLeftOp();
				replaceValueGetStmt(aBody, sgxObjLocal, units, localArray, (Unit)assignStmt, values);
			}

			units.insertBefore(assignStmt, currProStmt);
//			G.v().out.println("newInvokeStmt to insert is: ++++++++++++++++++++++++++ "+assignStmt+"++++++++++++++++++++++");
//			G.v().out.println("start insert before currStmt: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
//			G.v().out.println("InvokeExpr class is: ++++++++++++++++++++++++++ "+rightOp.getClass()+"++++++++++++++++++++++");        			
			((AssignStmt)currProStmt).setRightOp(tmpValue);
//			G.v().out.println("InvokeExpr class is: ++++++++++++++++++++++++++ "+tmpValue.getClass()+"++++++++++++++++++++++");        			

			values.clear();
			operator.clear();
	    	analyzeExp(tmpValue, values, operator, cons, variable);//
		}

		int index=0;
		String left_index="-1";
		String right_index="-1";
		String return_index="-1";
		boolean setParam0 = false, setParam1 = false;
		String symbolString = null;
		int val_type=0;
		int pos_index=0;
		
//    	for(Value local: values){
//			G.v().out.println("values:********"+local+"*************");
//		}			
//		for(Value local: variable){
//			G.v().out.println("variable:********"+local+"*************");//parameter non-constant
//		}
//		for(Value local: cons){
//			G.v().out.println("cons:********"+local+"*************");//constant
//		}
		for(String local: operator){
			symbolString = local;
//			G.v().out.println("operator:********"+local+"*************");
		}

		SootMethod toCall = Scene.v().getMethod
			      ("<invoker.sgx_invoker: void clear()>");
		Stmt newInvokeStmt = Jimple.v().newInvokeStmt(
				Jimple.v().newVirtualInvokeExpr
		           (sgxObjLocal, toCall.makeRef(), Arrays.asList()));
//		G.v().out.println("newInvokeStmt to insert is: ++++++++++++++++++++++++++ "+newInvokeStmt+"++++++++++++++++++++++");
//		G.v().out.println("start insert before currStmt: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
		units.insertBefore(newInvokeStmt, currProStmt);

		toCall = Scene.v().getMethod("<invoker.sgx_invoker: void setCounter(long)>");
		newInvokeStmt = Jimple.v().newInvokeStmt(
				Jimple.v().newVirtualInvokeExpr
		           (sgxObjLocal, toCall.makeRef(), Arrays.asList(LongConstant.v(counter))));
//		G.v().out.println("newInvokeStmt to insert is: ++++++++++++++++++++++++++ "+newInvokeStmt+"++++++++++++++++++++++");
//		G.v().out.println("start insert before currStmt: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
		units.insertBefore(newInvokeStmt, currProStmt);
		
		int returnTypeIndex = TypeIndex(leftOpValue);//return value type index
		pos_index = typeToList(returnTypeIndex).indexOf(leftOpValue);
		return_index = Integer.toString(returnTypeIndex*10+pos_index);
		
		val_type = TypeIndex(values.get(0));
		pos_index = typeToList(val_type).indexOf(values.get(0));
		
		indexwriter(Integer.toString(val_type));//tuple-0: opOne's type

		int list_size = 0;
		int MaxSize = (localArray.size()>N)?N:localArray.size();
		Random rand = new Random();
		
		if(values.size()==1){
			if(condVals.contains(values.get(0))){
				val_type = TypeIndex(values.get(0));//int or float
				pos_index = typeToList(val_type).indexOf(values.get(0));
				left_index = Integer.toString(val_type*10+pos_index);//
			}else{
				for(Local loc:localArray){//将variable随机插入localarray
					if((loc.equals(values.get(0))) && (list_size >= MaxSize - 1)){
						int index_random = rand.nextInt(MaxSize - 1);
						localArray.remove(loc);
						localArray.add(index_random, loc);
					}
					list_size++;
				}
				for(Local loc:localArray){
					if(!isTypeCompatible(values.get(0).getType(), loc.getType()))
						continue;
					if((loc.equals(values.get(0)) || (rand.nextDouble()<=ratio)) && (index<N)){
						if(loc.equals(values.get(0))){
							//val_type = TypeIndex(values.get(0));//int or float
							//left_index = "1"+Integer.toString(val_type*10+index);//
							left_index = Integer.toString(index);//
							setParam0 = true;
						}						
						newInvokeStmt = prepareInsertStmt(loc, sgxObjLocal, "invoker.sgx_invoker");//只add类型相同的变量
						units.insertBefore(newInvokeStmt, currProStmt);
						index++;
					}
				}
				if(!setParam0){
					left_index = ((Value)(values.get(0))).getType().toString()+"_"+values.get(0);
					setParam0 = true;
				}
			}
		}else if(values.size()==2){
			if(condVals.contains(values.get(0))){
//				G.v().out.println("values0 is cond val"+"++++++++++++++"+values.get(0));
				val_type = TypeIndex(values.get(0));//int or float
				pos_index = typeToList(val_type).indexOf(values.get(0));
				left_index = Integer.toString(val_type*10+pos_index);
				setParam0 = true;
			}
			if(condVals.contains(values.get(1))){
//				G.v().out.println("values1 is cond val"+"++++++++++++++"+values.get(1));
				val_type = TypeIndex(values.get(1));//int or float
				pos_index = typeToList(val_type).indexOf(values.get(1));
				right_index = Integer.toString(val_type*10+pos_index);
				setParam1 = true;
			}
			if(!setParam0 && !setParam1){
				for(Value val: values){//variable-tobehidden;
					for(Local loc:localArray){//将variable随机插入localarray
						if((loc.equals(val)) && (list_size >= MaxSize - 1)){
							int index_random = rand.nextInt(MaxSize - 1);
							localArray.remove(loc);
							localArray.add(index_random, loc);
						}
						list_size++;
					}
				}
				for(Local loc:localArray){
					if(!isTypeCompatible(values.get(0).getType(), loc.getType()) )
						continue;
					if((loc.equals(values.get(0))||(loc.equals(values.get(1)))||(rand.nextDouble()<=ratio)) && (index<N)){	
						if(loc.equals(values.get(0))){
//							val_type = TypeIndex(values.get(0));//int or float
							left_index = Integer.toString(index);//val_type*10+index);//
							setParam0 = true;
						}
						if(loc.equals(values.get(1))){
//							val_type = TypeIndex(values.get(1));//int or float
							right_index = Integer.toString(index);//
							setParam1 = true;
						}
						newInvokeStmt = prepareInsertStmt(loc, sgxObjLocal, "invoker.sgx_invoker");//只add类型相同的变量
						units.insertBefore(newInvokeStmt, currProStmt);
						index++;
					}
//					}
				}
			}else if(!setParam0){
				for(Local loc:localArray){//将variable随机插入localarray
					if((loc.equals(values.get(0))) && (list_size >= MaxSize - 1)){
						int index_random = rand.nextInt(MaxSize - 1);
						localArray.remove(loc);
						localArray.add(index_random, loc);
					}
					list_size++;
				}
				for(Local loc:localArray){
					if(!isTypeCompatible(values.get(0).getType(), loc.getType()))
						continue;
					if((loc.equals(values.get(0)) || (rand.nextDouble()<=ratio)) && (index<N)){
						if(loc.equals(values.get(0))){
							val_type = TypeIndex(values.get(0));//int or float
							left_index = Integer.toString(index);//
							setParam0 = true;
						}
						newInvokeStmt = prepareInsertStmt(loc, sgxObjLocal, "invoker.sgx_invoker");//只add类型相同的变量
						units.insertBefore(newInvokeStmt, currProStmt);
						index++;
					}
				}
			}else if(!setParam1){
				for(Local loc:localArray){//将variable随机插入localarray
					if((loc.equals(values.get(1))) && (list_size >= MaxSize - 1)){
						int index_random = rand.nextInt(MaxSize - 1);
						localArray.remove(loc);
						localArray.add(index_random, loc);
					}
					list_size++;
				}
				for(Local loc:localArray){
					if(!isTypeCompatible(values.get(1).getType(), loc.getType()))
						continue;
					if((loc.equals(values.get(1)) || (rand.nextDouble()<=ratio)) && (index<N)){
						if(loc.equals(values.get(1))){
							val_type = TypeIndex(values.get(1));//int or float
							right_index = Integer.toString(index);//
							setParam1 = true;
						}
						newInvokeStmt = prepareInsertStmt(loc, sgxObjLocal, "invoker.sgx_invoker");//只add类型相同的变量
						units.insertBefore(newInvokeStmt, currProStmt);
						index++;
					}
				}
			}
			if(!setParam0){
				left_index = ((Value)(values.get(0))).getType().toString()+"_"+values.get(0);
				setParam0=true;
			}
			if(!setParam1){
				right_index = ((Value)(values.get(1))).getType().toString()+"_"+values.get(1);
				setParam1=true;
			}
		}else{
			G.v().out.println("********error: values size isnot 1 nor 2!********");
		}
		indexwriter(left_index);//tuple-1
		indexwriter(right_index);//tuple-2
		if(!operator.isEmpty()){
			if(symbolString.equals(" + "))
				indexwriter("1");
			else if(symbolString.equals(" - ") || symbolString.equals(" cmp "))
				indexwriter("2");
			else if(symbolString.equals(" * "))
				indexwriter("3");
			else if(symbolString.equals(" / "))
				indexwriter("4");
			else if(symbolString.equals(" % "))
				indexwriter("5");
			else 
				indexwriter("-1");
		}else{
			indexwriter("-1");
		}
		indexwriter(return_index);
		
		if(left_index == "-1")
			G.v().out.println("stmt has no first operand:********"+left_index+"*************");
		if(right_index == "-1")
			G.v().out.println("stmt has no second operand:********"+right_index+"*************");

		toCall = Scene.v().getMethod ("<invoker.sgx_invoker: void updateValueInEnclave()>");
		
		newInvokeStmt = Jimple.v().newInvokeStmt(
				Jimple.v().newVirtualInvokeExpr
		           (sgxObjLocal, toCall.makeRef(), Arrays.asList())); //IntConstant.v(returnTypeIndex)));
//		G.v().out.println("newInvokeStmt to insert is: ++++++++++++++++++++++++++ "+newInvokeStmt+"++++++++++++++++++++++");
//		G.v().out.println("start insert before currStmt: ++++++++++++++++++++++++++ "+currProStmt+"++++++++++++++++++++++");
		units.insertBefore(newInvokeStmt, currProStmt);
		units.remove(currProStmt);
		counter++;
		
		return newInvokeStmt;
	}
	
	private InvokeStmt prepareInsertStmt(Value loggedValue, Local loggerLocal, String className){
		Type vType = loggedValue.getType();
		SootMethod toCall = null;
		if(vType instanceof IntType || vType instanceof BooleanType || vType instanceof ShortType){
			 toCall = Scene.v().getMethod
				      ("<"+className+": void add(int)>");}
		else if(vType instanceof DoubleType){
			 toCall = Scene.v().getMethod
				      ("<"+className+": void add(double)>");}
		else if(vType instanceof FloatType){
			 toCall = Scene.v().getMethod
				      ("<"+className+": void add(float)>");}
		else if(vType instanceof soot.LongType){
			 toCall = Scene.v().getMethod
				      ("<"+className+": void add(long)>");}
		else if(vType instanceof CharType){
			 toCall = Scene.v().getMethod
				      ("<"+className+": void add(char)>");}
		else if(vType instanceof ByteType){
			 toCall = Scene.v().getMethod
				      ("<"+className+": void add(byte)>");}
		else{
			toCall = Scene.v().getMethod
				      ("<"+className+": void add(java.lang.Object)>");
		}
		InvokeStmt newInvokeStmt = Jimple.v().newInvokeStmt(
					Jimple.v().newVirtualInvokeExpr
			           (loggerLocal, toCall.makeRef(), Arrays.asList(loggedValue)));
			 return newInvokeStmt;
	}
	
	@SuppressWarnings("unused")
	private boolean isTypeCompatible(Type typeValue, Type localType){
		if((localType.toString().equals(typeValue.toString())) || ( typeValue instanceof RefLikeType && localType instanceof RefLikeType) )
			return true;
		else
			return false;
	}
	
	@SuppressWarnings("unused")
	private void analyzeExp(
			Value exp,//x>y
//			ArrayList<String> params, 
			ArrayList<Value> values, 
			ArrayList<String> operator, 
			ArrayList<Value> cons, 
			ArrayList<Value> variable) {
//		G.v().out.println("exp:********"+exp.toString()+"*************");

		if(exp instanceof JLengthExpr){
//			G.v().out.println("JLengthExpr exp********"+exp.toString()+"*************");
			values.add(exp);
//			isInvoke = true;
		}
		else if(exp instanceof InstanceInvokeExpr){
//			G.v().out.println("InvokeExpr:********"+exp.toString()+"*************");
			values.add(exp);
//			isInvoke = true;
		}
		else if(exp instanceof BinopExpr){//add add div mul or sub xor rem shl shr 
//			G.v().out.println("BinopExpr:********"+exp.toString()+"*************");
			analyzeExp(((BinopExpr)exp).getOp1(), values, operator, cons, variable);
			analyzeExp(((BinopExpr)exp).getOp2(), values, operator, cons, variable);	
			operator.add(((BinopExpr)exp).getSymbol());
		}
		else if(exp instanceof InstanceOfExpr){
//			G.v().out.println("InstanceOfExpr exp********"+exp.toString()+"*************");
		}
		else if(exp instanceof CastExpr){
//			G.v().out.println("CastExpr exp********"+exp.toString()+"*************");
			analyzeExp(((BinopExpr)exp).getOp1(), values, operator, cons, variable);
//			operator.add(((CastExpr)exp).get);
		}else{
			if(exp instanceof Constant){
//				G.v().out.println("Constant exp********"+exp.toString()+"*************");
				values.add(exp);
				cons.add(exp);
			}else if(exp instanceof Local){
//				G.v().out.println("Constant exp********"+exp.toString()+"*************");
				values.add(exp);
				// variable.add(((Local)exp));
			}else if(exp instanceof ArrayRef){
//				G.v().out.println("ArrayRef:********"+exp.toString()+"*************");
				values.add(exp);
//				isInvoke = true;
			}else {
//				G.v().out.println("other type:********"+exp.getClass()+"*************");
				values.add(exp);
				// isInvoke = true;
			}
		}		
	}
	
	@SuppressWarnings("unused")
	private int TypeIndex(Value tValue){
		int typeIndex = -1;
		String typeStr = tValue.getType().toString();
		if(typeStr.equals("int"))
			typeIndex = 1;
		else if(typeStr.equals("double"))
			typeIndex = 2;
		else if(typeStr.equals("float"))
			typeIndex = 3;
		else if(typeStr.equals("char"))
			typeIndex = 4;
		else if(typeStr.equals("long"))
			typeIndex = 5;
		else if(typeStr.equals("byte"))
			typeIndex = 6;
		else //TODO: contains type object , boolean , short
			typeIndex = -1;
		return typeIndex;
	}
	
	private ArrayList<Value> typeToList(int typeIndex){
		if(typeIndex == 1)
			return condValsInt;
		else if(typeIndex == 2)
			return condValsDouble;
		else if(typeIndex == 3)
			return condValsFloat;
		else if(typeIndex == 4)
			return condValsChar;
		else if(typeIndex == 5)
			return condValsLong;
		else if(typeIndex == 6)
			return condValsByte;
		else //TODO: contains type object , boolean , short
			return condValsOtherType;
	}
    
//	@SuppressWarnings("unused")
//	private void insertValueInitStmt(
//			Body aBody,
//			Local sgxObjLocal,
//			PatchingChain<Unit> units, 
//			Unit currStmt, 
//			ArrayList<Value> condValsTypeArray){		
///*		SootMethod toCallMethod = Scene.v().getMethod("<Invoker.sgx_invoker: Void clear()>");
//		Stmt newInvokeStmt = Jimple.v().newInvokeStmt(
//				Jimple.v().newVirtualInvokeExpr(sgxObjLocal, toCallMethod.makeRef(), Arrays.asList()));
//		units.insertBefore(newInvokeStmt, currStmt);
//		
//		toCallMethod = Scene.v().getMethod
//			      ("<invoker.sgx_invoker: void setCounter(long)>");
//		newInvokeStmt = Jimple.v().newInvokeStmt(
//				Jimple.v().newVirtualInvokeExpr(sgxObjLocal, toCallMethod.makeRef(), Arrays.asList(LongConstant.v(counter))));
//		units.insertBefore(newInvokeStmt, currStmt);*/
//		
//		SootMethod toCallMethod = Scene.v().getMethod("<invoker.sgx_invoker: boolean initValueInEnclave(int[])>");//(int[] intArray, int length)
////		Local valueOfType = Jimple.v().newLocal("valueOfType", ArrayType.v(RefType.v("java.lang.Integer"), 1));
//		
////		Local arg = Jimple.v().newLocal("valueType", ArrayType.v(RefType.v("java.lang.Integer"), 1));
////		aBody.getLocals().add(arg);
////		G.v().out.println("arg is: ----------#"+arg.getType()+"#----------------");
//		
////		Stmt newAssignStmt = Jimple.v().newAssignStmt(arg, tArrayList);
//				
//				//Jimple.v().newArrayRef(valueOfType, 0);
//				//Jimple.v().newArrayRef(base, index)
//				//newParameterRef(ArrayType.v(RefType.v("java.lang.Integer"), 1), 0));
//			      //Jimple.v().newParameterRef(ArrayType.v(RefType.v("java.lang.String"), 1), 0));
////		G.v().out.println("newIdentityStmt is: ----------#"+newAssignStmt+"#----------------");
////		units.insertBefore(newAssignStmt, currStmt);	
//		
//		InvokeStmt newInvokeStmt = Jimple.v().newInvokeStmt(
//				Jimple.v().newVirtualInvokeExpr(sgxObjLocal, toCallMethod.makeRef(), condValsTypeArray));
//		G.v().out.println("newInvokeStmt is: ----------#"+newInvokeStmt+"#----------------");
//		units.insertBefore(newInvokeStmt, currStmt);	
//	}
	
	@SuppressWarnings("unused")
	private void insertSgxInitStmt(
			Body aBody,
			Local sgxObjLocal, //sgxObjLocal
			PatchingChain<Unit> units,
			Unit currStmt, //first stmt
			String className) //Object NewArrayExpr) {
			{
        ///"sgxInvoker = new invoker.sgx_invoker;"
		soot.jimple.NewExpr sootNew = soot.jimple.Jimple.v().newNewExpr(RefType.v(className));
	    soot.jimple.AssignStmt stmt = soot.jimple.Jimple.v().newAssignStmt(sgxObjLocal, sootNew);
		units.insertBefore(stmt, currStmt);
		
        //"specialinvoke sgxInvoker.<invoker.sgx_invoker: void <init>()>();"
		SpecialInvokeExpr newTrans = Jimple.v().newSpecialInvokeExpr(sgxObjLocal,
				Scene.v().getMethod("<invoker.sgx_invoker: void <init>()>").makeRef(),
				Arrays.asList());
		soot.jimple.Stmt invokeStmt = soot.jimple.Jimple.v().newInvokeStmt(newTrans);
		units.insertBefore(invokeStmt, currStmt);

        //"virtualinvoke sgxInvoker.<invoker.sgx_invoker: boolean initenclave()>();"
		SootMethod toCall = Scene.v().getMethod
			      ("<invoker.sgx_invoker: boolean initenclave()>");
		Stmt newInvokeStmt = Jimple.v().newInvokeStmt(
				Jimple.v().newVirtualInvokeExpr
		           (sgxObjLocal, toCall.makeRef(), Arrays.asList()));
		units.insertBefore(newInvokeStmt, currStmt);

        LocalGenerator localGenerator = new LocalGenerator(aBody);
        Local local1 = localGenerator.generateLocal(soot.ArrayType.v(IntType.v(), 1));
        NewArrayExpr newArrayExpr = Jimple.v().newNewArrayExpr(IntType.v(), IntConstant.v(condValsTypeArray.size()));
        AssignStmt assignStmt2 = Jimple.v().newAssignStmt(local1, newArrayExpr);    		
        units.insertBefore(assignStmt2, currStmt);

        int i=0;
        for(Value num:condValsTypeArray){
            ArrayRef arrayRef = Jimple.v().newArrayRef(local1, IntConstant.v(i++));
            AssignStmt assignStmt = Jimple.v().newAssignStmt(arrayRef, num);
    		units.insertBefore(assignStmt, currStmt);
        }
        
		toCall = Scene.v().getMethod
				("<invoker.sgx_invoker: boolean initValueInEnclave(int[])>");

		VirtualInvokeExpr initValueExpr = Jimple.v().newVirtualInvokeExpr
				(sgxObjLocal, toCall.makeRef(), 
						Arrays.asList(local1));
		Stmt newInitInvokeStmt = Jimple.v().newInvokeStmt(initValueExpr);
//		G.v().out.println("newInvokeStmt is: ----------#"+newInitInvokeStmt+"#----------------");
		units.insertBefore(newInitInvokeStmt, currStmt);
	}

	private AssignStmt initAssignStmt(Local l){
		Type t = l.getType();
		soot.jimple.AssignStmt stmt = null;
		if(t instanceof RefLikeType){
			stmt = soot.jimple.Jimple.v().newAssignStmt(l, NullConstant.v());
		}
		else if(t instanceof IntType){
			stmt = soot.jimple.Jimple.v().newAssignStmt(l, IntConstant.v(0));
		}
		else if(t instanceof DoubleType){
			stmt = soot.jimple.Jimple.v().newAssignStmt(l, DoubleConstant.v(0));
		}
		else if(t instanceof FloatType){
			stmt = soot.jimple.Jimple.v().newAssignStmt(l, FloatConstant.v(0));
		}
		else if(t instanceof soot.LongType){
			stmt = soot.jimple.Jimple.v().newAssignStmt(l, LongConstant.v(0));
		}
		else if(t instanceof BooleanType){
			stmt = soot.jimple.Jimple.v().newAssignStmt(l, IntConstant.v(0));
		}
		else if(t instanceof ShortType){
			stmt = soot.jimple.Jimple.v().newAssignStmt(l, IntConstant.v(0));
		}
		else if(t instanceof CharType){
			stmt = soot.jimple.Jimple.v().newAssignStmt(l, IntConstant.v(0));
		}
		else if(t instanceof ByteType){
			stmt = soot.jimple.Jimple.v().newAssignStmt(l, IntConstant.v(0));
		}
		return stmt;
	}
	private void initidentyLocal(
			List<Local> localList,
			PatchingChain<Unit> units, 
			Unit currStmt, 
			HashSet<Value> identifiedLocal){
		
		soot.jimple.AssignStmt stmt = null;
		for(Local l: localList){
//			G.v().out.println("++++++Local is:++++++++++"+l.toString());
			if(identifiedLocal.contains(l)){			
				G.v().out.println(l.toString()+": has been inited in original javafile!");
					continue;
			}
			stmt = initAssignStmt(l);
			G.v().out.println(l.toString()+": init stmt will be inserted into jimplefile!");
			units.insertBefore(stmt, currStmt);
		}
	}
}

