//to use dialog boxes
import javax.swing.JOptionPane;
public class KnightDriver {
	public static void main(String[] args)
	{
		//declaring knight and star objects
		Knight k1 = new Knight();
		Stars s1 = new Stars();
		
		//the following ask user for input in dialog boxes and then sets that information
		//in this case, set string "theName" to the input and then set that name via function call 
		//this same principle follows the next seven 
		String theName = JOptionPane.showInputDialog("What is the knights name?");
		k1.setName(theName);
		
		//must use parseInt to turn string into int
		String theHealth = JOptionPane.showInputDialog("What is the knights health?");
		k1.setHealth(Integer.parseInt(theHealth));
		
		String theNumberBattles = JOptionPane.showInputDialog("How many battles has the knight been in?");
		k1.setNumberBattles(Integer.parseInt(theNumberBattles));
		
		String theAge = JOptionPane.showInputDialog("How old is the knight?");
		k1.setAge(Integer.parseInt(theAge));
		
		String theAmountGold = JOptionPane.showInputDialog("How much gold does the knight have?");
		k1.setAmountGold(Integer.parseInt(theAmountGold));
		
		String theRow = JOptionPane.showInputDialog("How many rows of stars?");
		s1.setRow(Integer.parseInt(theRow));
		
		String theColumn = JOptionPane.showInputDialog("How many columns of stars?");
		s1.setColumn(Integer.parseInt(theColumn));

		//creates a variable string equal to the follwoing statements:
		String message = String.format("Knight Name: %s%n"
				+ "Knight Health: %d%n"
				+ "Knight Battles: %d%n"
				+ "Knight Age: %d%n"
				+ "Knight Gold: $%d"
				+ "%s",k1.getName(), k1.getHealth(),k1.getNumberBattles(),k1.getAge(),k1.getAmountGold(),s1.setStars());
		//prints out "message" into a dialog box
		JOptionPane.showMessageDialog(null, message);
	}
}
