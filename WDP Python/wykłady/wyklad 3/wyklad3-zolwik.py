from random import random
from turtle import pensize , pencolor , fd , bk , rt ,lt , speed
import random

pensize(4)
speed('fastest')

N = 400
D = 5
R = 55
kolory = ['blue' , 'red' , 'green' , 'yellow' , 'cyan' ]

for i in range(N):
    kolor = random.choice(kolory)
    pencolor(kolor)
    fd(D)
    rt(random.randint(-R , R))

input("koniec rysowania")