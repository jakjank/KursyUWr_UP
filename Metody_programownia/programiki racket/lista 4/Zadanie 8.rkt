#lang racket

(define-struct ord (val priority) #:transparent)

(define-struct hleaf ())

(define-struct hnode (elem rank l r) #:transparent)

(define (make-node elem heap-a heap-b)
   (if (and (hleaf? heap-a) (hleaf? heap-b))
       (hnode elem 0 heap-a heap-b)
       (if (> (hnode-rank heap-a) (hnode-rank heap-b))
           (hnode elem
                  (+ (hnode-rank heap-b) 1)
                  (hnode-rank heap-a)
                  (hnode-rank heap-b))
           (hnode elem
                  (+ (hnode-rank heap-a) 1)
                  (hnode-rank heap-b)
                  (hnode-rank heap-a)))))


(define (hord? p h)
   (or (hleaf? h)
       (<= p (ord-priority (hnode-elem h)))))

(define (rank h)
   (if (hleaf? h)
       0
       (hnode-rank h)))

(define (heap? h)
   (or (hleaf? h)
       (and (hnode? h)
            (heap? (hnode-l h))
            (heap? (hnode-r h))
            (<= (rank (hnode-r h))
                (rank (hnode-l h)))
            (= (hnode-rank h) (+ 1 (hnode-rank (hnode-r h))))
            (hord? (ord-priority (hnode-elem h))
                   (hnode-l h))
            (hord? (ord-priority (hnode-elem h))
                   (hnode-r h)))))
