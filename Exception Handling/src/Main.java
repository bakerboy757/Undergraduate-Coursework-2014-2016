
import java.util.Random;

import javax.swing.JOptionPane;

public class Main {
	public static void main(String[] args){
	//creates our hero character
	Knight k1 = new Knight();
	
	int gameCounter = 1;
	
	//checks to see if user wants to play again(runs first time)
	//maainLoop: used her to break out of game if cause arises
	mainLoop:
	while(k1.getHealth() > 0 && gameCounter <= 2){
		if(gameCounter == 1){
			String theName = JOptionPane.showInputDialog("Welcome to KnightFight!\nEnter the name of your knight:");
			k1.setName(theName);
		}
		//creates our enemies
		Enemy enemyType1 = Enemy.getRandomEnemy(); 
		Enemy enemyType2 = Enemy.getRandomEnemy(); 
		Enemy enemyType3 = Enemy.getRandomEnemy();
		
		//sees how many enemies we will face
		Random randomNum = new Random();
		int ranNumEnemies = 1 + randomNum.nextInt(3);
	
		String message1 = String.format("Your Knight walks through the wretched JavaBean Forest and encounters %d enemies %n"
										+"You pull out your weapon and our ready to fight!",ranNumEnemies);
		JOptionPane.showMessageDialog(null, message1);
	
		int count = 1;
		fightLoop:
		while(k1.getHealth() > 0){
			//this switch will run for each enemy, if there our three enemies then it will run for all of them
			//each enemy attacks our knight on each go, and our knight attacks each enemy on each go
			switch(ranNumEnemies){
				case 3: if(enemyType3.getHealth() > 0){
							enemyType3.fight(k1); 
							k1.fight(enemyType3);
						}
				case 2: if(enemyType2.getHealth() > 0){
							enemyType2.fight(k1); 
							k1.fight(enemyType2);
						}
				case 1: if(enemyType1.getHealth() > 0){
							enemyType1.fight(k1); 
							k1.fight(enemyType1);
						}	
			}
			//displays round information
			String round = String.format("Round %d\n\nYour Knight's Hitpoints: %d%n", count, k1.getHealth());
			switch (ranNumEnemies){
				case 3: round += String.format("%s's Hitpoints: %d%n", enemyType3, enemyType3.getHealth());
				case 2: round += String.format("%s's Hitpoints: %d%n", enemyType2, enemyType2.getHealth());
				case 1: round += String.format("%s's Hitpoints: %d%n", enemyType1, enemyType1.getHealth());
			}
			JOptionPane.showMessageDialog(null, round);	
			//checks to see if enemies our alive
			switch(ranNumEnemies){
				case 3: {if(enemyType1.getHealth() <= 0 && enemyType2.getHealth() <= 0 && enemyType3.getHealth() <= 0)
						break fightLoop;} 
				case 2:	{if(enemyType1.getHealth() <= 0 && enemyType2.getHealth() <= 0)
							break fightLoop;} 
				case 1: {if(enemyType1.getHealth() <= 0 )
						break fightLoop;} break;
				default: continue;
			}
			count++;
		}//end of fight loop
		//displays status of game:
		String message2 = "";
		String message3 = "";
		String message4 = "";
		if(k1.getHealth() > 0 && gameCounter < 2){
			message2 = String.format("Congrats! You beat %d wave of enemies! Prepare for your next Battle!", gameCounter);
			JOptionPane.showMessageDialog(null, message2);
		}
		else if(k1.getHealth() > 0 && gameCounter == 2){
			message3 = String.format("Congrats! You made it through the forest!");
			JOptionPane.showMessageDialog(null, message3);
		}
		else if(k1.getHealth() <= 0){
			message4 = String.format("You were Killed, %n"
					+ "Game Over");
			JOptionPane.showMessageDialog(null, message4);
			break mainLoop;
		}
								
		gameCounter++;
	}
		
	}
	
}

