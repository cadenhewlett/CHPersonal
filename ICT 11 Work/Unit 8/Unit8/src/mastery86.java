import java.awt.*;
import java.awt.event.*;

public class mastery86 extends java.applet.Applet implements ActionListener {
	Graphics screen;
	TextField color, topbottom;
	int ymod;
	Button submit;
	Label entercolor, entertopbottom;
	String colorword, topbottomword;
	Color clr; // this is a variable of type color it stores different basic Java colors

	public void init() {
		setLayout(null);
		color = new TextField(5);
		topbottom = new TextField(5);
		submit = new Button("Submit Color");
		entertopbottom = new Label("Enter Top or Bottom");
		entercolor = new Label("Enter red, blue, or green");
		color.setBounds(200, 10, 50, 20);
		topbottom.setBounds(200, 60, 50, 20);
		submit.setBounds(330, 10, 80, 20);
		entercolor.setBounds(50, 10, 150, 20);
		entertopbottom.setBounds(50, 60, 150, 20);
		submit.addActionListener(this);
		add(color);
		add(topbottom);
		add(submit);
		add(entertopbottom);
		add(entercolor);
		clr = Color.white;
	}

	public void actionPerformed(ActionEvent event) {
		colorword = color.getText();
		if (colorword.equals("red")) {
			clr = Color.red;
		} else if (colorword.equals("blue")) {
			clr = Color.blue;
		} else if (colorword.equals("green")) {
			clr = Color.green;
		} else {
			clr = Color.black;
		} // ends nested if..then
		
		topbottomword = topbottom.getText();
		if(topbottomword.equals("bottom")) {
			ymod = 0;
		}
		else if(topbottomword.equals("top")) {
			ymod = 50;
		}
		else {
			ymod = 25;
		}
		repaint(); // calls up the paint method,shows new color
	}

	public void paint(Graphics screen) {
		screen.setColor(clr);
		screen.fillRect(0, ymod, 500, 400);
	}// ends paint method
}// ends class ex86
