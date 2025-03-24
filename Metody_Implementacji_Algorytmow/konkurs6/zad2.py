import math

tprimes = set()

def sieve(num):
    prime = [True for i in range(num+1)]
# boolean array
    p = 2
    while (p * p <= num):
 
        # If prime[p] is not
        # changed, then it is a prime
        if (prime[p] == True):
 
            # Updating all multiples of p
            for i in range(p * p, num+1, p):
                prime[i] = False
        p += 1
 
    # Print all prime numbers
    for p in range(2, num+1):
        if prime[p]:
            tprimes.add(p)

sieve(1000000)

cases = int(input())
numbers = str(input())

for i in numbers.split(" "):
    num = int(i)
    if math.sqrt(num) in tprimes:
        print("YES")
    else:
        print("NO")