package project01;
/*Test bench checking input/output files against
 * input/output of objects and methods
 */
import java.io.*;
import java.util.Scanner;

public class TestBench {

	public static void main(String[] args) throws IOException {
		Scanner scan = new Scanner(System.in);
		System.out.print("Enter text file: ");
		String file = scan.next() + ".txt"; //Insert filename
		Readin standard = new Readin(file);
		FileAnalysis format = new FileAnalysis(standard.read());
		format.analyze();
		System.out.println(standard);
		scan.close();
	}
}
