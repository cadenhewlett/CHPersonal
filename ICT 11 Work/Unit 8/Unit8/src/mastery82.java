import java.awt.*;
import java.awt.event.*;

/**
 * 
 */

/**
 * @author Caden H
 *
 */
public class mastery82 extends java.applet.Applet implements ActionListener{

	/**
	 * 
	 */
	TextField grade;
	TextArea output;
	Button submit;
	Label enter_grade;
	String grade_word;
	int grade_int;
	
	public void init() {
		setLayout(null); 
		grade=new TextField(5);
		output=new TextArea(5,5);
		submit=new Button("Press");
		enter_grade=new Label("Please Enter Your Grade");
		grade.setBounds(100,10,50,20);
		output.setBounds(50,50,250,150);
		submit.setBounds(160,10,60,20);
		enter_grade.setBounds(0,10,100,25);
		submit.addActionListener(this); 
		add(grade);
		add(output);
		add(submit);
		add(enter_grade);
	}
	public void actionPerformed(ActionEvent event) {
		grade_word=grade.getText();
		grade_int=Integer.valueOf(grade_word).intValue();
		
		if (grade_int>95) { 
			output.setText("Great Job!");	}  //end of instructions if condition is true
		else {  //if condition is false
			output.setText("You can do better!"); 
		}

	}

}
