package homework1;


/**
 * @author Burak Demirkaya
 */

/**
 * Like class of the socail media software.
 */
public class Like extends Interaction { 
    /**
     * Creates a new Like object.
     * 
     * @param user The Account user who will like the post.
     * @param post The Post post which will be liked by the user.
     */
    public Like(Account user,Post post){ // interaction id eklenecek
        super(user,post);
    }
}
