package hw03;

public class ExpressionSolver {
	private String[] expression;
	
	ExpressionSolver(){
		expression = new String[10];
	}
	
	ExpressionSolver(String[] exp){
		expression = exp;
	}
	
	public int solve(){
		int first, second; 
		first = second = 0;
		String operator = "";
		int count = 0;
		
		//Read expression left to right
		for(String op: expression){
			switch(count){
				case 0: first = Integer.parseInt(op);	break;
				case 1: operator = op;					break;
				case 2: second = Integer.parseInt(op);
						first = operate(first,second,operator);
						//System.out.println("Second: " + second + "\nOperate: " + first);
						count = 0;						break;
				default: first = Integer.parseInt(op);	break;
			}
			count++;
		}
		
		return first;
	}

	//Match string operation with actual operation
	public int operate(int one, int two, String strop){
		int ans = 0;
		int operator = op(strop);
		//System.out.println("operatorint:" + operator);
		switch (operator){
			case 0:	ans = one + two; break;
			case 1:	ans = one - two; break;
			case 2:	ans = one * two; break;
			case 3:	ans = one / two; break;
			default: ans = 0; break;
		}
		
		return ans;
	}
	
	//Match string to find which operation is used
	public int op(String s){
		int operation = -1;
		
		//System.out.println("opeartion:" + s);
		if(s.equals("+"))
			operation = 0;
		if(s.equals("-"))
			operation = 1;
		if(s.equals("*"))
			operation = 2;
		if(s.equals("/"))
			operation = 3;
		
		return operation;
	}
	
	//Print out original equation + " = " answer
	public String toString(){
		String str = "";
		for(String s:expression)
			str += s + " ";
		str += "= " + solve();
		return str;
	}
}
