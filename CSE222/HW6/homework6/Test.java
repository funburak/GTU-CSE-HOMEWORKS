/**
 * @author Burak Demirkaya
 */

package homework6;

/**
 * Test class for myMap and mergeSort.
 */
public class Test {
    /**
     * Main method.
     * 
     * @param args Arguments needed for main.
     */
    public static void main(String[] args) {
        String input = "'Hush, hush!' whispered the rushing wind.";
        System.out.println("Original String: " + input);
        myMap map = new myMap();
        map.createMap(input);
        System.out.println("Preprocessed String: " + map.getStr());
        System.out.println("\nThe original (unsorted) map:");
        map.displayMap();

        mergeSort merge = new mergeSort(map);
        System.out.println("The sorted map:");
        merge.merge_Sort();
    }
}