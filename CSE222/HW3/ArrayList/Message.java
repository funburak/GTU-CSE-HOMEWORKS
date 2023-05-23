/**
 * @author Burak Demirkaya 
 */

package ArrayList;

/**
 * Message class of the social media software.
 */
public class Message {
    private int messageId;
    private int senderId;
    private int receiverId;
    private String content;

    /**
     * Creates a new Message object.
     * 
     * @param messageId The ID of the Message.
     * @param sender The sender Account of the Message.
     * @param receiver The receiver Account of the Message.
     * @param content The content of the Message.
     */
    public Message(int messageId, Account sender, Account receiver, String content){
        this.messageId = messageId;
        this.senderId = sender.getAccountId();
        this.receiverId = receiver.getAccountId();
        this.content = content;
    }

    /**
     * 
     * @return The ID of the Message.
     */
    public int getMessageId() {
        return messageId;
    }

    /**
     * Sets the ID of the Message.
     * 
     * @param messageId The ID of the Message.
     */
    public void setMessageId(int messageId) {
        this.messageId = messageId;
    }

    /**
     * 
     * @return The ID of the sender Account.
     */
    public int getSenderId() {
        return senderId;
    }

    /**
     * Sets the ID of the sender Account.
     * 
     * @param senderId The ID of the sender Account.
     */
    public void setSenderId(int senderId) {
        this.senderId = senderId;
    }

    /**
     * 
     * @return The ID of the receiver Account.
     */
    public int getReceiverId() {
        return receiverId;
    }

    /**
     * Sets the ID of the receiver Account.
     * 
     * @param receiverId The ID of the receiver Account.
     */
    public void setReceiverId(int receiverId) {
        this.receiverId = receiverId;
    }

    /**
     * 
     * @return The content of the Message.
     */
    public String getContent() {
        return content;
    }

    /**
     * Sets the content of the Message.
     * 
     * @param content The content of the Message.
     */
    public void setContent(String content) {
        this.content = content;
    }
}
