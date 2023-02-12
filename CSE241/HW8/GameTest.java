/**
 * @author Burak Demirkaya 210104004274
 */

/**
 * GameTest class to test the Game, Tetris and Tetromino classes
 */
public class GameTest {
    /**
     * 
     * @param args. Main method for the game.
     */
    public static void main(String[] args) {
        Game game = new Game();
        Tetris tetris_board = new Tetris(20,20);
        Tetromino tetro = new Tetromino(Tetromino.Piece.O);

            while(true){
                char rand = game.getRandomPieceType();        
                    if(rand == 'I'){
                        tetro = new Tetromino(Tetromino.Piece.I);
                    }
                    else if(rand == 'O'){
                        tetro = new Tetromino(Tetromino.Piece.O);
                    }
                    else if(rand == 'T'){
                        tetro = new Tetromino(Tetromino.Piece.T);
                    }
                    else if(rand == 'J'){
                        tetro = new Tetromino(Tetromino.Piece.J);
                    }
                    else if(rand == 'L'){
                        tetro = new Tetromino(Tetromino.Piece.L);
                    }
                    else if(rand == 'S'){
                        tetro = new Tetromino(Tetromino.Piece.S);
                    }
                    else if(rand == 'Z'){
                        tetro = new Tetromino(Tetromino.Piece.Z);
                    }
                    tetris_board.animate(tetro,game);
                    
                    if(tetris_board.boardFull()){
                        System.exit(-1);
                    }
            }
    }
}
