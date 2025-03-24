#lang racket


(define (llist-null)
  (lambda (xs) xs))

(define (list->llist xs)
  (lambda (ys) (append xs ys)))

(define (llist->list f)
  (f '()))

(define (llist-singleton x)
  (lambda (xs) (cons x xs)))

(define (llist-append f g)
  (lambda (xs) (f (g xs))))

(define (foldr-llist-reverse xs)
  (define (it xs)
    (if (null? xs)
        (llist-null)
        (llist-append (it (cdr xs)) (llist-singleton (car xs)))))
  (llist->list (it xs)))
