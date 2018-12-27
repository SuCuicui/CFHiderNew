package invoker;

import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.HashMap;

public class sgx_invoker{
	//public native int varargsMethod( int... no,float... fl,double... dl,long... lo );
  	public static final int N=20;
	public static native int print_ms();
	public static native int init();
	public static native int destroy();
	public static native int commitInt(long counter, int[] intArray, int intTail, double[] doubleArray, int doubleTail,float[] floatArray, int floatTail, long[] longArray, int longTail, char[] charArray,int charTail, byte[] byteArray,int byteTail);
	public static native float commitFloat(long counter, int[] intArray, int intTail, double[] doubleArray, int doubleTail,float[] floatArray, int floatTail, long[] longArray, int longTail, char[] charArray,int charTail, byte[] byteArray,int byteTail);
	public static native double commitDouble(long counter, int[] intArray, int intTail, double[] doubleArray, int doubleTail,float[] floatArray, int floatTail, long[] longArray, int longTail, char[] charArray,int charTail, byte[] byteArray,int byteTail);
	public static native char commitChar(long counter, int[] intArray, int intTail, double[] doubleArray, int doubleTail,float[] floatArray, int floatTail, long[] longArray, int longTail, char[] charArray,int charTail, byte[] byteArray,int byteTail);
	public static native byte commitByte(long counter, int[] intArray, int intTail, double[] doubleArray, int doubleTail,float[] floatArray, int floatTail, long[] longArray, int longTail, char[] charArray,int charTail, byte[] byteArray,int byteTail);
	public static native int commitBranch(long counter, int[] intArray, int intTail, double[] doubleArray, int doubleTail,float[] floatArray, int floatTail, long[] longArray, int longTail, char[] charArray,int charTail, byte[] byteArray,int byteTail);
	public static native int commitUpdate(long counter, int[] intArray, int intTail, double[] doubleArray, int doubleTail,float[] floatArray, int floatTail, long[] longArray, int longTail, char[] charArray,int charTail, byte[] byteArray,int byteTail);

	public static native int initValue(int[] intArray2, int length);
	
	static {
		try{
			System.out.println("invoker"+System.getProperty("java.library.path"));
			System.loadLibrary("SGX");
		}
		catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println("invoker"+System.getProperty("java.library.path"));
			e.printStackTrace();
		}
	}  

	//maximum cache size is determined by the MAX(cacheSize, expire). 
	//if no hash has expired, then the cache size can be exceeded by inserting more hash into CFCache.
	// HOwever, since each incoming call will increment the clock, the total number of entries in the CFCache 
	// will not exceed the expire. 
   static final int cacheSize = 100;
   static HashMap<Integer, String> CFCache = new HashMap<Integer, String>();
   static HashMap<Integer, Long> cacheClock = new HashMap<Integer, Long>();
   static HashMap<Integer, Long> cacheClockHour = new HashMap<Integer, Long>();

   static long clock = 0;
   static long clockHour = 0;
   static final long  expire = 1000;
   //static final long clockSize = 10000;

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
	

	static long request = 1;
	static long hitNum = 0;
	
	private String check_cache(int c_hash){
		if(clock%10000000==0){
			System.out.println("############################ Cache Hit ##########################\n");
			System.out.println(sgx_invoker.getHitRatio());		
		}
		request++;
		if(clock == Long.MAX_VALUE){
			clock=0;
			clockHour++;
			request = 1;
			hitNum = 0;
		}else{
			clock++;
		}
		Integer hash = new Integer(c_hash);
		if(CFCache.containsKey(hash)){
			hitNum++;
			cacheClock.put(hash, new Long(clock));
			return CFCache.get(hash);
		}else{
//			return "-1";
			return null;
		}
	}
	
	public static String getHitRatio(){
		return hitNum+"||"+request;
	}
	
	private void updateCache(int c_hash, String ret) {
		Integer hash = new Integer(c_hash);

		if(CFCache.size()<cacheSize){
			CFCache.put(hash, ret);
			cacheClock.put(hash , new Long(clock));
			cacheClockHour.put(hash, new Long(clockHour));
		}else{
			CFCache.put(hash, ret);
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

	public boolean initValueInEnclave(int[] intArray){
		if(1==initValue(intArray, intArray.length))
		return true;
		else
		return false;
	}
	
	public void updateValueInEnclave(){
		int c_hash=getArrayHash();
		String hitResultString=check_cache(c_hash);
		
		int ret = -1;
		if(hitResultString == null){
			ret = commitUpdate(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
			updateCache(c_hash, Integer.toString(ret));
		}
		else {
			System.out.println("hit");
			ret = Integer.valueOf(hitResultString);			
		}
		
		if(ret == 1)
			return;
		else if(ret == 0)
			System.out.println("error!");
		else{
			
			//throw new Exception("error");
			System.out.println("ret:"+ret);
			System.out.println("error");
			System.out.println("ret");
			System.exit(1);
		}
		
	}

	public int getArrayHash(){
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
		return cache.hashCode();
	}
	
	public boolean getBooleanValue(){ 
		int c_hash=getArrayHash();
		String hitResultString=check_cache(c_hash);
		
		int ret = -1;
		if(hitResultString == null){
			ret = commitBranch(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
			updateCache(c_hash, Integer.toString(ret));
		}
		else {
			System.out.println("hit");
			ret = Integer.valueOf(hitResultString);			
		}
		
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
	}
	
	public int getIntValue(){ 
		int c_hash=getArrayHash();
		String hit=check_cache(c_hash);
		
		int ret = -1;
		if(hit==null){
			 ret = commitInt(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
			updateCache(c_hash, String.valueOf(ret));
		}
		else {
			System.out.println("hit");
			ret = Integer.valueOf(hit);			
		}
		return ret;
	}

	public float getFloatValue(){ 
		int c_hash=getArrayHash();
		String hit=check_cache(c_hash);
		float ret = -1;
		if(hit==null){
			 ret = commitFloat(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
			updateCache(c_hash, String.valueOf(ret));
		}
		else {
			System.out.println("hit");
			ret = Float.valueOf(hit);			
		}
		
//		System.out.println("ret:"+ret);
//		System.out.println("error");
//		System.out.println("ret");
		return ret;
	
	}

	public double getDoubleValue(){ 
		int c_hash=getArrayHash();
		String hit=check_cache(c_hash);
		
		double ret = -1;
		if(hit==null){
			 ret = commitDouble(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
			updateCache(c_hash, String.valueOf(ret));
		}
		else {
			System.out.println("hit");
			ret = Double.valueOf(hit);			
		}
		return ret;
	}

	public char getCharValue(){ 
		int c_hash=getArrayHash();
		String hit=check_cache(c_hash);
		
		char ret;
		if(hit==null){
			 ret = commitChar(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
			updateCache(c_hash, String.valueOf(ret));
		}
		else {
			System.out.println("hit");
			ret = hit.charAt(0);			
		}
		return ret;
	}

	public byte getByteValue() throws UnsupportedEncodingException{ 
		int c_hash=getArrayHash();
		String hit=check_cache(c_hash);
		
		byte ret;
		if(hit==null){
			 ret = commitByte(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
			 updateCache(c_hash, String.valueOf(ret));
		}
		else {
			System.out.println("hit");
			ret = hit.getBytes(hit)[0];
		}
		return ret;
	}
}