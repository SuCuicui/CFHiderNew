package test;

public class Sort_Bubble {
	
	public static void main(String[] args) 
    {
    
//		System.out.println("main(): ");
        
        int[] numbers=new int[10];
        numbers[0]=10;
        numbers[1]=20;
        numbers[2]=15;
        numbers[3]=0;
        numbers[4]=6;
        numbers[5]=7;
        numbers[6]=2;
        numbers[7]=1;
        numbers[8]=-5;
        numbers[9]=55;
        
        
        System.out.println("排序前：");
        printArr(numbers);
        
        bubbleSort(numbers);
        System.out.println("排序后：");
        printArr(numbers);
//        
//        quick(numbers);
//        System.out.print("快速排序后：");
//        printArr(numbers);
    }
 
	
	 public static void bubbleSort(int[] numbers)
	    {
//		    System.out.println("bubbleSort(): ");
	        int temp = 0;
	        int size = numbers.length;
	        for(int i = 0 ; i < size-1; i ++)
	        {
	        for(int j = 0 ;j < size-1-i ; j++)
	        {
	            if(numbers[j] > numbers[j+1])  //交换两数位置
	            {
	            temp = numbers[j];
	            numbers[j] = numbers[j+1];
	            numbers[j+1] = temp;
	            }
	        }
	        }
	    }
	 
	 public static int getMiddle(int[] numbers, int low,int high)
	    {
//		    System.out.println("getMiddle(): ");
	        int temp = numbers[low]; //数组的第一个作为中轴
	        while(low < high)
	        {
	        while(low < high && numbers[high] > temp)
	        {
	            high--;
	        }
	        numbers[low] = numbers[high];//比中轴小的记录移到低端
	        while(low < high && numbers[low] < temp)
	        {
	            low++;
	        }
	        numbers[high] = numbers[low] ; //比中轴大的记录移到高端
	        }
	        numbers[low] = temp ; //中轴记录到尾
	        return low ; // 返回中轴的位置
	    }
	 
	 /**
	     * 
	     * @param numbers 带排序数组
	     * @param low  开始位置
	     * @param high 结束位置
	     */
	    public static void quickSort(int[] numbers,int low,int high)
	    {
//		    System.out.println("quickSort(): ");
	        if(low < high)
	        {
	          int middle = getMiddle(numbers,low,high); //将numbers数组进行一分为二
//	          printArr(numbers);
	          quickSort(numbers, low, middle-1);   //对低字段表进行递归排序
//	          printArr(numbers);
	          quickSort(numbers, middle+1, high); //对高字段表进行递归排序
//	          printArr(numbers);
	        }
	    
	    }
	    /**
	     * 快速排序
	     * @param numbers 带排序数组
	     */
	    public static void quick(int[] numbers)
	    {
//		    System.out.println("quick(): ");
	        if(numbers.length > 0)   //查看数组是否为空
	        {
	        quickSort(numbers, 0, numbers.length-1);
	        }
	    }
	    
	 
	 public static void printArr(int[] numbers)
	    {
//		    System.out.println("printArr(): ");
	        for(int i = 0 ; i < numbers.length ; i++ )
	        {
//		        System.out.println("No"+i+": ");
		        System.out.print(numbers[i] + " ");
	        }
	        System.out.println();
	    }


}