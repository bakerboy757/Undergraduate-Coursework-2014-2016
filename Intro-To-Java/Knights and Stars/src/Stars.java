public class Stars {
	
	//private member data
	private int row,
				column;
	//default constructor
	public Stars()
	{}
	//constructor
	public Stars(int row, int column){
		this.row = row;
		this.column = column;
	}
	//mutator functions to set data from main
	public void setRow(int row){
		this.row = row;
		
	}
	public void setColumn(int column){
		this.column = column;
		
	}
	//function to output stars properly
	//returns string so that message may be displayed in display boxes
	public String setStars(){
		
		//initializing an essentially dummy variable "string"
		String string = ("");
		
		for (int j = 0; j < row; j++){
			if (j % 2 == 0)
				string += ("\n");//adds new new line with no space if even row
			else
				string += ("\n ");//adds newline with space otherwise(for offset stars)
			for(int i = 0; i < column; i++)
				string +=("* ");//adds star with space for that row
		
		}
		return string;

	}
}
