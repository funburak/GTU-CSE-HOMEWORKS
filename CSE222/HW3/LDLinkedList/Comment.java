/**
 * @author Burak Demirkaya 
 */

package LDLinkedList;

/**
 * Comment of the social media software.
 */
public class Comment extends Interaction{
    private String content;

    private static int nextId = 1;

    /**
     * Creates a new Comment object.
     * 
     * @param user The Account user who has commented on the Post post.
     * @param post The Post post that will be commented on by the Account user.
     * @param content The content of the Comment.
     */
    public Comment(Account user, Post post, String content){
        super(user, post);
        this.setInteractionId(nextId++);
        this.content = content;
    }

    /**
     * 
     * @return The content of the Comment.
     */
    public String getContent() {
        return content;
    }

    /**
     * Sets the content of the Comment.
     * 
     * @param content The content of the Comment.
     */
    public void setContent(String content) {
        this.content = content;
    }
}
