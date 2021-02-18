class Stack: 

    def __init__(self):
        self.arr = []

    def push(self, val):
        self.arr.append(val)

    def pop(self):
        self.arr.pop()
    
    def top(self):
        return self.arr[-1]

    def size(self):
        return len(self.arr)

    def is_empty(self): 
        return self.size() == 0;

