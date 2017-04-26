package hw03;

public class Circle {
	private double radius = 1; 

	public Circle(double newRadius) {
		radius = newRadius;
	}
	public double getRadius() {
		return radius;
	}
	public void setRadius(double newRadius) {
		radius = (newRadius >= 0) ? newRadius : 0;
	}
	public double getArea() {
		return radius * radius * Math.PI;
	}
}