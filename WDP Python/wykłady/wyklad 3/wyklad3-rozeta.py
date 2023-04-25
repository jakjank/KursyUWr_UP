from turtle import *  #importuje wszystkie funkcje, mozna ale ostroznie
import random

speed('slow')
pensize(2)

def kwadrat(bok):
    for i in range(4):
        fd(bok)
        rt(90)

def rozeta(a , b , n):
    for i in range(n):
        fd(a)
        kwadrat(b)
        bk(a)     #fd(-a)
        rt(360/n)

rozeta(100 , 70 , 8)

input()