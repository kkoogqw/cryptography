import timeit


def showDiscreteLog(p, a):
    print('p: ' + str(p))
    print('a: ' + str(a))
    print()
    x = 1
    while x < p:
        print('x: ' + str(x) + '\tb: ' + str(pow(a, x, p)))
        x = x + 1

def CRT(dict_mod_num):
    M = 1
    for num, mod in dict_mod_num.items():
        M = M * mod
    ans = 0
    for num, mod in dict_mod_num.items():
        m = (int(M / mod)) % mod
        ans = ans + (num * inverse(m, mod) * (int(M / mod)))
    return ans % M

def inverse(a, n):
    t = 0
    a = a % n
    newt = 1
    r = n
    newr = a
    while newr != 0:
        quotient = int(r / newr)
        t, newt = newt, t - quotient * newt
        r, newr = newr, r - quotient * newr
    if t < 0:
        t = t + n
    return t

# Pohlig-Hellman attack
def findDiscreteLog(a, B, p):
    primes = prime_factors(p - 1)
    CRT_dict = {}
    for prime, power in primes.items():
        exp = 1
        x_list = []
        B_sub = B
        while exp <= power:
            q = int((p - 1) / pow(prime, exp))
            Bpow = pow(B_sub, q, p)
            apow = pow(a, int((p - 1) / prime), p)
            k = 0
            found = False
            while not found:
                if pow(apow, k, p) == Bpow:
                    x_list.append(k)
                    # Note that this only checks up to q - 1
                    found = True
                if not found:
                    k = k + 1
            B_sub = (B_sub * pow(inverse(a, p), k * pow(prime, exp - 1))) % p
            exp = exp + 1
        exp = 0
        ans_mod_prime = 0
        while exp < power:
            ans_mod_prime = ans_mod_prime + (pow(prime, exp) * x_list[exp])
            exp = exp + 1
        CRT_dict[ans_mod_prime % pow(prime, power)] = pow(prime, power)
    return CRT(CRT_dict)

def prime_factors(n):
    i = 2
    factors = {}
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
            try:
                factors[i] = factors[i] + 1
            except KeyError:
                factors[i] = 1
    if n > 1:
        try:
            factors[n] = factors[n] + 1
        except KeyError:
            factors[n] = 1
    return factors

def main():
    p = 5682549022748424631339131913370125786212509227588493537874673173634936008725904358935442101466555561124455782847468955028529037660533553941399408331331403379
    g = 2410497055970432881345493397846112198995088771364307195189734031205605186951241875096796459061741781667380437076874705300974836586165283741668656930807264789
    ya = 973768284341326272301553751114322685324340805902069613339667142187801529585352406975030927008752571917079716318221077758236884342662829402529734009607531649
    yb = 4149822765985031146554298777122732051870868431387323913747785791685310508836836283702926446817000114868007555717546362425841865173929670156568682745060708314
    print(findDiscreteLog(g, ya, p))
    print(findDiscreteLog(g, yb, p))

if __name__ == '__main__':
    main()