/**
 * @author Burak Demirkaya 
 */

package LinkedList;

import java.util.LinkedList;

/**
 * Post class of the social media software.
 */
public class Post {
    private int postId;
    private int accountId;
    private LinkedList<Like> likes;
    private LinkedList<Comment> comments;
    private String content;

     /**
     * Creates a new Post object.
     * 
     * @param postId The ID of the Post.
     * @param content The content of the Post.
     */
    public Post(int postId, String content){
        this.postId = postId;
        this.content = content;
        this.likes = new LinkedList<Like>();
        this.comments = new LinkedList<Comment>();
    }

    /**
     * Account user likes the Post.
     * Creates a new Like object and adds it to the likes list.
     * 
     * @param user The Account user who will like the Post.
     */
    public void likePosts(Account user){
        Like newLike = new Like(user,this);
        likes.add(newLike);
    }

     /**
     * Account user unlikes the post that he/she has liked before.
     * Condition: If the Post has liked by the user before, unlike it otherwise return false.
     * 
     * @param user The Account user who will unlike the post that he/she has liked before.
     * @return True if the user has liked the Post before, otherwise return False.
     */
    public boolean unlikePosts(Account user){
        boolean isLiked = false;
        int index = 0;
        for(int i=0; i<likes.size(); ++i){
            if(likes.get(i).getAccountId() == user.getAccountId()){
                isLiked = true;
                index = i;
                break;
            }
        }
        if(isLiked){
            likes.remove(index);
            return true;
        }
        else{
            System.err.println(user.getUsername() + " did not like post with Id " + postId + " before, so he/she cannot unlike it.");
            return false;
        }
    }

    /**
     * Account user comments on the Post.
     * Creates a new Comment object and adds it to the list comments.
     * 
     * @param user The Account user who will comment on the post.
     * @param content The content of the comment.
     */
    public void commentPosts(Account user, String content){
        Comment newComment = new Comment(user, this, content);
        comments.add(newComment);
    }

    /**
     * Account user uncomments the post that he/she has commented on before.
     * Condition: If the Post has commented on before by the user uncomment it, otherwise return false.
     * 
     * @param user The Account user who will uncomment the post that he/she has commented on before.
     * @return True if the user has commented on the Post before, otherwise return False.
     */
    public boolean uncommentPosts(Account user){
        boolean isCommented = false;
        int index = 0;
        for(int i=0; i<comments.size(); ++i){
            if(comments.get(i).getAccountId() == user.getAccountId()){
                isCommented = true;
                index = i;
                break;
            }
        }
        if(isCommented){
            comments.remove(index);
            return true;
        }
        else{
            System.err.println(user.getUsername() + "did not comment on post with Id " + postId + " before, so he/she cannot uncomment it.");
            return false;
        }
    }

    /**
     * Prints out the details of the interaction of the Post.
     * In order to print out the likers/commenters this method needs the currentAccounts that has been created so far.
     * 
     * @param currentAccounts The Accounts that has been created so far.
     */
    public void interactions(LinkedList<Account> currentAccounts){
        System.out.println("(Post Id: " + postId + ") " + content);
        if(this.likes.size() !=  0){
            System.out.print("This post was liked by the following account(s): ");
            for(int i=0; i<likes.size(); ++i){
                Like like = likes.get(i);
                Account likedBy = new Account();
                for(Account user : currentAccounts){
                    if(user.getAccountId() == like.getAccountId()){
                        likedBy = user;
                        break;
                    }
                }
                System.out.print(likedBy.getUsername() + ", ");
            }
            System.out.println();
        }
        else{
            System.out.println("This post has no likes.");
        }

        if(this.comments.size() != 0){
            System.out.println("This post has " + (this.comments.size()) + " comment(s).");     
            for (int i = 0; i < comments.size(); ++i) {
                Comment comment = comments.get(i);
                Account commentedBy = new Account();
                for (Account user : currentAccounts) {
                    if (user.getAccountId() == comment.getAccountId()) {
                        commentedBy = user;
                        break;
                    }
                }
                System.out.println("Comment " + comment.getInteractionId() + ": " + commentedBy.getUsername() + " said " + comment.getContent());
            }
        }
        else{
            System.out.println("This post has no comments.");
        }
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
     * @return The content of the Post.
     */
    public String getContent() {
        return content;
    }

    /**
     * Sets the content of the Post.
     * 
     * @param content The content of the Post.
     */
    public void setContent(String content) {
        this.content = content;
    }
}