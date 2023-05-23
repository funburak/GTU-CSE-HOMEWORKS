/**
 * @author Burak Demirkaya 
 */

package LDLinkedList;

/**
 * TestClass1 class that test the Scenario 1.
 */
public class TestClass1 {
    /**
     * The main method that will test the Scenario 1.
     * 
     * @param args The arguments for main.
     */
    public static void main(String[] args) {
        long startTime = System.nanoTime();
        System.out.println("1. Creating Accounts...");
        Account gizemsungu = new Account(1,"gizemsungu","13.01.1993","Istanbul");
        System.out.printf("An account with username %s has been created.\n",gizemsungu.getUsername());
        Account sibelgulmez = new Account(2,"sibelgulmez","10.03.1995","Istanbul");
        System.out.printf("An account with username %s has been created.\n",sibelgulmez.getUsername());
        Account gokhankaya = new Account(3,"gokhankaya","15.05.1990","Istanbul");
        System.out.printf("An account with username %s has been created.\n",gokhankaya.getUsername());

        LDLinkedList<Account> currentAccounts = new LDLinkedList<Account>();
        currentAccounts.add(gizemsungu);
        currentAccounts.add(sibelgulmez);
        currentAccounts.add(gokhankaya);

        System.out.println("\n2. Logging into account (username: sibelgulmez)...");
        sibelgulmez.login(currentAccounts);

        System.out.println("\n3. Sharing two posts...");
        Post post1 = new Post(1,"I like Java.");
        sibelgulmez.sharePost(post1);

        Post post2 = new Post(2, "Java the coffee...");
        sibelgulmez.sharePost(post2);

        System.out.println("\n4. Following gizemsungu and gokhankaya...");
        sibelgulmez.follow(gizemsungu);
        sibelgulmez.follow(gokhankaya);
        
        System.out.println("\n5. Logging out...");
        sibelgulmez.logout();

        System.out.println("\n6. Logging into another account (username: gokhankaya)...");
        gokhankaya.login(currentAccounts);

        System.out.println("\n7. Viewing sibelgulmez's profile...");
        gokhankaya.viewProfile(sibelgulmez);

        System.out.println("\n8. Liking a post of sibelgulmez...");
        gokhankaya.likePost(sibelgulmez, 1);

        System.out.println("\n9. Adding a comment on a post of sibelgulmez...");
        gokhankaya.commentPost(sibelgulmez, 1, "me too!");

        System.out.println("\n10. Following sibelgulmez and gizemsungu...");
        gokhankaya.follow(sibelgulmez);
        gokhankaya.follow(gizemsungu);

        System.out.println("\n11. Sending a message to gizemsungu...");
        Message message = new Message(1, gokhankaya, gizemsungu, "This homework is too easy!");
        gokhankaya.sendMessage(gizemsungu, message);

        System.out.println("\n12. Logging out from account 'gokhankaya'...");
        gokhankaya.logout();

        System.out.println("\n13. Logging into another account (username:gizemsungu)...");
        gizemsungu.login(currentAccounts);

        System.out.println("\n14. Checking outbox...");
        gizemsungu.viewOutbox(currentAccounts);

        System.out.println("\n15. Checking inbox...");
        gizemsungu.viewInbox(currentAccounts);

        System.out.println("\n16. Viewing sibelgulmez's profile...");
        gizemsungu.viewProfile(sibelgulmez);

        System.out.println("\n17. Viewing sibelgulmez's post interactions...");
        gizemsungu.viewInteractions(sibelgulmez,currentAccounts);

        System.out.println("\n18. Liking sibelgulmez's posts...");
        gizemsungu.likePost(sibelgulmez, 1);
        gizemsungu.likePost(sibelgulmez, 2);

        System.out.println("\n19. Viewing sibelgulmez's post interactions...");
        gizemsungu.viewInteractions(sibelgulmez,currentAccounts);

        System.out.println();
        gizemsungu.logout();

        long endTime   = System.nanoTime();
        long totalTime = (endTime - startTime) / 1000000;
        System.out.println(totalTime);
    }
}
