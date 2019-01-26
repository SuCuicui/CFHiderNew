package pegasus;

import java.util.ArrayList;
import java.util.HashMap;

import javax.management.ImmutableDescriptor;

public class sgx_invoker{
//export LD_LIBRARY_PATH=/home/xidian/Development/SGX-project/source-code/NaiveTest/bin
	//public native int varargsMethod( int... no,float... fl,double... dl,long... lo );
  public static final int N=100;
	public native int init();
	public native int destroy();
	public native int commit(long counter, int[] intArray, int intTail, double[] doubleArray, int doubleTail,float[] floatArray, int floatTail, long[] longArray, int longTail, char[] charArray,int charTail, byte[] byteArray,int byteTail);
  //  static {System.loadLibrary("/home/xidian/Development/SGX-project/source-code/NaiveTest/src/edu/xidian/libSGX.so");}  
   static {System.loadLibrary("SGX");}  
   static final int cacheSize = 100;
   static HashMap<Integer, Integer> CFCache = new HashMap<Integer, Integer>();
   static HashMap<Integer, Long> cacheClock = new HashMap<Integer, Long>();
   static HashMap<Integer, Long> cacheClockHour = new HashMap<Integer, Long>();

   static long clock = 0;
   static long clockHour = 0;
   static final long  expire = 100000;
   //static final long clockSize = 10000;

    //TODO: may potentially reduce the performance, can be improved later
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
	}
	
	private int check_cache(int c_hash){
		if(clock == Long.MAX_VALUE){
			clock=0;
		clockHour++;
		}else{
			clock++;
		}
		Integer hash = new Integer(c_hash);
		if(CFCache.containsKey(hash)){
			cacheClock.put(hash, new Long(clock));
			return CFCache.get(hash).intValue();
		}else{
			return -1;
		}
	}
	
	private void updateCache(int c_hash, int ret) {
		Integer hash = new Integer(c_hash);
		Integer returnVal = new Integer(ret);

		if(CFCache.size()<cacheSize){
			CFCache.put(hash, new Integer(ret));
			cacheClock.put(hash , new Long(clock));
			cacheClockHour.put(hash, new Long(clockHour));
		}else{
			Integer clearInt = getExpireCache();
			if(clearInt!=null)
				CFCache.remove(clearInt);
			CFCache.put(hash, returnVal);
			cacheClock.put(hash , new Long(clock));
			cacheClockHour.put(hash, new Long(clockHour));					
			}
		}
		
	private Integer getExpireCache() {
		for(Integer i: CFCache.keySet()){
			if(computeExpire(cacheClock.get(i), cacheClockHour.get(i),expire)){
				return i;
			}
		}
		return null;
	}
	
	private boolean computeExpire(Long hashClock, Long hashHour, long expire) {
		if((clockHour==hashHour)&&(clock-hashClock.longValue()<expire))
			return false;
		else if((clockHour-hashHour)==1 && (Long.MAX_VALUE-(hashClock.longValue()-clock)<expire))
			return false;
		else return true;
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


	
	public boolean call(){ 
		
		String cache=""+counter;
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
		int c_hash=cache.hashCode();
		
		int hit=check_cache(c_hash);
		
		int ret = -1;
		if(hit==-1){
			 ret = commit(counter,intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
			//int ret = 	commit(0,new int[]{1,1,1,4,5,6,7,8,9,0}, N,new double[]{0.0},0,new float[]{0},0,new long[]{0},0,new char[]{0},0);
			updateCache(c_hash, ret);
		}
		else ret = hit;
		
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
		
	//return commit(counter,intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail);

	
	}
//public static void main(String[] args)
//{
//	 sgx_invoker invo= new sgx_invoker();
//    invo.commit(0,new int[]{1,1,1,4,5,6,7,8,9,0},N,new double[]{0.0},0,new float[]{0},0,new long[]{0},0,new char[]{0},0,new byte[]{0},0);


//};

	
}
