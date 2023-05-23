/**
 * @author Burak Demirkaya
 */

package homework7;

import java.util.ArrayList;
import java.util.Map;

/**
 * bubbleSort class that implements bubble sort algorithm for myMap class.
 */
public class bubbleSort {
    private myMap originalMap;
    private myMap sortedMap;
    private ArrayList<Character> aux;

    /**
     * Creates a new bubbleSort object.
     * 
     * @param map original myMap object.
     */
    public bubbleSort(myMap map){
        this.originalMap = map;
        this.sortedMap = new myMap();
        this.aux = new ArrayList<Character>();
    }

    /**
     * Implements the bubble sort algorithm due to count values of info.
     * Sorts the originalMap into sortedMap.
     */
    public void bubble_Sort(){
        for(Map.Entry<Character,info> entry : originalMap.getMap().entrySet()){
            Character key = entry.getKey();
            aux.add(key);
        }

        long startTime = System.nanoTime();

        for(int i=0; i<originalMap.getMapSize()-1; ++i){
            for(int j=0; j<originalMap.getMapSize()-i-1; ++j){
                info value1 = originalMap.getMap().get(aux.get(j));
                info value2 = originalMap.getMap().get(aux.get(j+1));
                if(value1.getCount() > value2.getCount()){
                    Character temp = aux.get(j);
                    aux.set(j,aux.get(j+1));
                    aux.set(j+1,temp);
                }
            }
        }
        long endTime   = System.nanoTime();
        long totalTime = (endTime - startTime);
        System.out.println("Took " + totalTime + " ns to sort.");

        for(Character ch : aux){
            info value = originalMap.getMap().get(ch);
            sortedMap.getMap().put(ch, value);
        }

        sortedMap.displayMap();
        System.out.println(aux);
    }
}
