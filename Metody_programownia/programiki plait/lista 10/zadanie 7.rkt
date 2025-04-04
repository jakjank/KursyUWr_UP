#lang plait

(define-syntax my-and
  (syntax-rules ()
    ((my-and) #t)
    ((my-and x) x)
    ((my-and x y ...)
     (if x (my-and y ...) x))))

(define-syntax my-or
  (syntax-rules ()
    ((my-or) #f)
    ((my-or x) x)
    ((my-or x y ...)
     (let ((temp x))
       (if temp temp (my-or y ...))))))

(define-syntax my-let
  (syntax-rules ()
    ((my-let ((var expr) ...) body)
     ((lambda (var ...) body) expr ...))))

;przykład
;(my-let ((x 3) (y 4)) (+ x y))


(define-syntax my-let*
  (syntax-rules ()
    ((my-let* () body)
     ((lambda () body)))
    ((my-let* ((var1 expr1) (var2 expr2) ...) body)
     (my-let ((var1 expr1))
       (my-let* ((var2 expr2) ...) body)))))

;przykład
(my-let* ((x 3) (y (+ x 1))) (+ x y))