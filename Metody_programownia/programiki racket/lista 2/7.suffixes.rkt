#lang racket

(define (suffixes xs)
  (if (empty? xs)
      (cons xs null)
      (cons xs (suffixes (rest xs)))))