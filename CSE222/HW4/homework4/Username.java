package homework4;
/**
 * Username class of the museum entrance validation.
 */
public class Username {
    
    private String username;

    /**
     * Creates a new Username object.
     * 
     * @param username The username of the officer.
     */
    public Username(String username){
        this.username = username;
    }

    /**
     * 
     * @return true if the length of the username String is more than 1.
     */
    public boolean checkLengthOfUsername(){
        return (username.length() >= 1);
    }

    /**
     * Checks whether the username String contains only letters with recursion.
     * 
     * @param username The username of the officer.
     * @return true if the username is valid, false otherwise.
     */
    public boolean checkIfValidUsername(String username){
        if(username.length() == 0){
            return false;
        }
        else if(username.length() == 1){
            char firstLetter = username.charAt(0);
            return Character.isLetter(firstLetter);
        }
        else{
            char c = username.charAt(0);
            String subString = username.substring(1);
            return Character.isLetter(c) && checkIfValidUsername(subString);
        }
    }
    
    /**
     * 
     * @return the username of the officer.
     */
    public String getUsername() {
        return username;
    }
}
