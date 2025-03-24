from turtle import *
from math import sin

speed('fastest')

p=60
k=5
for i in range(63):
    fd(2*k)
    rt(-90)
    fd(sin(i/10)*p)
    rt(-90)
    fd(k)
    rt(-90)
    fd(sin(i/10)*p)
    rt(-90)
