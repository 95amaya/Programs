package hw02;

public class Fan {
	//Create global constants slow medium fast.
	//Create speed, radius, on, color private variables.
	public static String[] speeds = {"SLOW","MEDIUM","FAST"};
	private int speed, radius;
	private boolean on;
	private String color;
	
	//Default Constructor of a Fan
	Fan(){
		speed = 2;
		radius = 5;
		on = false;
		color = "Blue";
	}

	//Create getters and setters for each variable except the constants
	public String getSpeed() {
		if(speed > 3 || speed < 1)
			return speeds[1];
		return speeds[speed-1];
	}

	public void setSpeed(int speed) {
		this.speed = speed;
	}

	public int getRadius() {
		return radius;
	}

	public void setRadius(int radius) {
		this.radius = radius;
	}

	public boolean isOn() {
		return on;
	}

	public void setOn(boolean on) {
		this.on = on;
	}

	public String getColor() {
		return color;
	}

	public void setColor(String color) {
		this.color = color;
	}
	
	//Create toString to return the contents when the fan is on or off
	public String toString(){
		if(isOn())
			return "Speed: " + getSpeed() + "  Color: " + color + "  Radius:" + radius;
		else
			return "Color: " + color + "  Radius: " + radius  + "  fan is off"; 
	}
}
