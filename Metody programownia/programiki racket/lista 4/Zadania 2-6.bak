#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

; drzewo to:
; - albo (leaf)
; - albo (node l elem r), gdzie l i r to drzewa

(define (tree? x)
  (cond [(leaf? x) #t]
        [(node? x) (and (tree? (node-l x))
                        (tree? (node-r x)))]
        [else #f]))

; konstruktor sprawdzający rodzaje wartości pól
; uwaga: przegląda rekurencyjnie poddrzewa
(define (tree-node l elem r)
  (if (and (tree? l) (tree? r) (number? elem))
      (node l elem r)
      (error "nieprawidłowe pola węzła")))

(define (tree-alt? x)
  (or (leaf? x)
      (and (node? x)
           (tree-alt? (node-l x))
           (tree-alt? (node-r x)))))

(define example-tree
  (node (node (leaf) 1 (leaf))
        2
        (node (node (leaf) 3 (leaf))
              4
              (leaf))))

; drzewo binarnych przeszukiwań (BST) to drzewo takie, że:
; jeśli jest węzłem, to elementy lewego poddrzewa
; są mniejsze niż element węzła, zaś elementy prawego
; poddrzewa są większe (lub równe) niż element węzła

; stosujemy "lub równe" jeśli chcemy mieć wielokrotne
; wystąpenia wartości w drzewie

(define (find-bst x t)
  (cond [(leaf? t) #f]
        [(node? t)
         (cond [(= x (node-elem t)) #t]
               [(< x (node-elem t))
                (find-bst x (node-l t))]
               [else
                (find-bst x (node-r t))])]))

(define (insert-bst x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
         (cond [(= x (node-elem t)) t]
                [(< x (node-elem t))
                 (node (insert-bst x (node-l t))
                       (node-elem t)
                       (node-r t))]
                [else
                 (node (node-l t)
                       (node-elem t)
                       (insert-bst x (node-r t)))])]))


; Zadanie 2

(define (fold-tree f x t)
  (if (leaf? t)
      x
      (f (fold-tree f x (node-l t)) (node-elem t) (fold-tree f x (node-r t)))))

(define (tree-sum t)
  (fold-tree + 0 t))

(define (tree-flip t)
  (fold-tree (lambda (l elem r) (node r elem l)) (leaf) t))
  
(define (tree-height t)
  (fold-tree (lambda (l elem r) (if (> (+ l 1) (+ r 1)) (+ l 1) (+ r 1)))
             -1
             t))

(define (tree-span t)
  (cons
  (fold-tree (lambda (l elem r) (if (leaf? l) elem l)) (leaf) t)
  (fold-tree (lambda (l elem r) (if (leaf? r) elem r)) (leaf) t)
  ))

(define (flatten t)
  (fold-tree (lambda (l elem r) (append (append l `(,elem)) r)) '() t))


; Zadanie 3

(define (bst? t)
  (define xs (flatten t))
  (define (it  xs act)
    (if (null? xs)
        #t
        (if (< (car xs) act)
            #f
            (it (cdr xs) (car xs)))))
  (it (cdr xs) (car xs)))

(define (sum-paths t)
  (define (it t acc)
    (if (leaf? t)
        (leaf)
        (node (it (node-l t) (+ acc (node-elem t)))
              (+ acc (node-elem t))
              (it (node-r t) (+ acc (node-elem t))))))
  (it t 0))
        

; Zadanie 4

(define (flat-append t xs)
  null)


; Zaadanie 5

(define (insert-bst2 x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
         (cond  ;usunelismy ten kawalek i tyle
                [(< x (node-elem t))
                 (node (insert-bst2 x (node-l t))
                       (node-elem t)
                       (node-r t))]
                [else
                 (node (node-l t)
                       (node-elem t)
                       (insert-bst2 x (node-r t)))])]))

(define (treesort xs)
  (define (it t xs)
    (if (null? xs)
        t
        (it (insert-bst2 (car xs) t) (cdr xs))))
  (flatten (it (leaf) xs)))


; Zadanie 6

(define (delete x t)
  (define (add-smaller l-side r-side)
    (if (leaf? (node-l r-side))
        l-side
        (node (add-smaller l-side (node-l r-side))
              (node-elem r-side)
              (node-r r-side))))
  
    (if (leaf? t)
      t
      (cond [(< x (node-elem t))
             (node (delete x (node-l t)) (node-elem t) (node-r t))]
            [(> x (node-elem t))
             (node (node-l t) (node-elem t) (delete x (node-r t)))]
            [else
             (add-smaller (node-l t) (node-r t))])))
                                                          
             


