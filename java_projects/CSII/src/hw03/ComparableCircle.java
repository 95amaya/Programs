package hw03;

public class ComparableCircle extends Circle implements Comparable<Circle> {
	
	//Creating Constructor keeping in mind Circle is extended
	public ComparableCircle(double rad){
		super(rad);
	}
	
	//Using Circle getter and setters
	public double getRadius(){
		return super.getRadius();
	}
	
	public void setRadius(double newRadius) {
		super.setRadius(newRadius);
	}
	
	public double getArea() {
		return super.getArea();
	}
	
	//Override CompareTo to compare Circle area's
	public int compareTo(Circle one) {
		if(getArea() > one.getArea())
			return 1;
		else if(getArea() < one.getArea())
			return -1;
		else
			return 0;
	}
	
	public String toString(){
		return "Comparable Circle\nRadius: " +  getRadius() + "\nArea: " + getArea();
	}

}
