fibmap = {0:1, 1:1}

def fib(n):

    if n in fibmap.keys():
        return fibmap[n]

    fibmap[n] = fib(n-1) + fib(n-2)
    return fibmap[n]



for i in range(35):
    fib(i)
    print(i,':',fibmap[i])