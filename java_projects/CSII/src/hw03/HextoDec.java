package hw03;

public class HextoDec {
	private String hex;
	
	//Create Constructors that take in hex value
	HextoDec(){
		hex = "";
	}
	
	HextoDec(String s){
		hex = s.toUpperCase();
	}
	
	//Mutator method to take in hex value
	public void setHex(String s){
		hex = s.toUpperCase();	
	}
	
	//Convert hex character to decimal value 
	public int hexChartoDec(char s){
		int ch = s;
		
		if(ch > 47 && ch < 58) //0-9 Unicode
			return ch-48;
		else if(ch < 71 && ch > 64) //A-F Unicode
			return ch-55;
		else
			return 0;
	}
	
	//Convert hex string to decimal value
	public int hextoDecimal(){
		int dec = 0;
		
		//Start at the end of the String and move backwards
		for(int i = hex.length()-1, k = 0; i > 1; i--, k++){
			//Multiply each hex decimal value by hex place and add it to the total
			dec = dec + (int)Math.pow(16,k)*hexChartoDec(hex.charAt(i));
			//System.out.println("decimal: " + dec);
		}
		return dec;
	}
	
	//Print Hex value and converted Decimal value
	public String toString(){
		if(hex == "")
			return "Hex = " + hex + " Please setHex to a Hexadecimal Value.";
		return "Hex: " + hex + " = " + hextoDecimal();
	}

}
