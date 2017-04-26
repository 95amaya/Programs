import java.util.*;

public class sum {

	public static void main(String[] args) {
	
		int[] sorted = new int[10];
		
		for(int i = 1; i<=10; i++)
			sorted[i-1] = i;
		
		//System.out.println("Linear Search:" + linearsearch(sorted,10) + "Binary Search: " + binarysearch(sorted,9));
		
		System.out.println(recBinSearch(sorted,-2));
		
		
	}
	public static int binarysearch(int[] list, int key){
		int low = 0;
		int len = list.length - 1;
		while(len >= low){
			int mid = (low + len) / 2;
			if(key < list[mid])
				len = mid - 1;
			else if(key == list[mid])
				return mid;
			else
				low = mid + 1;
			
		}
		return -1 - low;
	}
	public static int linearsearch(int[] list, int key){
		for(int i = 0; i<list.length; i++)
			if(list[i] == key)
				return i;
		return -1;
		
	}
	public static void m(int n, int[] a){
		n = 5;
		a[0] = 10;
	}
	public static int max(int one, int two){
		if(one > two)
			return one;
		else
			return two;
	}
	public static void getRandArray(int n){
		int[] ranArray = new int[n];
		int max = 0;
		int sum01 = 0;
		for(int i = 0; i< n; i++){
			ranArray[i] =(int)(Math.random()*100);
			sum01 += ranArray[i];
			if(ranArray[i] > max)
				max = ranArray[i];
		}
		System.out.println(Arrays.toString(ranArray));
		System.out.println("Max : " + max);
		System.out.println("Sum : " + sum01);
	}
	
	public static int recBinSearch(int[] a, int key){
		return recBinSearch(a,0,a.length-1,key);
	}
	public static int recBinSearch(int[] a, int bottom, int top, int key){
		
		int mid = (top+bottom)/2;
		System.out.println("mid: " + mid);
		
		if(bottom == top-1)
			return -1;
		
		if(a[mid] == key)
			return mid;
		
		if(a[mid] < key)
			return recBinSearch(a, mid, top, key);
		
		if(a[mid] > key)
			return recBinSearch(a, bottom, mid, key);
		
		return 0;
	}

}
