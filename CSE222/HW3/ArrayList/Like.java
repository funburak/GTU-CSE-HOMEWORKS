/**
 * @author Burak Demirkaya 
 */

package ArrayList;

/**
 * Like class of the social media software.
 */
public class Like extends Interaction {
    
    /**
     * Creates a new Like object.
     * 
     * @param user The Account user who has liked the Post post.
     * @param post The Post post which has been liked by the Account user.
     */
    public Like(Account user, Post post){
        super(user, post);
    }
}
