package homework1;



/**
 * @author Burak Demirkaya
 */

/**
 * Post class of the social media software.
 */
public class Post { 
    private int postId;
    private int accountId;
    private Like[] likes;
    private Comment[] comments;
    private String content;

    /**
     * Creates a new Post object.
     * 
     * @param postID The ID of the post.
     * @param content The content of the post.
     */
    public Post(int postID,String content){
        this.postId = postID;
        this.content = content;
    }

    /**
     * The Account user likes the post of the caller Account object.
     * 
     * @param user The Account user who will like the post.
     */
    public void likePosts(Account user){
        Like newLike = new Like(user,this);
        if(likes == null){
            likes = new Like[1];
            likes[0] = newLike;
        }
        else{
            Like[] newLikes = new Like[likes.length+1];
            for(int i=0; i<likes.length; ++i){
                newLikes[i] = likes[i];
            }
            newLikes[likes.length] = newLike;
            likes = newLikes;
        }
    }

    /**
     * The Account user comments on the post of the caller Account object.
     * 
     * @param user The Account user who will comment on the post.
     * @param comment The content of the comment.
     */
    public void commentPosts(Account user,String comment){
        Comment newComment = new Comment(user,this, comment);
        if(comments == null){
            comments = new Comment[1];
            comments[0] = newComment;
        }
        else{
            Comment[] newComments = new Comment[comments.length+1];
            for(int i=0; i<comments.length; ++i){
                newComments[i] = comments[i];
            }
            newComments[comments.length] = newComment;
            comments = newComments;
        }
    }

    /**
     * Prints the interactions(likes/comments) of the posts of the caller.
     * 
     * @param currentAccounts Current accounts that has been created so far in order to print their names who liked/commented on the posts.
     */
    public void interactions(Account[] currentAccounts){
        System.out.printf("(Post ID: %d): %s.\n",postId,content);
        if(likes != null){
            Account[] likedBy = new Account[likes.length];
            int index = 0;
            System.out.print("This post was liked by the following account(s) : ");
            for(int i=0;i<currentAccounts.length; ++i){
                for(int j=0; j<likes.length; ++j){
                    if(currentAccounts[i].getAccountId() == likes[j].getAccountId()){
                        likedBy[index] = currentAccounts[i];
                        index++;
                    }
                }
            }
            for(int i=0; i<likes.length; ++i)
            System.out.printf("%s,",likedBy[i].getUsername());
            System.out.println();
        }
        else{
            System.out.println("This post has no likes.");
        }
        if(comments != null){
            Account[] commentedBy = new Account[comments.length];
            int index2 = 0;
            System.out.printf("The post has %d comment(s).\n",comments.length);
            for(int i=0; i<currentAccounts.length; ++i){
                for(int j=0; j<comments.length; ++j){
                    if(currentAccounts[i].getAccountId() == comments[j].getAccountId()){
                        commentedBy[index2] = currentAccounts[i];
                        index2++;
                    }
                }
            }
            for(int i=0; i<comments.length; ++i){
                System.out.printf("Comment %d: '%s' said '%s'.\n",postId,commentedBy[i].getUsername(),comments[i].getContent());
            }
        }
        else{
            System.out.println("This post has no comments.");
        }
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
     * 
     * @return The content of the post.
     */
    public String getContent() {
        return content;
    }

    /**
     * Sets the content of the post.
     * 
     * @param content The content of the post.
     */
    public void setContent(String content) {
        this.content = content;
    }
}
