/**
 * @author Burak Demirkaya 
 */

package ArrayList;

import java.util.ArrayList;

/**
 * TestClass3 class that will test Scenario 1, Scenario 2 and Scenario 3.
 */
public class TestClass3 {
    /**
     * The main method that will test Scenario 1, Scenario 2 and Scenario 3 but only print the details of Scenario 3.
     * 
     * @param args The arguments for main.
     */
    public static void main(String[] args) {
        long startTime = System.nanoTime();
        Account gizemsungu = new Account(1,"gizemsungu","13.01.1993","Istanbul");
        Account sibelgulmez = new Account(2,"sibelgulmez","10.03.1995","Istanbul");
        Account gokhankaya = new Account(3,"gokhankaya","15.05.1990","Istanbul");
        
        ArrayList<Account> currentAccounts = new ArrayList<Account>(3);
        currentAccounts.add(gizemsungu);
        currentAccounts.add(sibelgulmez);
        currentAccounts.add(gokhankaya);

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

        System.out.println("\nDid not print the details of the Scenario 1 and Scenario 2...");
        System.out.println("---------------Scenario 3 starts here.------------------");

        System.out.println("\n1. gizemsungu logs in...");
        gizemsungu.login(currentAccounts);

        System.out.println("\n2. gizemsungu blocks sibelgulmez...");
        gizemsungu.block(sibelgulmez);
        
        System.out.println("\n3. gizemsungu logs out...");
        gizemsungu.logout();

        System.out.println("\n4. sibelgulmez logs in...");
        sibelgulmez.login(currentAccounts);

        System.out.println("\n5. sibelgulmez tries to view profile of gizemsungu...");
        sibelgulmez.viewProfile(gizemsungu);

        System.out.println("\n6. sibelgulmez tries to send a message to gizemsungu...");
        Message message3 = new Message(3, sibelgulmez, gizemsungu, "Hello!");
        sibelgulmez.sendMessage(gizemsungu, message3);

        System.out.println();
        sibelgulmez.logout();

        long endTime   = System.nanoTime();
        long totalTime = (endTime - startTime) / 1000000;
        System.out.println(totalTime);
        
    }
}
