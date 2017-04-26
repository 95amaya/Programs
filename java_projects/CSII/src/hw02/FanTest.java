package hw02;

public class FanTest {

	public static void main(String[] args) {
		// Create 2 fans
		Fan fan1 = new Fan();
		Fan fan2 = new Fan();
		
		//set Fan variables
		fan1.setSpeed(3);
		fan1.setRadius(10);
		fan1.setColor("yellow");
		fan1.setOn(true);
		
		System.out.println("Fan1: " + fan1);
		System.out.println("Fan2: " + fan2);

	}

}
