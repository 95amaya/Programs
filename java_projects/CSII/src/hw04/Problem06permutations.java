package hw04;

import java.util.Scanner;

public class Problem06permutations {
	public static void main(String[] args) {
		//Problem 06 Generating permutations of a String recursively
		Scanner scan = new Scanner(System.in);
		System.out.println("---Problem06---");
		System.out.print("Enter a String: ");
		String blah =  scan.nextLine();
		System.out.println("Permutations:");
		displayPermutations(blah);
		scan.close();
	}
	
	public static void displayPermutations(String s){
		displayPermutations("",s);
	}
	public static void displayPermutations(String s1, String s2){ 
		if (s2.length() <= 1)					//Base Case: When String length is one stop
		      System.out.println(s1 + s2);
		    else
		      for (int i = 0; i < s2.length(); i++) {
		        try {
		          String remainder = s2.substring(0, i) + s2.substring(i + 1); //Get the remaining String 
		          displayPermutations(s1 + s2.charAt(i), remainder);		//Find remaining permutations
		        } catch (StringIndexOutOfBoundsException exception) {
		          exception.printStackTrace();
		        }
		      }
		
	}
}
