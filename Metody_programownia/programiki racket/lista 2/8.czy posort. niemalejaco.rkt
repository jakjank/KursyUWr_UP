#lang racket


(define (sorted? xs)
  (if (or(empty? xs) (empty? (rest xs)))
      #t
      (if (> (first xs) (second xs))
          #f
          (sorted? (rest xs)))))
      
        
  
    