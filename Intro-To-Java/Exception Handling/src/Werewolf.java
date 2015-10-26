import java.util.Random;


public class Werewolf extends Enemy{

	//private static String randomName;
	//private static int randomHealth;
	public Werewolf(){
		super("Dark Hunter The WereWolf", 20);	
		
	}
	/*
	public static String getRandomName(){
		return randomName;
	}
	
	public String randomNameGen(){
		Random randomNum = new Random();
		int randomNameNum = randomNum.nextInt(5);
		String randomName = "";
		switch (randomNameNum){
		case 0:   randomName = "Dark Hunter The WereWolf";   break;
		case 1:   randomName = "Savage Crescent The Werewolf";   break;
		case 2:   randomName = "Lone Paw The WereWolf";   break;
		case 3:   randomName = "Cruel Omega The WereWolf";   break;
		case 4:   randomName = "Dark Warrior The WereWolf";   break;
		}
		return randomName;
		
		
	}
	public static int getRandomHealth(){
		return randomHealth;
	} 
	public int randomHitPoints(){
		Random randomNum = new Random();
		randomHealth = 1 + randomNum.nextInt(30);
		return randomHealth;
	}
	
*/
	@Override
	public String toString() {
		super.toString();
		return "Dark Hunter The WereWolf";
	}
	@Override
	public int fight(Enemy e1) {
		int damage = 0;
		Random randomNum = new Random();
		damage = 10 + randomNum.nextInt(1);
		try {
			e1.takeDamage(damage);
		} catch (InvalidDamageException e) {
			e.printStackTrace();
		}
		return damage;
	}

}

