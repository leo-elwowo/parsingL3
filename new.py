class temp:
    def __init__(self) -> None:
        self.a = 2
        
    def __xor__(self, temp):
        print(3)
        
a = temp()
b = temp()

a ^ b

#on a redefini xor !!