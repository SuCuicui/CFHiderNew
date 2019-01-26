package pegasus;

import java.io.IOException;
import java.util.ArrayList;


public class sgx_invoker{
//export LD_LIBRARY_PATH=/home/xidian/Development/SGX-project/source-code/NaiveTest/bin
	//public native int varargsMethod( int... no,float... fl,double... dl,long... lo );
  	public static final int N=30;
	public static native int print_ms();
	public static native int init();
	public static native int destroy();
	public static native int commit(long counter, int[] intArray, int intTail, double[] doubleArray, int doubleTail,float[] floatArray, int floatTail, long[] longArray, int longTail, char[] charArray,int charTail, byte[] byteArray,int byteTail);
  //  static {System.loadLibrary("/home/xidian/Development/SGX-project/source-code/NaiveTest/src/edu/xidian/libSGX.so");}  
   
	static {
		try{
			//System.out.println("invoker"+System.getProperty("java.library.path"));
			System.loadLibrary("SGX");
		}
		catch (Exception e) {
			// TODO Auto-generated catch block
			//System.out.println("invoker"+System.getProperty("java.library.path"));
			e.printStackTrace();
		}
	}  

    //TODO: may potentially reduce the performance, can be improved later
	//ArrayList<Object> objects = null;
	Object[] objArray = new Object[N];
	int objTail= 0;

	int[] intArray = new int[N];
	int intTail = 0;
	
	double[] doubleArray = new double[N];
	int doubleTail = 0;
	
	float[] floatArray = new float[N];
	int floatTail = 0;
	
	long[] longArray = new long[N];
	int longTail = 0;
	
	char[] charArray = new char[N];
	int charTail = 0;
	
	byte[] byteArray = new byte[N];
	int byteTail = 0;
	
	long counter = -1;
	
	public void sgx_invoker(){
		//objects = new ArrayList<Object>();
	}
	


	public void clear(){
		intTail = 0;
		doubleTail = 0;
		floatTail = 0;
		longTail = 0;
		charTail = 0;
		byteTail = 0;
		//objects.clear();
	}
	
	public void add(Object o){
		if(o==null)
			intArray[intTail++]=0;
		else
			intArray[intTail++]=o.hashCode();
		//objArray[objTail++] = o;
	}

	public void add(int o){
		intArray[intTail++] = o;
	}
	
	public void add(double o){
		doubleArray[doubleTail++] = o;
	}
	public void add(float o){
		floatArray[floatTail++] = o;
	}
	
	public void add(long o){
		longArray[longTail++] = o;
	}
	public void add(char o){
		charArray[charTail++] = o;
	}
	public void add(byte o){
		byteArray[byteTail++] = o;
	}
	public void setCounter(long counter){
		this.counter = counter;
	}
	
	public boolean initenclave(){
		if(1==init())
		return true;
		else
		return false;
	}
	
	public boolean closeenclave(){
		if(0==destroy())
		return true;
		else
		return false;
	}

	public boolean call(){ 
	
		int ret = commit(counter,intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);

		
		if(ret == 1)
			return true;
		else if(ret == 0)
			return false;
		else{
			System.out.println("ret:"+ret);
			System.out.println("error");
			System.out.println("ret");
			System.exit(1);
		}
		return false;
	
	}
}
