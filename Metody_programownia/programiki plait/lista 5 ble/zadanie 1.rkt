#lang plait

; Zadanie 1
;1
(define (f1 a b)
  a)

;2
(define (f2 a b c)
  (a c(b c)))

;3             ^ zawezamy typy
(define (f3 [f : (('a -> 'a) -> 'a)])
  (f (lambda (x) x)))


;4
(define (f4 f q)
  (lambda (x) (pair (f x) (q x))))

;5 