package hw02;

public class LinearEquation {
	// Create private variables a-f
	private double a,b,c,d,e,f;
	
	//// Create constructor method of variables
	LinearEquation(double aa,double bb,double cc,double dd,double ee,double ff){
		a = aa;
		b = bb;
		c = cc;
		d = dd;
		e = ee;
		f = ff;
	}

	//Create getters for all variables
	public double getA() {
		return a;
	}

	public double getB() {
		return b;
	}

	public double getC() {
		return c;
	}

	public double getD() {
		return d;
	}

	public double getE() {
		return e;
	}

	public double getF() {
		return f;
	}
	
	// Create getter methods for x and y which only return if denominator != 0
	public double getX(){
		if(isSolvable())
			return (e*d - b*f)/(a*d - b*c);
		else
			return -1;
	}
	public double getY(){
		if(isSolvable())
			return (a*f - e*c)/(a*d - b*c);
		else
			return -1;
	}
	
	// Create boolean to return if the denominator != 0
	public boolean isSolvable(){
		return (a*d - b*c) != 0;
	}
	
	// Create toString to return the contents of the object
	public String toString(){
		if(!isSolvable())
			return "This equation has no solution";
		else
			return "x = " + getX() + "  y = " + getY();
	}

}
