package project01;
/*This class answers each question in particular based on its formatting,
 * type, and 
 * 
 */

import java.util.Scanner;

public class Question {
	private String ques;
	
	Question(){
		ques = "";
	}
	
	Question(String question){
		ques = question;
	}
	
	public String getQuestion(){
		return ques;
	}
	public void setQuestion(String q){
		ques = q;
	}
	
	public String ansQuestion(){
		Scanner scan = new Scanner(ques);

		String ans,line,type; 
		ans = line = type = ""; 
		boolean containsHeader = false;
		
		while(scan.hasNextLine()){
			line = scan.nextLine();
			line = line.trim();								//Take out extra white spaces before and after line
		
			if(line.isEmpty() || line.contains("Title:")){} //If line is empty or contains title skip it
			else if(containsHeader || type.equals("MT"))	//If answer has "?" or its matching then you are in the answer portion of the Question
				ans += getAns(line,type);	
			else if(line.contains("?")){					//Line has a header
				ans += getHeader(line,type) + "\t";
				containsHeader = true;
			}
			else if(line.contains("Type:")){ //Get Type of question
				type = line.substring(line.indexOf(" ") + 1);
				ans += formatType(type);
			}
			else{}
		}
		
		scan.close();
		return ans;
	}
	
	//Returns formatted Question Type
	private String formatType(String type){
		String format;
		if(type.equals("P"))
			format = "ESS\t";
		else if(type.equals("S"))
			format = "FIB\t";
		else if(type.equals("MT"))
			format = "MAT\t";
		else if(type.equals("MR"))
			format = "MC\t";
		else
			format = type + "\t";
		return format;
	}
	
	//Returns Question Header assuming the question has a question mark in it. Also checks if answer is in header line.
	private String getHeader(String line,String type){
		boolean containsHeader = line.indexOf("?") > line.length() - 3; //Checks if it contains header and answer or just header
		String header = line.substring(line.indexOf(" ") + 1);
		
		if(!containsHeader){ //Has title and answer
			String answer = (header.split("\\?")[1]).trim();	//split on "?", an escape character, to get answer portion
			header = header.split("\\?")[0] + "?\t";			//Get header portion
			header += getAns(answer,type);						//Slap the header and answer of the question together
		}	
		return header;
	}
	
	//Returns answer(s) to the question depending on type and header if type is matching
	public String getAns(String line, String type){
		
		String LineAns = line;
			
		if(LineAns.isEmpty())
			return LineAns;
		
		LineAns = LineAns.substring(LineAns.indexOf(" ") + 1);		//Gets past the number or letter part of the answer
		
		if(LineAns.contains(".") && !type.equals("P") && !type.equals("MT")) //Get rid of periods at end of answers in MC/TF
			LineAns = LineAns.substring(0,LineAns.indexOf("."));
		
		if(type.equals("S") || type.equals("MT"))					// add tab after getting short answer and matching question answers
			LineAns += "\t";
		
		if(type.equals("MC") || type.equals("MR") || type.equals("TF")){   //Multiple choice/answer and true false question formatting answer
			if(line.contains("*")){  //Finding answer
				if(type.equals("TF")){ //True/false specific answering format
					if(LineAns.contains("T") || LineAns.toLowerCase().contains("true"))
						LineAns = "TRUE";
					else
						LineAns = "FALSE";
				}
				else
					LineAns += "\t Correct \t";
			}
			else{
				if(type.equals("TF"))				//If type is true/false don't get wrong answer
					LineAns = "";
				else
					LineAns += "\t Incorrect \t";
			}
				
		}

		return LineAns;
	}
	
	public String toString(){ //Return question and answer 
		return ansQuestion();
	}

}
