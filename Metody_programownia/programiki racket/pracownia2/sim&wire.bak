#lang racket
(require data/heap)
(provide sim? wire?
         (contract-out
          [make-sim        (-> sim?)]
          [sim-wait!       (-> sim? positive? void?)]
          [sim-time        (-> sim? real?)]
          [sim-add-action! (-> sim? positive? (-> any/c) void?)]

          [make-wire       (-> sim? wire?)]
          [wire-on-change! (-> wire? (-> any/c) void?)]
          [wire-value      (-> wire? boolean?)]
          [wire-set!       (-> wire? boolean? void?)]

          [bus-value (-> (listof wire?) natural?)]
          [bus-set!  (-> (listof wire?) natural? void?)]

          [gate-not  (-> wire? wire? void?)]
          [gate-and  (-> wire? wire? wire? void?)]
          [gate-nand (-> wire? wire? wire? void?)]
          [gate-or   (-> wire? wire? wire? void?)]
          [gate-nor  (-> wire? wire? wire? void?)]
          [gate-xor  (-> wire? wire? wire? void?)]

          [wire-not  (-> wire? wire?)]
          [wire-and  (-> wire? wire? wire?)]
          [wire-nand (-> wire? wire? wire?)]
          [wire-or   (-> wire? wire? wire?)]
          [wire-nor  (-> wire? wire? wire?)]
          [wire-xor  (-> wire? wire? wire?)]

          [flip-flop (-> wire? wire? wire? void?)]))

;EVENTS
(struct val (wire boolean))

(struct event (time val))

(define (event<= x y)
  (<= (event-time x) (event-time y)))

;SIM
(struct sim (current-time event-heap) #:mutable #:transparent)

(define (make-sim)
  (sim 0 (make-heap event<=)))

(define (sim-time sim)
  (sim-current-time sim))

(define (sim-wait! sim time)
  (define (slow-incr-time sim final-time)
    (if (= (sim-time sim) (+ final-time 1))
        (void)
        (slow-incr-time (execute-actions sim))))
  (let ([new-time (+ (sim-current-time sim) time)])
    (slow-incr-time sim new-time)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (sim-add-action! sim delay action)
  (let ([new-event (event (+ delay (sim-current-time sim)) action)])
    (heap-add! (sim-event-heap sim) new-event)))

(define (execute-actions sim)
  (if (= (event-time (heap-min (sim-event-heap sim))) (sim-time sim))
      (begin
        (wire-set! (val-wire (event-val (sim-event-heap sim)))
                   (val-boolean (event-val (sim-event-heap sim))))
        (heap-remove-min sim)
        (execute-actions sim))
      (sim-current-time-set! ()))
        
  
 (define (insert-event events event)
    (if (null? events)
        (list event)
        (let ((time (caar events)))
          (if (< (car event) time)
              (cons event events)
              (cons (car events) (insert-event (cdr events) event))))))
  
; WIRE
(struct wire (sim actions value) #:mutable)

(define (make-wire sim)
  (wire sim '() #f))

(define (wire-on-change! wire action)
  (set-wire-actions! wire (cons action (wire-actions wire)))
  (apply action (list (wire-value wire))))

(define (wire-set! wire value)
  (when (not (eq? value (wire-value wire)))
    (set-wire-value! wire value)
    (for-each (lambda (action) (apply action (list value)))
              (wire-actions wire))))


(define (bus-set! wires value)
  (match wires
    ['() (void)]
    [(cons w wires)
     (begin
       (wire-set! w (= (modulo value 2) 1))
       (bus-set! wires (quotient value 2)))]))

(define (bus-value ws)
  (foldr (lambda (w value) (+ (if (wire-value w) 1 0) (* 2 value)))
         0
         ws))

(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))