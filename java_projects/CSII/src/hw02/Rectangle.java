package hw02;

public class Rectangle {
	//// Create private double variables width and height
	private double width;
	private double height;
	
	//// Create Constructors. Default w = h = 1; parameters wid and height are doubles
	Rectangle(){
		width = height  = 1;
	}
	Rectangle(double wid, double ht){
		width = wid;
		height = ht;
	}
	
	//// Getter Methods getArea() and getPerimeter() which return doubles area and perimeter
	public double getArea(){
		return width*height;
	}
	public double getPerimeter(){
		return 2*width + 2*height;
	}
	
	//// ToString method to return the width and height of class
	public String toString(){
		return "Width: " + width + "  Height: " + height; 
	}
}
