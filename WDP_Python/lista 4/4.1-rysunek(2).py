from turtle import *
import random

def kwadradito(bok):
    #begin_fill()
    #fillcolor(kolor)
    for i in range(4):
        fd(bok)
        rt(90)
    #end_fill()

def funkcja(glebia , bok):
    speed('fastest')
    kwadradito(bok)
    if glebia == 0:
        kwadradito(bok)
    else:
        for i in range(4):
            fd(bok/4)
            lt(90)
            funkcja(glebia-1 , bok/2)
funkcja(2 , 40)