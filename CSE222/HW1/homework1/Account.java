package homework1;


/**
 * @author Burak Demirkaya
 * 
 */

 /**
  * Account class of the social media software.
  */
public class Account {
    private boolean login;
    private int accountId;
    private String username;
    private String birthdate;
    private String location;
    private Post[] posts;
    private Message[] inboxMessages;
    private Message[] outboxMessages;
    private Account[] following;
    private Account[] followers;
    private Account[] blockedAccounts;

    /**
     * Creates an empty Account object.
     */
    public Account(){
        this.login = false;
    }

    /**
     * Creates a new Account object.
     * Sets the login status of the account false.
     * 
     * @param accountId The ID of the account.
     * @param username The username of the account.
     * @param birthdate Date of birth of the account.
     * @param location Current location of the account.
     */
    public Account(int accountId,String username, String birthdate, String location){
        this.username = username;
        this.birthdate = birthdate;
        this.location = location;
        this.accountId = accountId;
        this.login = false;
    }

    /**
     * Logs in the account.
     * 
     * First checks if one of the accounts has logged in before, if not, logs in the caller account.
     * Sets the login status of the account true.
     * 
     * @param currentAccounts Current accounts that has been created so far in order to check their login status. 
     */
    public void login(Account[] currentAccounts){
        Account loggedInAccount = new Account();
        boolean loggedIn = false;
        for(int i=0; i<currentAccounts.length; ++i){
            if(currentAccounts[i].isLogin()){
                loggedIn = true;
                loggedInAccount = currentAccounts[i];
                break;
            }
        }
        if(!loggedIn){
           this.login = true;
           System.out.printf("Succesfully logged into account %s.\n",this.getUsername());
        }
        else{
            System.out.printf("%s cannot login beacuse %s has already logged in!\n",this.getUsername(),loggedInAccount.getUsername());
            return;
        }
    }

    /**
     * Logs out the account.
     * 
     * If the account object has logged in, logs it out.
     * Sets the login status of the account false.
     */
    public void logout(){
        if(login){
            login = false;
            System.out.printf("Account %s has successfully logged out.\n",this.getUsername());
        }
        else{
            System.out.printf("%s cannot logout without logging in.\n",this.getUsername());
            return;
        }
    }

    /**
     * Shares a new post.
     * 
     * If account has no posts shared, opens a 1 size of Post array and puts the newPost post to its first index.
     * If account has shared more than one posts, opens up a new Post array with size 1 more than the previous post array. Copies the previous posts into it. 
     * Then puts the newPost at the end of it. Finally assigns new dynamic posts array to posts.
     * 
     * @param newPost A post object.
     * 
     */
    public void sharePost(Post newPost){
        if(this.isLogin()){
            if (posts == null) {
                posts = new Post[1];
                posts[0] = newPost;
                posts[0].setAccountId(this.getAccountId());
            }
            else{
                Post[] newPosts = new Post[posts.length + 1];
                for(int i=0;i<posts.length; ++i){
                    newPosts[i] = posts[i];
                }
                newPosts[posts.length] = newPost;
                newPosts[posts.length].setAccountId(this.getAccountId());
                posts = newPosts;
            }
        }
        else{
            System.out.printf("%s cannot share post without logging in.\n",this.getUsername());
            return;
        }
    }

    /**
     * Views the post of the user.
     * 
     * First checks if the Account object is logged in.
     * Prints out the posts of the user.
     * 
     * @param user The Account object whose posts will be viewed.
     */
    public void viewPosts(Account user){ // post classına eklenebilir
        if(this.isLogin()){
            if(user.posts != null){
                for(int i=0; i<user.posts.length; ++i){
                    System.out.printf("(PostID: %d) %s: %s.\n",user.posts[i].getPostId(),user.getUsername(),user.posts[i].getContent());
                }
            }
            else{
                System.out.println("This account has no posts shared.");
                return;
            }
        }
        else{
            System.out.printf("%s cannot view posts without logging in.\n",this.getUsername());
        }
    }

    /**
     * Likes the post of the user.
     * 
     * First checks if the Account object is logged in. Then likes the post of the user object if there exist a post with postID.
     * 
     * @param user The Account user whose post will be liked.
     * @param postID The ID of the posts which will be liked.
     * 
     */
    public void likePost(Account user,int postID){
        if(this.isLogin()){
            boolean postExist = false;
            int postIndex = 0;
            for(int i=0; i<user.posts.length; ++i){
                if(user.posts[i].getPostId() == postID){
                    postExist = true;
                    postIndex = i;
                    break;
                }
            }
            if(postExist){
                user.posts[postIndex].likePosts(this);
            }
            else{
                System.out.printf("There is not such a post with ID %d in the account %s",postID,user.getUsername());
            }
        }
        else{
            System.out.printf("%s cannot like post without logging in!\n",this.getUsername());
        }
    }

    /**
     * Comments on the post of the user.
     * 
     * First checks if the Account object is logged in. Then comments on the post of the user if there exists a post with postID.
     * 
     * @param user The Account user whose post will be commented.
     * @param postID The ID of the posts which will be commented.
     * @param comment The content of the comment.
     * 
     */
    public void commentPost(Account user,int postID,String comment){
        if(this.isLogin()){
            int postIndex = 0;
            boolean postExist = false;
            for(int i=0; i<user.posts.length; ++i){
                if(user.posts[i].getPostId() == postID){
                    postExist = true;
                    postIndex = i;
                    break;
                }
            }
            if(postExist){
                user.posts[postIndex].commentPosts(this,comment);
            }
            else{
                System.out.printf("There is not such a post with ID %d in the account %s",postID,user.getUsername());
            }
        }
        else{
            System.out.printf("%s cannot comment without logging in!\n",this.getUsername());
            return;
        }
    }

    /**
     * Views the interactions of the user's posts.
     * 
     * First checks if the Account object is logged in.
     * 
     * @param user The Account user whose posts' interactions will be viewed.
     * @param currentAccounts Current accounts that has been created so far in order to print their names who has liked/commented on posts.
     * 
     */
    public void viewInteractions(Account user,Account[] currentAccounts){
        if(this.isLogin()){
            if(user.posts != null){
                for(int i=0; i<user.posts.length; ++i){
                    user.posts[i].interactions(currentAccounts);
                }
            }
            else{
                System.out.printf("Username '%s' has no posts shared.\n",user.getUsername());
            }
        }
        else{
            System.out.printf("%s cannot view interactions without logging in.\n",this.getUsername());
            return;
        }
    }
    
    /**
     * Follows the user.
     * 
     * First checks if the Account object is logged in. 
     * Then opens a dynamic following Account array for the caller and follower Account array for the user.
     * Then fills these arrays with the Account properties.
     * 
     * 
     * @param user The Account user who will be followed.
     */
    public void follow(Account user){
        if(this.isLogin()){
            if(user.getUsername().equals(this.getUsername())){
                System.err.println("You cannot follow yourself!\n");
                return;
            }
            if(this.following == null){ // If there is no following account opens a 1 size of Account array
                this.following = new Account[1];
                this.following[0] = user;
            }
            else{ // When new following user is added, open a new following space and copy the remaining followers to it. Then add the new user at the end.
                Account[] newFollowing = new Account[this.following.length+1];      
                for(int i=0; i<this.following.length; ++i){
                    newFollowing[i] = this.following[i];
                }
                newFollowing[following.length] = user;            
                this.following = newFollowing;
            }
            if(user.followers == null){
                user.followers = new Account[1];
                user.followers[0] = this;
            }
            else{
                Account[] newFollowers = new Account[user.followers.length+1];
                for(int i=0; i<user.followers.length; ++i){
                    newFollowers[i] = user.followers[i];
                }
                newFollowers[user.followers.length] = this;
                user.followers = newFollowers;
            }
        }
        else{
            System.out.printf("%s cannot follow someone without logging in.\n",this.getUsername());
        }
    }

    /**
     * Blocks the user.
     * 
     * First checks if the Account object is logged in. Then blocks the user.
     * 
     * @param user The Account user who will be blocked.
     */
    public void block(Account user){
        if(this.isLogin()){
            if(this.blockedAccounts == null){ // If there is no blocked account opens a size of 1 Account array.
                blockedAccounts = new Account[1];
                blockedAccounts[0] = user;
                System.out.printf("You have successfully blocked %s.\n",user.getUsername());
            }
            else{ // If there are blocked accounts open up a new Account with size = previous size + 1. Sets the last blocked account to be user.
                Account[] newBlockedAccounts = new Account[blockedAccounts.length+1];
                for(int i=0; i<blockedAccounts.length; ++i){
                    newBlockedAccounts[i] = blockedAccounts[i];
                }
                newBlockedAccounts[blockedAccounts.length] = user;
                System.out.printf("You have successfully blocked %s.\n",user.getUsername());
            }
        }
        else{
            System.out.printf("%s cannot block someone without logging in.\n",this.getUsername());
        }
    }

    /**
     * Send message to user.
     * 
     * First checks if the Account object is logged in.
     * Then checks if the Account receiver has blocked the caller.
     * Then checks if the Account object is following receiver.
     * Then opens a dynamic outboxMessage array for the caller and inboxMessage for the receiver.
     * Then fills the arrays with Message properties.
     * 
     * @param receiver The Account user who will receive the message.
     * @param message  The Message object which will be sent to the receiver.
     */
    public void sendMessage(Account receiver, Message message){
        if(this.isLogin()){
            boolean isBlocked = false;
            boolean isFollowing = false;
            if(this.getUsername().equals(receiver.getUsername())){
                System.err.println("You cannot send message to yourself.");
                return;
            }
            for(int i=0;i<this.following.length; ++i){
                if(this.following[i].getUsername().equals(receiver.getUsername())){
                    isFollowing = true;
                    break;
                }
            }
            if(receiver.blockedAccounts != null){
                for(int i=0; i<receiver.blockedAccounts.length; ++i){
                    if(receiver.blockedAccounts[i].getUsername().equals(this.getUsername())){
                        isBlocked = true;
                        break;
                    }
                }
            }
            if(isBlocked){
                System.out.printf("You cannot send message to %s beacuse he/she has blocked you!\n",receiver.getUsername());
                return;
            }
            else{
                if(isFollowing){
                    if(this.outboxMessages == null){
                        this.outboxMessages = new Message[1];
                        this.outboxMessages[0] = message;
                    }
                    else{
                        Message[] newOutboxMessages = new Message[this.outboxMessages.length+1];
                        for(int i=0; i<this.outboxMessages.length; ++i){
                            newOutboxMessages[i] = this.outboxMessages[i];
                        }  
                        newOutboxMessages[this.outboxMessages.length] = message;
                        this.outboxMessages = newOutboxMessages;
                    }

                    if(receiver.inboxMessages == null){
                        receiver.inboxMessages = new Message[1];
                        receiver.inboxMessages[0] = message;
                    }
                    else{
                        Message[] newInboxMessages = new Message[receiver.inboxMessages.length+1];
                        for(int i=0; i<receiver.inboxMessages.length; ++i){
                            newInboxMessages[i] = receiver.inboxMessages[i];
                        }
                        newInboxMessages[receiver.inboxMessages.length] = message;
                        receiver.inboxMessages = newInboxMessages;
                    }
                }
                else{
                    System.out.printf("You cannot send message to %s beacuse you are not following him/her.",receiver.getUsername());
                    return;
                }
            }
        }
        else{
            System.out.printf("%s cannot send message without logging in.\n",this.getUsername());
            return;
        }
    }

    /**
     * Views outbox messages.
     * 
     * First checks if the Account object is logged in.
     * Then prints the outbox message details of the account.
     * 
     * @param currentAccounts The accounts that has been created so far in order to print the usernames of the message senders.
     */
    public void viewOutbox(Account[] currentAccounts){ 
        if(this.isLogin()){
            int outbox = 0;
            Account receiver = new Account();
            if(outboxMessages != null){
                outbox = outboxMessages.length;
                System.out.printf("There is/are %d message(s) in the outbox.\n",outbox);
                for(int i=0; i<currentAccounts.length; ++i){ 
                    for(int j=0; j<this.outboxMessages.length; ++j){
                        if(currentAccounts[i] != null){
                            if(currentAccounts[i].getAccountId() == this.outboxMessages[j].getReceiverId()){
                                receiver = currentAccounts[i];
                                break;
                            }
                        }
                    }
                }
                for(int i=0; i<outboxMessages.length; ++i){
                    System.out.printf("Message ID: %d\n",outboxMessages[i].getMessageId());
                    System.out.printf("From: %s\n",this.getUsername());
                    System.out.printf("To: %s\n",receiver.getUsername());
                    System.out.printf("Message: %s\n",outboxMessages[i].getContent());
                }
            }
            else{
                System.out.printf("There is/are %d message(s) in the outbox.\n",outbox);
            }
        }
        else{
            System.out.printf("%s cannot view outbox messages without logging in.\n",this.getUsername());
            return;
        }
    }

    /**
     * Views inbox messages.
     * 
     * First checks if the Account object is logged in.
     * Then prints the inbox messages details of the account.
     * 
     * @param currentAccounts The accounts that has been created so far in order to print the usernames of the message receivers.
     */
    public void viewInbox(Account[] currentAccounts){ 
        if(this.isLogin()){
            int inbox = 0;
            Account sender = new Account();
            if(inboxMessages != null){
                inbox = inboxMessages.length;
                System.out.printf("There is/are %d message(s) in the inbox.\n",inbox);
                for(int i=0; i<currentAccounts.length; ++i){ 
                    for(int j=0; j<this.inboxMessages.length; ++j){
                        if(currentAccounts[i] != null){
                            if(currentAccounts[i].getAccountId() == this.inboxMessages[j].getSenderId()){
                                sender = currentAccounts[i];
                                break;
                            }
                        }
                    }
                }
                for(int i=0; i<inboxMessages.length; ++i){
                    System.out.println();
                    System.out.printf("Message ID: %d\n",inboxMessages[i].getMessageId());
                    System.out.printf("From: %s\n",sender.getUsername());
                    System.out.printf("To: %s\n",this.getUsername());
                    System.out.printf("Message: %s\n",inboxMessages[i].getContent());
                }
            }
            else{
                System.out.printf("There is/are %d message(s) in the inbox.\n",inbox);
            }   
        }
        else{
            System.out.printf("%s cannot view your inbox messages without logging in.\n",this.getUsername());
            return;
        }
    }
    
    /**
     * Views profile of the account.
     * 
     * First checks if the Account object is logged in.
     * Then prints out the information of that account such as userID, username, birthdate, location, following and followers account's usernames and the number of the posts.
     * 
     * @param account The account user whose profile will be viewed.
     */
    public void viewProfile(Account account){
        if(this.isLogin()){
            int followerLength = 0;
            int followingLength = 0;
            int postsLength = 0;
            boolean isBlocked = false;
                if(account.blockedAccounts != null){
                    for(int i=0; i<account.blockedAccounts.length; ++i){
                        if(account.blockedAccounts[i].getUsername().equals(this.getUsername())){
                            isBlocked = true;
                            break;
                        }
                    }
                }
            if(isBlocked){
                System.out.printf("You cannot view this profile beacuse %s has blocked you!\n",account.getUsername());
                return;
            }
            System.out.println("User ID: " + account.getAccountId());
            System.out.println("Username: " + account.getUsername());
            System.out.println("Location: " + account.getLocation());
            System.out.println("Birth Date: " + account.getBirthdate());
            if(account.followers != null){
                followerLength = account.followers.length;
            }
            if(account.following != null){
                followingLength = account.following.length;
            }
            if(account.posts != null){
                postsLength = account.posts.length;
            }
            System.out.printf("%s is following %d account(s) and has %d follower(s).\n ",account.getUsername(),followingLength,followerLength);
            if(account.followers != null){
                System.out.printf("The followers of %s are: ",account.getUsername());
                for(int i=0; i<account.followers.length; ++i){
                    System.out.printf("%s, ",account.followers[i].getUsername());
                }
                System.out.println();
            }
            if(account.following != null){
                System.out.printf("%s is following: ",account.getUsername());
                for(int i=0;i<account.following.length; ++i){
                    System.out.printf("%s,",account.following[i].getUsername());
                }
            }
            else{
                System.out.printf("%s is not following anyone.",account.getUsername());
            }
            System.out.printf("\n%s has %d posts.\n",account.getUsername(),postsLength);
        }
        else{
            System.out.printf("%s cannot view someone's profile without logging in.",this.getUsername());
            return;
        } 
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
     * @param accountId The ID for the account.
     */
    public void setAccountId(int accountId) {
        this.accountId = accountId;
    }

    /**
     * 
     * @return The username of the account.
     */
    public String getUsername() {
        return username;
    }

    /**
     * Sets the username of the account.
     * 
     * @param username The username for the account.
     */
    public void setUsername(String username) {
        this.username = username;
    }

    /**
     * 
     * @return Date of birth of account in String format.
     */
    public String getBirthdate() {
        return birthdate;
    }

    /**
     * Sets the birthdate of the account.
     * 
     * @param birthdate Date of the birth of the account in String format.
     */
    public void setBirthdate(String birthdate) {
        this.birthdate = birthdate;
    }

    /**
     * 
     * @return The location of the account.
     */
    public String getLocation() {
        return location;
    }

    /**
     * Sets the location of the account.
     * 
     * @param location The location of the account.
     */
    public void setLocation(String location) {
        this.location = location;
    }

    /**
     * 
     * 
     * @return The login status.
     */
    public boolean isLogin(){
        return login;
    }
}