import java.util.Random;


public class Vampire extends Enemy{

	//private static String randomName;
	//private static int randomHealth;
	public Vampire(){
		super("Ciro The Vampire", 15);
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
		case 0:   randomName = "Ciro The Vampire";   break;
		case 1:   randomName = "Arnoldo The Vampire ";   break;
		case 2:   randomName = "Fino The Vampire";   break;
		case 3:   randomName = "Egidio The Vampire";   break;
		case 4:   randomName = "Emilio The Vampire";   break;
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
		return "Ciro The Vampire" ;
	}
	@Override
	public int fight(Enemy e1) {
		int damage = 0;
		Random randomNum = new Random();
		damage = 3 + randomNum.nextInt(10);
		try {
			e1.takeDamage(damage);
		} catch (InvalidDamageException e) {
			e.printStackTrace();
		}
		return damage;
	}

}




