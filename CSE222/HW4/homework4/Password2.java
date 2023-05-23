package homework4;
/**
 * Password2 class of the museum entry validation.
 */
public class Password2 {
    private int password2;

    /**
     * Creates a new Password2 object.
     * 
     * @param password2 The password2 of the officer.
     */
    public Password2(int password2){
        this.password2 = password2;
    }

    /**
     * Checks whether the password2 is between 10 and 10000.
     * @return true if password1 is between 10 and 10000, false otherwise. 
     */
    public boolean checkIfValidPassword2(){
        if(password2 > 10 && password2 < 10000){
            return true;
        }
        return false;
    }

    /**
     * Checks if it is possible to obtain the password2 by the summation of denominations.
     * 
     * @param password2 The password2 of the officer.
     * @param denominations The list of denominations.
     * @return true if it possible to obtain the password2 by the summation of the denominations, false otherwise.
     */
    public boolean isExactDivision(int password2, int[] denominations){      
        if(password2 == 0){
            return true;
        }
        for(int i=0; i<denominations.length; ++i) {
            if(password2 >= denominations[i] && isExactDivision(password2 - denominations[i], denominations)) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * 
     * @return the password2 of the officer.
     */
    public int getPassword2(){
        return password2;
    }
}
