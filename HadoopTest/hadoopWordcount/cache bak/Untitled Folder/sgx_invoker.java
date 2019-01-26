package pegasus;

import java.util.ArrayList;

import javax.management.ImmutableDescriptor;

public class sgx_invoker{
//export LD_LIBRARY_PATH=/home/xidian/Development/SGX-project/source-code/NaiveTest/bin
	//public native int varargsMethod( int... no,float... fl,double... dl,long... lo );
  public static final int N=100;
	static final int Cache_len=16;
	static final int Max_life=20;
	public int empty_flag=1;
	public native int init();
	public native int destroy();
	public native int commit(long counter, int[] intArray, int intTail, double[] doubleArray, int doubleTail,float[] floatArray, int floatTail, long[] longArray, int longTail, char[] charArray,int charTail, byte[] byteArray,int byteTail);
  //  static {System.loadLibrary("/home/xidian/Development/SGX-project/source-code/NaiveTest/src/edu/xidian/libSGX.so");}  
   static {System.loadLibrary("SGX");}  

    //TODO: may potentially reduce the performance, can be improved later
	
	int[] hash_cache=new int[Cache_len];
	int[] cache_life=new int[Cache_len];
	int[] cache_result=new int[Cache_len];
	//ArrayList<Object> objects = null;
	Object[] objArray = new Object[100000];
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
	
	public sgx_invoker(){
		//objects = new ArrayList<Object>();
		for(int i=0;i<Cache_len;i++){
			hash_cache[i]=0;
			cache_life[i]=0;
			cache_result[i]=0;
		}
	}
	
	public void clear(){
		intTail = 0;
		doubleTail = 0;
		floatTail = 0;
		longTail = 0;
		charTail = 0;
		byteTail = 0;
		objTail=0;
		//objects.clear();
	}
	public void add(){
		//System.out.println("null input");
	}
	
	public void add(Object o){
		if(o==null)
			intArray[intTail++] = 0;
		else
		    intArray[intTail++] = o.hashCode();
//		if(o != null){
//			
//			//o="empty object";
//			//System.out.println("object has been updated");
//			//}else{
//			objArray[objTail] = o;
//			System.out.println("the object value is "+o);}
//			else {
//				//o = new sgx_invoker(); 
//				System.out.println(" null object ");};
			
	}
	
	public void add(int o){
		//if(intTail>100){
		//System.out.println("too long");}
		
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
	//sgx_invoker invo2= new sgx_invoker();
	private int cache_lru(int p,int cache,int result){
		if(p<Cache_len && p>=0){//hit
			cache_life[p]=Max_life;
			empty_flag=0;
			for(int i=0;i<Cache_len;i++){
				cache_life[i]--;
				if(cache_life[i]<=0){
					empty_flag=1;
				}
			}			
		}
		if(p==-1){//insert
			int add_flag=0;
			empty_flag=0;
			//System.out.println("insert");
			for(int i=0;i<Cache_len;i++){
				cache_life[i]--;
				
				if(cache_life[i]<=0){
					if(add_flag==0){
						cache_result[i]=result;
						hash_cache[i]=cache;
						cache_life[i]=Max_life;
						add_flag=1;
						//System.out.println("add");
					}else{
						empty_flag=1;
					}
				}
			}
		}
	return 0;
	}
	private int check_cache(int hash){
		int hit=0;
		int i;
		for(i=0;i<Cache_len;i++){
			if(hash_cache[i]==hash){
				hit=1;
				break;
			}
		}
		cache_lru(i,0,0);
		if(i<Cache_len){
			return i;
		}else{
			return -1;
		}
	}
	public boolean call(){ 
		//int[] intArray; double[] doubleArray; float[] floatArray; long[] longArray;
//		ArrayList<Integer> intArray = new ArrayList<Integer>();
//		ArrayList<Double> doubleArray = new ArrayList<Double>();
//		ArrayList<Float> floatArray = new ArrayList<Float>();
//		ArrayList<Long> longArray = new ArrayList<Long>();
//		ArrayList<String> charArray = new ArrayList<String>();
//		for(Object obj: objects){
//			if(obj instanceof Integer)
//				intArray.add((Integer)obj);
//				//c_call(((Integer)obj).intValue());
//			if(obj instanceof Double)
//				c_call(((Double)obj).doubleValue());
//			if(obj instanceof Float)
//				c_call(((Float)obj).floatValue());
//			if(obj instanceof Long)
//				c_call(((Long)obj).longValue());
//			String srt="abc";
//			//...
//		}
//		//int, double, float, boolean, long
////		objects.add(new Integer(x));
////		objects.add(args);
////		objects.add("S2");
////		objects.add(2.5);
//		//<invokeSGX(int, int int, double)>
//		//Object[] objectArray = (Object[])objects.toArray();
//		int[] intPrimArray = new int[intArray.size()];
//		for(int i = 0; i< intA public static void main(String[] args)
//		rray.size();i++){
//		    intPrimArray[i] = intArray.get(i);
//		}
	/*	String cache=""+counter;
		for(int loop=0;loop<intTail;loop++){
			cache = cache + intArray[loop];
		}
		for(int loop=0;loop<doubleTail;loop++){
			cache = cache + doubleArray[loop];
		}
		for(int loop=0;loop<floatTail;loop++){
			cache = cache + floatArray[loop];
		}
		for(int loop=0;loop<longTail;loop++){
			cache = cache + longArray[loop];
		}
		for(int loop=0;loop<charTail;loop++){
			cache = cache + charArray[loop];
		}
		for(int loop=0;loop<byteTail;loop++){
			cache = cache + byteArray[loop];
		}
                */
		//int c_hash=cache.hashCode();
		//int hit=check_cache(c_hash);
		//System.out.println("cache"+c_hash);
		//if(hit==-1){//falure
		//System.out.println("not hit");

        if(counter==2||counter==1||counter==0)
		{
		       return(intArray[0]==0);
		}


		int ret = commit(counter,intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
		//int ret = 	commit(0,new int[]{1,1,1,4,5,6,7,8,9,0}, N,new double[]{0.0},0,new float[]{0},0,new long[]{0},0,new char[]{0},0);
		/*
		if(empty_flag==1){
			cache_lru(-1,c_hash,ret);
		}else{
			for(int i=0;i<Cache_len;i++){
			cache_life[i]--;
			}
		}
*/
		if(ret == 1)
			return true;
		else if(ret == 0)
			return false;
		else{
			
			//throw new Exception("error");
			System.out.println("ret:"+ret);
			System.out.println("error");
			System.out.println("ret");
			System.exit(1);
		}
		return false;
/*
		}else if(hit<Cache_len){//hit
		//System.out.println("hit");
		if(cache_result[hit] == 1)
			return true;
		else if(cache_result[hit] == 0)
			return false;	
		}
		
		*/
	//return commit(counter,intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail);

	
	}
//public static void main(String[] args)
//{
//	 sgx_invoker invo= new sgx_invoker();
//    invo.commit(0,new int[]{1,1,1,4,5,6,7,8,9,0},N,new double[]{0.0},0,new float[]{0},0,new long[]{0},0,new char[]{0},0,new byte[]{0},0);

//};

	
}
