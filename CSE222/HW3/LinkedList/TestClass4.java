/**
 * @author Burak Demirkaya 
 */

package LinkedList;

import java.util.LinkedList;

/**
 * TestClass4 class that will test the Scenario 1, Scenario 2, Scenario 3 and Scenario 4.
 */
public class TestClass4 {
    /**
     * The main method that will test the Scenario 1, Scenario 2, Scenario 3 and Scenario 4 but only print the details of Scenario 4.
     * 
     * @param args The arguments for main.
     */
    public static void main(String[] args) {
        long startTime = System.nanoTime();
        Account gizemsungu = new Account(1,"gizemsungu","13.01.1993","Istanbul");
        Account sibelgulmez = new Account(2,"sibelgulmez","10.03.1995","Istanbul");
        Account gokhankaya = new Account(3,"gokhankaya","15.05.1990","Istanbul");
        Account burakdemirkaya = new Account(4,"burakdemirkaya","01.12.2000","Istanbul");
        Account account5 = new Account(5, "account5", "29.03.1980", "Istanbul");
        Account account6 = new Account(6, "account6", "29.03.1981", "Istanbul");
        Account account7 = new Account(7, "account7", "29.03.1982", "Istanbul");
        Account account8 = new Account(8, "account8", "29.03.1983", "Istanbul");
        Account account9 = new Account(9, "account9", "29.03.1984", "Istanbul");
        Account account10 = new Account(10, "account10", "29.03.1985", "Istanbul");

        LinkedList<Account> currentAccounts = new LinkedList<Account>();
        currentAccounts.add(gizemsungu);
        currentAccounts.add(sibelgulmez);
        currentAccounts.add(gokhankaya);
        currentAccounts.add(burakdemirkaya);
        currentAccounts.add(account5);
        currentAccounts.add(account6);
        currentAccounts.add(account7);
        currentAccounts.add(account8);
        currentAccounts.add(account9);
        currentAccounts.add(account10);

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

        gizemsungu.login(currentAccounts);

        Post post3 = new Post(1,"Post1");
        gizemsungu.sharePost(post3);

        Post post4 = new Post(2,"Post2");
        gizemsungu.sharePost(post4);

        gizemsungu.logout();

        sibelgulmez.login(currentAccounts);

        //sibelgulmez.viewProfile(gizemsungu);

        System.out.println();
        //sibelgulmez.viewPosts(gizemsungu);

        sibelgulmez.likePost(gizemsungu, 1);

        sibelgulmez.logout();

        gokhankaya.login(currentAccounts);
        
        //gokhankaya.viewProfile(sibelgulmez);

        //gokhankaya.viewPosts(sibelgulmez);

        gokhankaya.commentPost(sibelgulmez, 2, "Nice!");

        Message message2 = new Message(2, gokhankaya, gizemsungu, "Hello!");
        gokhankaya.sendMessage(gizemsungu, message2);

        gokhankaya.logout();

        gizemsungu.login(currentAccounts);

        //gizemsungu.viewProfile(gizemsungu);

        //gizemsungu.viewInbox(currentAccounts);

        gizemsungu.logout();

        gizemsungu.login(currentAccounts);

        gizemsungu.block(sibelgulmez);

        gizemsungu.logout();

        sibelgulmez.login(currentAccounts);

        sibelgulmez.viewProfile(gizemsungu);

        Message message3 = new Message(3, sibelgulmez, gizemsungu, "Hello!");
        sibelgulmez.sendMessage(gizemsungu, message3);

        System.out.println();
        sibelgulmez.logout();

        System.out.println("\nDid not print out the details of Scenario 1, Scenario 2 and Scenario 3.");
        System.out.println("----------------Scenario 4 starts here--------------------");

        System.out.println("\n1. burakdemirkaya logs in.");
        burakdemirkaya.login(currentAccounts);
        
        System.out.println("\n2. burakdemirkaya follows gizemsungu and gokhankaya.");
        burakdemirkaya.follow(gizemsungu);
        burakdemirkaya.follow(gokhankaya);

        System.out.println("\n3. burakdemirkaya views profile of gizemsungu.");
        burakdemirkaya.viewProfile(gizemsungu);

        System.out.println("\n4. burakdemirkaya likes gizemsungu's posts.");
        burakdemirkaya.likePost(gizemsungu, 1);
        burakdemirkaya.likePost(gizemsungu, 2);

        System.out.println("\n5. burakdemirkaya views post interactions of gizemsungu.");
        burakdemirkaya.viewInteractions(gizemsungu, currentAccounts);

        System.out.println("\n6. burakdemirkaya shares a post.");
        Post post5 = new Post(1, "FORZABBL");
        burakdemirkaya.sharePost(post5);

        System.out.println("\n7. burakdemirkaya follows account5.");
        burakdemirkaya.follow(account5);
        
        System.out.println("\n8. burakdemirkaya blocks account10.");
        burakdemirkaya.block(account10);

        System.out.println("\n9. burakdemirkaya logs out.");
        burakdemirkaya.logout();

        System.out.println("\n10. gizemsungu logs in.");
        gizemsungu.login(currentAccounts);

        System.out.println("\n11. gizemsungu views her own profile.");
        gizemsungu.viewProfile(gizemsungu);

        System.out.println("\n12. gizemsungu follows burakdemirkaya.");
        gizemsungu.follow(burakdemirkaya);

        System.out.println("\n13. gizemsungu views profile of burakdemirkaya.");
        gizemsungu.viewProfile(burakdemirkaya);

        System.out.println("\n14. gizemsungu likes post of burakdemirkaya by accident.");
        gizemsungu.likePost(burakdemirkaya, 1);

        System.out.println("\n15. gizemsungu views posts interactions of burakdemirkaya.");
        gizemsungu.viewInteractions(burakdemirkaya, currentAccounts);

        System.out.println("\n16. gizemsungu unlikes the post she liked.");
        gizemsungu.unlikePost(burakdemirkaya, 1);

        System.out.println("\n17. gizemsungu again views posts interactions of burakdemirkaya");
        gizemsungu.viewInteractions(burakdemirkaya, currentAccounts);

        System.out.println("\n18. gizemsungu comments on burakdemirkaya's post.");
        gizemsungu.commentPost(burakdemirkaya, 1, "LETS GO BBL!");

        System.out.println("\n19. gizemsungu views posts interactions of burakdemirkaya");
        gizemsungu.viewInteractions(burakdemirkaya, currentAccounts);

        System.out.println("\n20. gizemsungu deletes her comment on burakdemirkaya's post.");
        gizemsungu.uncommentPost(burakdemirkaya, 1);

        System.out.println("\n21. gizemsungu views posts interactions of burakdemirkaya");
        gizemsungu.viewInteractions(burakdemirkaya, currentAccounts);

        System.out.println("\n22. gizemsungu views her actions history.");
        gizemsungu.showHistory();

        System.out.println("\n23. gizemsungu logs out.");
        gizemsungu.logout();

        System.out.println("\n24. account10 logs in.");
        account10.login(currentAccounts);

        System.out.println("\n25. account10 tries to view profile of burakdemirkaya.");
        account10.viewProfile(burakdemirkaya);

        System.out.println("\n26. account10 logs out.");
        account10.logout();

        System.out.println("\n27. burakdemirkaya logs in.");
        burakdemirkaya.login(currentAccounts);

        System.out.println("\n28. burakdemirkaya unblocks account10.");
        burakdemirkaya.unblock(account10);

        System.out.println("\n29. burakdemirkaya follows account10.");
        burakdemirkaya.follow(account10);

        System.out.println("\n30. burakdemirkaya sends a message to account10.");
        Message message4 = new Message(1, burakdemirkaya, account10, "Sorry that was a mistake.");
        burakdemirkaya.sendMessage(account10, message4);

        System.out.println("\n31. burakdemirkaya views his own profile.");
        burakdemirkaya.viewProfile(burakdemirkaya);

        System.out.println("\n32. burakdemirkaya unfollows account5 and gokhankaya.");
        burakdemirkaya.unfollow(account5);
        burakdemirkaya.unfollow(gokhankaya);

        System.out.println("\n33. burakdemirkaya views his own profile again.");
        burakdemirkaya.viewProfile(burakdemirkaya);

        System.out.println("\n34. burakdemirkaya logs out.");
        burakdemirkaya.logout();

        long endTime   = System.nanoTime();
        long totalTime = (endTime - startTime) / 1000000;
        System.out.println(totalTime);
    }
}
