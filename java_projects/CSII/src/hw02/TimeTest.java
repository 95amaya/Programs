package hw02;

public class TimeTest {

	public static void main(String[] args) {
		//You can create a random list using random method:
		double[] list = new double[100000]; 
		for (int i = 0; i < list.length; i++) {
		     list[i] = Math.random() * list.length;
	    }
		
		StopWatch watch = new StopWatch();
		watch.start();
		selectionSort(list);
		watch.stop();
		System.out.println("Selection Sort Time(ms): " + watch.getElapsedTime());
		
		
		
	}

	// The method for sorting the numbers
	public static void selectionSort(double[] list) {
		for (int i = 0; i < list.length - 1; i++) {
    	// Find the minimum in the list[i..list.length-1]
			double currentMin = list[i];
			int currentMinIndex = i;
			for (int j = i + 1; j < list.length; j++) {
				if (currentMin > list[j]) {
					currentMin = list[j];
					currentMinIndex = j;
				}
			}
			// Swap list[i] with list[currentMinIndex] if necessary;
			if (currentMinIndex != i) {
				list[currentMinIndex] = list[i];
				list[i] = currentMin;
			}
		}
	}
}
