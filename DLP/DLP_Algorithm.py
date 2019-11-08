
import math


# Baby-Step-Giant-Step/Shanks Algorithm
def BSGS_method(a, b, p):
    m = math.ceil(math.sqrt(p))
    limit = int(p / m)

    hash_map_1 = {}

    for i in range(limit + 1):
        hash_map_1[i] = pow(a, i * m) % p

    hash_map_2 = {}
    for j in range(m + 1):
        temp = b * pow(a, j) % p
        hash_map_2[temp] = j

    for k in range(len(hash_map_1)):
        if hash_map_1[k] in hash_map_2:
            return (k * m - hash_map_2[hash_map_1[k]]) % p
    return None

'''================================================================================='''

# Extend Euclidean Algorithm
def extend_gcd(a, b):
    a1, a2 = 0, 1
    b1, b2 = 1, 0
    while b > 0:
        q, rest = divmod(a, b)
        a1, a2 = a2 - (q * a1), a1
        b1, b2 = b2 - (q * b1), b1
        a, b = b, rest
    return a, a2, b2

# Using the ext-gcd to get the mod-inverse of value
def mod_inverse(a, m):
    g, a, b = extend_gcd(a, m)
    if g != 1:
        raise Exception("Cannot find the inverse of %d on %d" %(a, m))
    else:
        return a % m

# G = s1 U s2 U s3
# f(x) operation
def pre_function(x, a, b, ALPHA, BETA, P, n):
    # n = 4309874666
    temp = x % 3

    if temp == 0:
        _x = pow(x, 2, P)
        _a = 2 * a % n
        _b = 2 * b % n
        return _x, _a, _b

    if temp == 1:
        # func = []
        _x = (x * BETA) % P
        _a = a
        _b = (b + 1) % n
        return _x, _a, _b

    if temp == 2:
        _x = (x * ALPHA) % P
        _b = b
        _a = (a + 1) % n
        return _x, _a, _b


# Pollard_rho Algorithm

def Pollard_Rho(alpha, beta, p, n):
    x, a, b = 1, 0, 0
    x, a, b = pre_function(x, a, b, alpha, beta, p, n)
    _x, _a, _b = pre_function(x, a, b, alpha, beta, p, n)

    while x != _x:
        x, a, b = pre_function(x, a, b, alpha, beta, p, n)
        _x, _a, _b = pre_function(_x, _a, _b, alpha, beta, p, n)
        _x, _a, _b = pre_function(_x, _a, _b, alpha, beta, p, n)
    d = math.gcd(_b - b, n)
    # print(d)
    if d != 1:
        result = ((a - _a) // d) * mod_inverse(((_b - b) // d), n // d) % (n // d)
        while pow(alpha, result, p) != beta:
            result += (n // d)
        return result
    else:
        result = ((a - _a) * mod_inverse(_b - b, n)) % n
        return result

'''================================================================================='''

def check_rsult(g, alpha, beta, p):
    temp = pow(g, alpha, p)
    if beta == temp:
        print("g^alpha = %d\nthe beta is %d\nThe result is correct!" %(temp, beta))
        return True
    else:
        print("g^alpha = %d, unequal the beta! \nThe result is error!" % temp)
        return False