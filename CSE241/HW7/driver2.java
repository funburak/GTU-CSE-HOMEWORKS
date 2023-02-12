import java.util.Scanner;

public class driver2{

    /**
     * Main method for driver2. Takes input from the user.
     * @param args
     */
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        int row = 1;
        int col = 1;
        try{
            System.out.println("Please enter the size of the tetris board");
            try {
                row = s.nextInt();
                col = s.nextInt();
                if(row < 0 || col < 0 ){
                    throw new IllegalArgumentException("Row or column cannot be negative integers!");
                }    
            } catch (IllegalArgumentException e){
                System.out.println(e.getMessage());
            }
            Tetris board = new Tetris(row, col);
            
            while(true){
            System.out.println("Please enter the tetromino type. R for random. Q to quit.");
            char p = s.next().charAt(0);
            while(true){
                if(p == 'I' || p == 'O' || p == 'T' || p == 'L' || p == 'J' || p == 'S' || p == 'Z' || p == 'R' || p == 'Q'){
                    break;
                }
                else{
                    System.out.println("Please enter valid tetromino type!");
                    p = s.next().charAt(0);
                }
            }
            Tetromino.Piece piece = Tetromino.Piece.O;
            switch(p){
                case 'I':
                    piece = Tetromino.Piece.I;
                    break;
                case 'O':
                    piece = Tetromino.Piece.O;
                    break;
                case 'T':
                    piece = Tetromino.Piece.T;
                    break;
                case 'J':
                    piece = Tetromino.Piece.J;
                    break;
                case 'L':
                    piece = Tetromino.Piece.L;
                    break;
                case 'S':
                    piece = Tetromino.Piece.S;
                    break;
                case 'Z':
                    piece = Tetromino.Piece.Z;
                    break;
                case 'R':
                    piece = Tetromino.Piece.R;
                    break;
                case 'Q':
                    piece = Tetromino.Piece.Q;
                    break;
                default:
                    System.err.println("Please enter valid tetromino type");
                    break;
            }
    
            if(piece == Tetromino.Piece.Q){
                System.out.println("Exiting.");
                break;
            }
                Tetromino t1 = new Tetromino(piece);
                t1.print();
                board.add(t1);
                board.draw();
                board.animate(t1);
            }
        } finally{
            s.close();
        }

    }
}