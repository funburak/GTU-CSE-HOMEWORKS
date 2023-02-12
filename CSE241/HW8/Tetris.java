/**
 * 
 * @author Burak Demirkaya 210104004274
 * 
 */

import java.util.Random;

/**
 * Tetris board class
 * 
 */
public class Tetris {

    /**
     * 2D char array to represent the tetris game.
     */
    private char[][] Board;
    /**
     * Number of rows of the board.
     */
    private int board_row;

    /**
     * Number of columns of the board.
     */
    private int board_col;


    /**
     * Creates a row x col board and fills it border with '#' so that the borders can be easily seen.
     * 
     * @param row Row number of the Tetris board
     * @param col Column number of the Tetris board
     * 
     */
    Tetris(int row,int col){
        board_row = row;
        board_col = col;
        char[][] temp = new char[row][col];

        for(int r=0; r<board_row; ++r){
            for(int c=0; c<board_col; ++c){
                if(r == 0 || r==board_row-1 || c == 0 || c == board_col-1){
                    temp[r][c] = '#';
                }
                else{
                    temp[r][c] = ' ';
                }            
            }
        }
        Board = temp;
    }

    /**
     * Adds the tetromino to the middle row of the Tetris board.
     * 
     * @param t Takes a Tetromino object
     */
    public void add(Tetromino t){
        int mid_col = board_col / 2 ;
        char[][] shape = t.getShape();
        for(int r=0; r<shape.length; ++r){
            for(int c=0; c<shape[r].length; ++c){
                Board[r+1][c+mid_col-1] = shape[r][c];
            }
        }
    }

    /**
     * Deletes the added tetromino from the middle of the Tetris board.
     * 
     * @param t Takes a tetromino object
     */
    public void deleteAdd(Tetromino t){
        int mid_col = board_col / 2;
        char[][] shape = t.getShape();
        for(int r=0; r<shape.length; ++r){
            for(int c=0; c<shape[r].length; ++c){
                Board[r+1][mid_col + c -1] = ' ';
            }
        }
    }

    /**
     * 
     * Prints the Tetris board.
     */
    public void draw(){
        for(int r=0; r<board_row; ++r){
            for(int c=0; c<board_col; ++c){
                System.out.print(Board[r][c]);
            }
            System.out.println();
        }
    }

    /**
     * First by random calculate the rotation count rotation direction to rotate the tetromino.
     * Then calculates by random the move count and move direction. If move direction is left it multiplies
     * move count by -1.
     * Finally drop downs the tetromino on the Tetris board until it hits bottom or hits another tetromino.
     * 
     * @param t Takes a tetromino object
     * @param game Takes a game object to paint the game board in GUI.
     */
    public void animate(Tetromino t, Game game){
        int bottom = board_row - 1;
        int count = 0;
        Random r = new Random();
        int rotate_count = r.nextInt(5); // Random integers in range of [0,4]
        int rotate_direction = r.nextInt(2) + 1; // Random integers in range of [1,2]

        if(rotate_direction == 1){ // Left rotate
            for(int i=0; i<rotate_count; ++i){
                t.rotate('l');
            }
        }
        else if(rotate_direction == 2){ // Right rotate
            for(int i=0; i<rotate_count; ++i){
                t.rotate('r');
            }
        }

        int move_count = r.nextInt(board_col/2-1-t.getCol());
        int move_direction = r.nextInt(2) + 1;
        if(move_direction == 1){ // Left move
            move_count *= -1;
        }

        char[][] shape = t.getShape();

        while(count <= bottom){
            if(move_direction == 'l'){
                t.moveLeft();
            }
            else if(move_direction == 'r'){
                t.moveRight();
            }
            draw();
            deleteAdd(t);
            
            for(int i=0; i<t.getCol(); ++i){ // Collision check
                if((Board[t.getRow()+count+1+i][t.getCol()+i+count] != ' ')){
                    return;
                }
            }

            for(int r1=0; r1<shape.length; ++r1){ // Erases the previous point
                for(int c=0; c<shape[0].length; ++c){
                    Board[r1+count+1][board_col/2 + move_count +c-1] = ' ';
                }
            }

            game.colorBoard(Board);

            for(int r2=0; r2<shape.length; ++r2){ // Puts shape to the board
                for(int c=0; c<shape[0].length; ++c){
                    Board[r2+count+2][board_col/2 + move_count + c-1] = shape[r2][c];
                }
            }

            game.colorBoard(Board);
                        
            sleep();
            count++;


            if(count+shape.length >= bottom-1){
                break;
            }
        }
        draw();
    }
    /**
     * Sleeps for 50 miliseconds than deletes the entire screen and flushes the output buffer.
     * And set the cursor to the top of the terminal.
     * 
     */
    public void sleep() {
        try {
            Thread.sleep(50); // Sleeps 50 milliseconds
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.print("\033[H\033[2J");   // Erases entire screen
        System.out.flush(); // flush the output buffer
    }

    /**
     *  If the board's row 2 is full, it returns true. Otherwise returns false.
     * 
     * @return boolean.
     */
    public boolean boardFull(){
        boolean full = true;
        for(int i=1; i<board_col-1; ++i){
            if(Board[2][i] == ' '){
                full = false;
                break;
            }
        }
        return full;
    }
    /**
     * Checks for columns if all full return true, otherwise return false.
     * 
     * @return boolean. 
     */
    public boolean checkColumns(){
        boolean full = true;
        for(int i=1; i<board_row-1; ++i){
            for(int j=1; j<board_row-1; ++j){
                if(Board[i][j] == ' '){
                    full = false;
                    break;
                }
            }
        }
        return full;
    }

    /**
     * If reset button is pressed. It refreshes the board.
     */
    public void clearBoard(){
        for(int r=0; r<board_row; ++r){
            for(int c=0; c<board_col; ++c){
                if(r == 0 || r==board_row-1 || c == 0 || c == board_col-1){
                    Board[r][c] = '#';
                }
                else{
                    Board[r][c] = ' ';
                }            
            }
        }
    }

    /**
     * Returns the 2d char board.
     * 
     * @return tetris Board.
     */
    public char[][] getBoard() {
        return Board;
    }

} // end class Tetris
