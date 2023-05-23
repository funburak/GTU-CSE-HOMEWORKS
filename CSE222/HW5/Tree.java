
/**
 * @author Burak Demirkaya
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

import javax.swing.JFrame;
import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;

/**
 * Tree class.
 */
public class Tree {
    private String[][] text;
    private JFrame frame;
    private JTree tree;

    /**
     * Creates a new Tree object.
     * Creates a 1x1 String array.
     * Creates a new JFrame object.
     */
    public Tree(){
        text = new String[1][1];
        frame = new JFrame();
        frame.setSize(500,500);
        frame.setResizable(false);
        frame.setTitle("JTree");
        frame.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
    }

    /**
     * Reads the filename and stores the informations into an 2D dynamic String array.
     * 
     * @param filename The name of the file.
     */
    public void readFromFile(String filename){
        try {
            Scanner s = new Scanner(new File(filename));
            int rowNumber = 0;
            int colNumber = 0;
            while(s.hasNextLine()){
                String line = s.nextLine();
                String[] nodes = line.split(";");
                colNumber++;

                if(rowNumber >= text.length){
                    String[][] newText = new String[text.length+1][colNumber];
                    for(int i=0; i<text.length; ++i){
                        newText[i] = text[i];
                    }
                    text = newText;
                }
                text[rowNumber] = new String[nodes.length];
                for(int i=0; i<nodes.length; ++i){
                    text[rowNumber][i] = nodes[i];
                }
                rowNumber++;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * Creates JTree from 2D String array that has been read from the .txt file.
     */
    public void createTree(){
        DefaultMutableTreeNode root = new DefaultMutableTreeNode("Root");
        for(int i=0; i<text.length; ++i){
            DefaultMutableTreeNode parent = root;
            for(int j=0; j<text[i].length; ++j){
                DefaultMutableTreeNode child = getChild(parent, text[i][j]);
                if(child == null){
                    child = new DefaultMutableTreeNode(text[i][j]);
                    parent.add(child);
                }
                parent = child;
            }
        }
        tree = new JTree(root);
        showTree();
    }

    /**
     * Displays the tree.
     */
    public void showTree(){
        frame.add(tree);
        frame.setVisible(true);
    }

    /**
     * Checks whether the parent Node has a child named node.
     * 
     * @param parent Parent node.
     * @param node The String node that will be checked.
     * @return The child of that node if parent has a child named node, otherwise null.
     */
    private DefaultMutableTreeNode getChild(DefaultMutableTreeNode parent, String node){
        for(int i=0; i<parent.getChildCount(); ++i){
            DefaultMutableTreeNode child = (DefaultMutableTreeNode) parent.getChildAt(i);
            if(child.toString().equals(node)){
                return child;
            }
        }
        return null;
    }

    /**
     * Applies the BFS algorithm in the JTree using queue.
     * 
     * @param input The String that will be searched in the JTree.
     */
    public void BFS(String input){
        Queue<DefaultMutableTreeNode> queue = new LinkedList<DefaultMutableTreeNode>();
        queue.offer((DefaultMutableTreeNode) tree.getModel().getRoot());

        int count=1;
        while(!queue.isEmpty()){
            DefaultMutableTreeNode current = queue.poll();
            if(current.toString().equals(input)){
                System.out.println("Step " + count + " -> " + current.toString() + " (Found!)");
                return;
            }
            System.out.println("Step " + count + " -> " +current.toString());
            for(int i=0; i<current.getChildCount(); ++i){
                queue.offer((DefaultMutableTreeNode) current.getChildAt(i));
            }
            count++;
        }
        System.out.println("Not Found!");
    }
    
    /**
     * Applies DFS algorithm in the JTree using a recursive helper method.
     * 
     * @param input The String that will be searched in the JTree.
     */
    public void DFS(String input){
        DefaultMutableTreeNode root = (DefaultMutableTreeNode) tree.getModel().getRoot();
        if(!DFSHelper(root, input, 1)){
            System.out.println("Not Found!");
        }
    }

    /**
     * Helper method of the DFS algorithm. Uses recursion.
     * 
     * @param root The root of the JTree.
     * @param input The String that will be searched in the JTree.
     * @param step The number of steps that has been done.
     * @return True if the input has been found, otherwise false.
     */
    private boolean DFSHelper(DefaultMutableTreeNode root, String input,int step){
        if(root == null){
            return false;
        }
        if(root.toString().equals(input)){
            System.out.println("Step " + step + " -> " + root.toString() + " (Found!)");
            return true;
        }
        System.out.println("Step " + step + " -> " + root.toString());
        for(int i=root.getChildCount()-1; i>=0; --i){
            boolean result = DFSHelper((DefaultMutableTreeNode) root.getChildAt(i), input,step+1);
            if(result){
                return true;
            }
        }
        return false;
    }

    /**
     * Applies post-order traversal search algorithm in the JTree using a recursive helper method.
     * 
     * @param input The String that will be searched in the JTree.
     */
    public void postOrderTraversal(String input){
        DefaultMutableTreeNode root = (DefaultMutableTreeNode) tree.getModel().getRoot();
        if(!postOrderTraversalHelper(root, input,1)){
            System.out.println("Not Found!");
        }
    }

    /**
     * Helper method of the post-order traversal search algorithm. Uses recursion.
     * 
     * @param root The root of the JTree.
     * @param input The String that will be searched in the JTree.
     * @param step The number of steps that has been done.
     * @return true if input has been found, otherwise false.
     */
    private boolean postOrderTraversalHelper(DefaultMutableTreeNode root, String input, int step){
        if(root == null){
            return false;
        }
        boolean result = false;
        for(int i=0; i<root.getChildCount(); ++i){
            result = postOrderTraversalHelper((DefaultMutableTreeNode) root.getChildAt(i), input, step+1);
        }
        if(root.toString().equals(input)){
            System.out.println("Step " + step + " -> " + root.toString() + " (Found!)");
            return true;
        }
        if(!result){
            System.out.println("Step " + step + " -> " + root.toString()); 
        }
        return result;
    }

    /**
     * Moves a source node into the destination node. If destination node does not exist in JTree, create it, if exists overwrite şt.
     * 
     * @param source The String array of the source node.
     * @param destination The String of the destination node.
     */
    public void move(String[] source, String destination){
        DefaultMutableTreeNode root = (DefaultMutableTreeNode) tree.getModel().getRoot();
        DefaultMutableTreeNode curr = root;

        DefaultMutableTreeNode sourceNode = getNode(curr,source);
        if(sourceNode == null){
            System.out.print("Cannot move ");
            for(int i=0; i<source.length; ++i){
                System.out.print(source[i] + "->");
            }
            System.out.print(" because it does not exist in the tree.\n");
            return;
        }
        
        DefaultMutableTreeNode destinationNode = getChild(curr, destination);
        
        if(destinationNode == null){
            if(source.length == 2){
                destinationNode = new DefaultMutableTreeNode(destination);
                curr.add(destinationNode);
                DefaultMutableTreeNode parent = (DefaultMutableTreeNode) sourceNode.getParent();
                if(parent.isLeaf()){
                    parent.removeFromParent();
                }
                sourceNode.removeFromParent();
                destinationNode.add(sourceNode);
            }
            if(source.length == 3){
                destinationNode = new DefaultMutableTreeNode(destination);
                curr.add(destinationNode);
                DefaultMutableTreeNode parentSource = (DefaultMutableTreeNode) sourceNode.getParent();
                DefaultMutableTreeNode childSource = new DefaultMutableTreeNode(parentSource);
                destinationNode.add(childSource);
                DefaultMutableTreeNode grandChildSource = new DefaultMutableTreeNode(sourceNode);
                sourceNode.removeFromParent();
                childSource.add(grandChildSource);
            }
            if(source.length == 4){
                destinationNode = new DefaultMutableTreeNode(destination);
                curr.add(destinationNode);
                DefaultMutableTreeNode grandParentSource = (DefaultMutableTreeNode) sourceNode.getParent().getParent();
                destinationNode.add(grandParentSource);
                DefaultMutableTreeNode child = new DefaultMutableTreeNode(grandParentSource);
                grandParentSource.add(child);
                DefaultMutableTreeNode grandChild = new DefaultMutableTreeNode(sourceNode);
                child.add(grandChild);
            }
        }
        else{
            DefaultMutableTreeNode overwriteNode = getChild(destinationNode, sourceNode.toString());
            if(overwriteNode != null){
                DefaultMutableTreeNode parent = (DefaultMutableTreeNode) overwriteNode.getParent();
                overwriteNode.removeFromParent();
                if(parent.getChildCount() == 0){
                    parent.removeFromParent();
                }
            }
            else{
                if(source.length == 3){
                    overwriteNode = new DefaultMutableTreeNode(sourceNode.getParent());
                    destinationNode.add(overwriteNode);
                    overwriteNode.add(sourceNode);
                }
                if(source.length == 4){
                    overwriteNode = new DefaultMutableTreeNode(sourceNode.getParent().getParent());
                    destinationNode.add(overwriteNode);
                    DefaultMutableTreeNode parent = new DefaultMutableTreeNode(source[2]);
                    overwriteNode.add(parent);
                    parent.add(sourceNode);
                }
            }
        }
       
        DefaultMutableTreeNode parent = (DefaultMutableTreeNode) sourceNode.getParent();
        while(parent != null && parent.getChildCount() == 0 && !parent.isRoot()){
            DefaultMutableTreeNode grandparent = (DefaultMutableTreeNode) parent.getParent();
            parent.removeFromParent();
            parent = grandparent;
        }
        
        JTree tree2 = new JTree(curr);
        frame.dispose();
        this.movedTree(tree2);
    }

    /**
     * Displays the new JTree that a node has been moved to another node.
     * 
     * @param tree The JTree that will represent the tree.
     */
    public void movedTree(JTree tree){
        JFrame frame2= new JFrame("Moved JTree");
        frame2.setSize(500, 500);
        frame2.add(tree);
        frame2.setVisible(true);
        frame2.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
    }

    /**
     * Checks whether the given String array contains the JTree. 
     * 
     * @param root The root of the JTree.
     * @param source The String array of the source.
     * @return the last node of the source if it found in the tree, otherwise null.
     */
    private DefaultMutableTreeNode getNode(DefaultMutableTreeNode root, String[] source) {
        DefaultMutableTreeNode node = root;
        for (String s : source) {
            boolean found = false;
            for (int i = 0; i < node.getChildCount(); i++) {
                DefaultMutableTreeNode child = (DefaultMutableTreeNode) node.getChildAt(i);
                if (child.toString().equals(s)) {
                    node = child;
                    found = true;
                    break;
                }
            }
            if (!found) {
                return null;
            }
        }
        return node;
    }
    

    /**
     * Main method of the Tree class.
     * 
     * @param args The arguments for main.
     */
    public static void main(String[] args){
        Tree tree = new Tree();
        int choice = -1;
        Scanner s = new Scanner(System.in);
        String input = null;
        String source = null;
        String destination = null;
        do{
            System.out.println("Select from the menu.");
            System.out.println("1. Read from the file and create tree.");
            System.out.println("2. Apply BFS algorithm.");
            System.out.println("3. Apply DFS algorithm.");
            System.out.println("4. Apply post order traversal algorithm.");
            System.out.println("5. Apply move operation.");
            System.out.println("0. Exit.");
            choice = s.nextInt();
            switch(choice){
                case 1:
                    tree.readFromFile("tree.txt");
                    tree.createTree();
                    System.out.println("Tree has been created.");
                    tree.showTree();
                    break;
                case 2:
                    System.out.println("Enter input.");
                    input = s.next();
                    System.out.println("Using BFS to find " + input + " in the tree...");
                    tree.BFS(input);
                    break;
                case 3:
                    if(input != null){
                        System.out.println("Using DFS to find " + input + " in the tree...");
                        tree.DFS(input);
                    }
                    else{
                        System.out.println("Enter input from the menu selection 2.");
                    }
                    break;
                case 4:
                    if(input != null){
                        System.out.println("Using Post-Order Traversal to find " + input + " in the tree...");
                        tree.postOrderTraversal(input);
                    }
                    else{
                        System.out.println("Enter input from the menu selection 2.");
                    }
                    break;
                case 5:
                    System.out.println("Enter the node you want to move from.(Enter the strings with ',' between them.)");
                    source = s.next();
                    System.out.println("Enter the node where you want to move.");
                    destination = s.next();
                    String[] sources = source.split(",");
                    tree.move(sources,destination);
                    break;
                case 0:
                    System.out.println("Terminating program...");
                    System.exit(-1);
                    break;
                default:
                    System.out.println("Enter valid item from the menu.");
                    break;
            }
        }while(choice!=0);
        s.close();
    }
}