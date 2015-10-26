
public class InvalidDamageException extends Exception {
	/**
	 * 
	 */
	//serial used to get rid of warning
	private static final long serialVersionUID = 1L;

	public InvalidDamageException(){
		super();
	}
	//displays message to user if damage is below zero
	public InvalidDamageException(String message){
		super(message);
	}
}
