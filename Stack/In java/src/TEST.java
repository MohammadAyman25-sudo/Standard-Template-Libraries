public class TEST {
    public static void main(String[] args) {
       Stack st = new Stack();
       st.push(5);
       st.push(4);
       st.push(8);
        try{
            System.out.println(st.size());
            System.out.println(st.top());
            st.pop();
            System.out.println(st.size());
            System.out.println(st.top());
            st.pop();
            System.out.println(st.size());
            System.out.println(st.top());
            st.pop();
            System.out.println(st.size());
            st.pop();
        }catch(Exception ex){
            System.out.println(ex);
        }
    }
}
