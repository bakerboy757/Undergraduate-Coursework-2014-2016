import java.util.Random;
public class TicTacToe {
	//constants used
	//got idea for enum from book assignment pg 358
	public enum Tiles {
		X,
		O,
		E;
	}
	//makes the board
	private Tiles [][] board = new Tiles[3][3];
	private int x, 
				y, 
				compX,
				compY,
				winner;
	//sets the board to all empty
	public TicTacToe(){
		for (int i = 0; i < 3; i ++)
			for (int j = 0; j < 3; j++)
				board[i][j]=Tiles.E;
	}
	//mutator functions
	public void setX(int x){
		this.x = x;
	}
	public void setY(int y){
		this.y = y ;
	}
	public void setWinner(int w){
		this.winner = w;
	}
	//accessor funstions
	public int getX(){
		return x;
	}	
	public int getY(){
		return y;
	}
	public int getWinner(){
		return winner;
	}

	public void displayBoard(){
		System.out.println("---------FSU---------");
		System.out.println("---------------------");
		
		for(int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++)
				System.out.printf("|  " + board[i][j] + "  |");
			System.out.println("");
			System.out.println("---------------------");
			
		}
		if (isBoardFull() == true && checkWin() == false)
			System.out.println("---------DRAW--------");
		if (winner == 1)
			System.out.println("--Player X you WIN!--");
		if (winner == -1)
			System.out.println("--Player O you WIN!--");
		System.out.println("---BY: Tyler Kelly---");
		
	}
	public void badComputer(){
		Random ranX = new Random();
		Random ranY = new Random();
		//creates two random coordinates
		compX = ranX.nextInt(3);
		compY = ranY.nextInt(3);
		//if these are the coordiantes of an empty tile than place O there
		if(board[compX][compY] == Tiles.E)
			board[compX][compY] = Tiles.O;
		//if the tile has something else:
		else{
			//while that tile is not empty
			//keep making new coordinates
			while(board[compX][compY] != Tiles.E){
				compX = ranX.nextInt(3);
				compY = ranY.nextInt(3);
				if(board[compX][compY] == Tiles.E){
					board[compX][compY] = Tiles.O;
					break;
				}//end if
				
			}//end while
		}//end else
			
	}//end func
	public void advancedComp(){
		//checks to see where a smart move is, plays defensively
		if (((board[0][0] == Tiles.X  && board[0][1] == Tiles.X) || (board[2][0] == Tiles.X && board[1][1] == Tiles.X) ||(board[1][2] == Tiles.X && board[2][2] == Tiles.X)) && board[0][2] == Tiles.E){
			compX = 0;	
			compY = 2;
		}
		else if (((board[0][0] == Tiles.X  && board[0][2] == Tiles.X) || (board[2][1] == Tiles.X && board[1][1] == Tiles.X)&& board[0][1] == Tiles.E)){
			compX = 0;	
			compY = 1;
		}
		else if (((board[0][2] == Tiles.X  && board[0][1] == Tiles.X) || (board[2][2] == Tiles.X && board[1][1] == Tiles.X) ||(board[1][0] == Tiles.X && board[2][0] == Tiles.X))&& board[0][0] == Tiles.E){
			compX = 0;	
			compY = 0;
		}
		else if (((board[0][0] == Tiles.X  && board[2][0] == Tiles.X) ||(board[1][1] == Tiles.X && board[1][2] == Tiles.X))&& board[1][0] == Tiles.E){
			compX = 1;	
			compY = 0;
		}
		else if (((board[1][0] == Tiles.X  && board[1][1] == Tiles.X) ||(board[0][2] == Tiles.X && board[2][2] == Tiles.X)) && board[1][2] == Tiles.E){
			compX = 1;	
			compY = 2;
		}
		else if (((board[0][0] == Tiles.X  && board[1][0] == Tiles.X) || (board[0][2] == Tiles.X && board[1][1] == Tiles.X) ||(board[2][2] == Tiles.X && board[2][1] == Tiles.X))&& board[2][0] == Tiles.E){
			compX = 2;	
			compY = 0;
		}
		else if (((board[0][1] == Tiles.X  && board[1][1] == Tiles.X) ||(board[2][0] == Tiles.X && board[2][2] == Tiles.X))&& board[2][1] == Tiles.E){
			compX = 2;	
			compY = 1;
		}
		else if (((board[2][0] == Tiles.X  && board[2][1] == Tiles.X) || (board[0][0] == Tiles.X && board[1][1] == Tiles.X) ||(board[0][2] == Tiles.X && board[1][2] == Tiles.X))&& board[2][2] == Tiles.E){
			compX = 2;	
			compY = 2;
		}
		//if none of those cases happen then print to the corner or center spots
		else if (board[1][1] == Tiles.E){
			compX = 1;	
			compY = 1;
		}
		else if (board[0][0] == Tiles.E) {
			compX = 0;	
			compY = 0;
		}
		else if (board[0][2] == Tiles.E) {
			compX = 0;	
			compY = 2;
		}
		else if (board[2][0] == Tiles.E) {
			compX = 2;	
			compY = 0;
		}
		else if (board[2][0] == Tiles.E) {
			compX = 0;	
			compY = 2;
		}
		//if none of those cases work just print at an empty spot
		else{
			for (int i = 0; i < 3; i ++)
				for (int j = 0; j < 3; j++){
					if (board[i][j]==Tiles.E){
						compX = i;
						compY = j;
				}	
			}
		}
		board[compX][compY] = Tiles.O;			
	}	
	public boolean checkRowWin(){
		//if three in a row, its a win
		boolean isWin = false;
		for(int i = 0; i < board.length; i++){
			if (board[i][0] == Tiles.X  && board[i][1] == Tiles.X && board[i][2] == Tiles.X )
				isWin = true;
			if( board[i][0] == Tiles.O && board[i][1] == Tiles.O && board[i][2] == Tiles.O)
				isWin = true;
		}	
		return isWin;
	}
	public boolean checkColumnWin(){
		//if a three in a column
		boolean isWin = false;
		for(int j = 0; j < board.length; j++){
			if (board[0][j] == Tiles.X  && board[1][j] == Tiles.X && board[2][j] == Tiles.X)
				isWin = true;
			if (board[0][j] == Tiles.O &&  board[1][j] == Tiles.O &&  board[2][j] == Tiles.O)
				isWin = true;
			}
		return isWin;
	}
	public boolean checkDiagonalWin(){
		//if three in a diagonal
		boolean isWin = false;
		if (board[0][0] == Tiles.X  && board[1][1] == Tiles.X && board[2][2] == Tiles.X)
			isWin = true;
		if (board[0][2] == Tiles.X && board[1][1] == Tiles.X && board[2][0] == Tiles.X)
			isWin = true;
		if ( board[0][0] == Tiles.O &&  board[1][1] == Tiles.O &&  board[2][2] == Tiles.O)
			isWin = true;
		if ( board[0][2] == Tiles.O &&  board[1][1] == Tiles.O && board[2][0] == Tiles.O)
			isWin = true;
		return isWin;
	}
	public boolean checkWin(){
		// FvFvT == true
		return (checkDiagonalWin() ||checkColumnWin() || checkRowWin());
	}
	public void printToBoardX(){
		//called each time there is input
		if (validPosition() == true)
			board[x][y] = Tiles.X;
	}
	public void printToBoardO(){
		//called each time there is input
		if (validPosition() == true)
			board[x][y] = Tiles.O; 
	}
	public boolean isBoardFull(){
		boolean isFull = true;
		for (int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++)
				if (board[i][j] == Tiles.E)
					isFull = false;
		}
		return isFull;
	}
	public boolean validPosition(){
		boolean isValid = true;
		if (x >= 3 || y >= 3)
			isValid = false;
		if (x < 0 || y < 0)
			isValid = false;
		if (board [x][y] != Tiles.E)
			isValid = false;
		return isValid;	
	}
	
}

