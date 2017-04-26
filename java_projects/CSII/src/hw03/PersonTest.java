package hw03;

public class PersonTest {

	public static void main(String[] args) {
		// Person, Student, Employee, Faculty, Staff
		Person[] People = new Person[5];
		
		People[0] = new Person("Michael Jordan", "Chicago", "none", "none");
		People[1] = new Student("Me", "San Antonio", "555-555", "me@aol.com", "Junior");
		People[2] = new Employee("Marshall Mathers", "Detroit", "*67", "none", "M", "500,000", "03/17/1995" );
		People[3] = new Staff("Marshawn Lynch", "Seattle", "none", "none", "R", "600,000", "09/12/1996", "Beast Mode");
		People[4] = new Faculty("Tupac Shakur", "Oakland", "555-555", "none", "L", "700,000", "09/14/1996", "3-5 PM", "Executive");
		
		for(Person p: People)
			System.out.println(p);

	}

}
