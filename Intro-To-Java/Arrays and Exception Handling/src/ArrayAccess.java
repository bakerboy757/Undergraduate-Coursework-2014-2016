/*
Kelly, Tyler
COP-3252
Assignment 6
April 5, 2015
*/

// ArrayAccess.java
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class ArrayAccess extends JFrame 
{
   /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JTextField inputField;
   private JTextField retrieveField1;
   private JTextField retrieveField2;
   private JTextField outputField;
   private JPanel inputArea; 
   private JPanel retrieveArea;
   private JPanel outputArea;

   private int num;
   private int index = 0;
   private int array[] = new int[ 10 ];
   private String result, result2;
   
   // set up GUI
   public ArrayAccess()
   {
      super( "Accessing Array values" );
      setLayout( new FlowLayout() );
      
      // set up input Panel
      inputArea = new JPanel();
      inputArea.add( new JLabel( "Enter array elements here" ) );
      inputField = new JTextField( 10 );
      inputArea.add( inputField );
      inputField.addActionListener( 
         new ActionListener()
         {
            public void actionPerformed( ActionEvent e )
            {
            	try{
            		//initially puts number enterd at 0th index and then puts it in each one up from there
            		array[index] = Integer.parseInt(inputField.getText());
            		index++; 
            	}catch (NumberFormatException exc){
            		JOptionPane.showMessageDialog(null, "Please enter only integer values", "Invalid Input", JOptionPane.ERROR_MESSAGE);
						
            	}catch(ArrayIndexOutOfBoundsException ex){
            		JOptionPane.showMessageDialog(null, "Array may contain only 10 elements", "Array Full", JOptionPane.ERROR_MESSAGE);

            	}
               inputField.setText( "" );
            } // end method actionPerformed
         } // end anonymous inner class
      ); // end call to addActionListener
      
      // set up retrieve Panel
      retrieveArea = new JPanel( new GridLayout( 2, 2 ) );
      retrieveArea.add( new JLabel( "Enter number to retrieve" ) );
      retrieveField1 = new JTextField( 10 );
      retrieveArea.add( retrieveField1 );
      retrieveField1.addActionListener( 
         new ActionListener() 
         {
            public void actionPerformed( ActionEvent event ) 
            {
            	try{
            		boolean found = false;
            		String number = retrieveField1.getText();
            		num = Integer.parseInt(number);
            		result = "";
            		//goes through array to find number and at what index it is at
            		for (int i = 0; i < array.length; i++){
            			if(array[i] == num){
            				result += i + " ";
            				found = true;
            			}
            			
            		}
            		//throws exception if number not found
            		if(found == false){
            			throw new NumberNotFoundException();
            		}
            		outputField.setText(num + " was in these indices: " + result);
            		}catch (NumberNotFoundException e){
            			JOptionPane.showMessageDialog(null, e.getMessage(), "Not Found", JOptionPane.ERROR_MESSAGE);
            		}catch(NumberFormatException e){
                		JOptionPane.showMessageDialog(null, "Please enter only integer values", "Invalid Input", JOptionPane.ERROR_MESSAGE);
            		}
               retrieveField1.setText( "" );
            } // end method actionPerformed
         } // end anonymous inner class
      ); // end call to addActionListener
            
      retrieveArea.add( new JLabel( "Enter index to retrieve" ) );
      retrieveField2 = new JTextField( 10 );
      retrieveArea.add( retrieveField2 );
      retrieveField2.addActionListener(
         new ActionListener() 
         {
            public void actionPerformed( ActionEvent event )
            {
            	try{
            		//gets the text entered as a string value
            		String number = retrieveField2.getText();
            		//turns that string value into an int
            		num = Integer.parseInt(number);
            		//if the number wanted is out of bounds of the user entered array
            		//then throw exception
            		if(num >= index)
            			throw new ArrayIndexOutOfBoundsException();
            		//prints out number at that index
            	    outputField.setText(String.valueOf(array[num]));
            		}catch (NumberFormatException e){
            			JOptionPane.showMessageDialog(null, "Please enter only integer values", "Invalid Input", JOptionPane.ERROR_MESSAGE);
            		}catch(ArrayIndexOutOfBoundsException e){
                		JOptionPane.showMessageDialog(null, "Index Not Found", "Index Out of Bounds", JOptionPane.ERROR_MESSAGE);
            		}
               retrieveField2.setText( "" );
            } // end anonymous inner class
         } // end new ActionListener
      ); // end call to addActionListener
      
      // set up output Panel
      outputArea = new JPanel();
      outputArea.add( new JLabel( "Result" ) );
      outputField = new JTextField( 30 );
      outputField.setEditable( false );
      outputArea.add( outputField );

      add( inputArea );
      add( retrieveArea );
      add( outputArea );
   }  // end constructor
} // end class ArrayAccess