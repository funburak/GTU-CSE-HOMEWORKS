/**
 * @author Burak Demirkaya
 */

package LDLinkedList;

import java.util.AbstractList;

/**
 * LDLinkedList structure class that use lazy deletion strategy.
 */
public class LDLinkedList<E> extends AbstractList<E>{
    
    private int size = 0;
    private Node<E> head = null;
    private int lazyDeleteCount = 0;

    /**
     * Node inner class of LDLinkedList
     */
    private static class Node<E>{
        private E data;
        private Node<E> next;
        private boolean isLazyDeleted;

        private Node(E data){
            this.data = data;
            this.next = null;
            this.isLazyDeleted = false;
        }
    }

    /**
     * Creates a new LDLinkedList list using super class constructor.
     */
    public LDLinkedList(){
        super();
    }

    /**
     * Checks the status of the node whether it has marked as lazy deleted or not.
     * 
     * @param index The index of the node that will be checked.
     * @return The status of the nodes lazily deleted status.
     */
    public boolean lazyDeleted(int index){
        Node<E> curr = head;
        for(int i=0; i<index; ++i){
            curr = curr.next;
        }
        return curr.isLazyDeleted;
    }

    /**
     * @return The number of nodes that has been lazily deleted.
     */
    public int getLazyDeleteCount(){
        return lazyDeleteCount;
    }

    @Override
    public boolean add(E data){
        Node<E> newNode = new Node<E>(data);
        if(head == null){
            head = newNode;
        }
        else{
            Node<E> curr = head;
            while(curr.next != null){
                curr = curr.next;
            }
            curr.next = newNode;
        }
        size++;
        return true;
    }

    @Override
    public E remove(int index){
        if(index < 0 || index >= size){
            throw new IndexOutOfBoundsException("Invalid index");
        }
        else{
            Node<E> toRemoved = getNode(index);
            if(toRemoved.isLazyDeleted){ // If the same node has marked before, return null
                return null;
            }
            toRemoved.isLazyDeleted = true;
            this.lazyDeleteCount++;
            
            if(this.lazyDeleteCount == 2){
                Node<E> prev = null;
                Node<E> curr = head;
                while(curr != null){
                    if(curr.isLazyDeleted){
                        if(prev == null){
                            head = curr.next;
                        }
                        else{
                            prev.next = curr.next;
                        }
                        this.lazyDeleteCount--;
                        size--;
                        if(this.lazyDeleteCount == 0){
                            break;
                        }
                    }
                    else{
                        prev = curr;
                    }
                    curr = curr.next;
                }
            }
            return toRemoved.data;
        }
    }

    /**
     * Takes an index and returns the node at that position.
     * 
     * @param index The index of the list element.
     * @return The node at the given index.
     */
    public Node<E> getNode(int index) {
        if(index < 0 || index >= size){
            throw new IndexOutOfBoundsException("Invalid index");
        }
        else{
            Node<E> curr = head;
            for(int i=0; i<index; ++i){
                curr = curr.next;
            }
            return curr;
        }
    }

    @Override
    public String toString() {
        Node<E> curr = head;
        String s1 = "";
        while(curr != null){
            if(!curr.isLazyDeleted){
                s1 += curr.data.toString() + " ";
            }
            curr = curr.next;
        }
        return s1;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public E get(int index) {
        if(index < 0 || index >= size){
            throw new IndexOutOfBoundsException("Invalid index");
        }
        else{
            Node<E> curr = head;
            for(int i=0; i<index; ++i){
                curr = curr.next;
            }
            return curr.data;
        }
    }
}