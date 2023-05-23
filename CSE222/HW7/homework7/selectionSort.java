/**
 * @author Burak Demirkaya
 */

package homework7;

import java.util.ArrayList;
import java.util.Map;

/**
 * selectionSort class which implements the selection sort algorithm for the myMap class.
 */
public class selectionSort {
    private myMap originalMap;
    private myMap sortedMap;
    private ArrayList<Character> aux;


    /**
     * Creates a new selectionSort object.
     * 
     * @param map original myMap object.
     */
    public selectionSort(myMap map){
        this.originalMap = map;
        sortedMap = new myMap();
        aux = new ArrayList<Character>();
    }

    /**
     * Implements the selection sort algorithm due to count values of info.
     * Sorts the originalMap into sortedMap.
     */
    public void selection_Sort(){
        for(Map.Entry<Character,info> entry : originalMap.getMap().entrySet()){
            Character key = entry.getKey();
            aux.add(key);
        }
        
        long startTime = System.nanoTime();

        for(int i=0; i<originalMap.getMapSize()-1; ++i){
            int minIndex = i;
            for(int j=i+1; j<originalMap.getMapSize(); ++j){
                info value1 = originalMap.getMap().get(aux.get(j));
                info value2 = originalMap.getMap().get(aux.get(minIndex));
                if(value1.getCount() < value2.getCount()){
                    minIndex = j;
                }
            }
            Character temp = aux.get(minIndex);
            aux.set(minIndex,aux.get(i));
            aux.set(i,temp);
        }

        long endTime   = System.nanoTime();
        long totalTime = (endTime - startTime);
        System.out.println("Took " + totalTime + " ns to sort.");

        for(Character ch : aux){
            info value = originalMap.getMap().get(ch);
            sortedMap.getMap().put(ch,value);
        }
        sortedMap.displayMap();
        System.out.println(aux);
    }
}
