# a @ b，其中 @ 是矩阵乘法
def mul(a, b):
    return [[sum(x * y for x, y in zip(row, col)) for col in zip(*b)]
            for row in a]

# a^n @ f0
def pow_mul(a, n, f0):
    res = f0
    while n:
        if n & 1:
            res = mul(a, res)
        a = mul(a, a)
        n >>= 1
    return res
