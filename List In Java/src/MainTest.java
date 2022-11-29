public class MainTest {
    public static void main(String[] args) {
        Linked_List l = new Linked_List();
        l.insert(5);
        l.insert(8);
        l.insert(6);
        System.out.println(l.front());
        System.out.println(l.back());
        l.erase();
        System.out.println(l.front());
        System.out.println(l.back());
        l.erase();
        System.out.println(l.front());
        System.out.println(l.back());
        l.erase();
        System.out.println(l.front());
        System.out.println(l.back());
        l.erase();
        System.out.println(l.front());
        System.out.println(l.back());
    }
}
