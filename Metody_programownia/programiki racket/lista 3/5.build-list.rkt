#lang racket

(define (build-list n f)
  (define (it n f i)
    (if (= i n)
        null
        (cons (f i) (it n f (+ i 1)))))
  (it n f 0))


(define (negatives n)
  (build-list n (lambda (x) (- (+ x 1)))))

(define (reciprocals n)
  (build-list n (lambda (x) (/ 1 (+ 1 x)))))

(define (evens n)
  (build-list n (lambda (x) (* x 2))))

(define (identityM n)
  (build-list n (lambda (x) (helpIM x n))))

(define (helpIM x n)
  (define (it ktory)
    (if (= ktory n)
        null
        (if (= ktory x)
            (cons 1 (it (+ ktory 1)))
            (cons 0 (it (+ ktory 1))))))
  (it 0))
