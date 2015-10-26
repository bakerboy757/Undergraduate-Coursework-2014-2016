
import java.util.Random;
import javax.swing.JOptionPane;

public class KnightDriver {
	public static void main(String[] args){
	
	Knight k1 = new Knight();
	Knight k2 = new Knight();
	String answer = "yes";
	//checks to see if user wants to play again(runs first time)
	while(answer.equals("yes")){
		//sets your knights data
		String theName = JOptionPane.showInputDialog("Welcome to KnightFight!\nEnter the name of your knight:");
		k1.setName(theName);
		
		String theWeapon =JOptionPane.showInputDialog("Now select your weapon! (Choose number)\n1) Long Sword\n2) Battle Axe\n3) Spear\n4) Warhammer\nYour choice my liege?:");
		k1.setWeapon(Integer.parseInt(theWeapon));
		
		String theAutoGenerate = JOptionPane.showInputDialog("Would you like to auto generate your opponent? (yes|no)");
		//autogenerates knight
		if (theAutoGenerate.equals("yes") || theAutoGenerate.equalsIgnoreCase("y")){
			k2.setName(k2.randomNameGen());
			k2.setWeapon(k2.randomWeaponGen());
		}
		//lets you create your knight
		else {
			String oppName = JOptionPane.showInputDialog("What is the name of your enemy?");
			k2.setName(oppName);
			String oppWeapon =JOptionPane.showInputDialog("Now select your enemy's weapon! (Choose number)\n1) Long Sword\n2) Battle Axe\n3) Spear\n4) Warhammer\nYour choice my liege?:");
			k2.setWeapon(Integer.parseInt(oppWeapon));
		}
	    //randomizes starting health of each knight
		int k1Health = k1.randomHitPoints();
		int k2Health = k2.randomHitPoints();
		k1.setArmor(k1.randomArmorGen());
		k2.setArmor(k2.randomArmorGen());
		
		//displays info on each knight
		String message = String.format("Your Knight's Name: %s%n"
				+ "Your Knight's Weapon: %s%n"
				+ "Your Knight's Hitpoints: %d%n"
				+ "Your Knight's armor type: %s%n"
				+ "\n"
				+ "Your Enemy's Name: %s%n"
				+ "Your Enemy's Weapon: %s%n"
				+ "Your Enemy's Hitpoints: %d%n"
				+ "Your Enemy's armor type: %s%n"
				,k1.getName(), k1.getWeapon(), k1Health,k1.getArmor(), k2.getName(), k2.getWeapon(), k2Health, k2.getArmor());
		JOptionPane.showMessageDialog(null, message);
		//checks to see if user still wants to play
		String cont = JOptionPane.showInputDialog("Press 'y' to continue or press 'n' to exit the application");
		if (cont.equals("n"))
			System.exit(0);
		//chooses a random knight to go first
		Random randomNum = new Random();
		int ranKnightNum = randomNum.nextInt(2);
		//used to count round number
		int count = 1;
		//enemy goes first
		if (ranKnightNum == 0){
			while(k1Health > 0 && k2Health > 0)
			{	
				if (count == 1)
					JOptionPane.showMessageDialog(null, "Your enemy starts the battle!");
				//damage done to knight health
				k1Health -= k2.fight();
				k2Health -= k1.fight();
				String round = String.format("Round %d\n\nYour Knight's Hitpoints: %d%n"
						+ "Your Enemy's Hitpoints: %d%n", count, k1Health, k2Health);
				JOptionPane.showMessageDialog(null, round);
				count++;
			}
		}
		//your knight goes first
		else{
			while(k1Health > 0 && k2Health > 0)
			{
				if (count == 1)
					JOptionPane.showMessageDialog(null, "You start the battle!");
				k2Health -= k1.fight();
				k1Health -= k2.fight();
				String round = String.format("Round %d\n\nYour Knight's Hitpoints: %d%n"
						+ "Your Enemy's Hitpoints: %d%n", count, k1Health, k2Health);
				JOptionPane.showMessageDialog(null, round);		
				count++;
			}
		}
		//if both knights die at same time
		if (k1Health <=0 && k2Health <=0 && k1Health == k2Health)
			JOptionPane.showMessageDialog(null, "T'was a marvelous Batlle!\n You killed eachother at the same time!");	
		//if your health falls below zero
		if (k1Health <= 0)
			JOptionPane.showMessageDialog(null, "Your enemy is the winner!");	
		//if enemy health falls below zero
		else if(k2Health <= 0)
			JOptionPane.showMessageDialog(null, "You are the winner!");
		
		answer = JOptionPane.showInputDialog("Do you want to play again? (yes|no)");
		
		}
	
	}
}
