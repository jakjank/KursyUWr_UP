#lang plait

(define-type Op
  (op-add)
  (op-mul)
  (op-sub)
  (op-div)
  (op-pow))

(define-type OpUnary
  (op-fact)
  (op-opp)) ;opposite

(define-type Exp
  (exp-number [n : Number])
  (exp-op [op : Op] [e1 : Exp] [e2 : Exp])
  (exp-op1 [op : OpUnary] [e : Exp]))


(define (parse-Op s)
  (let ([sym (s-exp->symbol s)])
  (cond
    [(equal? sym '+) (op-add)]
    [(equal? sym '-) (op-sub)]
    [(equal? sym '*) (op-mul)]
    [(equal? sym '/) (op-div)]
    [(equal? sym '^) (op-pow)])))

(define (parse-OpUnary s)
  (let ([sym (s-exp->symbol s)])
  (cond
    [(equal? sym '!) (op-fact)]
    [(equal? sym '-) (op-opp)])))


(define (parse-Exp s)
  (cond
    [(s-exp-number? s) (exp-number (s-exp->number s))]
    [(s-exp-list? s)
     (let ([xs (s-exp->list s)])
       (if (= (length xs) 3)
           (exp-op (parse-Op  (first  xs))
                   (parse-Exp (second xs))
                   (parse-Exp (third  xs)))
           (exp-op1 (parse-OpUnary (first xs))
                    (parse-Exp (second xs)))))]))

; ==============================================

(define (^ a n)
  (if (= n 0)
      1
      (* a (^ a (- n 1)))))

(define (fact a)
  (if (= a 0)
      1
      (* a (fact (- a 1)))))

(define (opp a)
  (- 0 a))
       
(define (eval-op op)
  (type-case Op op
    [(op-add) +]
    [(op-sub) -]
    [(op-mul) *]
    [(op-div) /]
    [(op-pow) ^]))

(define (eval-op1 op1)
  (type-case OpUnary op1
    [(op-opp) opp]
    [(op-fact) fact]))


(define (eval e)
  (type-case Exp e
    [(exp-number n)    n]
    [(exp-op op e1 e2)
     ((eval-op op) (eval e1) (eval e2))]
    [(exp-op1 op e)
     ((eval-op1 op) (eval e))]))


 (eval (parse-Exp `(- (+ (- (! 5)) 1) 1)))

;rebornix
;wingrunr