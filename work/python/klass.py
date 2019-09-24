

class Rational():
    unit = 1

    def __init__(self, num, denom = 1):
        self.num = num
        self.denom = denom

    def __str__(self):
        return str(self.num) + '/' + str(self.denom)

    def gcd(a,b):

        if b == 0:
            return a

        return Rational.gcd(b, a % b)

    def reduce(self):
        gcdVal = Rational.gcd(self.num, self.denom)
        self.num //= gcdVal
        self.denom //= gcdVal
        
        
    def __mul__(self, rational):
        newVal = Rational(self.num * rational.num, self.denom * rational.denom)
        newVal.reduce()

        return newVal

    def __add__(self, rational):

        newVal = Rational(self.num, self.denom)            
        rational.num *= newVal.denom
        newVal.num *= rational.denom
        newVal.denom *= rational.denom
        newVal.num += rational.num
        newVal.reduce()

        return newVal
        
half = Rational(1, 2)
print(half)
quarter = Rational(1, 4)
print(quarter)
print(half*quarter)