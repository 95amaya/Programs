package hw03;

import java.util.Scanner;

public class SwapCase {

	public static void main(String[] args) {
		
		// Problem 03 using String Builder Class's built-in reverse method to print reversed String
		StringBuilder blah = new StringBuilder();
		String str = "Hello World";
		blah.append(str);
		System.out.println(str + "\n" + blah.reverse() + "\n");
		
		// Problem 04 testing swapCase first prompting user for an input String
		Scanner scan = new Scanner(System.in);
		System.out.print("Enter a string: ");
		str = scan.nextLine();
		System.out.println("The new string is: " + swapCase(str));
		scan.close();

	}
	
	//Using Character class's isUpperCase() and toLowerCase() methods to switch the case's of the string
	public static String swapCase(String s){
		String str = "";
		
		for(int i = 0; i < s.length(); i++){
			if(Character.isUpperCase(s.charAt(i)))
				str += Character.toLowerCase(s.charAt(i));
			else
				str += Character.toUpperCase(s.charAt(i));
		}
		
		return str;
	}

}
