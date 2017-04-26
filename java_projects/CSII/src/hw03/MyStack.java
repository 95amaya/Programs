package hw03;

import java.util.ArrayList;

public class MyStack {
	private ArrayList<Object> stack;
	
	MyStack(){
		stack = new ArrayList<Object>();
	}
	
	public boolean isEmpty(){
		return stack.isEmpty();
	}
	
	public int getSize(){
		return stack.size();
	}
	
	public void push(Object element){
		stack.add(element);
	}
	
	public Object peek(){
		if(isEmpty())
			return null;
		return stack.get(stack.size()-1);
	}
	
	public Object pop(){
		if(isEmpty())
			return null;
		Object temp = peek();
		stack.remove(stack.size()-1);
		return temp;
	}
	
	public String toString(){
		return stack.toString();
	}

}
