class Node:
    def __init__(self, x = 0, n = None):
        self.val = x
        self.next = n

class Linked_List:
    def __init__(self):
        self.sz = 0
        self.head = None
    def insert(self, x):
        if(self.sz == 0):
            self.head = Node()
            self.tail = self.head
            self.head.val = x
            self.tail.next = None
        else:
            new_node = Node()
            self.tail.next = new_node
            self.tail = self.tail.next
            self.tail.val = x
        self.sz += 1
        
    
    def erase_end(self):
        if(self.sz == 0):
            return None
        
        if(self.head == self.tail):
            self.tail = None
        else:
            cur = self.head
            while cur.next is not self.tail:
                cur = cur.next
            self.tail = cur
            self.tail.next = None
        self.sz -= 1
        
        
    def erase_front(self):
        if(self.sz == 0):
            return None
        if(self.head == self.tail):
            self.head = None
            self.tail = None
        else:
            cur = self.head
            self.head = self.head.next
            cur = None
        self.sz -= 1
            
    def size(self):
        return self.sz
    def display(self):
        cur = self.head
        while cur != None:
            print(cur.val, end=' ')
            cur = cur.next


l = Linked_List()
print("Size: ", l.size())
l.insert(5)
print("Size: ", l.size())
l.insert(4)
print("Size: ", l.size())
l.insert(6)
print("Size: ", l.size())
l.display()
print()
l.erase_end()
print("Size: ", l.size())
l.display()
l.erase_front()
print("Size: ", l.size())
l.display()

