/**
 * @author Burak Demirkaya
 */

package homework6;

import java.util.ArrayList;
import java.util.Map;

/**
 * mergeSort class that implements merge sort algorithm for myMap class.
 */
public class mergeSort {
    private myMap originalMap;
    private myMap sortedMap;
    private ArrayList<Character> aux;

    /**
     * Creates new mergeSort object. Assings map to the originalMap and creates a sortedMap object and a aux list in order to use in the sorting.
     * 
     * @param map myMap object for the originalMap.
     */
    public mergeSort(myMap map){
        this.originalMap = map;
        this.sortedMap = new myMap();
        this.aux = new ArrayList<Character>(originalMap.getMapSize());
    }

    /**
     * Sorts the originalMap into sortedMap.
     */
    public void sort(){
        sort(0, this.originalMap.getMapSize()-1);
    }

    /**
     * Helper of the sort method. Uses recursive.
     * 
     * @param left Left index
     * @param right Right index.
     */
    private void sort(int left, int right){
        if(left < right){
            int mid = left + (right-left)/2;

            sort(left, mid);
            sort(mid+1, right);

            merge(left, mid, right);
        }
    }

    /**
     * Merges the sorted sub arrays. Simply checks for the count values of the info object and sorts the aux list according to the count values.
     * 
     * @param left Left index.
     * @param mid Middle index. 
     * @param right Right index.
     */
    public void merge(int left, int mid, int right){
        sortedMap.getMap().clear(); // Clears the preivous sortedMap.

        int leftSize = mid - left + 1;
        int rightSize = right - mid;
        ArrayList<Character> Left = new ArrayList<Character>(leftSize);
        ArrayList<Character> Right = new ArrayList<Character>(rightSize);
        int i,j;

        for(i=0; i<leftSize; ++i){
            Left.add(aux.get(left+i));
        }

        for(j=0; j<rightSize; ++j){
            Right.add(aux.get(mid+j+1));
        }

        i=0;j=0;
        int k = left;

        while(i < leftSize && j < rightSize){
            info leftInfo = originalMap.getMap().get(Left.get(i));
            Character leftChar = Left.get(i);
            info rightInfo = originalMap.getMap().get(Right.get(j));
            Character rightChar = Right.get(j);
            if(leftInfo.getCount() <= rightInfo.getCount()){
                aux.set(k,leftChar);
                i++;
            }
            else{
                aux.set(k,rightChar);
                j++;
            }
            k++;
        }

        while(i < leftSize){
            Character leftChar = Left.get(i);
            aux.set(k,leftChar);
            i++;k++;
        }

        while(j < rightSize){
            Character rightChar = Right.get(j);
            aux.set(k,rightChar);
            j++;k++;   
        }

        for(Character ch : aux){ // Put the sorted aux list into sortedMap with their corresponding info values.
            info infoValue = originalMap.getMap().get(ch);
            sortedMap.getMap().put(ch, infoValue);
        }
    }

    /**
     * Implement the merge sort algorithm for myMap.
     */
    public void merge_Sort(){
        for(Map.Entry<Character,info> entry : originalMap.getMap().entrySet()){ // Add all the key values of the map into aux list before sorting.
            Character key = entry.getKey();
            aux.add(key);
        }

        sort();

        sortedMap.displayMap();
        System.out.println("The aux list: " + aux);
    }
}