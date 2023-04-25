from turtle import *
import time

def tarcza():
    for i in range(60):
        penup()
        if i%5 == 0:
            fd(140)
            pendown()
            pensize(3)
            fd(10)
            penup()
            bk(150)
            rt(6)
        else:
            fd(145)
            pendown()
            pensize(1)
            fd(5)
            pensize(1)
            penup()
            bk(150)
            rt(6) 
    pendown()

def minutnik(m , s):
    rt(6*m + (s%60)*6/60)
    pensize(2)
    fd(120)
    bk(140)
    fd(20)
    lt(6*m + (s%60)*6/60)

def godzinowa(g , m):
    rt(30*g + m*6/12)
    pensize(5)
    fd(70)
    bk(70)
    lt(30*g + m*6/12)

def sekundnik(s):
    rt(s*6)
    pensize(1)
    pencolor('red')
    fd(140)
    bk(140)
    lt(s*6)
    pencolor('black')

def godzina(g , m , s):
    minutnik(m , s)
    godzinowa(g,m)
    sekundnik(s)
    

#g = int(input('Podaj godzine: '))
#m = int(input('Podaj minute: '))
tracer(0,0)
stop = 1
lt(90)
while stop > 0:
    czas = time.localtime()
    g = czas[3]
    m = czas[4]
    s = czas[5]
    tarcza()
    godzina(g , m , s)
    update()
    time.sleep(1)
    clear()