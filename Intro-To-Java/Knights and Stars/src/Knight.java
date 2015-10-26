
public class Knight 
{
	//private member data to hold knights attributes
	private String name;
	private int health,
				numberBattles,
				age,
				amountGold;
	//default constructor
	public Knight()
	{}
	//constructor
	public Knight(String name, int health, int numberBattles, int age, int amountGold)
	{
		this.name = name;
		this.health = health;
		this.numberBattles = numberBattles;
		this.age = age;
		this.amountGold = amountGold;
	}
	//mutator functions to set the attributes of the knight from user input
	public void setName(String name){
		this.name = name;
	}
	
	public void setHealth(int health){
		this.health = health;
	}

	public void setNumberBattles(int numberBattles){
		this.numberBattles = numberBattles;
	}
	public void setAge(int age){
		this.age = age;
	}
	public void setAmountGold(int amountGold){
		this.amountGold = amountGold;
	}
	//accessor functions to give output to main function
	public String getName(){
		return name;
	}
	
	public int getHealth(){
		return health;
	}
	public int getNumberBattles(){
		return numberBattles;
	}
	public int getAge(){
		return age;
	}
	public int getAmountGold(){
		return amountGold;
	}
	
}

