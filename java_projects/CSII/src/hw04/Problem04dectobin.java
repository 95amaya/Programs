package hw04;

public class Problem04dectobin {

	public static void main(String[] args) {
		
		////////Problem04//////////////
		int num = 25;
		System.out.println("---Problem04---");
		System.out.println(dec2Bin(num));
		
		//////////Problem05////////////
		System.out.println("---Problem05---");
		for(int i = 0; i < 51;i++)
			System.out.print(bin2Dec(dec2Bin(i)) + " "); //Using dec2bin method to check bin2dec
	}
	
	//Finding binary value to decimal input			--- Problem04
	public static String dec2Bin(int val){

		if(val == 1)	//Base case: if value is 1 or 0 return that value
			return "1";
		if(val == 0)
			return "0";
		
		if(val%2==1)	//If the value is odd return a 1 added onto the previous binary value
			return dec2Bin(val/2) + "1";
		
		return dec2Bin(val/2) + "0";
	}
	
	//Finding decimal value of binary input recursively --- Problem05
	public static String bin2Dec(String str){
		int len = str.length()-1;

		if(len == 0)	//Base Case: If string length is 0 return the number 16^0 place.
			return Integer.parseInt(str) + "";
		
		if(str.charAt(0) == '0')	//If there is a zero return the remaining number skipping the zero.
			return bin2Dec(str.substring((str.length()-len)));
		
		return Integer.parseInt(bin2Dec(str.substring((str.length()-len)))) + (int)Math.pow(2,len) + ""; //Parse the String and add it's decimal equivalent 16^n
	}
	
}
