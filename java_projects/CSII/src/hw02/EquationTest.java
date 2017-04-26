package hw02;

import java.util.Scanner;

public class EquationTest {

	public static void main(String[] args) {
		// Create Scanner object to scan in each variable
		Scanner scan = new Scanner(System.in);
		System.out.println("Enter to corresponding: ax + by = e and cx + dy = f");
		System.out.print("a: ");
		double a = scan.nextDouble();
		System.out.print("b: ");
		double b = scan.nextDouble();
		System.out.print("e: ");
		double e = scan.nextDouble();
		System.out.print("c: ");
		double c = scan.nextDouble();
		System.out.print("d: ");
		double d = scan.nextDouble();
		System.out.print("f: ");
		double f = scan.nextDouble();
		
		//Create LinearEquatino object with these variable and print it out
		LinearEquation line = new LinearEquation(a,b,c,d,e,f);
		System.out.println(line.toString());
		
		scan.close();

	}

}
