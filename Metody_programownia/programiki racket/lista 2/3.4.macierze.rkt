#lang racket

; zadanie 3:

(define-struct macierz (a b c d) #:transparent)

(define (matrix-mul m n)
  (if (and (macierz? m) (macierz? n))
      (macierz (+ (* (macierz-a m) (macierz-a n))
                  (* (macierz-b m) (macierz-c n)))
               (+ (* (macierz-a m) (macierz-b n))
                  (* (macierz-b m) (macierz-d n)))
               (+ (* (macierz-c m) (macierz-a n))
                  (* (macierz-d m) (macierz-c n)))
               (+ (* (macierz-c m) (macierz-b n))
                  (* (macierz-d m) (macierz-d n))))
      ["blad"]))

(define (matrix-id m)
  (if (and (= (macierz-a m) 1)
           (= (macierz-b m) 0)
           (= (macierz-c m) 0)
           (= (macierz-d m) 1))
           #t
           #f))

(define (matrix-exp m k)
  (define tmp m)
  (define (it m k)
    (if (= k 1)
        m
        (it (matrix-mul m tmp) (- k 1))))
  (if (= k 0)
      (macierz 1 0 0 1)
      (it m k)))

(define (fib-matrix k)
  (define m (matrix-exp (macierz 1 1 1 0) k))
  (macierz-b m))

; zadanie 4:

(define (matrix-exp-fast m k)
  (define (it m k)
    (if (= k 1)
        m
        (if (= (modulo k 2) 0)
            (it (matrix-mul m m) (/ k 2))
            (matrix-mul (it m (- k 1)) m)
             )))
  (if (= k 0)
      (macierz 1 0 0 1)
      (it m k)))

(define (fib-fast k)
  (macierz-b (matrix-exp-fast (macierz 1 1 1 0) k)))
  

(define start (current-inexact-milliseconds))
(fib-fast 4096)
(- (current-inexact-milliseconds) start)