#lang plait


(define (remove x xs)
  (if (= (first xs) x)
      (rest xs)
      (cons (first xs) (remove x (rest xs)))))
      

(define (perms xs)
  (if (empty? xs)
      '())
       (map (lambda (x) (append '(x) (perms (remove x xs)))) xs))