
public class driver1 {
    /**
     * Main method for driver1. Adds three O piece in to the board and animates it.
     * @param args
     */
    public static void main(String[] args) {
        Tetris board = new Tetris(20, 20);
        Tetromino t1 = new Tetromino(Tetromino.Piece.T);
        Tetromino t2 = new Tetromino(Tetromino.Piece.S);
        Tetromino t3 = new Tetromino(Tetromino.Piece.O);

        board.add(t1);
        board.draw();
        board.animate(t1);

        board.add(t2);
        board.draw();
        board.animate(t2);

        board.add(t3);
        board.draw();
        board.animate(t3);

        System.out.println("----------Driver 1 finished------------");
    }
}
