#lang racket

(define (my-compose f g)
  (lambda (x) (f (g x))))

; ((my-compose square inc) 5) ->
; ((lambda (x) (square (inc x))) 5) ->
; (square (inc 5)) ->
; (square (6))) ->
; sqrt(6)

; ((my-compose inc square) 5) ->
; ((lambda (x) (inc (square x))) 5) ->
; (inc (square 5)) ->
; (inc 2.23) ->
; 3.23