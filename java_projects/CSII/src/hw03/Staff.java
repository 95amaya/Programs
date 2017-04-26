package hw03;

public class Staff extends Employee{
	private final String title;
	
	//Create Constructors keeping in mind Employee super class
	Staff(){
		super();
		title = "";
	}
	
	Staff(String n, String a, String p, String e, String off, String sal, String date, String t){
		super(n,a,p,e,off,sal,date);
		title = t;
		
	}
	
	public String getTitle(){
		return title;
	}
	
	//Overwrite Employee toString()
	public String toString(){
		return "Staff: " + super.getName();
	}

}
