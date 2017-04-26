package hw04;

public class Problem01series {
	
	public static void main(String[] args){
		/////////Problem 01////////////////////
		System.out.println("---Problem01---");
		for(int i = 1; i < 11; i++)
			System.out.println(series(i));
		
		////////Problem 02/////////////////////
		String hi = "hello world";
		
		System.out.println("\n---Problem02---");
		reverseDisplay(hi);
		
		///////Problem 03//////////////////////
		System.out.println("\n\n---Problem03---");
		reverseDisp(hi);
		
	}
	
	//Displays 1/n Series from 1 to n recursively --- Problem01
	public static String series(int n){
		if(n == 1)
			return "1";
		
		return series(n-1) + " + 1/" + n;
	}
	
	//Displays reverse String recursively 		--- Problem02
	public static void reverseDisplay(String str){
		int len = 0;
		if(len >= str.length()){
			System.out.print(str.substring(len));
			return;
		}
		
		reverseDisplay(str.substring(len+1));		
		System.out.print(str.substring(len,len+1));
	}
	
	//Displays reverse String recursively with helper method ---  Problem03
	public static void reverseDisp(String str){
		reverseDisp(str,0);
	}
	
	//Helper method
	public static void reverseDisp(String str, int len){
		if(len == str.length() - 1){
			System.out.print(str.charAt(str.length()-1));
			return;
		}
		
		reverseDisp(str,len+1);
		System.out.print(str.charAt(len));
	}

}
