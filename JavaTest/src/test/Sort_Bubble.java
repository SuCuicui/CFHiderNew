package test;

public class Sort_Bubble {
	
	public static void main(String[] args) 
    {
    
		System.out.println("main(): ");
        
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
		    System.out.println("bubbleSort(): ");
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
	 
	 public static void printArr(int[] numbers)
	    {
		    System.out.println("printArr(): ");
	        for(int i = 0 ; i < numbers.length ; i++ )
	        {
//		        System.out.println("No"+i+": ");
		        System.out.print(numbers[i] + " ");
	        }
	        System.out.println();
	    }


}