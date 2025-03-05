#lang plait

(module+ test
  (print-only-errors #t))

;; abstract syntax -------------------------------

(define-type Op
  (add)
  (sub)
  (mul)
  (div))

(define-type Exp
  (numE [n : Number])
  (opE [op : Op] [args : (Listof Exp)]))

;; parse ----------------------------------------

(define (parse-args [args : (Listof S-Exp)] [acc : (Listof Exp)]) : (Listof Exp)
  (if (empty? args)
      acc
      (parse-args
       (rest  args)
       (append acc (list (parse (first args)))))))

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{SYMBOL ANY ...} s)
     (opE (parse-op (s-exp->symbol (first (s-exp->list s))))
          (parse-args (rest (s-exp->list s)) '()))]
    [else (error 'parse "invalid input")]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '/) (div)]
    [else (error 'parse "unknown operator")]))
                 
(module+ test
  (test (parse `2)
        (numE 2))
  (test (parse `{+ 2 1})
        (opE (add) (list (numE 2) (numE 1))))
  (test (parse `{* 3 4})
        (opE (mul) (list (numE 3) (numE 4))))
  (test (parse `{+ {* 3 4} 8})
        (opE (add)
             (list (opE (mul) (list (numE 3) (numE 4)))
                   (numE 8))))
  (test/exn (parse `{{+ 1 2}})
            "invalid input")
  (test (parse `{+ 1})
        (opE (add) (list (numE 1))))
  (test/exn (parse `{^ 1 2})
            "unknown operator"))
  
;; eval --------------------------------------

(define-type-alias Value Number)

(define (op->proc [op : Op]) : ((Listof Value) -> Value)
  (type-case Op op
    [(add) my+]
    [(sub) my-]
    [(mul) my*]
    [(div) my/]))

;operatory

(define (my-op-def [args : (Listof Value)] [acc : Number] [f : (Number Number -> Number)]) : Number
  (if (empty? args)
      acc
      (my-op-def (rest args) (f acc (first args)) f)))

(define (my+ [args : (Listof Value)]) : Number
  (if (= (length args) 0)
      (error 'my+ "Wrong number of arguments")
      (my-op-def (rest args) (first args) +)))

(define (my- [args : (Listof Value)]) : Number
  (if (= (length args) 0)
      (error 'my+ "Wrong number of arguments")
      (my-op-def (rest args) (first args) -)))

(define (my* [args : (Listof Value)]) : Number
  (if (= (length args) 0)
      (error 'my+ "Wrong number of arguments")
      (my-op-def (rest args) (first args) *)))

(define (my/ [args : (Listof Value)]) : Number
  (if (= (length args) 0)
      (error 'my+ "Wrong number of arguments")
      (my-op-def (rest args) (first args) /)))

(define (eval [e : Exp]) : Value
   (type-case Exp e
     [(numE n) n]
     [(opE o args) ((op->proc o) (map eval args))]))

(define (run [e : S-Exp]) : Value
  (eval (parse e)))

(module+ test
  (test (run `2)
        2)
  (test (run `{+ 2 1})
        3)
  (test (run `{* 2 1})
        2)
  (test (run `{+ {* 2 3} {+ 5 8}})
        19))

;; printer ———————————————————————————————————-

(define (print-value [v : Value]) : Void
  (display v))

(define (main [e : S-Exp]) : Void
  (print-value (eval (parse e))))
