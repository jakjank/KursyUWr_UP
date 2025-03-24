#lang racket
; z wykladu
(define-syntax-rule
  (stream-cons v s)
  (cons v (delay s)))

(define stream-car car)

(define (stream-cdr s)
  (force (cdr s)))

(define stream-null null)
(define stream-null? null?)

(define (stream-ref s n)
  (if (= n 0)
      (stream-car s)
      (stream-ref (stream-cdr s) (- n 1))))

(define (stream-filter p s)
  (if (stream-null? s)
      stream-null
      (if (p (stream-car s))
          (stream-cons (stream-car s)
                       (stream-filter p (stream-cdr s)))
          (stream-filter p (stream-cdr s)))))

(define (integers-from n)
  (stream-cons n (integers-from (+ n 1))))

(define (divides? a b)
  (= (remainder b a) 0))

(define (map2 f xs ys)
  (stream-cons
   (f (stream-car xs)
      (stream-car ys))
   (map2 f (stream-cdr xs) (stream-cdr ys))))

; zadanie 2

(define (is-divider n list-of-num)
  (if (empty? list-of-num)
      #f
      (if (divides? (car list-of-num) n)
          #t
          (is-divider n (cdr list-of-num)))))
          
(define (not-mult s earlier-primes)
  (if (is-divider (stream-car s) earlier-primes)
      (not-mult (stream-cdr s) earlier-primes)
      (stream-cons
       (stream-car s)
       (not-mult (stream-cdr s) (cons (stream-car s) earlier-primes)))))

(define primes (not-mult (integers-from 2) '()))

;primes
;(stream-ref primes 1)
;(stream-ref primes 2)
;(stream-ref primes 3)
;(stream-ref primes 10)

; zadanie 3

(define factorial (stream-cons 1 (map2 * (integers-from 1) factorial)))

;factorial ;0! = 1
;(stream-ref factorial 1) ;1! = 1
;(stream-ref factorial 2)
;(stream-ref factorial 3)
;(stream-ref factorial 5)

; zadanie 4

(define (partial-sums s)
  (if (stream-null? s)
      stream-null
      (stream-cons (stream-car s) (map2 + (stream-cdr s) (partial-sums s)))))

;(define a (partial-sums primes))
;(stream-ref a 1) 2+3 = 5
;(stream-ref a 2) 2+3+5 = 10
;(stream-ref a 3) 2+3+5+7 = 17


; zadanie 5

(define (merge s1 s2)
  (cond [(stream-null? s1) s2]
        [(stream-null? s2) s1]
        [(= (stream-car s1) (stream-car s2))
         (stream-cons
          (stream-car s1)
          (merge (stream-cdr s1) (stream-cdr s2)))]
        [(< (stream-car s1) (stream-car s2))
         (stream-cons
          (stream-car s1)
          (merge (stream-cdr s1) s2))]
        [else
         (stream-cons
          (stream-car s2)
          (merge s1 (stream-cdr s2)))]))

(define (scale s n)
  (if (stream-null? s)
      s
      (stream-cons
       (* (stream-car s) n)
       (scale (stream-cdr s) n))))

(define hamming
  (stream-cons 1 (merge (scale hamming 2)
                        (merge (scale hamming 3)
                               (scale hamming 5)))))
  







  