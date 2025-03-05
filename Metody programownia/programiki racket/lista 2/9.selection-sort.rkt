#lang racket

(define (select xs)
  (define (it xs mini others)
    (if (empty? xs)
        (cons mini others)
        (if (< (first xs) mini)
            (it (rest xs) (first xs) (cons mini others))
            (it (rest xs) mini (cons (first xs) others)))))
  (it (rest xs) (first xs) null))

(define (selection-sort xs)
  (if (empty? xs)
      xs
      (cons (first (select xs))
            (selection-sort (rest (select xs))))))