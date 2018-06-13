import java.awt.*;
import java.awt.event.*;
public class buttons extends java.applet.Applet implements ActionListener {
 Button but1;
 String buttonpressed; //stores the label of the button
 int count, butnum, low, high;
 public void init() {
 but1=new Button("Button1");
 but1.addActionListener(this);
 count= 0;
 add(but1);
 
 }

public boolean contains(int number, int min, int max) {
		return (number >= min && number <= max);
	}
 public void actionPerformed(ActionEvent event){
	 
 //store the label of the button pressed in our String variable
	 Dimension d = getSize();
	 int[] countKeep = new int[(d.height+d.width)/2];
 buttonpressed=event.getActionCommand();

 //use an if then to determine which button has
 //been pressed. Display different messages for each button
 if (buttonpressed.equals("Button1")){count += 1;}
 if(count > 1) {count = 0;}
 if(buttonpressed.equals("Button1")) {

	 for(int count = 10,clr = 0;((count<d.width)||(count<d.height)); count += 10, clr++){
		 if(clr>6) {clr=0;}
		 butnum+=1;
		 Button but1;
		 but1=new Button(""+butnum);
		 countKeep[butnum] = butnum;
		 but1.setBounds(100,100,count,count);
		 but1.addActionListener(this);

		 switch(clr){
		 case 1:
			 but1.setBackground(Color.red);
			 break;
		 case 2:
			 but1.setBackground(Color.orange);
			 break;
		 case 3:
			 but1.setBackground(Color.yellow);
			 break;
		 case 4:
			 but1.setBackground(Color.green);
			 break;
		 case 5:
			 but1.setBackground(Color.blue);
			 break;
		 case 6:
			 but1.setBackground(Color.gray);
			 break;
		 default:
			 but1.setBackground(Color.magenta);
		 }
		 add(but1);
	 }
	 if(buttonpressed.equals(""+butnum)){
		 but1.setBackground(Color.white);
		 add(but1);
		 }
	 }
 }
 
 }
 //ends if statement
 //ends actionPerformed
//end ex82a