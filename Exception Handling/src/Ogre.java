import java.util.Random;

//same process in all 4 subclasses
//commenting out code instead of deleting to work on later
public class Ogre extends Enemy{

	//private static String randomName;
	//private static int randomHealth;
	//unfortunately set to const values as I could not make the random variables work correctly
	public Ogre(){
		super("Broig The Ogre", 30);
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
			case 0:   randomName = "Broig The Ogre";   break;
			case 1:   randomName = "Veirth The Ogre";   break;
			case 2:   randomName = "Trigrut The Ogre";   break;
			case 3:   randomName = "Negrok The Ogre";   break;
			case 4:   randomName = "Wiluzrog The Ogre";   break;
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
		return "Broig The Ogre";
	}
	@Override
	//returns a damage in that will be used in take damage mthod
	public int fight(Enemy e1) {
		int damage = 0;
		Random randomNum = new Random();
		damage = 6 + randomNum.nextInt(4);
		try {
			e1.takeDamage(damage);
		} catch (InvalidDamageException e) {
			e.printStackTrace();
		}
		return damage;
	}

}

	

