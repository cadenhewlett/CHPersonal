import java.awt.*;
import java.awt.event.*;

@SuppressWarnings("deprecation")
public class unitExerQ2 extends java.applet.Applet implements ActionListener {
	
	//Define variables
	Graphics screen;
	TextField hemo, mcv, ferri, output;
	Label hemo_L, mcv_L, ferri_L;
	Button diagnosis;
	int hemo_I, mcv_I, ferri_I;
	
	public void init() {
		//Initialize Objects
		setLayout(null);
		hemo = new TextField(1);
		mcv = new TextField(1);
		ferri = new TextField(1);
		hemo_L = new Label("Hemoglobin: ");
		mcv_L = new Label("Mean Cell Volume: ");
		ferri_L = new Label("Ferritin: ");
		output = new TextField(5);
		diagnosis = new Button("Submit Diagnosis");
		hemo.setBounds(50, 0, 100, 50);
		hemo_L.setBounds(0, 0, 100, 25);
		mcv.setBounds(50, 75, 100, 50);
		mcv_L.setBounds(0, 75, 100, 25);
		ferri.setBounds(50, 150, 100, 50);
		mcv_L.setBounds(0, 150, 100, 25);
		output.setBounds(50, 300, 150, 150);
		diagnosis.setBounds(50, 200, 100, 25);
		diagnosis.addActionListener(this); //add an action listener
		add(hemo);
		add(hemo_L);
		add(mcv);
		add(mcv_L);
		add(ferri);
		add(ferri_L);
		add(output);
		add(diagnosis);

	}

	public void actionPerformed(ActionEvent event) { //when the diagnosis button is pressed
		//Converts TextField inputs into integers
		hemo_I = Integer.valueOf(hemo.getText());
		mcv_I = Integer.valueOf(mcv.getText());
		ferri_I = Integer.valueOf(ferri.getText());
		
		//Applies a set of conditionals to determine output
		if((hemo_I < 115) && (mcv_I < 80) && (ferri_I < 20)) {
			output.setText("This patient has iron deficiency.");
		}
		else if((hemo_I < 115) && (mcv_I < 80) && (ferri_I > 100)) {
			output.setText("This patient has anemia chronic disease.");
		}
		else {
			output.setText("This patient doesn't seem to have any iron related problems.");
		}
	}

}
