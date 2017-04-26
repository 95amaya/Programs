package hw03;

public class CircleTest {

	public static void main(String[] args) {
		
		// Create Circle and ComparableCircle
		Circle cir = new Circle(4);
		ComparableCircle comp = new ComparableCircle(5);
		
		System.out.println("Circle Radius: " + cir.getRadius() + "\n");
		System.out.println(comp + "\n");
		
		//ComparableCircle compared to Circle
		if(comp.compareTo(cir) > 0)
			System.out.println("ComparableCircle is bigger");
		else if(comp.compareTo(cir) < 0)
			System.out.println("ComparableCircle is smaller");
		else
			System.out.println("ComparableCircle is the same size");

	}

}
