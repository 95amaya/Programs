//import java.io.*;

//import project01.Readin;

public class CSIIHWTemp {

	public static void main(String[] args) {
		String blah = "hello World";
		String hi = blah;
		for(int i = 0; i<blah.length();i++){
			hi = hi.substring(1);
			System.out.println(hi);
		}
		/*
		for(int k = 8; k < 9; k++){
		String file = "/Users/MichaelAAmaya/Downloads/input_output/input" + k + ".txt";
		
		 // File names to Read & Write.
        String actualFile   = "/Users/MichaelAAmaya/workspace/CSII/temp.txt";
        String expectedFile = "/Users/MichaelAAmaya/Downloads/input_output/output" + k + ".txt";
        String descptnFile  = "check.txt";
        
        try{
        // Create FileReader & Writer Objects.
        FileReader actualFileReader  = new FileReader(actualFile);
        FileReader expctdFileReader  = new FileReader(expectedFile);
        FileWriter resultDesc = new FileWriter(descptnFile);
       
        // Create Buffered Object.
        BufferedReader actlFileBufRdr = new BufferedReader(actualFileReader);
        BufferedReader expcFileBufRdr = new BufferedReader(expctdFileReader);
        BufferedWriter resultFileBufWrtr = new BufferedWriter(resultDesc);
       
        // Get the file contents into String Variables.
        String actlFileContent = actlFileBufRdr.readLine();
        String expctdFileContent = expcFileBufRdr.readLine();
       
        // Compare the Contents of the files.
        String startOfComparision = "---------START----------";
        resultFileBufWrtr.write(startOfComparision);
        resultFileBufWrtr.newLine();
        System.out.println("file: " + file + "\n" + startOfComparision);
       
        boolean isDifferent = false;
        int lineNumber = 1;
       
        if (actlFileContent != null || expctdFileContent != null) {
               
                // Check whether Actual file contains data or not
                while((actlFileContent!=null)  ){
                       
                        // Check whether Expected file contains data or not
                        if (((expctdFileContent )!=null)) {
                               
                        	
                        	String correction = " ";
                        	String AfileSub = IgnoreWhiteSpaces(actlFileContent);
                        	String EfileSub = IgnoreWhiteSpaces(expctdFileContent);
                        	
                        	int from = 0;
                        	//System.out.println(AfileSub.split(" ")[1] + " |||||||| " + EfileSub.split(" ")[1]);
                        	
                        	//System.out.println(AfileSub.length() + " vs. " + EfileSub.length());
                        	//System.out.println("ActualSt:" + AfileSub);
                        	//System.out.println("Expected:" + EfileSub);
                        	
                        	//if(AfileSub.length() > EfileSub.length())
                        		//System.out.println("Actual File is bigger:" + AfileSub.substring(EfileSub.length()));
                        	//if(EfileSub.length() > AfileSub.length())
                        		//System.out.println("Expected File is bigger:" + EfileSub.substring(AfileSub.length()));
                        	
                                // Check whether both the files have same data in the lines
                        		for(int i = 0; i < AfileSub.length() && i < EfileSub.length(); i++){ //&& i < actlFileContent/expctdFileContent.length()
                        			
                        			String check01 = AfileSub.charAt(i) + "";
                        			String check02 = EfileSub.charAt(i) + "";
                              
                        			
                        			if (!check01.equalsIgnoreCase(check02)) {
                        				correction += AfileSub.charAt(i);                      				 
                                        isDifferent = true;
                        			}			
                        		}
                        		
                        		/*if(lineNumber == 9){
                        			System.out.println(AfileSub.length() + " vs. " + EfileSub.length());
                                	System.out.println("\tActualSt---" + AfileSub);
                                	System.out.println("\tExpected---" + EfileSub);
                        		}
                        		
                        		if(!correction.equals(" ") || AfileSub.length() != EfileSub.length()){
                        			System.out.print("Difference in Line "+lineNumber+" :- Line Lengths :");
                        			System.out.println(AfileSub.length() + " vs. " + EfileSub.length());
                                	System.out.println("\tActualSt---" + AfileSub);
                                	System.out.println("\tExpected---" + EfileSub);
                        			resultFileBufWrtr.write("Difference in Line "+lineNumber+" :- Actual Vs. Expected File : ");
                        			resultFileBufWrtr.newLine();
                        		}
                
                                lineNumber = lineNumber+1;
                                expctdFileContent= expcFileBufRdr.readLine();
                        }
                        else{
                                resultFileBufWrtr.write("Difference in Line "+lineNumber+" :- Actual File contains :"+actlFileContent+", Expected File Contains - "+expctdFileContent);
                                resultFileBufWrtr.newLine();
                                System.out.println("Difference in Line "+lineNumber+" :- Actual File contains :"+actlFileContent+", Expected File Contains - "+expctdFileContent);
                                isDifferent = true;
                                lineNumber = lineNumber+1;
                        }
                        actlFileContent=actlFileBufRdr.readLine();
                }
               
                // Check for the condition : if Actual File has Data & Expected File doesn't contain data.
                while ((expctdFileContent!=null)&&(actlFileContent==null)) {
                        resultFileBufWrtr.write("Difference in Line "+lineNumber+" :- Actual File contains :"+actlFileContent+", Expected File Contains - "+expctdFileContent);
                        resultFileBufWrtr.newLine();
                        System.out.println("Difference in Line "+lineNumber+" :- Actual File contains :"+actlFileContent+", Expected File Contains - "+expctdFileContent);
                        isDifferent = true;
                        lineNumber = lineNumber+1;
                        expctdFileContent= expcFileBufRdr.readLine();
                }
        }
        else{
                // Mention that both the files don't have Data.
                resultFileBufWrtr.write("Difference in Line "+lineNumber+" :- Actual File contains :"+actlFileContent+", Expected File Contains - "+expctdFileContent);
                resultFileBufWrtr.newLine();
                System.out.println("Difference in Line "+lineNumber+" :- Actual File contains :"+actlFileContent+", Expected File Contains - "+expctdFileContent);
                isDifferent = true;
        }
       
        // Check is there any difference or not.
        String endOfComparision = "-----------END----------";
        if (isDifferent) {
                resultFileBufWrtr.append(endOfComparision);
                System.out.println(endOfComparision);
        }
        else{
                resultFileBufWrtr.append("No difference Found");
                resultFileBufWrtr.newLine();
                resultFileBufWrtr.append(endOfComparision);
               
                System.out.println("No difference Found");
                System.out.println(endOfComparision);
        }
       
        //Close the streams.
        actualFileReader.close();
        expctdFileReader.close();
        resultFileBufWrtr.close();
        actlFileBufRdr.close();
        expcFileBufRdr.close();
        }
        catch( FileNotFoundException e )
        {
        	e.printStackTrace();
        }
		}//for loop end
	}
	
	public static String IgnoreWhiteSpaces(String str){
		String spaceLess = "";
		String lc = str.toLowerCase();
		int i = 0;
		
		while(i < str.length()){
			if(str.charAt(i) != 32 && str.charAt(i) != 9 && str.charAt(i) != 61)
				spaceLess += str.charAt(i);
			i++;
		}	
		return spaceLess;*/
	}
}
