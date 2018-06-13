import java.awt.*;
import java.awt.event.*;
public class ex95m extends java.applet.Applet implements AdjustmentListener,ActionListener,ItemListener{
 Graphics screen;
 Scrollbar size,size2;
 int width,width2;//integers for 
 Checkbox mybox1,mybox2,mybox3,mybox4,mybox5,mybox6; //checkboxes variable
 CheckboxGroup mygroup,mygroup2; //this declares a checkboxgroup\
 Button red,blue;
 String buttonpressed,word,menuitem;
 Choice mymenubar;
 Color clr;

public void init() {
 setLayout(null);
 mymenubar=new Choice(); //initializes the new menubar
 mymenubar.addItem("square");//adds the items to menu
 mymenubar.addItem("oval");
 mymenubar.setBounds(0,120,20,100);
 mymenubar.addItemListener(this);//adds listener to menu
 add(mymenubar); //adds menu bar to the applet
 size=new Scrollbar(1,100,1,70,100);//initializing the scrollbar
 size.addAdjustmentListener(this);
 size.setBounds(30,10,20,100); //resizing the scrollbar
 add(size);
 size2=new Scrollbar(0,100,1,0,40);//initializing the scrollbar
 size2.addAdjustmentListener(this);
 size2.setBounds(30,150,100,20); //resizing the scrollbar
 add(size2);
 red=new Button("Red");
 red.addActionListener(this);
 red.setBounds(210,10,80,30);
 add(red);
 blue=new Button("Blue");
 blue.addActionListener(this);
 blue.setBounds(300,10,80,30);
 add(blue);
 width=50; //starting width of rectangle
 clr=Color.blue; //gives starting value for color
 mygroup=new CheckboxGroup(); //initializes the new checkboxgroup
 mybox1=new Checkbox("Red",mygroup,false); //initializes the checkboxes
 mybox2=new Checkbox("Blue",mygroup,false);
 mybox3=new Checkbox("Green",mygroup,false);
 mybox1.addItemListener(this); //adds a listener to checkbox
 mybox2.addItemListener(this); //adds a listener to checkbox
 mybox3.addItemListener(this); //adds a listener to checkbox
 mybox1.setBounds(5,10,10,10);
 mybox2.setBounds(5,40,10,10);
 mybox3.setBounds(5,70,10,10);
 add(mybox1); //add the checkboxes to the applet
 add(mybox2);
 add(mybox3);
 word="square";
 
 mygroup2=new CheckboxGroup(); //initializes the new checkboxgroup
 mybox4=new Checkbox("Red",mygroup2,false); //initializes the checkboxes
 mybox5=new Checkbox("Blue",mygroup2,false);
 mybox6=new Checkbox("Green",mygroup2,false);
 mybox4.addItemListener(this); //adds a listener to checkbox
 mybox5.addItemListener(this); //adds a listener to checkbox
 mybox6.addItemListener(this); //adds a listener to checkbox
 mybox4.setBounds(150,10,10,10);
 mybox5.setBounds(150,40,10,10);
 mybox6.setBounds(150,70,10,10);
 add(mybox4); //add the checkboxes to the applet
 add(mybox5);
 add(mybox6);
 
 menuitem="square";
 }
public void adjustmentValueChanged(AdjustmentEvent event) {
 width=size.getValue();
 width2=size2.getValue();
 repaint();
 }
public void itemStateChanged(ItemEvent event) {
 if (mybox1.getState()==true) {word="square";}
 if (mybox2.getState()==true) {word="circle";}
 if (mybox3.getState()==true) {word="rect";}
 if (mybox4.getState()==true) {clr = Color.RED;}
 if (mybox5.getState()==true) {clr = Color.DARK_GRAY;}
 if (mybox6.getState()==true) {clr = Color.MAGENTA;}
 menuitem=mymenubar.getSelectedItem(); 
		 
 
 repaint(); 
 }



public void actionPerformed(ActionEvent event){
 buttonpressed=event.getActionCommand();
 if (buttonpressed.equals("Red")){
 clr=Color.red;
 }
 if (buttonpressed.equals("Blue")){
 clr=Color.blue;
 }
 repaint();
 }//ends actionperformed
public void paint(Graphics screen) {
	
	if (word.equals("square")) {
		 screen.drawRect(60,50,100,100);}
		 else if (word.equals("circle")) {
		 screen.drawOval(60,50,100,100);}
		 else if (word.equals("rect")) {
			 screen.drawRect(80,50,40,100);}
		 else {screen.fillOval(0,110,100,100);}
	screen.fillOval(100,width,10,20);
	 screen.setColor(clr);
	 if (menuitem.equals("square")){
			screen.fillRect(100+width2,70,10,10);
			screen.fillRect(100-width2,70,10,10);
			}
		if (menuitem.equals("oval")){
			screen.fillOval(100+width2,70,10,10);
			screen.fillOval(100-width2,70,10,10);}
			
 screen.drawLine(100+width2,70,200,150);
 screen.drawLine(100-width2,70,200,150);
 screen.setFont( new Font ("Arial", Font.BOLD,50)); 
 screen.drawString("THOT",150,170);
 }//ends paint method
}//ends ex94b