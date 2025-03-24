#lang racket


(define (product xs)
  (define (it xs acc)
    (if (null? xs)
        acc
        (it (cdr xs) (* acc (car xs)))))
  (it xs 1))