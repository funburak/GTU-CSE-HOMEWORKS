/**
 * @author Burak Demirkaya 
 */

package LinkedList;

import java.util.LinkedList;

/**
 * Account class of the social media software.
 */
public class Account { 
    private boolean login;
    private int accountId;
    private String username;
    private String birthdate;
    private String location;
    private LinkedList<Post> posts; // node olarak eklenecek
    private LinkedList<Message> inboxMessages;
    private LinkedList<Message> outboxMessages;
    private LinkedList<Account> following;
    private LinkedList<Account> followers;
    private LinkedList<Account> blockedAccounts;
    private LinkedList<String> history;

    /**
     * Creates a new empty Account object.
     * 
     */
    public Account(){
        this(0,"","","");
    }

    /**
     * Creates a new Account object and sets it login status to false.
     * 
     * @param accountId The ID of the Account.
     * @param username The username of the Account.
     * @param birthdate The birthdate of the Account in String format.
     * @param location The current location of the Account.
     */
    public Account(int accountId, String username, String birthdate, String location){
        this.login = false;
        this.accountId = accountId;
        this.username = username;
        this.birthdate = birthdate;
        this.location = location;
        this.posts = new LinkedList<Post>();
        this.inboxMessages = new LinkedList<Message>();
        this.outboxMessages = new LinkedList<Message>();
        this.following = new LinkedList<Account>();
        this.followers = new LinkedList<Account>();
        this.blockedAccounts = new LinkedList<Account>();
        this.history = new LinkedList<String>();
    }

    /**
     * Logins the Account to the software.
     * Checks if any other account has logged in before, if so terminates the method.
     * 
     * @param currentAccounts The Accounts that has been created so far.
     */
    public void login(LinkedList<Account> currentAccounts){
        boolean loggedIn = false;
        Account loggedInAccount = new Account();
        for(int i=0; i<currentAccounts.size(); ++i){ 
            if(currentAccounts.get(i).isLogin()){
                loggedIn = true;
                loggedInAccount = currentAccounts.get(i);
                break;
            }
        }
        if(!loggedIn){
            this.login = true;
            System.out.println("Succesfully logged into account " + this.getUsername());
        }
        else{
            System.err.println(this.getUsername() + " cannot login because " + loggedInAccount.getUsername() + " has already logged in.");
            return;
        }
    }

    /**
     * Logs out the Account from the software.
     * Condition: If the Account has logged in before.
     * 
     */
    public void logout(){
        if(this.isLogin()){
            login = false;
            System.out.println(this.getUsername() + " has succesfully logged out.");
        }
        else{
            System.err.println(this.getUsername() + " cannot logout without logging in.");
            return;
        }
    }

    /**
     * Account shares a post.
     * Condition: If the Account is logged in.
     * 
     * @param newPost The post object that will be shared.
     */
    public void sharePost(Post newPost){
        if(this.isLogin()){
            posts.add(newPost);
            this.addHistory(new String("You have shared a post: " + newPost.getContent()));
        }
        else{
            System.err.println(this.getUsername() + " cannot share post without logging in.");
            return;
        }
    }

    /**
     * Account views the posts of user.
     * Condition: If the Account is logged in.
     * 
     * @param user The Account whose posts will be viewed.
     */
    public void viewPosts(Account user){
        if(this.isLogin()){
            if(user.posts != null){
                for(int i=0; i<user.posts.size(); ++i){
                    System.out.println("(Post ID: " + user.posts.get(i).getPostId() + ") " + user.getUsername() + ": " + user.posts.get(i).getContent());
                }
                this.addHistory(new String("You have viewed posts of " + user.getUsername()));
            }
            else{
                System.err.println(user.getUsername() + " has no posts shared.");
                return;
            }
        }
        else{
            System.err.println(this.getUsername() + " cannot view posts of " + user.getUsername() + " without logging in.");
            return;
        }
    }

    /**
     * Account object likes the post of the user.
     * Condition: If the Account is logged in.
     * 
     * @param user The Account user whose post will be liked.
     * @param postId The ID of the post which will be liked.
     */
    public void likePost(Account user, int postId){
        if(this.isLogin()){
            boolean postExist = false;
            int index = 0;
            for(int i=0; i<user.posts.size(); ++i){
                if(user.posts.get(i).getPostId() == postId){
                    postExist = true;
                    index = i;
                    break;
                }
            }
            if(postExist){
                user.posts.get(index).likePosts(this);
                this.addHistory(new String("You have liked " + user.getUsername() + "'s post id: " + postId));
            }
            else{
                System.err.println("There is no such post with " + postId + " in the account " + user.getUsername());
                return;
            }
        }
        else{
            System.err.println(this.getUsername() + " cannot like post of " + user.getUsername() + " without logging in.");
            return;
        }
    }

    /**
     * Account object unlikes the post of user that he/she has liked before.
     * Condition: If the Account is logged in.
     * Condition: If Account object has liked user's post before unlike it, otherwise terminate the method.
     * 
     * @param user The Account user whose post will be unliked.
     * @param postId The ID of the post that will be unliked.
     */
    public void unlikePost(Account user, int postId){
        if(this.isLogin()){
            boolean postExist = false;
            int index = 0;
            for(int i=0; i<user.posts.size(); ++i){
                if(user.posts.get(i).getPostId() == postId){
                    postExist = true;
                    index = i;
                    break;
                }
            }
            if(postExist){
                if(user.posts.get(index).unlikePosts(this)){
                    this.addHistory(new String("You have unliked " + user.getUsername() + "'s post id: " + postId));
                }
            }
            else{
                System.err.println("There is no such post with " + postId + " in the account " + user.getUsername());
                return;
            }
        }
        else{
            System.err.println(this.getUsername() + " cannot unlike post of " + user.getUsername() + " without logging in.");
            return;
        }
    }

    /**
     * Account objects comments on the user's post with ID postId.
     * Condition: If the Account is logged in.
     * 
     * @param user The Account user whose post will be commented on.
     * @param postId The ID of the post that will be commented on.
     * @param comment The content of the comment.
     */
    public void commentPost(Account user, int postId, String comment){
        if(this.isLogin()){
            boolean postExist = false;
            int index = 0;
            for(int i=0; i<user.posts.size(); ++i){
                if(user.posts.get(i).getPostId() == postId){
                    postExist = true;
                    index = i;
                    break;
                }
            }
            if(postExist){
                user.posts.get(index).commentPosts(this,comment);
                this.addHistory(new String("You have commented on " + user.getUsername() + "'s post id: " + postId));
            }
            else{
                System.err.println("There is no such post with " + postId + " in the account " + user.getUsername());
                return;
            }
        }
        else{
            System.err.println(this.getUsername() + " cannot comment on post of " + user.getUsername() + " without logging in.");
            return;
        }
    }

    /**
     * Account object uncomments the post that he/she has commented on before.
     * Condition: If the Account is logged in.
     * Condition: If the Account object has commented on the post before remove it, otherwise terminate the method.
     * 
     * @param user The Account user whose post will be uncommented on.
     * @param postId The ID of the post that will be uncommented on.
     */
    public void uncommentPost(Account user, int postId){
        if(this.isLogin()){
            boolean postExist = false;
            int index = 0;
            for(int i=0; i<user.posts.size(); ++i){
                if(user.posts.get(i).getPostId() == postId){
                    postExist = true;
                    index = i;
                    break;
                }
            }
            if(postExist){
                if(user.posts.get(index).uncommentPosts(this)){
                    this.addHistory(new String("You have uncommented on " + this.getUsername() + "'s post id: " + postId));
                }
            }
            else{
                System.err.println("There is no such post with " + postId + " in the account " + user.getUsername());
                return;
            }
        }
        else{
            System.err.println(this.getUsername() + " cannot uncomment on post of " + user.getUsername() + " without logging in.");
            return;
        }
    }

     /**
     * Account object views the post interactions of the Account user.
     * Condition: If the Account is logged in.
     * In order to print out the details of the likers/commenters, currentAccounts that has been created so far is needed.
     * 
     * @param user The Account user whose posts interactions will be viewed.
     * @param currentAccounts The Accounts that has been created so far.
     */
    public void viewInteractions(Account user, LinkedList<Account> currentAccounts){
        if(this.isLogin()){
            if(user.posts != null){
                for(int i=0; i<user.posts.size(); ++i){
                    user.posts.get(i).interactions(currentAccounts);
                }
                this.addHistory(new String("You have viewed post interactions of " + user.getUsername()));
            }
            else{
                System.err.println(user.getUsername() + " has no posts shared.");
                return;
            }
        }
        else{
            System.err.println(this.getUsername() + " cannot view interactions of " + user.getUsername() + " 's posts without logging in.");
            return;
        }
    }

    /**
     * Account objects follows the Account user.
     * Condition: If the Account is logged in.
     * 
     * @param user The Account user who will be followed.
     */
    public void follow(Account user){
        if(this.isLogin()){
            if(this.getUsername().equals(user.getUsername())){
                System.err.println("You cannot follow yourself.");
                return;
            }
            if(!this.following.contains(user)){
                this.following.add(user);
                user.followers.add(this);
                this.addHistory(new String("You have followed " + user.getUsername()));
            }
            else{
                System.out.println("You have already followed " + user.getUsername());
                return;
            }
        }
        else{
            System.err.println(this.getUsername() + " cannot follow " + user.getUsername() + " without logging in.");
            return;
        }
    }

    /**
     * Account objects unfollows the Account user if he/she has followed him/her before.
     * Condition: If the Account is logged in.
     * Condition: If the Account object has followed Account user before unfollow him/her, otherwise terminate the method.
     * 
     * @param user The Account user who will be unfollowed.
     */
    public void unfollow(Account user){
        if(this.isLogin()){
            boolean isFollowing = false;
            int index = 0;
            int index2 = 0;
            if(this.getUsername().equals(user.getUsername())){
                System.err.println("You cannot unfollow yourself.");
                return;
            }
            for(int i=0; i<following.size(); ++i){
                if(following.get(i).getUsername().equals(user.getUsername())){
                    isFollowing = true;
                    index = i;
                    break;
                }
            }
            for(int i=0; i<user.followers.size(); ++i){
                if(user.followers.get(i).getUsername().equals(this.getUsername())){
                    index2 = i;
                    break;
                }
            }
            if(isFollowing){
                this.following.remove(index);
                user.followers.remove(index2);
                System.out.println("You have succesfully unfollowed " + user.getUsername());
                this.addHistory(new String("You have unfollowed " + user.getUsername()));

            }
            else{
                System.err.println(this.getUsername() + " cannot unfollow " + user.getUsername() + " because he/she is not following him/her.");
                return;
            }
        }
    }

     /**
     * Account object blocks the user and if he/she is following user, unfollow the user.
     * Condition: If the Account is logged in.
     * 
     * @param user The Account user who will be blocked.
     */
    public void block(Account user){
        if(this.isLogin()){
            if(this.getUsername().equals(user.getUsername())){
                System.err.println("You cannot block yourself.");
                return;
            }
            else{
                if(!blockedAccounts.contains(user)){
                    blockedAccounts.add(user);
                    System.out.println("You have succesfully blocked " + user.getUsername());
                    this.unfollow(user);
                    this.addHistory(new String("You have blocked " + user.getUsername()));
                }
                else{
                    System.out.println("You have already blocked " + user.getUsername());
                }
            }
        }
        else{
            System.out.println(this.getUsername() + " cannot block someone without logging in.");
            return;
        }
    }

     /**
     * Account objects unblocks the user.
     * Condition: If the Account is logged in.
     * Condition: If the Account object has blocked user before unblock user, otherwise terminate the method.
     * 
     * @param user The Account uswe who will be unblocked.
     */
    public void unblock(Account user){
        if(this.isLogin()){
            boolean isBlocked = false;
            int index = 0;
            for(int i=0; i<blockedAccounts.size(); ++i){
                if(blockedAccounts.get(i).getUsername().equals(user.getUsername())){
                    isBlocked = true;
                    index = i;
                    break;
                }
            }
            if(isBlocked){
                blockedAccounts.remove(index);
                System.out.println("You have succesfully unblocked " + user.getUsername());
                this.addHistory(new String("You have unblocked " + user.getUsername()));
            }
            else{
                System.err.println("You have not blocked " + user.getUsername() + " before.");
                return;
            }
        }
        else{
            System.out.println(this.getUsername() + " cannot unblock someone without logging in.");
            return;
        }
    }

    /**
     * Account object sends message to user.
     * Condition: If the Account is logged in.
     * Condition: If the Account is following user and if user has not blocked Account object before.
     * 
     * @param user The Account user who will receive the message.
     * @param message The Message object that will be sent to user.
     */
    public void sendMessage(Account user, Message message){
        if(this.isLogin()){
            boolean isFollowing = this.following.contains(user);
            boolean isBlocked = user.blockedAccounts.contains(this);
            if(this.getUsername().equals(user.getUsername())){
                System.err.println("You cannot send message to yourself.");
                return;
            }
            if(isBlocked){
                System.err.println("You cannot send message to " + user.getUsername() + " because he/she has blocked you!");
                return;
            }
            else{
                if(isFollowing){
                    this.outboxMessages.add(message);
                    user.inboxMessages.add(message);
                    this.addHistory(new String("You have sent message to " + user.getUsername()));
                }
                else{
                    System.err.println("You cannot send message to " + user.getUsername() + " because you are not following him/her.");
                    return;
                }
            }
        }
        else{
            System.err.println(this.getUsername() + " cannot send message to " + user.getUsername() + " without logging in.");
            return;
        }
    }

    /**
     * Account objects checks his/her outbox.
     * Condition: If the Account is logged in.
     * The Account that has been created so far is needed in order to print out the details.
     * 
     * @param currentAccounts The Accounts that has been created so far.
     */
    public void viewOutbox(LinkedList<Account> currentAccounts){
        if(this.isLogin()){
            Account receiver = new Account();
            if(outboxMessages.size() != 0){
                System.out.println("There is/are " + outboxMessages.size() + " message(s) in the outbox.");
                for(int j=0; j<outboxMessages.size(); ++j){
                    for(int i=0; i<currentAccounts.size(); ++i){
                        if(currentAccounts.get(i).getAccountId() == outboxMessages.get(j).getSenderId()){
                            receiver = currentAccounts.get(i);
                            break;
                        }
                    }
                }
                for(int i=0; i<outboxMessages.size(); ++i){
                    System.out.println();
                    System.out.println("Message ID: " + outboxMessages.get(i).getMessageId());
                    System.out.println("From: " + receiver.getUsername());
                    System.out.println("To: " + this.getUsername());
                    System.out.println("Message: " + outboxMessages.get(i).getContent());
                }
            }
            else{
                System.out.println("There is/are " + outboxMessages.size() + " message(s) in the inbox.");
            }
            this.addHistory(new String("You have viewed your outbox."));
        }
        else{
            System.err.println( this.getUsername() + " cannot view inbox message(s) without logging in.");
            return;
        }
    }

    /**
     * Account objects checks his/her inbox.
     * Condition: If the Account is logged in.
     * The Account that has been created so far is needed in order to print out the details.
     * 
     * @param currentAccounts The Accounts that has been created so far.
     */
    public void viewInbox(LinkedList<Account> currentAccounts){
        if(this.isLogin()){
            Account sender = new Account();
            if(inboxMessages.size() != 0){
                System.out.println("There is/are " + inboxMessages.size() + " message(s) in the inbox.");
                for(int j=0; j<inboxMessages.size(); ++j){
                    for(int i=0; i<currentAccounts.size(); ++i){
                        if(currentAccounts.get(i).getAccountId() == inboxMessages.get(j).getSenderId()){
                            sender = currentAccounts.get(i);
                            break;
                        }
                    }
                }
                for(int i=0; i<inboxMessages.size(); ++i){
                    System.out.println();
                    System.out.println("Message ID: " + inboxMessages.get(i).getMessageId());
                    System.out.println("From: " + sender.getUsername());
                    System.out.println("To: " + this.getUsername());
                    System.out.println("Message: " + inboxMessages.get(i).getContent());
                }
            }
            else{
                System.out.println("There is/are " + inboxMessages.size() + " message(s) in the inbox.");
            }
            this.addHistory(new String("You have viewed your inbox."));
        }
        else{
            System.err.println(this.getUsername() + " cannot view inbox message(s) without logging in.");
            return;
        }
    }
    
     /**
     * Account objects views the profile of user.
     * Condition: If the Account is logged in.
     * Condition: If the user has not blocked the Account object before.
     * 
     * @param user The Account user whose profile will be viewed.
     */
    public void viewProfile(Account user){
        if(this.isLogin()){
            boolean isBlocked = user.blockedAccounts.contains(this);
            if(isBlocked){
                System.out.println("You cannot view profile of " + user.getUsername() + " because he/she has blocked you!");
                return;
            }
            System.out.println("User ID: " + user.getAccountId());
            System.out.println("Username: " + user.getUsername());
            System.out.println("Location: " + user.getLocation());
            System.out.println("Birth Date: " + user.getBirthdate());

            System.out.println(user.getUsername() + " is following " + user.following.size() + " account(s) and has " + user.followers.size() + " followers.");
            if(user.followers.size() != 0){
                System.out.print("The followers of " + user.getUsername() + " are: ");
                for(int i=0; i<user.followers.size(); ++i){
                    System.out.print(user.followers.get(i).getUsername() + ", ");
                }
                System.out.println();
            }
            if(user.following.size() != 0){
                System.out.print(user.getUsername() + " is following: ");
                for(int i=0; i<user.following.size(); ++i){
                    System.out.print(user.following.get(i).getUsername() + ", ");
                }
            }
            else{
                System.out.println(user.getUsername() + " is not following anyone.");
            }
            System.out.println( "\n" + user.getUsername() + " has " + user.posts.size() + " posts.");
            this.viewPosts(user);
            this.addHistory(new String("You have viewed profile of " + user.getUsername()));
        }
        else{
            System.err.println(this.getUsername() + " cannot view profile of" + user.getUsername() +  "without logging in.");
            return;
        }
    }

    /**
     * Adds the action history to the history list.
     * 
     * @param content The action history that will be added into history list.
     */
    private void addHistory(String content){
        history.add(content);
    }

    /**
     * Account views his/her action history.
     * Condition: If the Account is logged in.
     * 
     */
    public void showHistory(){
        if(this.isLogin()){
            for(int i=0; i<history.size(); ++i){
                System.out.println(history.get(i));
            }
        }
        else{
            System.out.println(this.getUsername() + " cannot view his/her history without logging in.");
            return;
        }
    }

    /**
     * 
     * @return The status of the login.
     */
    public boolean isLogin(){
        return login;
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
     * @param accountId The ID of the Accoun.
     */
    public void setAccountId(int accountId) {
        this.accountId = accountId;
    }

    /**
     * 
     * @return The username of the Account object.
     */
    public String getUsername() {
        return username;
    }

    /**
     * Sets the username of the Account.
     * 
     * @param username The username of the Account.
     */
    public void setUsername(String username) {
        this.username = username;
    }

    /**
     * 
     * @return The birthdate of the Account object in String format.
     */
    public String getBirthdate() {
        return birthdate;
    }

    /**
     * Sets the birthdate of the Account.
     * 
     * @param birthdate The birthdate of the Account in String format.
     */
    public void setBirthdate(String birthdate) {
        this.birthdate = birthdate;
    }

    /**
     * 
     * @return The location of the Account.
     */
    public String getLocation() {
        return location;
    }

    /**
     * Sets the location of the Account.
     * 
     * @param location The current location of the Account.
     */
    public void setLocation(String location) {
        this.location = location;
    }
}