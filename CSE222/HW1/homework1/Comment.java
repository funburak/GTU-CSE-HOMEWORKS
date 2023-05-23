package homework1;

/**
 * Comment class of the social media software.
 */
public class Comment extends Interaction { 
    private String content;

    /**
     * Creates a new Comment object.
     * 
     * @param user The Account user who will comment on the post.
     * @param post The Post post which will be commented on.
     * @param content The content of the comment.
     */
    public Comment(Account user,Post post,String content){
        super(user,post);
        this.content = content;
    }

    /**
     * Sets the content of the comment.
     * 
     * @param content The content of the comment.
     */
    public void setContent(String content) {
        this.content = content;
    }

    /**
     * 
     * @return The content of the comment.
     */
    public String getContent() {
        return content;
    }
}
