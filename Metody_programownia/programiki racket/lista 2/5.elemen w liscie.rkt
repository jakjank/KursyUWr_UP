#lang racket


(define (elem-with-filter x xs)
  (define (rowne e)
    (if (equal? e x)
        #t
        #f))
  (if (empty? (filter rowne xs))
      #f
      #t))

(define (elem x xs)
  (if (empty? xs)
      #f
      (if (equal? (first xs) x)
          #t
          (elem x (rest xs)))))