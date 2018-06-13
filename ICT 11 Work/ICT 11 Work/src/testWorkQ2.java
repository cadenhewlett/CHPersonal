import java.awt.*;
import java.awt.event.*;
import java.util.Random;
public class testWorkQ2 extends java.applet.Applet implements ItemListener{
 Graphics screen;
 Choice mymenubar;//menubar variable 
 Checkbox mybox1,mybox2,mybox3,mybox4; //checkboxes variable
 CheckboxGroup mygroup; //this declares a checkboxgroup
 String menuitem;
 int length, width;
 Color clr;
 public void init() {
 mymenubar=new Choice(); //initializes the new menubar
 mymenubar.addItem("Red");//adds the items to menu
 mymenubar.addItem("Blue");
 mymenubar.addItem("Green");
 mymenubar.addItem("RANDOM");
 mymenubar.addItemListener(this);//adds listener to menu
 add(mymenubar); 
 mygroup=new CheckboxGroup(); //initializes the new checkboxgroup
 mybox1=new Checkbox("50x50",mygroup,false); //initializes the checkboxes
 mybox2=new Checkbox("100x100",mygroup,false);
 mybox3=new Checkbox("10x200",mygroup,false);
 mybox4=new Checkbox("RANDOM",mygroup,false);
 mybox1.addItemListener(this); //adds a listener to checkbox
 mybox2.addItemListener(this); //adds a listener to checkbox
 mybox3.addItemListener(this); //adds a listener to checkbox
 mybox4.addItemListener(this); //adds a listener to checkbox
 add(mybox1); //add the checkboxes to the applet
 add(mybox2);
 add(mybox3);
 add(mybox4);
 
 width = 50;
 length = 100;
 clr=Color.white; //initial value for clr variable
 }
 public void itemStateChanged(ItemEvent event) {
//the if checks to see if the checkbox has been clicked. If it is selected, then getstate is true, then
//we will change thecolor accordingly
Random randomNum = new Random(); //new random
int max = 850;
int min = 20;
menuitem=mymenubar.getSelectedItem(); //gets the name of the current selected

 if (mybox1.getState()==true) {
	 width = 50;
	 length = 50;
	}
 if (mybox2.getState()==true) {
	 width = 100;
	 length = 100;
	 }
 if (mybox3.getState()==true) {
	 width = 10;
	 length = 700;
	 }
 if (mybox4.getState()==true) {
	 width = min + randomNum.nextInt(max); //width is the sum of the minimum plus a random num in the range of max
	 length = min + randomNum.nextInt(max); //length is the sum of the minimum plus a random num in the range of max
	 }
 if (menuitem.equals("Red")){
 clr=Color.red; //sets shape clr to red if menu item is selected
 }
 else if (menuitem.equals("Blue")){
 clr=Color.blue; //sets shape clr to blue if menu item is selected
 }
 else if (menuitem.equals("Green")){
 clr=Color.green; //sets shape clr to green if menu item is selected
 }
 else if (menuitem.equals("RANDOM")){
	 int min2 = 0; //minimum RGB value
	 int max2 = 255;//maximum RGB value
	 int r = min2 + randomNum.nextInt(max2); //r is the sum of the minimum plus a random num in the range of max
	 int g = min2 + randomNum.nextInt(max2); //g is the sum of the minimum plus a random num in the range of max
	 int b = min2 + randomNum.nextInt(max2); //b is the sum of the minimum plus a random num in the range of max
	 clr=new Color(r, g, b);
 }//ends if
 repaint(); //call//calls up the paint method again, so new color is shown
 } //ends itemStateChanged Method
 public void paint(Graphics screen) {
 screen.setColor(clr);
 screen.fillRect(0,0,width,length);
 }
} //ends ex93
