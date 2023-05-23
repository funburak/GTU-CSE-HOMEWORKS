/**
 * @author Burak Demirkaya
 */

package homework7;

import java.util.Scanner;

/**
 * Test class to test the sortign algorithms.
 */
public class Test {
    /**
     * Main method for testing.
     * 
     * @param args Arguments needed for main method.
     */
        public static void main(String[] args) {
    
            String bestCase = "a bb ccc dddd eeeee ";
            myMap bestMap = new myMap();
            bestMap.createMap(bestCase);

            String avgCase = "aaaaa bb cccccc ddd e";
            myMap avgMap = new myMap();
            avgMap.createMap(avgCase);

            String worstCase = "aaaaa bbbb ccc dd e ";
            myMap worstMap = new myMap();
            worstMap.createMap(worstCase);

            int selection = -1;
            Scanner sc = new Scanner(System.in);
            do{ 
                System.out.println("Select a sorting algorithm from the menu.");
                System.out.println("1. Merge Sort");
                System.out.println("2. Selection Sort");
                System.out.println("3. Insertion Sort");
                System.out.println("4. Bubble Sort");
                System.out.println("5. Quick Sort");
                System.out.println("0. Exit");
                selection = sc.nextInt();
                switch(selection){
                    case 1:
                        System.out.println("Merge Sort...");
                        System.out.println("The original map: (best case)");
                        bestMap.displayMap();
                        mergeSort bestMS = new mergeSort(bestMap);
                        bestMS.merge_Sort();

                        System.out.println("The original map: (average case)");
                        avgMap.displayMap();
                        mergeSort avgMS = new mergeSort(avgMap);
                        avgMS.merge_Sort();

                        System.out.println("The original map: (worst case)");
                        worstMap.displayMap();
                        mergeSort worstMS = new mergeSort(worstMap);
                        worstMS.merge_Sort();
                    break;

                    case 2:
                        System.out.println("Selection Sort...");
                        System.out.println("The original map: (best case)");
                        bestMap.displayMap();
                        selectionSort bestSS = new selectionSort(bestMap);
                        System.out.println("The sorted map: ");
                        bestSS.selection_Sort();

                        System.out.println("The original map: (average case)");
                        avgMap.displayMap();
                        selectionSort avgSS = new selectionSort(avgMap);
                        System.out.println("The sorted map: ");
                        avgSS.selection_Sort();

                        System.out.println("The original map: (worst case)");
                        worstMap.displayMap();
                        selectionSort worstSS = new selectionSort(worstMap);
                        System.out.println("The sorted map: ");
                        worstSS.selection_Sort();
                    break;

                    case 3:
                        System.out.println("Insertion Sort...");
                        System.out.println("The original map: (best case)");
                        bestMap.displayMap();
                        insertionSort bestIS = new insertionSort(bestMap);
                        System.out.println("The sorted map: ");
                        bestIS.insertion_Sort();

                        System.out.println("The original map: (average case)");
                        avgMap.displayMap();
                        insertionSort avgIS = new insertionSort(avgMap);
                        System.out.println("The sorted map: ");
                        avgIS.insertion_Sort();

                        System.out.println("The original map: (worst case)");
                        worstMap.displayMap();
                        insertionSort worstIS = new insertionSort(worstMap);
                        System.out.println("The sorted map: ");
                        worstIS.insertion_Sort();
                    break;

                    case 4:
                        System.out.println("Bubble Sort...");
                        System.out.println("The original map: (best case)");
                        bestMap.displayMap();
                        bubbleSort bestBS = new bubbleSort(bestMap);
                        System.out.println("The sorted map: ");
                        bestBS.bubble_Sort();

                        System.out.println("The original map: (average case)");
                        avgMap.displayMap();
                        bubbleSort avgBS = new bubbleSort(avgMap);
                        System.out.println("The sorted map: ");
                        avgBS.bubble_Sort();

                        System.out.println("The original map: (worst case)");
                        worstMap.displayMap();
                        bubbleSort worstBS = new bubbleSort(worstMap);
                        System.out.println("The sorted map: ");
                        worstBS.bubble_Sort();
                    break;

                    case 5:
                        System.out.println("Quick Sort...");
                        System.out.println("The original map: (best case)");
                        bestMap.displayMap();
                        quickSort bestQS = new quickSort(bestMap);
                        System.out.println("The sorted map: ");
                        bestQS.quick_Sort();

                        System.out.println("The original map: (average case)");
                        avgMap.displayMap();
                        quickSort avgQS = new quickSort(avgMap);
                        System.out.println("The sorted map: ");
                        avgQS.quick_Sort();

                        System.out.println("The original map: (worst case)");
                        worstMap.displayMap();
                        quickSort worstQS = new quickSort(worstMap);
                        System.out.println("The sorted map: ");
                        worstQS.quick_Sort();
                    break;

                    case 0:
                        System.out.println("Exiting...");
                        System.exit(-1);
                    break;

                    default:
                        System.out.println("Please enter a valid item from the menu.");
                        break;
                }
            }while(selection!=0);
            sc.close();
        }
}
