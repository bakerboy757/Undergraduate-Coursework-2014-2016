import java.util.Random;
//knight extends enemy in order to fight the enemy with the fight method
public class Knight extends Enemy
{
	//private member data to hold knights attributes
	private static String name;
	//private static int hitpoints;
	

	

	//constructor
	public Knight()
	{
		super(name, 100);
	}
	

	@Override
	public String toString() {
		return "" + name;
	}

	/*
	public int randomHitPoints(){
		Random randomNum = new Random();
		hitpoints = 1 + randomNum.nextInt(100);
		return hitpoints;
	}
	
	*/
	//mutator function to set the name of the knight from user input
	public void setName(String name){
		Knight.name = name;
	}

	
	//functions to give output to main function
	public String getName(){
		return name;
	}
	
	
	
	//performs the background work for the fight sequence


	@Override
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



