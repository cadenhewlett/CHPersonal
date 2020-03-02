import java.awt.*;
import java.awt.event.*;

public class mastery87 extends java.applet.Applet implements ActionListener {
	Graphics screen;
	TextField shape;
	Button submit;
	Label entershape;
	String shapeword; // this is to get the String the person typed in
	int shapeint; // this is to store the number when converting the String

	public void init() {
		setLayout(null);
		shape = new TextField(5);
		submit = new Button("Submit shape");
		entershape = new Label("Enter 1 for red, 2 for blue, or 3 for green");
		shape.setBounds(250, 10, 50, 20);
		submit.setBounds(330, 10, 80, 20);
		entershape.setBounds(0, 10, 240, 20);
		submit.addActionListener(this);
		add(shape);
		add(submit);
		add(entershape);
		shapeint = 1;
	}

	public void actionPerformed(ActionEvent event) {
		shapeword = shape.getText();// get the String from textfield
		if (shapeword == "Square") {
			shapeint = 1;
		} else if (shapeword == "Rectangle") {
			shapeint = 2;
		} else if (shapeword == "Oval") {
			shapeint = 3;
		}
		repaint(); // calls up the paint method again
	}

	public void paint(Graphics screen) {

		screen.setColor(Color.black);

		switch (shapeint) { // begin switch statement
		case 1:
			screen.fillRect(0, 0, 500, 500);// fill in a rectangle using the shape specified above
		case 2:
			screen.fillRect(0, 0, 500, 300);// fill in a rectangle using the shape specified above
		case 3:
			screen.fillOval(0, 0, 500, 300);
		default: // if any other number,the shape is black
			screen.fillRect(0, 0, 500, 500);// fill in a rectangle using the shape specified above
		}// ends switch statement
	}// ends paint method
}// ends class ex87