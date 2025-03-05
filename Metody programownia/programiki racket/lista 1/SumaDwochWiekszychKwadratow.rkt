#lang racket
(require rackunit)

(define (sdwk a b c)
  (cond ((and (<= a b) (<= a c)) (+ (* c c) (* b b)))
        ((and (<= b a) (<= b c)) (+ (* c c) (* a a)))
        ((and (<= c b) (<= c a)) (+ (* a a) (* b b)))))

(check-equal? (sdwk 1 2 3) 13)
(check-equal? (sdwk 5 5 3) 50)
(check-equal? (sdwk 1 2 0) 5)
(check-equal? (sdwk 3 3 3) 18)