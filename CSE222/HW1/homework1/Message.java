package homework1;


/**
 * @author Burak Demirkaya
 */

/**
 * Message class for the social media software.
 */
public class Message {
    private int messageId;
    private int senderId;
    private int receiverId;
    private String content;

    /**
     * Creates a new Message object.
     * 
     * @param messageID The ID of the message.
     * @param sender The sender account of the message.
     * @param receiver The receiver account of the message.
     * @param content The content of the message.
     */
    public Message(int messageID,Account sender, Account receiver, String content){
        this.senderId = sender.getAccountId();
        this.receiverId = receiver.getAccountId();
        this.content = content;
        this.messageId = messageID;
    }

    /**
     * 
     * @return The ID of the message.
     */
    public int getMessageId() {
        return messageId;
    }

    /**
     * Sets the ID of the message.
     * 
     * @param messageId The ID for the message.
     */
    public void setMessageId(int messageId) {
        this.messageId = messageId;
    }

    /**
     * 
     * @return The sender account's ID.
     */
    public int getSenderId() {
        return senderId;
    }

    /**
     * Sets the sender's ID of the message.
     * 
     * @param senderId The ID for the sender.
     */
    public void setSenderId(int senderId) {
        this.senderId = senderId;
    }

    /**
     * 
     * @return The receiver account's ID.
     */
    public int getReceiverId() {
        return receiverId;
    }

    /**
     * Sets the receiever ID of the message.
     * 
     * @param receiverId The ID for the receiver.
     */
    public void setReceiverId(int receiverId) {
        this.receiverId = receiverId;
    }

    /**
     * 
     * @return The content of the message.
     */
    public String getContent() {
        return content;
    }

    /**
     * Sets the content of the message.
     * 
     * @param content The content of the message.
     */
    public void setContent(String content) {
        this.content = content;
    }
}
