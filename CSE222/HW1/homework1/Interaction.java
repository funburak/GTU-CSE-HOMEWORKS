package homework1;


/**
 * @author Burak Demirkaya
 */


/**
 * Interaction class of the social media software.
 * 
 */
public abstract class Interaction { 
    /**
     * The ID of the interaction.
     */
    protected int interactionId;
    /**
     * The ID of the account.
     */
    protected int accountId;
    /**
     * The ID of the post.
     */
    protected int postId;

    /**
     * Creates a new Interaction object.
     * 
     * @param user The user who interacts to the post.
     * @param post The post which will be interacted with.
     */
    public Interaction(Account user,Post post){ // interaction id eklenecek
        this.accountId = user.getAccountId();
        this.postId = post.getPostId();
    }

    /**
     * 
     * @return The ID of the interaction.
     */
    public int getInteractionId() {
        return interactionId;
    }

    /**
     * Sets the ID of the interaction.
     * 
     * @param interactionId The ID of the interaction.
     */
    public void setInteractionId(int interactionId) {
        this.interactionId = interactionId;
    }

    /**
     * 
     * @return The ID of the account.
     */
    public int getAccountId() {
        return accountId;
    }

    /**
     * Sets the ID of the account.
     * 
     * @param accountId The ID of the account.
     */
    public void setAccountId(int accountId) {
        this.accountId = accountId;
    }

    /**
     * 
     * @return The ID of the post.
     */
    public int getPostId() {
        return postId;
    }

    /**
     * Sets the ID of the post.
     * 
     * @param postId The ID of the post.
     */
    public void setPostId(int postId) {
        this.postId = postId;
    }
}
