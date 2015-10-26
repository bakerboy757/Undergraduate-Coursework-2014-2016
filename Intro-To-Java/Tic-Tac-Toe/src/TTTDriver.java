import java.util.Scanner;
public class TTTDriver {
	
	public static void main(String[] args) {
		//these variables serve as basic menu options
		String playAgain = "yes",
			   comp = "no",
			   compDiff = "easy";
	
		do{//this is the main do while loop that asks the menu related questions and repeats if the user want to play again
			TicTacToe t1 = new TicTacToe();//new board
			System.out.println("Do you want to play vs. a computer? (yes|no): ");
			Scanner scn = new Scanner(System.in);
			comp = scn.nextLine();
			if (comp.equals("yes")){
				System.out.println("Do you want to play vs. an advanced computer"
						+ " or an easy computer? (adv|easy): ");
				Scanner scn1 = new Scanner(System.in);
				compDiff = scn1.nextLine();
			}
			
			do{
				System.out.printf("Player X make a move in form of 'num1 num2': ");
				Scanner input = new Scanner(System.in);
		
				int xCoord1 = input.nextInt();
				int xCoord2 = input.nextInt();
				//checks to make sure user entered valid points that are in bounds
				if (xCoord1 >= 3 ||xCoord2 >= 3 || xCoord1 < 0 || xCoord2 < 0){
					System.out.printf("Enter a valid position Player X: ");
					Scanner input1 = new Scanner(System.in);
					
					xCoord1 = input1.nextInt();
					xCoord2 = input1.nextInt();
				}
				//sets these coordinates
				t1.setX(xCoord1);
				t1.setY(xCoord2);
				//checks to make sure space is empty for user to place there
				if (t1.validPosition() == false){
					while (t1.validPosition() == false){
						System.out.printf("Enter a valid position Player X: ");
						Scanner input1 = new Scanner(System.in);
						
						xCoord1 = input1.nextInt();
						xCoord2 = input1.nextInt();
						
						t1.setX(xCoord1);
						t1.setY(xCoord2);
					}
				}
				//sends the coordinates to the board
				t1.printToBoardX();
				//if that was winning move then show that they won
				if (t1.checkWin() == true){
					int w = 1;
					t1.setWinner(w);
					break;
				}
				//displays board after each player turn (doesnt print twice if comp is playing)
				if(comp.equals("no"))
					t1.displayBoard();
				if(comp.equals("yes")){
					if(compDiff.equals("adv")){
						t1.advancedComp();
						t1.displayBoard();
						if (t1.checkWin() == true){
							int w = -1;
							t1.setWinner(w);
							break;
						}
						if(t1.isBoardFull() == true){
							int w = 0;
							t1.setWinner(w);
							break;
						}
							
					}
					else if(compDiff.equals("easy")){
						t1.badComputer();
						t1.displayBoard();
						if (t1.checkWin() == true){
							int w = -1;
							t1.setWinner(w);
							break;
						}
						if(t1.isBoardFull() == true){
							int w = 0;
							t1.setWinner(w);
							break;
						}
					}
				}
				//player two option
				//has same steps as before for player x
				if(comp.equals("no")){
				
					System.out.printf("Player O make a move in form of 'num1 num2': ");
					Scanner input2 = new Scanner(System.in);
					
					int oCoord1 = input2.nextInt();
					int oCoord2 = input2.nextInt();
					if (xCoord1 >= 3 ||xCoord2 >= 3 || xCoord1 < 0 || xCoord2 < 0){
						System.out.printf("Enter a valid position Player X: ");
						Scanner input1 = new Scanner(System.in);
						
						xCoord1 = input1.nextInt();
						xCoord2 = input1.nextInt();
					}
					t1.setX(oCoord1);
					t1.setY(oCoord2);
					if (t1.validPosition() == false){
						while (t1.validPosition() == false){
							System.out.printf("Enter a valid position Player O: ");
							Scanner input3 = new Scanner(System.in);
							
							oCoord1 = input3.nextInt();
							oCoord2 = input3.nextInt();
							
							t1.setX(oCoord1);
							t1.setY(oCoord2);
						}
					}
					t1.printToBoardO();
					if (t1.checkWin() == true){
						int w2 = -1;
						t1.setWinner(w2);
						break;
					}	
					t1.displayBoard();
				}//endplayer 2 while loop
				
			}while(t1.checkWin() == false || t1.isBoardFull() == true);//as long as the game is not over, keep repeating
			t1.displayBoard();
			
			System.out.printf("Would you like to play again? (yes|no): ");
			Scanner input4 = new Scanner(System.in);
			playAgain = input4.nextLine();
			}while(playAgain.equals("yes"));
	}
}

