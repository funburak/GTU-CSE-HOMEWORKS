package homework1;


/**
 * @author Burak Demirkaya
 */

/**
 * TestClass2 class that tests the Scenario 1 and Scenario 2.
 */
public class TestClass2 {
    /**
     * Main method to test Scenario 1 and Scenario 2.
     * 
     * @param args
     */
    public static void main(String[] args) {
        long startTime = System.nanoTime();
        Account gizemsungu = new Account(1,"gizemsungu","13.01.1993","Istanbul");
        Account sibelgulmez = new Account(2,"sibelgulmez","10.03.1995","Istanbul");
        Account gokhankaya = new Account(3,"gokhankaya","15.05.1990","Istanbul");
        
        // In order to print the details of the users, I stored accounts in currentAccount array.
        Account[] currentAccounts = new Account[3];
        currentAccounts[0] = gizemsungu;
        currentAccounts[1] = sibelgulmez;
        currentAccounts[2] = gokhankaya;

        sibelgulmez.login(currentAccounts);

        Post post1 = new Post(1,"I like Java.");
        sibelgulmez.sharePost(post1);

        Post post2 = new Post(2, "Java the coffee...");
        sibelgulmez.sharePost(post2);

        sibelgulmez.follow(gizemsungu);
        sibelgulmez.follow(gokhankaya);
        
        sibelgulmez.logout();

        gokhankaya.login(currentAccounts);

        //gokhankaya.viewProfile(sibelgulmez);

        //gokhankaya.viewPosts(sibelgulmez);

        gokhankaya.likePost(sibelgulmez, 1);

        gokhankaya.commentPost(sibelgulmez, 1, "me too!");

        gokhankaya.follow(sibelgulmez);
        gokhankaya.follow(gizemsungu);

        Message message = new Message(1, gokhankaya, gizemsungu, "This homework is too easy!");
        gokhankaya.sendMessage(gizemsungu, message);

        gokhankaya.logout();

        gizemsungu.login(currentAccounts);

        //gizemsungu.viewOutbox(currentAccounts);

        //gizemsungu.viewInbox(currentAccounts);

        //gizemsungu.viewProfile(sibelgulmez);

        //gizemsungu.viewPosts(sibelgulmez);

        //gizemsungu.interactions(sibelgulmez,currentAccounts);

        gizemsungu.likePost(sibelgulmez, 1);
        gizemsungu.likePost(sibelgulmez, 2);

        //gizemsungu.interactions(sibelgulmez,currentAccounts);

        gizemsungu.logout();

        System.out.println("\nDid not print the details of the Scenario 1...");
        System.out.println("---------------Scenario 2 starts here---------------------");

        System.out.println("\n1. gizemsungu logs in...");
        gizemsungu.login(currentAccounts);

        System.out.println("\n2. gizemsungu shares a post...");
        Post post3 = new Post(1,"Post1");
        gizemsungu.sharePost(post3);

        System.out.println("\n3. gizemsungu shares another post...");
        Post post4 = new Post(2,"Post2");
        gizemsungu.sharePost(post4);

        System.out.println("\n4. gizemsungu logs out...");
        gizemsungu.logout();

        System.out.println("\n5. sibelgulmez logs in...");
        sibelgulmez.login(currentAccounts);

        System.out.println("\n6. sibegulmez views gizemsungu's profile...");
        sibelgulmez.viewProfile(gizemsungu);

        System.out.println();
        sibelgulmez.viewPosts(gizemsungu);

        System.out.println("\n7. sibelgulmez likes Post1...");
        sibelgulmez.likePost(gizemsungu, 1);

        System.out.println("\n8. sibelgulmez logs out...");
        sibelgulmez.logout();

        System.out.println("\n9. gokhankaya logs in...");
        gokhankaya.login(currentAccounts);
        
        System.out.println("\n10. gokhankaya views sibelgulmez's profile...");
        gokhankaya.viewProfile(sibelgulmez);

        gokhankaya.viewPosts(sibelgulmez);

        System.out.println("\n11. gokhankaya comments on Post2...");
        gokhankaya.commentPost(sibelgulmez, 2, "Nice!");

        System.out.println("\n12. gokhankaya sends message to gizemsungu...");
        Message message2 = new Message(2, gokhankaya, gizemsungu, "Hello!");
        gokhankaya.sendMessage(gizemsungu, message2);

        System.out.println("\n13. gokhankaya logs out...");
        gokhankaya.logout();

        System.out.println("\n14. gizemsungu logs in...");
        gizemsungu.login(currentAccounts);

        System.out.println("\n15. gizemsungu views her own profile...");
        gizemsungu.viewProfile(gizemsungu);

        System.out.println("\n16. gizemsungu checks her inbox...");
        gizemsungu.viewInbox(currentAccounts);

        System.out.println("\n17. gizemsungu logs out...");
        gizemsungu.logout();

        long endTime   = System.nanoTime();
        long totalTime = (endTime - startTime) / 1000000;
        System.out.println(totalTime);
    }
}
