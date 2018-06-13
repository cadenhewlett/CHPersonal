import java.awt.*;
import java.awt.event.*;
public class testWork9Q2 extends java.applet.Applet implements AdjustmentListener,ActionListener,ItemListener{
 Graphics screen;
 Checkbox size1, size2, size3, size4;
 CheckboxGroup size;
 int width, length;
 Button red,blue;
 String buttonpressed;
 Color clr;

 public void init() {
	 setLayout(null);
	 size=new CheckboxGroup();//initializing the scrollbar
	 
	 size1 = new Checkbox("50x80", size, false);
	 size1.addItemListener(this);
	 add(size1);
	 
	 size2 = new Checkbox("100x100", size, false);
	 size2.addItemListener(this);
	 add(size2);
	 
	 size3 = new Checkbox("240x10", size, false);
	 size3.addItemListener(this);
	 add(size3);
	 
	 size4 = new Checkbox("75x300", size, false);
	 size4.addItemListener(this);
	 add(size4);
 
 width=50; //starting width of rectangle
 length=50;
 clr=Color.blue; //gives starting value for color
 }
 public void itemStateChanged(ItemEvent event) {
	 if (size1.getState()==true) {length=50; width = 80;}
	 if (size2.getState()==true) {length=100; width = 100;}
	 if (size3.getState()==true) {length=240; width = 10;} 
	 if (size4.getState()==true) {length=75; width = 300;} 
	 repaint();
 
 }
 public void adjustmentValueChanged(AdjustmentEvent event) {

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
	 screen.setColor(clr);
 screen.drawRect(100,100,width,length);
 }//ends paint method
}//ends testq2

