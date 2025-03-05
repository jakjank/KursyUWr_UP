#lang racket


(define (maximum xs)
  (define (it xs maxi)
    (if (empty? xs)
        maxi
        (if (> (first xs) maxi)
            (it (rest xs) (first xs))
            (it (rest xs) maxi))))
   (if (empty? xs)
       -inf.0
       (it (rest xs) (first xs))))