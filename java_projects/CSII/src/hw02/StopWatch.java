package hw02;

public class StopWatch {
	//// Create private double variable starTime and endTime
	private double startTime;
	private double endTime;
	
	//// Create default constructor that starts the time
	StopWatch(){
		startTime = System.currentTimeMillis();
		endTime = 0;
	}
	
	//// Create mutator methods that start and stop time
	public void start(){
		startTime = System.currentTimeMillis();
	}
	public void stop(){
		endTime = System.currentTimeMillis();
	}
	
	//// Create getter method getElapsedTime to return the elapsed time from start to stop
	public double getElapsedTime(){
		return endTime - startTime;
	}
}
