def insert(tree, n):
    if tree is None:
        return [n, None, None]
    if n < tree[0]:
        tree[1] = insert(tree[1], n)
    elif tree[0] < n:
        tree[2] = insert(tree[2], n)
    else:
        print("insert duplicate")
    return tree

t = None
t = insert(t, 10)
t = insert(t, 19)
t = insert(t, 5)
t = insert(t, 1)
t = insert(t, 8)
t = insert(t, 15)
t = insert(t, 1)

print(t)

# [10, [5, [1, None, None], [8, None, None]], [19, [15, None, None], None]]
