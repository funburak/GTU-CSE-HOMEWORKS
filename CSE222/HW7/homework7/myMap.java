/**
 * @author Burak Demirkaya
 */

package homework7;

import java.util.LinkedHashMap;
import java.util.Map;

/**
 * myMap class
 */
public class myMap{
    private LinkedHashMap<Character,info> map;
    private int mapSize;
    private String str;

    /**
     * Creates a new myMap object, sets the size to zero.
     */
    public myMap(){
        map = new LinkedHashMap<Character,info>();
        mapSize = 0;
    }

    /**
     * Preprocess the string. Lower the upper cases and ignores the non letter andd non white space characters.
     * 
     * @param string The String which will be preprocessed.
     * @return the preprocessed String.
     */
    private String preprocessString(String string){
        if(string == null) return null;
        String result = "";
        for(int i=0; i<string.length(); ++i){
            char c = string.charAt(i);
            if(Character.isUpperCase(c)){
                c = Character.toLowerCase(c);
                result += c;
            }
            else if(Character.isLetter(c) || Character.isWhitespace(c)){
                result += c;
            }
        }
        return result;
    }

    /**
     * Creates a map with the preprocessed String.
     * 
     * @param input The preprocessed String.
     */
    public void createMap(String input){
        this.str = this.preprocessString(input);
        if(str == null){
            System.out.println("Please enter a non-null string.");
            return;
        }
        String[] words = str.split(" "); // Split the preprocessed string into String array.

        for(String str : words){
            for(int i=0; i<str.length(); ++i){
                char c = str.charAt(i);
                if(!map.containsKey(c)){
                    info infoValue = new info();
                    infoValue.push(str);
                    map.put(c, infoValue);
                    mapSize++;
                }
                else{
                    info infoValue = map.get(c);
                    infoValue.push(str);
                    map.put(c,infoValue);
                }
            }
        }
    }

    /**
     * Prints out the details of the map.
     */
    public void displayMap(){
        for(Map.Entry<Character,info> entry : map.entrySet()){
            Character ch = entry.getKey();
            info value = entry.getValue();
            System.out.println("Letter: " + ch  + " - " + "Count: " + value.getCount() + " - " + "Words: " + value.getWords().toString());
        }
    }

    /**
     * 
     * @return the LinkedHashMap.
     */
    public LinkedHashMap<Character, info> getMap() {
        return map;
    }

    /**
     * 
     * @return the size of the map.
     */
    public int getMapSize() {
        return mapSize;
    }
    
    /**
     * 
     * @return the preprocessed String.
     */
    public String getStr() {
        return str;
    }
}