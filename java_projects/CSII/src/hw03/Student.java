package hw03;

public class Student extends Person {
	private final String status;
	
	//Create Constructors keeping in mind Person super class
	Student(){
		super();
		status = "";
	}
	
	Student(String stat){
		status = stat;
	}
	
	Student(String n, String a, String p, String e, String stat){
		super(n,a,p,e);
		status = stat;
	}
	
	public String getStatus(){
		return status;
	}
	
	//Overwrite Person toString()
	public String toString(){
		return "Student: " + super.getName();
	}

}
