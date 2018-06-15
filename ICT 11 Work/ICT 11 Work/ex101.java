import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
public class ex101 extends java.applet.Applet implements ActionListener {
 int counter, total, num, count;
 Button but1;
 String buttonpressed;
 TextArea output;
 TextField input;
 public void init() { 
 but1=new Button("Button1");
 but1.addActionListener(this);
 add(but1);
 
 input = new TextField(5);
 input.setBounds(10, 10, 25, 50);
 add(input);
 
 output=new TextArea(10,30);
 add(output);
 }//ends init
 public void actionPerformed(ActionEvent event){
	 output.setText("");
	 buttonpressed=event.getActionCommand();
	 if(buttonpressed.equals("Button1")) {
		 num=Integer.valueOf(input.getText()).intValue();
     for (int counter=1;counter<10;counter=counter+1) {
		 total=counter*num;
		 output.append(""+num+"*"+counter+"="+total+"\n");
	 }
 }
	 
 //ends for loop
 }//ends doloop method
}//ends class 102b