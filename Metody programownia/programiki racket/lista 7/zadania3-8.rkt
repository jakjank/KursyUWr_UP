#lang racket

; Zadanie 3

(define/contract (suffixes xs)
  (parametric->/c [a] (-> (listof a) (listof (listof a))))
  (define (it xs acc)
    (if (empty? xs)
        (list acc)
        (cons acc (it (cdr xs) (append acc (list(car xs)))))))
  (it xs '()))


(define (suffixes-without-contracts xs)
  (define (it xs acc)
    (if (empty? xs)
        (list acc)
        (cons acc (it (cdr xs) (append acc (list(car xs)))))))
  (it xs '()))

;(time (suffixes (range 3000))) wypisuje wynik funkcji

(define (time-difference)
   (define a (time (suffixes (range 3000))))
   (define b (time (suffixes-without-contracts (range 3000))))
  null)


(define (how-long f)
  (define t1 (current-inexact-milliseconds))
  f
  (- (current-inexact-milliseconds) t1))

;(how-long (suffixes (range 4000)))
;(how-long (suffixes-without-contracts (range 4000)))

; Zadanie 4

;pozycje pozytywne - wyciagmy z pudelek (sprawdzamy czy tag sie zgadza)
;pozycje negatywne - wkaladamy do pudelek (otagowujemy)
;pozycja w kontrakcie jest pozytywna jesli jest parzyscie wiele
;razy "po lewej stronie" strzalki

;PRZYKLAD 1
;(parametric->/c [a b] (-> a b a))
;                         n^n^p^       (p^ -pozytywna) (n^ - negatywna)

(define/contract (przyklad1 a b)
  (parametric->/c [a b] (-> a b a))
  a)

;PRZYKLAD2
;(parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
;                               p^p^n^     p^n^ n^p^

(define/contract (przyklad2 f1 f2 a)
  (parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
  (f1 a (f2 a)))
;(przyklad2 (lambda (x y) "s") (lambda (x) #t) 7)

;PRZYKLAD 3
;(parametric->/c [a b c] (-> (-> b c) (-> a b) (-> a c)))
;                               p^n^     p^n^     n^p^

(define/contract (przyklad3 f1 f2)
  (parametric->/c [a b c] (-> (-> b c) (-> a b) (-> a c)))
  (lambda (x) (f1 (f2 x))))
;(przyklad3 (lambda (x) "s") (lambda (x) x))

;PRZYKLAD 4
;(parametric->/c [a] (-> (-> (-> a a) a) a))
;                               n^p^ n^ p^

(define/contract (przyklad4 f)
  (parametric->/c [a] (-> (-> (-> a a) a) a))
  (f (lambda (x) x)))
;(przyklad4 (lambda (x) x))


; Zadanie 5

(define/contract (foldl-map f a xs)
  (parametric->/c [a b c] (-> (-> a b (cons/c c b)) b (listof a)
                              (cons/c (listof c) b)))
  (define (it a xs ys)
    (if (null? xs)
        (cons (reverse ys) a)
        (let [(p (f (car xs) a))]
          (it (cdr p)
              (cdr xs)
              (cons (car p) ys)))))
  (it a xs null))

; lambda 0 '(1 2 3)
; 0 '(1 2 3) null
; p = cons 0 1
; it 1 '(2 3) (cons 0 null)
; p = cons 1 3
; it 3 '(3) (cons 1 0 null)
; p = cons 3 6
; it 6 '() (cons 3 1 0 null)
; (cons '(0 1 3) 6)
