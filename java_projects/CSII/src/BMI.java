//import java.util.*;

public class BMI {

	public static void main(String[] args) {
		double weightInKg = 50;
		double heightInM = 1.5;
		
		double BMI = weightInKg/(Math.pow(heightInM,2));
				
		if(BMI < 30)
			if(BMI < 25)
				if(BMI < 18.5)
					System.out.println("Underweight");
				else
					System.out.println("Normal");
			else
				System.out.println("Overweight");
		else
			System.out.println("Obese");
		///////////////////////////////////////////////////
		/*double[][][] scores = {
				{ {7.5, 20.5}, {9.0, 22.5}, {15, 33.5}, {13, 21.5}
				{7.5, 20.5}, {9.0, 22.5}, {15, 33.5}, {13, 21.5}
				{7.5, 20.5}, {9.0, 22.5}, {15, 33.5}, {13, 21.5}
				{7.5, 20.5}, {9.0, 22.5}, {15, 33.5}, {13, 21.5}
				}
		}*/
	}

}
