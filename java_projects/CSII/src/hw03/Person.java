package hw03;

public class Person {
	private String name, address, phone, email;
	
	// Create Constructors
	Person(){
		name = "";
		address = "";
		phone = "";
		email = "";
	}
	
	Person(String n, String a, String p, String e){
		name = n;
		address = a;
		phone = p;
		email = e;
	}

	//Create Getter Setter Methods
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getAddress() {
		return address;
	}

	public void setAddress(String address) {
		this.address = address;
	}

	public String getPhone() {
		return phone;
	}

	public void setPhone(String phone) {
		this.phone = phone;
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) {
		this.email = email;
	}
	
	public String toString(){
		return "Person: " + getName() + "\nAddress: " + getAddress() + "\nPhone: " 
				+ getPhone() + "\nEmail: " + getEmail() + "\n";
	}

}
