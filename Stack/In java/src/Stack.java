class StackNode{
    public int val;
    public StackNode next;
    public StackNode(){
        next = null;
    }
}

public class Stack {
    private StackNode tp, cur;
    private int _size;
    public Stack(){
        cur = tp = null;
        _size = 0;
    }
    public void push(int x){
        if(tp == null){
            tp = new StackNode();
        }else{
            cur = new StackNode();
            cur.next = tp;
            tp = cur;
        }
        tp.val = x;
        _size++;
    }
    public void pop() throws Exception{
        if(tp == null)
            throw new Exception("Stack is Empty!");
        cur = tp;
        tp = cur.next;
        cur = null;
        _size--;
    }

    public int top() throws Exception {
        if(tp == null)
            throw new Exception("Stack is Empty!");
        return tp.val;
    }

    public int size(){
        return _size;
    }
}
