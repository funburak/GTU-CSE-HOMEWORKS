/**
 * @author Burak Demirkaya
 */

package homework7;

import java.util.ArrayList;
import java.util.Map;

/**
 * quickSort class that implements the quick sort algorithm for myMap class.
 */
public class quickSort {
    private myMap originalMap;
    private myMap sortedMap;
    private ArrayList<Character> aux;


    /**
     * Creates a new quickSort object.
     * 
     * @param map original myMap object.
     */
    public quickSort(myMap map){
        this.originalMap = map;
        this.sortedMap = new myMap();
        this.aux = new ArrayList<Character>();
    }

    /**
     * Implements the quick sort algorithm due to count values of info.
     * Sorts the originalMap into sortedMap.
     */
    public void quick_Sort(){
        for(Map.Entry<Character,info> entry : originalMap.getMap().entrySet()){
            Character key = entry.getKey();
            aux.add(key);
        }

        long startTime = System.nanoTime();
        quickSortHelper(0, originalMap.getMapSize()-1);
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

    /**
     * Recursively sorts the subarrays.
     * @param low starting index of the subarray.
     * @param high ending index of the subarray.
     */
    public void quickSortHelper(int low, int high){
        if(low < high){
            int p = partition(low, high);

            quickSortHelper(low, p-1);
            quickSortHelper(p+1, high);
        }
    }

    /**
     * Partitions the subarray of characters based on a pivot element.
     * @param low starting index of the subarray.
     * @param high ending index of the subarray.
     * @return the index of the pivot element after partitioning.
     */
    public int partition(int low, int high){
        sortedMap.getMap().clear();
        info pivot = originalMap.getMap().get(aux.get(high));
        int i = low-1;

        for(int j=low; j<=high-1; ++j){
            info value = originalMap.getMap().get(aux.get(j));
            if(value.getCount() < pivot.getCount()){
                i++;
                Character temp = aux.get(i);
                aux.set(i,aux.get(j));
                aux.set(j,temp);
            }
        }
        Character temp = aux.get(i+1);
        aux.set(i+1,aux.get(high));
        aux.set(high,temp);
        return (i+1);
    }
}
