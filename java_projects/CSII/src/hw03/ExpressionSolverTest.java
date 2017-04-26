package hw03;

public class ExpressionSolverTest {

	public static void main(String[] args) {
		
		// Create ExressionSovler and send in args split
		ExpressionSolver solver = new ExpressionSolver(args[0].split(" "));
		System.out.println(solver);
	}
	

}
