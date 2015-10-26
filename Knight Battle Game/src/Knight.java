import java.util.Random;
public class Knight 
{
	//private member data to hold knights attributes
	private String name;
	private int numWeapon, hitpoints, damage, armor;
	

	//constructor
	public Knight()
	{
	}
	
	public String randomNameGen(){
		Random randomNum = new Random();
		int randomNameNum = randomNum.nextInt(5);
		String randomName = "";
		switch (randomNameNum){
			case 0:   randomName = "Bob";   break;
			case 1:   randomName = "Shovel Knight";   break;
			case 2:   randomName = "Propeler Knight";   break;
			case 3:   randomName = "Polar Knight";   break;
			case 4:   randomName = "Plague Knight";   break;
		}
		return randomName;
		
	}
	//random number generators
	public int randomWeaponGen(){
		Random randomNum = new Random();
		int randomWeaponNum = 1 + randomNum.nextInt(4);
		return randomWeaponNum;
	}
	public int randomHitPoints(){
		Random randomNum = new Random();
		hitpoints = 1 + randomNum.nextInt(100);
		return hitpoints;
	}
	public int randomArmorGen(){
		Random randomNum = new Random();
		armor = 1 + randomNum.nextInt(4);
		return armor;
	}
	
	//mutator functions to set the attributes of the knight from user input
	public void setName(String name){
		this.name = name;
	}

	public void setWeapon(int numWeapon){
		this.numWeapon = numWeapon ;
	}
	public void setArmor(int armor){
		this.armor = armor;
	}
	//functions to give output to main function
	public String getName(){
		return name;
	}
	
	public String getWeapon(){
		String nameWeapon = "";
		switch (numWeapon){
			case 1:   nameWeapon = "Long Sword";   break;
			case 2:   nameWeapon = "Battle Axe";   break;
			case 3:   nameWeapon = "Spear";   break;
			case 4:   nameWeapon = "Warhammer";   break;
		}
		return nameWeapon;
	}
	public String getArmor(){
		String nameArmor = "";
		switch (armor){
			case 1:   nameArmor = "Iron";   break;
			case 2:   nameArmor = "Leather";   break;
			case 3:   nameArmor = "Fur";   break;
			case 4:   nameArmor = "Chainmail";   break;
		}
		return nameArmor;
		
	}
	//performs the background work for the fight sequence
	
	public int fight(){
		damage = 0;
		Random randomNum = new Random();
		switch (numWeapon){
			case 1:   
				switch (armor){
				//randomizes the hitdamage on iron armor, each weapon has same base damage with random damages added on
					case 1: damage = 6 + randomNum.nextInt(1); break;
					case 2: damage = 6 + randomNum.nextInt(3); break;
					case 3: damage = 6 + randomNum.nextInt(4); break;
					case 4: damage = 6 + randomNum.nextInt(2); break;
				} 				
				break;
			case 2:   
				switch (armor){
				//randomizes the hitdamage on leather armor, each weapon has same base damage with random damages added on
					case 1: damage = 7 + randomNum.nextInt(1); break;
					case 2: damage = 7 + randomNum.nextInt(3); break;
					case 3: damage = 7 + randomNum.nextInt(4); break;
					case 4: damage = 7 + randomNum.nextInt(2); break;
				} 		   
				break;
			case 3:   
				switch (armor){
				//randomizes the hitdamage on fur armor, each weapon has same base damage with random damages added on
					case 1: damage = 4 + randomNum.nextInt(2); break;
					case 2: damage = 4 + randomNum.nextInt(4); break;
					case 3: damage = 4 + randomNum.nextInt(5); break;
					case 4: damage = 4 + randomNum.nextInt(3); break;
					} 		  
				break;
			case 4:   
				switch (armor){
				//randomizes the hitdamage on chainmail armor, each weapon has same base damage with random damages added on
					case 1: damage = 8 + randomNum.nextInt(1); break;
					case 2: damage = 8 + randomNum.nextInt(4); break;
					case 3: damage = 8 + randomNum.nextInt(5); break;
					case 4: damage = 8 + randomNum.nextInt(3); break;
				} 		  
				break;
		}
		return damage;
	}

}


