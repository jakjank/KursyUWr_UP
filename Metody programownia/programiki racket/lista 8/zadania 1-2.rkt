#lang racket


;Zadanie 1
(define example (mcons 1 (mcons 2 (mcons 3 null))))

(define (cycle! xs)
  (define (it xs first)
    (cond[(equal? (mcdr xs) null) (set-mcdr! xs first)]
         [else (it (mcdr xs) first)]))
  (begin (it xs xs)
         xs))

;Zadanie 2

(define (mreverse! xs)
  (define (it current previous)
    (if (equal? (mcdr current) null)
        (begin
          (set-mcdr! current previous)
          current)
        (let
          ((next (mcdr current)))
          (set-mcdr! current previous)
          (it next current))))        
  (it xs null))
      

(mreverse! example)