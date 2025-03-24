from turtle import *


def kawalek(n,bok):
    if n<=1:
        for i in range(4):
            fd(bok)
            rt(90)
    else:
        for i in range(8):
            if i%2 == 0:
                fd(bok)
                bk(2*bok/3)
                lt(90)
                penup()
                fd(bok/3)
                pendown()
                kawalek(n-1 , bok/3)
                penup()
                bk(bok/3)
                rt(90)
                fd(2*bok/3)
                rt(90)
                pendown()
            else:
                penup()
                lt(90)
                fd(bok/3)
                lt(90)
                fd(bok/3)
                pendown()
                kawalek(n-1 , bok/3)
                penup()
                fd(-bok/3)
                lt(-90)
                fd(-bok/3)
                rt(90)
                pendown()

tracer(0,0)
penup()
goto(-120,120)
pendown()
kawalek(5,81)
update()
input()