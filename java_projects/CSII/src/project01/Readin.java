package project01;
/*First Layer of reading in the file before file analysis 
 * in order to check the formatting of the test before
 * proceeding to analyze it.
*/
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Readin {
	private String file;
	
	Readin(){
		file = "";
	}
	
	Readin(String filename){
		file = filename;
	}
	
	public String getFile(){
		return file;
	}
	
	//Returns file as a string using FileReader and BufferedReader objects.
	public String read(){
		// This will reference one line at a time
        String line = null;
        String text = "";

        try {
            // FileReader reads text files in the default encoding.
            FileReader fileReader = 
                new FileReader(getFile());

            // Always wrap FileReader in BufferedReader.
            BufferedReader bufferedReader = 
                new BufferedReader(fileReader);
                 
            while((line = bufferedReader.readLine()) != null){ //Storing each line of the file to a string
            	text += line + "\n";
            }

            // Always close files.
            bufferedReader.close();            
        }
        catch(FileNotFoundException ex) {
            System.out.println(
                "Unable to open file '" + 
                getFile() + "'");                
        }
        catch(IOException ex) {
            System.out.println(
                "Error reading file '" 
                + getFile() + "'");                   
            // Or we could just do this: 
            // ex.printStackTrace();
        }     
        return text;
	}
	
	
	public String toString(){
		return "File Read... Answers written to Output.txt";
	}

}
