package hw02;

public class RectTest {

	public static void main(String[] args) {
		//Create rectangles
		Rectangle R1 = new Rectangle(4,40);
		Rectangle R2 = new Rectangle(3.5,35.9);
		
		//Print out width and height then area and perimeter
		System.out.println("Rectangle ONE");
		System.out.println(R1.toString());
		System.out.println("Area: " + R1.getArea());
		System.out.println("Perimeter: " + R1.getPerimeter() + "\n");

		System.out.println("Rectangle TWO");
		System.out.println(R2.toString());
		System.out.println("Area: " + R2.getArea());
		System.out.println("Perimeter: " + R2.getPerimeter());
	}

}
