/**
 * @author Burak Demirkaya
 */

package homework7;

import java.util.ArrayList;
import java.util.Map;

/**
 * insertionSort class which implements the insertion sort algorithm for myMap class.
 */
public class insertionSort {
    private myMap originalMap;
    private myMap sortedMap;
    private ArrayList<Character> aux;

    /**
     * Creates a new insertionSort object.
     * 
     * @param map original myMap object.
     */
    public insertionSort(myMap map){
        this.originalMap = map;
        this.sortedMap = new myMap();
        this.aux = new ArrayList<Character>();
    }

    /**
     * Implements the insertion sort algorithm due to count values of info.
     * Sorts the originalMap into sortedMap.
     */
    public void insertion_Sort(){
        for(Map.Entry<Character,info> entry : originalMap.getMap().entrySet()){
            Character key = entry.getKey();
            aux.add(key);
        }
        
        long startTime = System.nanoTime();

        for(int i=1; i<aux.size(); ++i){
            char key = aux.get(i);
            info value = originalMap.getMap().get(key);
            int j = i-1;

            while(j >= 0 && originalMap.getMap().get(aux.get(j)).getCount() > value.getCount()){
                aux.set(j+1,aux.get(j));
                j--;
            }
            aux.set(j+1,key);
        }

        long endTime   = System.nanoTime();
        long totalTime = (endTime - startTime);
        System.out.println("Took " + totalTime + " ns to sort.");

        for(Character ch : aux){
            info infoValue = originalMap.getMap().get(ch);
            sortedMap.getMap().put(ch, infoValue);
        }

        sortedMap.displayMap();
        System.out.println(aux);
    }
}