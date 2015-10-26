import java.util.*;
//knight is a subclass of enemy
public abstract class Enemy {

	
	protected int health;
	protected  String name;
	
	
	//default constructor
	public Enemy(){}
	//constructor
	public Enemy(String name, int health){
		this.health = health;
		this.name = name;
	}
	//accessors and mutators
	public void setName(String name){
		this.name = name;
	}
	public void setHealth(int health){
		this.health = health;
	}
	//throws standard exception
	public String getName()throws IllegalArgumentException{
		if (name == null)
			throw new IllegalArgumentException();
		else
			return name;
	}
	public int getHealth(){
		return health;
	}
	//overlaods Objects toString method
	public String toString(){
		return "" + this.name;
	}
	//overloaded in subclasses
	public abstract int fight(Enemy enemyType);
	//throws custom exception
	//causes damage to calling object
	public void takeDamage(int damage) throws InvalidDamageException {
		if(damage < 0)
			throw new InvalidDamageException("Damage less than zero");
		else{
			health -= damage;
		}
		
	}
	//returns random enemy object(using random number generator
	//which it instantiates from one of the three implementations
	//AKA static method factory
	public static Enemy getRandomEnemy(){
		Random randomNum = new Random();
		int randomEnemy = randomNum.nextInt(3);
		
		switch (randomEnemy){
			case 2:   return new Ogre();
			case 1:   return new Werewolf();
			case 0:   return new Vampire(); 
			default: return null;
		}
	}	
	



		
}

