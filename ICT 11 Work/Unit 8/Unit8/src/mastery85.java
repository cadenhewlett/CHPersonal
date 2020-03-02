import java.awt.*;
import java.awt.event.*;
public class mastery85 extends java.applet.Applet implements ActionListener{
	TextField grade;
	TextArea output;
	Button submit;
	Label entergrade;
	String gradeword;
 	int gradeint;
 	public void init() {
 		setLayout(null);
 		grade=new TextField(5);
 		output=new TextArea(5,5);
 		submit=new Button("Press");
 		entergrade=new Label("Enter your grade");
 		grade.setBounds(100,10,50,20);
 		output.setBounds(50,50,250,150);
 		submit.setBounds(330,10,60,20);
 		entergrade.setBounds(0,10,97,20);
 		submit.addActionListener(this);
 		add(grade);
 		add(output);
 		add(submit);
 		add(entergrade);
 }
 public void actionPerformed(ActionEvent event) {
	 gradeword=grade.getText();
	 gradeint=Integer.valueOf(gradeword).intValue();
//here is the nested if..then statement
	 if (gradeint<50) {
		 output.setText("Your grade is an F"); }
	 else if (gradeint < 60 && gradeint > 50) {
		 output.setText("Your grade is a C-");}
	 else if (gradeint < 70 && gradeint > 60) {
		 output.setText("Your grade is a C");}
	 else if (gradeint< 80 && gradeint > 70) {
		 output.setText("Your grade is a C+");}
	 else if (gradeint< 90 && gradeint > 90) {
		 output.setText("Your grade is a B");}
	 else {output.setText("Your grade is an A");
	 }//end of nested if then
 }
}//ends class ex85