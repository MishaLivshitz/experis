from random import randint

lst = []
for i in range(100):
    lst.append(randint(-50,50))


def findMinPos(lst):

    if len(lst) == 0:
        return None

    lst.sort()
    i = 0
    while i<len(lst) and lst[i] < 0:
        i+=1
    
    filter(lambda x: x>0, lst)

    if len(lst) == 0 or lst[i]>1:
        return 1
    
    while i+1 < len(lst) and (lst[i+1]-lst[i]) <= 1:
        i+=1

    return lst[i]+1


def findMisPosBetter(lst):
    
    if lst is None:
        raise N


print(findMinPos(lst))
print(lst)