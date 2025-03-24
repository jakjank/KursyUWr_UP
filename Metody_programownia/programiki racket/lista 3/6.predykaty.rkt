#lang racket

(define (empty-set)
  (lambda (x) #f))

;(define (singleton a)
;  (lambda (x)
;    (define (it x tmp)
;      (if (null? tmp)
;          #f
;          (if (equal? (car tmp) x)
;              #t
;              (it x (cdr tmp)))))
;    (it x (list a))))

(define (singleton a)
  (lambda (x) (if (equal? a x)
                  #t
                  #f)))

(define (in a s)
  (s a))

(define (union s t)
  (lambda (x) (if (s x)
                  #t
                  (if (t x)
                      #t
                      #f))))

(define (intersect  s t)
  (lambda (x) (if (and (s x) (t x))
                  #t
                  #f)))