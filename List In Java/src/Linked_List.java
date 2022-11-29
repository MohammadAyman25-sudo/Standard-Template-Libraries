class Node{
    public int info;
    public Node next;
    public Node prev;
    public Node(){
        next = null;
        prev = null;
        info = 0;
    }
}

public class Linked_List {
    private Node head;
    private Node tail;
    private int _size;
    public Linked_List(){
        head = null;
        tail = null;
        _size = 0;
    }
    void insert(int x){
        if(_size == 0){
            head = new Node();
            head.info = x;
            tail = head;
        }else{
            tail.next = new Node();
            tail.next.info = x;
            tail.next.prev = tail;
            tail = tail.next;
        }
        _size++;
    }
    void erase(){
        if(head == tail){
            head = null;
            tail = null;
            _size--;
        }
        else if(head == null){
            System.err.println("List is Empty");
        }
        else{
            tail = tail.prev;
            tail.next.prev = null;
            tail.next = null;
            _size--;
        }
    }
    int front(){
        if(head == null){
            System.err.println("List is Empty");
            //return 0;
        }
        return head.info;
    }
    int back(){
        if(head == null){
            System.err.println("List is Empty");
            return 0;
        }
        return tail.info;
    }
}
