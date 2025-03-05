#lang racket

(define (normal-if a b c)
  (if a b c))

(define (weird-if a b c)
  (or (and a b) c))

 