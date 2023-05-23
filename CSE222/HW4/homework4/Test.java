package homework4;

/**
 * Test class of the museum entry validation.
 */
public class Test {
    /**
     * Main method for the museum entry validation tests.
     * @param args Arguments for main.
     */
    public static void main(String[] args) {
        Username username = new Username("burak");
        Password1 password1 = new Password1("[rac()ecar]");
        Password2 password2 = new Password2(74);
        int[] denominations = {4,17,29};
        if(username.checkLengthOfUsername()){
            if(username.checkIfValidUsername(username.getUsername())){
                if(password1.checkLengthOfPassword1()){
                    if(password1.checkBracketsOfPassword1()){
                       if(password1.containsUserNameSpirit(username.getUsername(), password1.getPassword1())){
                            if(password1.checkFirstBracket()){
                                if(password1.isBalancedPassword(password1.getPassword1())){
                                    if(password1.isPalindromePossible(password1.getPassword1())){
                                        if(password2.checkIfValidPassword2()){
                                            if(password2.isExactDivision(password2.getPassword2(), denominations)){
                                                System.out.println("The username and passwords are valid. The door is opening, please wait.");
                                            }
                                            else{
                                                System.out.println("The password2 is invalid. It is not compatible with the denominations.");
                                            }
                                        }
                                        else{
                                            System.out.println("The password2 is invalid. It should be between 10 and 10,000.");
                                        }
                                    }
                                    else{
                                        System.out.println("The password1 is invalid. It should be possible to obtain a palindrome from the password1.");
                                    }
                                }
                                else{
                                    System.out.println("Password1 is invalid. It should be balanced.");
                                }
                            }
                            else{
                                System.out.println("The first bracket of password1 must be an open bracket.");
                            }
                        }
                        else{
                            System.out.println("The password1 is invalid. It should have at least 1 character from the username.");
                        }
                    }
                    else{
                        System.out.println("The password1 is invalid. It should have at least 2 brackets.");
                    }
                }
                else{
                    System.out.println("The password1 is invalid. It should have at least 8 characters.");
                }
            }
            else{
                System.out.println("The username is invalid. It should have letters only.");
            }
        }
        else{
            System.out.println("The username is invalid. It should have at least 1 character.");
        }
    }
}
