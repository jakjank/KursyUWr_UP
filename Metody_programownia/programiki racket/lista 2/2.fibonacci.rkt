#lang racket

(require rackunit)

(define (fib-iter n)
  (define (it i n acc1 acc2)
    (cond [(= n 0) acc1]
          [(= n 1) acc2]
          [(< i n) (it (+ i 1) n acc2 (+ acc2 acc1))]
          (else acc1)))
  (it 0 n 0 1))

(define (fib-rek n)
  (cond [(= n 0) 0]
        [(= n 1) 1]
        [else (+ (fib-rek (- n 1)) (fib-rek (- n 2)))]))

;(check-equal? (fib-iter 12) 144)
;(check-equal? (fib-iter 1) 1)
;(check-equal? (fib-iter 0) 0)
;(check-equal? (fib-rek 12) 144)
;(check-equal? (fib-rek 1) 1)
;(check-equal? (fib-rek 0) 0)


;(define start (current-inexact-milliseconds))
;(fib-iter 4096)
;(- (current-inexact-milliseconds) start)