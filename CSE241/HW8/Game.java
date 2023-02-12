/**
 * @author Burak Demirkaya 210104004274
 * 
 */

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.Random;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 * Game class implements both ActionListener and KeyListener interfaces. ActionListener is for the buttons
 * ,KeyListener is for the key pressed.
 */
public class Game implements ActionListener, KeyListener{

    /**
     * JFrame to represent the frame of the game.
     */
    private JFrame frame;

    /**
     * JButton[][] to represent the board.
     */
    private JButton[][] board;

    /**
     * JButton[] to represent the operator buttons like start, end and reset.
     */
    private JButton[] operatorButtons;

    /**
     * JButtons for operators.
     */
    private JButton startButton, endButton, resetButton;

    /**
     * JPanel to fill the JButtob[][] board in.
     */
    private JPanel panel;

    /**
     * JTextField to show the game status.
     */
    private JTextField textField;

    /**
     * Tetromino to store the current Tetromino.
     */
    private Tetromino tetro;

    /**
     * Tetris to store the tetris_board in the terminal.
     */
    private Tetris tetris_board;

    //private Timer timer;

    int point = 0;

    /**
     * Default constructor for game class. The frame, panels and JButtons are all implemented here.
     * 
     */
    public Game(){
        tetris_board = new Tetris(20,20);

        frame = new JFrame("Tetris");
        frame.setSize(700,700);
        frame.setLayout(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        

        startButton = new JButton("START");
        endButton = new JButton("END");
        resetButton = new JButton("RESET");
        
        operatorButtons = new JButton[3];
        operatorButtons[0] = startButton;
        operatorButtons[1] = endButton;
        operatorButtons[2] = resetButton;

        for(int i=0; i<operatorButtons.length; ++i){
            operatorButtons[i].addActionListener(this);
            operatorButtons[i].setFocusable(false);
        }

        startButton.setBounds(100,600,100,50);
        endButton.setBounds(300,600,100,50);
        resetButton.setBounds(500, 600, 100, 50);

        panel = new JPanel();
        panel.setBounds(50, 50, 450, 500);
        panel.setLayout(new GridLayout(20,20,10,10));


        board = new JButton[20][20];
        for(int i=0; i<board.length; ++i){
            for(int j=0; j<board[i].length; ++j){
                board[i][j] = new JButton();
                panel.add(board[i][j]);
            }
        }

        textField = new JTextField();
        textField.setEditable(false);
        textField.setBounds(550, 100, 100, 50);
        textField.setText("Score!");

        frame.add(startButton);
        frame.add(endButton);
        frame.add(resetButton);
        frame.add(panel);
        frame.add(textField);
        frame.addKeyListener(this);
        frame.setFocusable(true);
        frame.setResizable(false);
        frame.setVisible(true);
    }
   
    /**
     * 
     * @return a random char to represent a Tetromino piece.
     */
    public char getRandomPieceType(){
        char[] pieces = {'I','O','T','J','L','S','Z'};
        Random r = new Random();
        int index = r.nextInt(pieces.length);
        return pieces[index];
    }

    /**
     * Takes the board from the terminal and checks each cell if there is a character in
     * that cell it colors the cell with the corresponding color.
     * 
     * @param terminal_board. 
     */
    public void colorBoard(char[][] terminal_board){
        try {
            Thread.sleep(50); // Sleeps 50 milliseconds
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        for(int i1=0; i1<terminal_board.length; ++i1){
            for(int j=0; j<terminal_board[i1].length; ++j){
                board[i1][j].setBackground(Color.WHITE);
            }
        }

        for(int i=0; i<terminal_board.length; ++i){
            for(int j=0; j<terminal_board[i].length; ++j){
                if(terminal_board[i][j] != ' '){
                    if(terminal_board[i][j] == 'I'){
                        board[i][j].setBackground(Color.CYAN);
                    }
                    else if(terminal_board[i][j] == 'O'){
                        board[i][j].setBackground(Color.BLACK);
                    }
                    else if(terminal_board[i][j] == 'T'){
                        board[i][j].setBackground(Color.BLUE);
                    }
                    else if(terminal_board[i][j] == 'J'){
                        board[i][j].setBackground(Color.GREEN);
                    }
                    else if(terminal_board[i][j] == 'L'){
                        board[i][j].setBackground(Color.ORANGE);
                    }
                    else if(terminal_board[i][j] == 'S'){
                        board[i][j].setBackground(Color.GRAY);
                    }
                    else if(terminal_board[i][j] == 'Z'){
                        board[i][j].setBackground(Color.RED);
                    }
                    else if(terminal_board[i][j] == '#'){
                        board[i][j].setBackground(Color.YELLOW);
                    }
                    else if(i == terminal_board.length-2){
                        board[i][j].setBackground(Color.YELLOW);
                    }
                }
            }
        }
    }

    /**
     * If startButton is clicked it will start the game. 
     * If resetButton is clicked it will reset the board.
     * If endButton is clicked the program will be terminated.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == startButton){

            for(int i=0; i<board.length; ++i){
                for(int j=0; j<board[i].length; ++j){
                    board[i][j].setBackground(Color.WHITE);
                }
            }

            textField.setText("Game Started!");
        }
        else if(e.getSource() == endButton){
            System.exit(-1);
        }
        else if(e.getSource() == resetButton){
            for(int i=0; i<board.length; ++i){
                for(int j=0; j<board[i].length; ++j){
                    board[i][j].setBackground(Color.WHITE);
                }
            }
            tetris_board.clearBoard();
            textField.setText("Game resetted!");
        }
    }

    /**
     * If a key is typed.
     */
    @Override
    public void keyTyped(KeyEvent e) {
        // TODO Auto-generated method stub
        
    }

    /**
     * If UP arrow key is pressed, it will rotate the tetromino left.
     * If DOWN arrow key is pressed, it will move the tetromino  down.
     * If LEFT arrow key is pressed, it will move the tetromino left.
     * If RIGHT arrow key is pressed, it will move the tetromino right.
     */
    @Override
    public void keyPressed(KeyEvent e) {
        if(e.getKeyCode() == KeyEvent.VK_UP){
            tetro.rotate('l');
        }
        else if(e.getKeyCode() == KeyEvent.VK_RIGHT){
            tetro.moveRight();
        }
        else if(e.getKeyCode() == KeyEvent.VK_DOWN){
            tetro.moveDown();
        }
        else if(e.getKeyCode() == KeyEvent.VK_LEFT){
            tetro.moveLeft();
        }
    }

    /**
     * If a key is released.
     */
    @Override
    public void keyReleased(KeyEvent e) {
        // TODO Auto-generated method stub
        
    }
} // end class Game
