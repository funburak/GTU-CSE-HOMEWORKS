/**
 * @author Burak Demirkaya
 */

package homework6;

import java.util.ArrayList;

/**
 * info class.
 */
public class info {
    private int count;
    private ArrayList<String> words;

    /**
     * Creates a new info object, setting the count to zero.
     */
    public info(){
        count = 0;
        words = new ArrayList<String>();
    }

    /**
     * Adds a new word to the words list. Increment count by 1.
     * 
     * @param word The word that will be added to list.
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
