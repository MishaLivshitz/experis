

class myDs:

    def __init__(self, size):
        self.lst = [[0,0] for i in range(size)]
        self.resetVal = 0
        self.resetStep = 0

    def get(self, index):
        
        if self.resetStep > self.lst[index][1]:
            self.lst[index][0] = self.resetVal
            self.lst[index][1] = self.resetStep

        return self.lst[index][0]

    def set(self, index, nv):
        self.lst[index][0] = nv
        self.lst[index][1] = self.resetStep

    def reset(self, nv):
        self.resetStep +=1
        self.resetVal = nv


myds = myDs(10)
myds.set(1,100)
myds.set(5,300)
myds.get(1)
myds.get(5)
myds.set(1,400)
myds.reset(999)
myds.set(7,888)
myds.set(9,1234)
myds.reset(777)
myds.set(9,1234)
myds.reset(777)
print(myds.lst)
print(myds.get(0))
print(myds.get(5))
print(myds.get(7))
print(myds.get(1))
print(myds.get(0))
print(myds.get(9))
print(myds.lst)