from turtle import *
import time

tracer(0,0)
FRAME_RATE = 1/30
szerokosc = 400

N = 125
kolor_nieba_1 = [255,252,201]
kolor_nieba_2 = [203 , 96 , 21]
kolor_slonca_1 = [255,239,0]
kolor_slonca_2 = [221 , 50 , 36]
kolor_morza_1 = [0 , 164 , 180]
kolor_morza_2 = [0,20,64]
niebo_koniec = [0.80921875, 0.4237499, 0.13828125]
niebo_poczatek = [0.14784124016988864, 0.07741752244107827, 0.025263467377940052]
x = -100
y = 50
trzcina_start = [0,110,51]
trzcina_glowa_start = [172,159,60]

def niebo(kolor):
    wysokosc_nieba = 100
    penup()
    goto(-200,100)
    pendown()
    begin_fill()
    fillcolor(kolor)
    fd(szerokosc)
    rt(90)
    fd(wysokosc_nieba)
    rt(90)
    fd(szerokosc)
    rt(90)
    fd(wysokosc_nieba)
    rt(90)
    end_fill()
    penup()
    goto(0,0)

def slonce(x,y , kolor):
    penup()
    goto(x,y)
    pendown()
    begin_fill()
    fillcolor(kolor)
    circle(25)
    end_fill()
    penup()
    goto(0,0)
    
def morze(kolor):
    wysokosc_morza = 100
    penup()
    goto(-200,0)
    pendown()
    begin_fill()
    fillcolor(kolor)
    fd(szerokosc)
    rt(90)
    fd(wysokosc_morza)
    rt(90)
    fd(szerokosc)
    rt(90)
    fd(wysokosc_morza)
    rt(90)
    end_fill()
    penup()
    goto(0,0)

def trzciny(alfa , kolor , kolor2 , a ,b , wysokosc):
    penup()
    goto(a , b)
    lt(90 + alfa)
    pendown()
    pensize(3)
    color(kolor)
    fd(wysokosc)
    pensize(5)
    color(kolor2)
    fd(15)
    penup()
    pensize(1)
    color('black')
    rt(90 + alfa)
    goto(0,0)

def zachod(a , b , niebo_koniec):
    licznik = 0
    for i in range(N):
        if i < 110:
            kolor_nieba = [(a*(N-i)/N + b*(i)/N)/256 for a,b in zip(kolor_nieba_1 , kolor_nieba_2)]
        else:
            niebo_koniec = [a/1.12 for a in niebo_koniec]
            kolor_nieba = niebo_koniec

        kolor_slonca = [(a*(N-i)/N + b*(i)/N)/256 for a,b in zip(kolor_slonca_1 , kolor_slonca_2)]
        kolor_morza = [(a*(N-i)/N + b*(i)/N)/256 for a,b in zip(kolor_morza_1 , kolor_morza_2)]
        t0 = time.time()
        a = a + 2
        b = b - 1
        clear()
        niebo(kolor_nieba)
        slonce(a,b , kolor_slonca)
        morze(kolor_morza)
        if i%5 == 0:
            licznik +=1
        trzciny(licznik%3 , 'green' , 'yellow' , -165 , -100 ,75)
        trzciny(licznik%3 , 'green' , 'yellow' , -170 , -100 ,80)
        trzciny(licznik%3 , 'green' , 'yellow' , -180 , -100 ,90)
        trzciny(licznik%3 , 'green' , 'yellow' , -157 , -100 ,85)
        trzciny(licznik%3 , 'green' , 'yellow' , -150 , -100 ,100)
        trzciny(licznik%3 , 'green' , 'yellow' , -145 , -100 ,75)
        trzciny(licznik%3 , 'green' , 'yellow' , -150 , -100 ,80)
        trzciny(licznik%3 , 'green' , 'yellow' , -160 , -100 ,90)
        trzciny(licznik%3 , 'green' , 'yellow' , -137 , -100 ,85)
        trzciny(licznik%3 , 'green' , 'yellow' , -120 , -100 ,100)
        trzciny(licznik%3 , 'green' , 'yellow' , -125 , -100 ,75)
        trzciny(licznik%3 , 'green' , 'yellow' , -130 , -100 ,80)
        trzciny(licznik%3 , 'green' , 'yellow' , -100 , -100 ,90)
        trzciny(licznik%3 , 'green' , 'yellow' , -107 , -100 ,85)
        trzciny(licznik%3 , 'green' , 'yellow' , -90 , -100 ,100)
        trzciny(licznik%3 , 'green' , 'yellow' , -192 , -100 ,60)
        trzciny(licznik%3 , 'green' , 'yellow' , -75 , -100 ,55)
        update()
        
        delta = time.time() - t0
        if delta < FRAME_RATE:
            time.sleep(FRAME_RATE - delta)

def wschod(x,y , niebo_poczatek):
    licznik = 0
    for i in range(N):
        if i < 15:
            niebo_poczatek = [x*1.12 for x in niebo_poczatek]
            kolor_nieba = niebo_poczatek
        else:
            kolor_nieba = [(x*(N-i)/N + y*(i)/N)/256 for x,y in zip(kolor_nieba_2 , kolor_nieba_1)]

        kolor_slonca = [(x*(N-i)/N + y*(i)/N)/256 for x,y in zip(kolor_slonca_2 , kolor_slonca_1)]
        kolor_morza = [(x*(N-i)/N + y*(i)/N)/256 for x,y in zip(kolor_morza_2 , kolor_morza_1)]
        t0 = time.time()
        x = x - 2
        y = y + 1
        clear()
        niebo(kolor_nieba)
        slonce(x,y , kolor_slonca)
        morze(kolor_morza)
        if i%5 == 0:
            licznik +=1
        trzciny(licznik%3 , 'green' , 'yellow' , -165 , -100 ,75)
        trzciny(licznik%3 , 'green' , 'yellow' , -170 , -100 ,80)
        trzciny(licznik%3 , 'green' , 'yellow' , -180 , -100 ,90)
        trzciny(licznik%3 , 'green' , 'yellow' , -157 , -100 ,85)
        trzciny(licznik%3 , 'green' , 'yellow' , -150 , -100 ,100)
        trzciny(licznik%3 , 'green' , 'yellow' , -145 , -100 ,75)
        trzciny(licznik%3 , 'green' , 'yellow' , -150 , -100 ,80)
        trzciny(licznik%3 , 'green' , 'yellow' , -160 , -100 ,90)
        trzciny(licznik%3 , 'green' , 'yellow' , -137 , -100 ,85)
        trzciny(licznik%3 , 'green' , 'yellow' , -120 , -100 ,100)
        trzciny(licznik%3 , 'green' , 'yellow' , -125 , -100 ,75)
        trzciny(licznik%3 , 'green' , 'yellow' , -130 , -100 ,80)
        trzciny(licznik%3 , 'green' , 'yellow' , -100 , -100 ,90)
        trzciny(licznik%3 , 'green' , 'yellow' , -107 , -100 ,85)
        trzciny(licznik%3 , 'green' , 'yellow' , -90 , -100 ,100)
        trzciny(licznik%3 , 'green' , 'yellow' , -192 , -100 ,60)
        trzciny(licznik%3 , 'green' , 'yellow' , -75 , -100 ,55)
        update()
        
        delta = time.time() - t0
        if delta < FRAME_RATE:
            time.sleep(FRAME_RATE - delta)

while True:
    zachod(x ,y, niebo_koniec)
    time.sleep(0.5)
    wschod(x+250 , y-125 ,niebo_poczatek)
    time.sleep(0.5)
input()