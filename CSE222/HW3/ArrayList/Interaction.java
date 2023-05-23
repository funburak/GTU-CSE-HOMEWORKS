/**
 * @author Burak Demirkaya 
 */


package ArrayList;

/**
 * Interaction class of the socail media software.
 */
public abstract class Interaction {
    /**
     * The ID of the Interaction.
     */
    protected int interactionId;
    /**
     * The ID of the Account.
     */
    protected int accountId;
    /**
     * The ID of the Post.
     */
    protected int postId;

    /**
     * Creates a new Interaction object.
     * 
     * @param user The Account user who made the interaction.
     * @param post The Post post which will be interacted with.
     */
    public Interaction(Account user, Post post){
        this.accountId = user.getAccountId();
        this.postId = post.getPostId();
    }

    /**
     * 
     * @return The ID of the Interaction.
     */
    public int getInteractionId() {
        return interactionId;
    }

    /**
     * Sets the ID of the Interaction.
     * 
     * @param interactionId The ID of the Interaction.
     */
    public void setInteractionId(int interactionId) {
        this.interactionId = interactionId;
    }

    /**
     * 
     * @return The ID of the Account.
     */
    public int getAccountId() {
        return accountId;
    }

    /**
     * Sets the ID of the Account.
     * 
     * @param accountId The ID of the Account.
     */
    public void setAccountId(int accountId) {
        this.accountId = accountId;
    }

    /**
     * 
     * @return The ID of the Post.
     */
    public int getPostId() {
        return postId;
    }

    /**
     * Sets the ID of the Post.
     * 
     * @param postId The ID of the Post.
     */
    public void setPostId(int postId) {
        this.postId = postId;
    }
}
