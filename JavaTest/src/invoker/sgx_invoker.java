package invoker;

import java.io.UnsupportedEncodingException;

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
	public static native int deleteValue();
	
	static {
		try{
//			System.out.println("invoker"+System.getProperty("java.library.path"));
			System.loadLibrary("SGX");
		}
		catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println("invoker"+System.getProperty("java.library.path"));
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
	

	static long request = 1;
	static long hitNum = 0;
	
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
//		System.out.println(String.valueOf(o)+" is added to list;");
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
		if(1==initValue(intArray, intArray.length)){
//			System.out.println("initValueInEnclave(Array) is okay!");
			return true;
		}
		else
			return false;
	}
	
	public boolean deleteValueInEnclave(){
		if(1==deleteValue()){
//			System.out.println("deleteValueInEnclave( is okay!");
			return true;
		}
		else
			return false;
	}
	
	
	public void updateValueInEnclave(){
		int ret = -1;
		ret = commitUpdate(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
		
		if(ret == 1){
//			System.out.println("updateValueInEnclave is okay!");
			return;
		}
		else if(ret == 0){
			System.out.println("error!");
			return;
		}
		else{
			
			//throw new Exception("error");
			System.out.println("ret:"+ret);
			System.out.println("error");
			System.out.println("ret");
			System.exit(1);
		}
		
	}
	public boolean getBooleanValue(){ 
		
		int ret = -1;
		ret = commitBranch(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
		
		if(ret == 1){
//			System.out.println("getBooleanValue is okay!");
			return true;
		}
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
		int ret = -1;
		ret = commitInt(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);

//		if(ret !=-1)
//			  System.out.println("getIntValue is okay!");
		return ret;
	}

	public float getFloatValue(){ 
		float ret = -1;
		ret = commitFloat(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
		
		return ret;
	
	}

	public double getDoubleValue(){ 
		
		double ret = -1;
		ret = commitDouble(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
			
		return ret;
	}

	public char getCharValue(){ 
		char ret;
		ret = commitChar(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
		return ret;
	}

	public byte getByteValue() throws UnsupportedEncodingException{ 
		byte ret;
		ret = commitByte(counter, intArray,intTail,doubleArray,doubleTail,floatArray,floatTail,longArray,longTail,charArray,charTail,byteArray,byteTail);
		
		return ret;
	}
}