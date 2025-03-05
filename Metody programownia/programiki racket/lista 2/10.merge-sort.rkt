#lang racket


(define (split xs)
  (define (it xs left right i)
    (if (empty? xs)
        (cons left right)
        (if (= (modulo i 2) 0)
            (it (rest xs)
                (cons (first xs) left)
                right
                (+ i 1))
            (it (rest xs)
                left
                (cons (first xs) right)
                (+ i 1)))))
  (it xs null null 0))

(define (merge xs ys)
  (define (it xs ys rs) ; rs - results
    (if (and (empty? xs) (empty? ys))
        rs
        (if (empty? ys)
            (it (rest xs) ys (append rs (cons (first xs) null)))
            (if (empty? xs)
                (it xs (rest ys) (append rs (cons (first ys) null)))
                (if (< (first xs) (first ys))
                    (it (rest xs)
                        ys
                        (append rs (cons (first xs) null)))
                    (it xs
                       (rest ys)
                       (append rs (cons (first ys) null))))))))
  (it xs ys null))

(define (merge-sort xs)
  (if (eq? (cdr xs) null)
      xs
      (merge (merge-sort (car (split xs)))
             (merge-sort (cdr (split xs))))))