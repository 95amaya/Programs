package hw03;

public class MyStackTest {

	public static void main(String[] args) {
		// Create MyStack object
		MyStack stack = new MyStack();
		
		stack.push("Hello");
		stack.push("World");
		
		System.out.println(stack.peek());
		System.out.println(stack);
		System.out.println(stack.pop());
		System.out.println(stack);
	}

}
