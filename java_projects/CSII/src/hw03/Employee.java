package hw03;

public class Employee extends Person {
	private String office, salary, hired;
	
	//Create Constructors keeping in mind Person super class
	Employee(){
		super();
		office = "";
		salary = "";
		hired = "";
	}
	
	Employee(String off, String sal, String date){
		office = off;
		salary = sal;
		hired = date;
		
	}
	
	Employee(String n, String a, String p, String e, String off, String sal, String date){
		super(n,a,p,e);
		office = off;
		salary = sal;
		hired = date;
	}

	//Create Getter Setter Methods
	public String getOffice() {
		return office;
	}

	public void setOffice(String office) {
		this.office = office;
	}

	public String getSalary() {
		return salary;
	}

	public void setSalary(String salary) {
		this.salary = salary;
	}

	public String getHired() {
		return hired;
	}
	
	//Overwrite Person toString()
	public String toString(){
		return "Employee: " + super.getName();
	}

}
