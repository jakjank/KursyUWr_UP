#lang racket

(define empty-queue (cons '() '()))

(define (empty?  q)
  (null? (car q)))

(define (reload xs ys)
  (if (null? ys)
      xs
      (reload (cons (car ys) xs) (cdr ys))))

(define (push-back x q)
  (if (null? (car q)) ;przeladowujemy dopoki gdy poczatek pusty
      (cons (reload (car q) (cons x (cdr q))) '())
      (cons (car q) (cons x (cdr q)))))

(define (front q)
  (if (null? (car q))
      "queue is empty"
      (car (car q))))

(define (pop q)
  (if (null? (car q))
      (cons (cdr (reload '() (cdr q)) '())) ;problem gdy nie ma co sciagac 
      (if (null? (cdr (car q)))
          (cons (reload '() (cdr q)) '())
          (cons (cdr (car q)) (cdr q)))))

         
      

  
