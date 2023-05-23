package homework4;

import java.util.Stack;

/**
 * Password1 class of the museum entrance valdiation.
 */
public class Password1 {
    
    private String password1;
    private static int count = 0;

    /**
     * Creates a new Password1 object.
     * @param password1 The password1 of the officer.
     */
    public Password1(String password1){
        this.password1 = password1;
    }

    /**
     * Checks the length of the password String.
     * 
     * @return true if the password1 String's length is more than 8, false otherwise.
     */
    public boolean checkLengthOfPassword1(){
        return (password1.length() >= 8);
    }

    /**
     * Counts the number of the brackets in the password1 String.
     * 
     * @return true if the number of the brackets are more than 2, false otherwise.
     */
    public boolean checkBracketsOfPassword1(){
        int bracketCount = 0;
        for(int i=0; i<password1.length(); ++i){
            char c = password1.charAt(i);
            if((c == '(') || (c == ')') || (c == '{') || (c == '}') || (c == '[') || (c == ']')){
                bracketCount++;
            }
        }
        return (bracketCount >= 2);
    }

    /**
     * Checks whether the password1 String contains a character of username.
     * 
     * @param username The username of the officer.
     * @param password1 The password1 of the officer.
     * @return true if password1 contains at least 1 character of username, false otherwise.
     */
    public boolean containsUserNameSpirit(String username, String password1){
        Stack<Character> stack = new Stack<Character>();
        for(int i=0; i<username.length(); ++i){
            char c = username.charAt(i);
            stack.push(c);
        }

        for(int i=0; i<password1.length(); ++i){
            char ch = password1.charAt(i);
            if(stack.contains(ch)){
                return true;
            }
        }
        return false;
    }

    /**
     * Checks whether the first bracket of the password1 is an open bracket.
     * 
     * @return true if the first bracket of the password1 is an open bracket, false otherwise.
     */
    public boolean checkFirstBracket(){
        Stack<Character> stack = new Stack<Character>();
        for(int i=0; i<password1.length(); ++i){
            char c = password1.charAt(i);
            if(!Character.isLetter(c)){
                stack.push(c);
            }
        }
        char firstBracket = ' ';
        while(!stack.isEmpty()){
            firstBracket = stack.pop();
        }
        if((firstBracket == ')') || (firstBracket == '}') || (firstBracket == ']')){
            return false;
        }
        return true;
    }

    /**
     * Checks if it possible to balance the brackets of the password1.
     * Counts the number of the each unique brackets and compares the number of each brackets.
     * 
     * @param password1 The password1 of the officer.
     * @return true if the password1 is balanced, false otherwise.
     */
    public boolean isBalancedPassword(String password1){
        Stack<Character> stack = new Stack<Character>();
        int openRoundBracketCount = 0;
        int closeRoundBracketCount = 0;
        int openCurlyBracketCount = 0;
        int closeCurlyBracketCount = 0;
        int openSquareBracketCount = 0;
        int closeSquareBracketCount = 0;
        for(int i=0; i<password1.length(); ++i){
            char c = password1.charAt(i);
            if(!Character.isLetter(c)){
                stack.push(c);
            }
        }
        char currentBracket = ' ';
        while(!stack.isEmpty()){
            currentBracket = stack.pop();
            switch (currentBracket){
                case '(':
                    openRoundBracketCount++;
                    break;
                case ')':
                    closeRoundBracketCount++;
                    break;
                case '{':
                    openCurlyBracketCount++;
                    break;
                case '}':
                    closeCurlyBracketCount++;
                    break;
                case '[':
                    openSquareBracketCount++;
                    break;
                case ']':
                    closeSquareBracketCount++;
                    break;
            }
        }
        if((openRoundBracketCount == closeRoundBracketCount) && (openCurlyBracketCount == closeCurlyBracketCount) && (openSquareBracketCount == closeSquareBracketCount)){
            return true;
        }
        else{
            return false;
        }
    }

    /**
     * Checks if it is possible to obtain a palindrome by rearranging the letters in the password1 String.
     * Removes brackets from the string to check for the letters only.
     * 
     * @param password1 The password1 of the officer.
     * @return true if it possible to obtain a palindrome, false otherwise.
     */
    public boolean isPalindromePossible(String password1){
        String newString = removeBrackets(password1);
        if(password1.length() < 1){
            return true;
        }
        else{
            char firstChar = newString.charAt(0);
            int lastIndex = newString.lastIndexOf(firstChar);
            if(lastIndex > 0){ // If the first character of the string is found later in the string.
                newString = newString.substring(1, lastIndex) + newString.substring(lastIndex+1);
                return isPalindromePossible(newString);
            }
            else if(lastIndex == 0){ // If the first character doesnt occur later in the string increase count by 1, if the single characters are more than 1 return false.
                newString = newString.substring(1);
                count++;
                if(count > 1){ // If the single characters are more than 1 in the string return false.
                    return false;
                }
                return isPalindromePossible(newString); 
            }
            else{
                return false;
            }
        }
    }

    /**
     * Removes the brackets of the password1 in order to check for the palindrome.
     * 
     * @param password1 The password1 of the officer.
     * @return password1 that the brackets has been removed.
     */
    private String removeBrackets(String password1){
        String result = "";
        for(int i=0; i<password1.length(); ++i){
            char c = password1.charAt(i);
            if(Character.isLetter(c)){
                result+= c;
            }
        }
        return result;
    }

    /**
     * 
     * @return password1 of the officer.
     */
    public String getPassword1() {
        return password1;
    }
}
