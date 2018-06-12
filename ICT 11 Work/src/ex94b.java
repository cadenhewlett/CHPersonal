import java.awt.*;
import java.awt.event.*;
public class ex94b extends java.applet.Applet implements AdjustmentListener,ActionListener{
 Graphics screen;
 Scrollbar size;
 int width;
 Button red,blue;
 String buttonpressed;
 Color clr;

 public void init() {
 setLayout(null);
 size=new Scrollbar(0,50,1,0,100);//initializing the scrollbar
 size.addAdjustmentListener(this);
 size.setBounds(100,10,100,20); //resizing the scrollbar
 add(size);
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
 }
 public void adjustmentValueChanged(AdjustmentEvent event) {
 width=size.getValue();
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
 screen.drawRect(100,100,width,50);
 }
}//ends paint m