#lang plait

(define-type (Tree 'a)
  (leaf)
  (node [l : (Tree 'a)] [elem : 'a] [r : (Tree 'a)]))

(define example-tree
  (node (node (leaf) 1 (leaf))
        2
        (node (leaf)
              3
              (node (leaf) 4 (leaf)))))

(define (process-tree f-node f-leaf
  