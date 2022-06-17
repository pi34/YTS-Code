import time
import math

# Regular Prime Number Method

def meth(n):

    print(2)
    for i in range(3, n+1, 2):
        factors = False

        for j in range(2, math.floor(i**(1/2))+1):
            if (i % j == 0):
                factors = True

        if not factors:
            print(i)

"""start = time.time()
meth(100000)
end = time.time()

print(end - start)"""

# The Sieve of Eratosthenes

def sieve(n):
    numbers = [0 for i in range(n+1)]
    x = 2

    while (x**2 <= n):
        if numbers[x] == 0:
            
            for i in range(x, n+1, x):
                numbers[i] = 1
            numbers[x] = 0
            
        x+= 1

    for i in range(2, len(numbers)):
        if numbers[i] == 0:
            print(i)

start = time.time()
sieve(10000000)
end = time.time()

print(end - start)

start = time.time()
meth(100000)
end = time.time()

print(end - start)
