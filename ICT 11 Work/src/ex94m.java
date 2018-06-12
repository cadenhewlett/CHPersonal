import java.applet.*;
import java.awt.*;
import java.awt.event.*;
 
 
public class ex94m extends Applet implements ActionListener
{
    Label nameLabel;
    Label genderLabel;
    Label ageLabel;
    Label highesteducationLabel;
    Label degreeselectLabel;
    Label skilllevelLabel;
    Label whenstartLabel;
     
    TextField nameInput;
    Button submit;
    Button clear;
     
    Choice ageInput;
    Choice highesteducationInput;
    Choice degreeselectInput;
    Choice whenstartInput;
     
    CheckboxGroup genderInput;
    CheckboxGroup skilllevelInput;
     
    String name;
    String gender;
    String age;
    String highesteducation;
    String degreeselect;
    String skilllevel;
    String whenstart;
     
     
    public void init() 
    {
        setSize(600, 400);
         
        nameLabel = new Label ("Enter your name: ");
        genderLabel = new Label ("Select your gender: ");
        ageLabel = new Label ("Select your age: ");
        highesteducationLabel = new Label ("Select your highest education: ");
        degreeselectLabel = new Label ("Select the degree you wish to pursue: ");
        skilllevelLabel = new Label ("Select your skill level in the culinary field: ");
        whenstartLabel = new Label ("Select how soon you are able to start: ");
         
        nameInput = new TextField(10);
        submit = new Button("Submit");
        clear = new Button("Clear");
         
        genderInput = new CheckboxGroup();
        skilllevelInput = new CheckboxGroup();
         
        ageInput = new Choice();
        ageInput.addItem("15");
        ageInput.addItem("16");
        ageInput.addItem("17");
        ageInput.addItem("18");
        ageInput.addItem("19");
        ageInput.addItem("20");
        ageInput.addItem("21");
        ageInput.addItem("21 - 25");
        ageInput.addItem("26 - 30");
        ageInput.addItem("31 to 40");
        ageInput.addItem("41 to 50");
        ageInput.addItem("50 and older");
         
        highesteducationInput = new Choice();
        highesteducationInput.addItem("GED");
        highesteducationInput.addItem("High School");
        highesteducationInput.addItem("Some College");
        highesteducationInput.addItem("Associate Degree");
        highesteducationInput.addItem("College Degree");
        highesteducationInput.addItem("Post-Graduate Degree");
         
        degreeselectInput = new Choice();
        degreeselectInput.addItem(" Le Cordon Bleu Culinary Arts");
        degreeselectInput.addItem("Patisserie and Baking");
         
        whenstartInput = new Choice();
        whenstartInput.addItem("1 Week");
        whenstartInput.addItem("1 Month");
        whenstartInput.addItem("3 Months");
        whenstartInput.addItem("6 Months");
        whenstartInput.addItem("more than 6 Months");
 
        add(nameLabel);
        add(nameInput);
         
        add(genderLabel);
        add(new Checkbox ("Male", genderInput, true));
        add(new Checkbox ("Female", genderInput, false));
         
        add(ageLabel);
        add(ageInput);
         
        add(highesteducationLabel);
        add(highesteducationInput);
         
        add(degreeselectLabel);
        add(degreeselectInput);
         
        add(skilllevelLabel);
        add(new Checkbox ("Begginer", skilllevelInput, true));
        add(new Checkbox ("Advanced", skilllevelInput, false));
         
        add(whenstartLabel);
        add(whenstartInput);
         
         
        add(submit);
         
        submit.addActionListener(this);
         
        add(clear);
         
        clear.addActionListener(this);
    }
    public void paint(Graphics g)
    {
        g.drawString("Name: " + name, 10, 150);
        g.drawString("Gender: " + gender, 10, 180);
        g.drawString("Age: " + age, 10, 210);
        g.drawString("Highest Education: " + highesteducation, 10, 240);
        g.drawString("Preferred Degree: " + degreeselect, 10, 270);
        g.drawString("Skill Level: " + skilllevel, 10, 300);
        g.drawString("Start Time: " + whenstart, 10, 330);
         
         
    }
     
    public void actionPerformed(ActionEvent e)
    {
        name = nameInput.getText();
        gender = genderInput.getSelectedCheckbox().getLabel();
        age = ageInput.getSelectedItem(); 
        highesteducation = highesteducationInput.getSelectedItem();
        degreeselect = degreeselectInput.getSelectedItem();
        skilllevel = skilllevelInput.getSelectedCheckbox().getLabel();
        whenstart = whenstartInput.getSelectedItem();
         
        if (e.getSource() == clear)
        {
        }
         
        repaint();
    }
     
}