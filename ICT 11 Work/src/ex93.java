import java.awt.*;
import java.awt.event.*;
public class ex93 extends java.applet.Applet implements ItemListener{
	Graphics screen;
	Checkbox mybox1,mybox2,mybox3, mybox4; //checkboxes variable
	CheckboxGroup mygroup; 
	int shape;
 public void init() {
 mygroup=new CheckboxGroup(); //initializes the new checkboxgroup
 mybox1=new Checkbox("Oval",mygroup,false); //initializes the checkboxes
 mybox2=new Checkbox("Sqaure",mygroup,false);
 mybox3=new Checkbox("Circle",mygroup,false);
 mybox4= new Checkbox("RoundSquare",mygroup,false);
 mybox1.addItemListener(this); //adds a listener to checkbox
 mybox2.addItemListener(this); //adds a listener to checkbox
 mybox3.addItemListener(this); //adds a listener to checkbox
 mybox4.addItemListener(this);
 add(mybox1); //add the checkboxes to the applet
 add(mybox2);
 add(mybox3);
 add(mybox4);
 shape = 0;
 //initial value for clr variable
 }
 public void itemStateChanged(ItemEvent event) {
//the if checks to see if the checkbox has been clicked. If it is selected, then getstate is true, then
//we will change thecolor accordingly
 if (mybox1.getState()==true) {shape = 1;}
 else if (mybox2.getState()==true) {shape = 2;}
 else if (mybox3.getState()==true) {shape = 3;}
 else if (mybox4.getState()==true) {shape = 4;}
 else {}
 repaint(); //calls up the paint method again, so new color is shown
 } //ends itemStateChanged Method
 public void paint(Graphics screen) {
	 screen.setColor(Color.MAGENTA);
	 switch(shape) {
	 	case 1:
	 		screen.fillOval(100, 100, 50, 150);
	 		break;
	 	case 2:
	 		screen.fillRect(100, 100, 100, 100);
	 		break;
	 	case 3:
	 		screen.fillOval(100, 100, 100, 100);
	 		break;
	 	case 4:
	 		screen.fillRoundRect(100, 100, 100, 100, 10, 10);
	 		break;
	 	default:
	 		screen.setColor(Color.WHITE);
	 		screen.drawRect(0, 0, 10, 10);
	 		break;

}
 }
} //ends ex93