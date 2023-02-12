/**
 * 
 * @author Burak Demirkaya 210104004274
 * 
 * 
 * 
 * 
 */


import java.util.Random;

public class Tetromino{

    /**
     * 
     * Tetromino pieces in enum.
     * 
     * 
     */
    public enum Piece{
        I,O,T,J,L,S,Z,R,Q
    }

    private char[][] shape;
    private Piece piece_type;
    private int row_;
    private int col_;

    /**
     * Constructs an objects with the given parameter p
     * 
     * @param p The piece type of the tetromino
     */
    public Tetromino(Piece p){
        piece_type = p;

        switch(piece_type) {
            case I:
                shape = new char[1][4];
                row_ = 1;
                col_ = 4;
                for(int c=0; c<4; ++c){
                    shape[0][c] = 'I';
                }
                break;
            case O:
                shape = new char[2][2];
                row_ = 2;
                col_ = 2;
                for(int r=0; r<2; ++r){
                    for(int c=0; c<2; ++c){
                        shape[r][c] = 'O';
                    }
                }
                break;
            case T:
                shape = new char[2][3];
                row_ = 2;
                col_ = 3;
                for(int r=0; r<2; ++r){
                    for(int c=0; c<3; ++c){
                        if(r == 0 || (r == 1 && c == 1)){
                            shape[r][c] = 'T';
                        }
                        else{
                            shape[r][c] = ' ';
                        }
                    }
                }
                break;      
            case J:
                shape = new char[3][2];
                row_ = 3;
                col_ = 2; 
                for(int r=0; r<3; ++r){
                    for(int c=0; c<2; ++c){
                        if((r == 2 && c == 0) || (c == 1)){
                            shape[r][c] = 'J';
                        }
                        else{
                            shape[r][c] = ' ';
                        }
                    }
                }
                break;
            case L:
                shape = new char[3][2];
                row_ = 3;
                col_ = 2; 
                for(int r=0; r<3; ++r){
                    for(int c=0; c<2; ++c){
                        if((r == 0 && c == 0) || (r == 1 && c == 0) || (r == 2)){
                            shape[r][c] = 'L';
                        }
                        else{
                            shape[r][c] = ' ';
                        }
                    }
                }
                break;
            case S:
                shape = new char[2][3];
                row_ = 2;
                col_ = 3; 
                for(int r=0; r<2; ++r){
                    for(int c=0; c<3; ++c){
                        if((r == 0 && c == 1) || (r == 0 && c == 2) || (r == 1 && c == 0) || (r == 1 && c == 1)){
                            shape[r][c] = 'S';
                        }
                        else{
                            shape[r][c] = ' ';
                        }
                    }
                }
                break;
            case Z:
                shape = new char[2][3];
                row_ = 2;
                col_ = 3; 
                for(int r=0; r<2; ++r){
                    for(int c=0; c<3; ++c){
                        if((r == 0 && c == 0) || (r == 0 && c == 1) || (r == 1 && c == 1) || (r == 1 && c == 2)){
                            shape[r][c] = 'Z';
                        }
                        else{
                            shape[r][c] = ' ';
                        }
                    }
                }
                break;
            case R:
                Random r = new Random();
                int random = r.nextInt(7) + 1;
                switch (random) {
                    case 1:
                    shape = new char[1][4];
                    row_ = 1;
                    col_ = 4;
                    for(int c=0; c<4; ++c){
                        shape[0][c] = 'I';
                    }                        
                    break;
                    case 2:
                    shape = new char[2][2];
                    row_ = 2;
                    col_ = 2;
                    for(int r1=0; r1<2; ++r1){
                        for(int c=0; c<2; ++c){
                            shape[r1][c] = 'O';
                        }
                    }
                    break;
                    case 3:
                    shape = new char[2][3];
                    row_ = 2;
                    col_ = 3;
                    for(int r3=0; r3<2; ++r3){
                        for(int c=0; c<3; ++c){
                            if(r3 == 0 || (r3 == 1 && c == 1)){
                                shape[r3][c] = 'T';
                            }
                            else{
                                shape[r3][c] = ' ';
                            }
                        }
                    }
                    break;      
                    case 4:
                    shape = new char[3][2];
                    row_ = 3;
                    col_ = 2; 
                    for(int r4=0; r4<3; ++r4){
                        for(int c=0; c<2; ++c){
                            if((r4 == 2 && c == 0) || (c == 1)){
                                shape[r4][c] = 'J';
                            }
                            else{
                                shape[r4][c] = ' ';
                            }
                        }
                    }                        
                    break;
                    case 5:
                    shape = new char[3][2]; 
                    row_ = 3;
                    col_ = 2;
                    for(int r5=0; r5<3; ++r5){
                        for(int c=0; c<2; ++c){
                            if((r5 == 0 && c == 0) || (r5 == 1 && c == 0) || (r5 == 2)){
                                shape[r5][c] = 'L';
                            }
                            else{
                                shape[r5][c] = ' ';
                            }
                        }
                    }                        
                    break;
                    case 6:
                    shape = new char[2][3]; 
                    row_ = 2;
                    col_ = 3;
                    for(int r6=0; r6<2; ++r6){
                        for(int c=0; c<3; ++c){
                            if((r6 == 0 && c == 1) || (r6 == 0 && c == 2) || (r6 == 1 && c == 0) || (r6 == 1 && c == 1)){
                                shape[r6][c] = 'S';
                            }
                            else{
                                shape[r6][c] = ' ';
                            }
                        }
                    }                        
                    break;
                    case 7:
                    shape = new char[2][3]; 
                    row_ = 2;
                    col_ = 3;
                    for(int r7=0; r7<2; ++r7){
                        for(int c=0; c<3; ++c){
                            if((r7 == 0 && c == 0) || (r7 == 0 && c == 1) || (r7 == 1 && c == 1) || (r7 == 1 && c == 2)){
                                shape[r7][c] = 'Z';
                            }
                            else{
                                shape[r7][c] = ' ';
                            }
                        }
                    }                        
                    break;
                }
                break;
            case Q:
                break;
        }
    }
    /**
     * 
     * @return the shape of the tetromnio in 2d char array
     */
    public char[][] getShape(){
        return shape;
    }


    /**
     * 
     * Prints the tetromnino
     * 
     */
    public void print(){
        for (char[] row : getShape()){
            for (char c : row) {
                System.out.print(c);
            }
            System.out.println();
        }
    }

    /**
     * Rotates the tetromino shape clockwise or counter-clockwise by 90 degrees.
     * 
     * @param direction Takes a char direction left for 'l' and right for 'r'
     */
    public void rotate(char direction){
        char[][] temp = new char[col_][row_];

        if (direction == 'l') { // Left rotate
            for (int r = 0; r < getRow(); ++r) {
                for (int c = 0; c < getCol(); ++c) {
                    temp[col_ - 1 - c][r] = shape[r][c];
                }
            }
        } else if (direction == 'r') { // Right rotate
            for (int r = 0; r < row_; ++r) {
                for (int c = 0; c < col_; ++c) {
                    temp[c][row_ - 1 - r] = shape[r][c];
                }
            }
        }

        shape = new char[col_][row_];

        for(int r=0; r<col_; ++r){
            for(int c=0; c<row_; ++c){
                shape[r][c] = temp[r][c];
            }
        }

        int temp_row = row_;
        row_ = col_;
        col_ = temp_row;
    }

    /**
     * 
     * @return row_ Returns the row size of the tetromino shape
     */
    public int getRow(){
        return row_;
    }

    /**
     * 
     * @return col_ Returns the column size of the tetromino shape
     */
    public int getCol(){
        return col_;
    }
    
} // end class Tetromino