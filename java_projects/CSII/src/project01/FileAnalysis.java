package project01;
/*Second layer of analyzing file in the string format.
 * Breaks up each question individually and answers/writes
 * them to an output file before finishing in analyze method.
 */

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class FileAnalysis {
	private String filestr;
	
	FileAnalysis(){}
	
	FileAnalysis(String file){
		filestr = file;
	}
	
	public String getFilestr(){
		return filestr;
	}
	
	//Analyzes the file string reading in one question at a time and writing one answer at a time to the file
	public void analyze(){
		String fileName = "Output.txt";
        String line = null;
        String text = "";
		Question q = new Question();
		
			//Reading in file as a string and answering/writing questions on the go
        try {
        	Scanner scan = new Scanner(filestr);
        	
        	   // Assume default encoding.
            FileWriter fileWriter =
                new FileWriter(fileName);

            // Always wrap FileWriter in BufferedWriter.
            BufferedWriter bufferedWriter =
                new BufferedWriter(fileWriter);
        	
        	while(scan.hasNext()){
        		line = scan.nextLine();
        		if(line.contains("Type: ") && text.length() > 1){ //Breaking up each question by finding "Type: " 
            		q.setQuestion(text);
            		text = "";
            		// Note that write() does not automatically append a newline character.
            		// write the answer of one question to the file.
            		System.out.println(q);
            		bufferedWriter.write(q.ansQuestion() + "\t");
            	}
            	text += line + "\n";
        	}
        	//write the answer of the last question to the file
            q.setQuestion(text);
            System.out.println(q);
            bufferedWriter.write(q.ansQuestion());
        
            // Always close files.
            bufferedWriter.close();
            scan.close();
        }
        
        catch(IOException ex) {
        	System.out.println("Error writing to file '"
            + fileName + "'");
        // Or we could just do this:
        // ex.printStackTrace();
        }
		
	}
}
