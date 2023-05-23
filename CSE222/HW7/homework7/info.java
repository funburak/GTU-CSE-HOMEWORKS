/**
 * @author Burak Demirkaya
 */

package homework7;

import java.util.ArrayList;

/**
 * info class
 */
public class info {
    private int count;
    private ArrayList<String> words;


    /**
     * Creates a new info object.
     */
    public info(){
        count = 0;
        words = new ArrayList<String>();
    }

    /**
     * Adds the word to the words list.
     * 
     * @param word The word which will be added to the words list.
     */
    public void push(String word){
        words.add(word);
        count++;
    }

    /**
     * 
     * @return the count of the info.
     */
    public int getCount(){
        return count;
    }

    /**
     * 
     * @return the words list.
     */
    public ArrayList<String> getWords() {
        return words;
    }
}
