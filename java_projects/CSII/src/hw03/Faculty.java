package hw03;

public class Faculty extends Employee{
	private String offhours, rank;
	
	//Create Constructors keeping in mind Employee super class
	Faculty(){
		super();
		offhours = "";
		rank = "";
	}
	
	Faculty(String n, String a, String p, String e, String off, String sal, String date, String hours, String ran){
		super(n,a,p,e,off,sal,date);
		offhours = hours;
		rank = ran;
	}

	//Create Getter Setter Methods
	public String getOffhours() {
		return offhours;
	}

	public void setOffhours(String offhours) {
		this.offhours = offhours;
	}

	public String getRank() {
		return rank;
	}

	public void setRank(String rank) {
		this.rank = rank;
	}

	//Overwrite Employee toString()
	public String toString() {
		return "Faculty: " + super.getName();
	}
	
	

}
