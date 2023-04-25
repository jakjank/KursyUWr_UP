import random
import array
from turtle import *

def kwadracik(bok):
    kolor = [random.random() , random.random() , random.random()]
    begin_fill()
    fillcolor(kolor)
    for i in range(4):
        fd(bok)
        rt(90)
    end_fill()

def kwadracik_ciemny(bok):
    kolor = [random.random()/2 , random.random()/2 , random.random()/2]
    begin_fill()
    fillcolor(kolor)
    for i in range(4):
        fd(bok)
        rt(90)
    end_fill()

def kwadrat(bok , ktory):
    for l in range(5):
        for k in range(5):
            if ktory == 0:
                kwadracik_ciemny(bok)
                fd(bok)
            else:
                kwadracik(bok)
                fd(bok)
        move(-5*bok , -bok)

def move(x,y):
    penup()
    fd(x)
    lt(90)
    fd(y)
    rt(90)
    pendown()

tracer(0,0)
bok = 15
move(-200,200)
for i in range(4):
    for j in range(4):
        ktory = (i + j)%2
        kwadrat(bok , ktory)
    move(5*bok , 20*bok)
update()
input()
