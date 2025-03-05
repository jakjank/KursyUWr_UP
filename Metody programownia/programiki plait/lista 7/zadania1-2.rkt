#lang plait

; Zadanie 1

(define-type (2-3-tree 'a)
  (leaf)
  (node1 [l : (2-3-tree 'a)] [elem : 'a] [r : (2-3-tree 'a)])
  (node2 [l : (2-3-tree 'a)] [elem1 : 'a] [b : (2-3-tree 'a)] [elem2 : 'a] [r : (2-3-tree 'a)]))

(define (height-help t acc)
    (type-case (2-3-tree 'a) t
      [(leaf) acc]
      [(node1 l elem r)
       (if (= (height-help l (+ 1 acc)) (height-help r (+ 1 acc)))
           (+ 1 acc)
           -1)]
      [(node2 l e1 b e2 r)
       (if (and (= (height-help l (+ 1 acc)) (height-help b (+ 1 acc)))
                (= (height-help b (+ 1 acc)) (height-help r (+ 1 acc))))
           (+ 1 acc)
           -1)]))

(define (height-ok? t)
  (if (< (height-help t 0) 0)
      #f
      #t))

(define (max t maxi)
  (type-case (2-3-tree 'a) t
    [(leaf) maxi]
    [(node1 l elem r)
     (let ((lm (max l maxi))
           (rm (max r maxi)))
       (cond [(and (> elem lm) (> elem rm)) elem]
             [(> lm rm) lm]
             [else rm]))]
    [(node2 l e1 b e2 r)
     (let ((lm (max l maxi))
           (rm (max r maxi))
           (bm (max b maxi)))
       (cond [(and (> e1 lm) (> e1 rm) (> e1 bm) (> e1 e2)) e1]
             [(and (> lm rm) (> lm bm) (> lm e2)) lm]
             [(and (> rm lm) (> rm bm) (> rm e2)) rm]
             [(and (> bm lm) (> bm rm) (> bm e2)) rm]
             [else e2]))]))
       
(define (min t mini)
  (type-case (2-3-tree 'a) t
    [(leaf) mini]
    [(node1 l elem r)
     (let ((lm (min l mini))
           (rm (min r mini)))
       (cond [(and (< elem lm) (< elem rm)) elem]
             [(< lm rm) lm]
             [else rm]))]
    [(node2 l e1 b e2 r)
     (let ((lm (min l mini))
           (rm (min r mini))
           (bm (min b mini)))
       (cond [(and (< e1 lm) (< e1 rm) (< e1 bm) (< e1 e2)) e1]
             [(and (< lm rm) (< lm bm) (< lm e2)) lm]
             [(and (< rm lm) (< rm bm) (< rm e2)) rm]
             [(and (< bm lm) (< bm rm) (< bm e2)) rm]
             [else e2]))]))

(define (left-smaller? t) ;cond a nie type-case bo rozpatruje tylko wierzcholki
  (cond [(node1? t)
         (if (< (max (node1-l t) (node1-elem t)) (node1-elem t))
             #t
             #f)]
        [(node2? t)
         (if (and
              (< (max (node2-l t) (node2-elem1 t)) (node2-elem1 t))
              (< (max (node2-l t) (node2-elem1 t)) (node2-elem2 t)))
             #t
             #f)]))

(define (right-bigger? t)
  (cond [(node1? t)
         (if (> (min (node1-r t) (node1-elem t)) (node1-elem t))
             #t
             #f)]
        [(node2? t)
         (if (and
              (> (min (node2-r t) (node2-elem1 t)) (node2-elem1 t))
              (> (min (node2-r t) (node2-elem1 t)) (node2-elem2 t)))
             #t
             #f)]))

(define (b-between? t)
  (if (and
       (> (min (node2-b t) (node2-elem1 t)) (node2-elem1 t))
       (< (max (node2-b t) (node2-elem2 t)) (node2-elem2 t)))
      #t
      #f))
        
  
(define example-tree
  (node1
   (node2
    (leaf)
    1
    (leaf)
    2
    (leaf))
   3
   (leaf)))