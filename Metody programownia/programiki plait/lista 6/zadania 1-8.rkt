#lang plait

; brak 7

; Zadanie 1

;definicja map:
(define (map f xs)
  (if (empty? xs)
      '()
      (cons (f (first xs))
            (map f (rest xs)))))

; pokazac (map f (map g xs)) ≡ (map (lambda (x) (f (g x))) xs)

; niech P będzie własnoscia list, taka że zachodzi:
;  1) P(empty)
;  2) dla dowolnej listy xs i wartosci x jesli P(xs) to P((cons x xs))

;  1)(map f (map g empty)) = (z def. map) '() = (map (lambda (x) (f (g x))) empty)
;  2) wezmy dowolne x i xs i zał. ze
;    (map f (map g xs)) ≡ (map (lambda (x) (f (g x))) xs)
;    Dalej:

;    ((map f (map g (cons x xs))) = (def. map)
;    = (map f (cons (g x) (map g xs))) = (def. map)
;    = (cons (f (g x)) (map f (map g xs))) = (zał.)
;    = (cons (f (g x)) (map (lambda (x) (f (g x))) xs)) =
;    = (map (lambda (x) (f (g x))) (cons x xs))
;  Na mocy indukcji mamy (map f (map g xs)) ≡ (map (lambda (x) (f (g x))) xs)


; Zadanie 2

; definicja append:
(define (append xs ys)
  (if (empty? xs)
      ys
      (cons (first xs) (append (rest xs) ys))))

; 1) Niech ys yo dowolna lista
;    (append empty ys) = ys (jakas lista - git)
; 2)  Wezmy dowolne xs i ys i zał. (append xs ys) = zs
;     Wezmy dowolny element x
;     (append (cons x xs) ys) = (def.)
;     (cons x (append xs ys)) = (zal.)
;     (cons x zs) - jakas lista git
;   Na mocy indukcji teza


; Zadanie 3

( define-type ( NNF 'v )
   ( nnf-lit [ polarity : Boolean ] [ var : 'v ])
   ( nnf-conj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ])
   ( nnf-disj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ]) )

; Zasada indukcji dla NNF:
; Niech P to własnosc NNF. Jesli
; 1) Zachodzi P(nnf-lit) dla dowolnego (nnf-lit)
; 2) Jesli dlapewnych formul-nnf ls i ps zachodzi P(ls) i P(ps)
;    to zachodzi P(nnf-conj ls ps) oraz P(nnf-disj ls ps)
; to P zachodzi dla wszystkich formuł nnf


; Zadanie 4

; negacja nnf - zamiana 'polarity' na przeciwna i and na or i or na end
(define (neg-nnf ls)
  (if (nnf-lit? ls)
      (if (nnf-lit-polarity ls)
          (nnf-lit #f (nnf-lit-var ls))
          (nnf-lit #t (nnf-lit-var ls)))
      (if (nnf-conj? ls)
          (nnf-disj (neg-nnf (nnf-conj-l ls)) (neg-nnf (nnf-conj-r ls)))
          (nnf-conj (neg-nnf (nnf-disj-l ls)) (neg-nnf (nnf-disj-r ls))))))

(define example-ls (nnf-conj
                    (nnf-disj
                     (nnf-lit #t "x")
                     (nnf-lit #f "y"))
                    (nnf-lit #f "z")))


; Pokazac ze (neg-nnf (neg-nnf fi)) ≡ fi dla dowolnej formuły fi

; 1) mamy dwie mozliwosci:
;    Niech lit to literał bez nagacji - nazwa zmiennej "x"
;    (neg-nnf (neg-nnf (nnf-lit #f "x")) = (neg-nnf (nnf-lit #t "x")) =
;     = (nnf-lit #f "x")
;   Kiedy literał jest zanegowany to analogicznie

; 2) Niech ls i ps to pewne formuly-nnf. Załozmy ze zachodzi
;    (neg-nnf (neg-nnf ls)) = ls oraz (neg-nnf (neg-nnf ps)) = ps. Wtedy
;    Dla koniunkcji:
;      (neg-nnf (neg-nnf (nnf-conj ls ps))) = (z def. neg-nnf)
;      = (neg-nnf (nnf-disj (neg-nnf ls) (neg-nnf ps))) = (z def. neg-nnf)
;      = (nnf-conj (neg-nnf (neg-nnf ls)) (neg-nnf (neg-nnf ps))) = (z zał.)
;      = (nnf-conj ls ps)   -czyli  git
;    Dla alternatywy analogicznie
; Zatem na mocy indukcji (neg-nnf (neg-nnf fi)) ≡ fi dla dowolnej formuły fi


; Zadanie 5

; dla kazdej formuly musimy deklarowac wartosciowanie jakie chcemy
(define (sigma nazwa)
  (cond [(equal? nazwa "x") #t] ;pod x #t
        [(equal? nazwa "y") #f] ;pod y #f
        [else #t] ;pod z #t
        ))

(define (eval-nnf f ls)
  (if (nnf-lit? ls)
      (if (nnf-lit-polarity ls)
          (sigma (nnf-lit-var ls))
          (not (sigma (nnf-lit-var ls))))
      (if (nnf-conj? ls)
          (and (eval-nnf sigma (nnf-conj-l ls)) (eval-nnf sigma (nnf-conj-r ls)))
          (or (eval-nnf sigma (nnf-disj-l ls)) (eval-nnf sigma (nnf-disj-r ls))))))

; Dowod:
; 1) Wezmy literal x (bez negacji). Rozwazmy wart. x->#t Mamy wtedy 
;    (eval-nnf sigma (neg-nnf (nnf-lit #t x))) = (def. neg-nnf)
;    = (eval-nnf sigma (nnf-lit #f x)) = (def. eval-nnf)
;    = (not (sigma x)) = #f  czyli git bo x->#t
; Dla wartosciowania x->#f i wersji bez negacji w obu wartosciowaniach analogicznie.

; 2) Wezmy pewne formuły-nnf ls ps i zał. ze zachodzi
;    (eval-nnf sigma (neg-nnf ls)) = (not (eval-nnf sigma ls)) oraz
;    (eval-nnf sigma (neg-nnf ps)) = (not (eval-nnf sigma ps)) dla
;    pewnego wart. sigma. Wtedy
;    Dla koniunkcji:
;      (eval-nnf sigma (neg-nnf (nnf-conj ls ps))) = (def. neg-nnf)
;      = (eval-nnf sigma (nnf-disj (neg-nnf ls) (neg-nnf ps))) = (def. eval-nnf)
;      = (or (eval-nnf sigma (neg-nnf ls)) (eval-nnf sigma (neg-nnf ps))) = (z zał.)
;      = (or (not (eval-nnf sigma ls)) (not (eval-nnf sigma ps))) = 
;      = (not (and (eval-nnf sigma ls) (eval-nnf sigma ps))) = (def. eval 'odwrotnie')
;      = (not (eval-nnf sigma (nnf-conj ls ps))) - czyli git
;    Dla alternatywy
;      analogicznie
; Zatem na mocy indukcji mamy  że dla dowolnej formuły φ i wartościowania σ
; zachodzi (eval-nnf σ (neg-nnf φ)) ≡ (not(eval-nnf σ φ)).

      

; Zadanie 6

( define-type ( Formula 'v )
   ( var [ var : 'v ])
   ( neg [ f : ( Formula 'v ) ])
   ( conj [ l : ( Formula 'v ) ] [ r : ( Formula 'v ) ])
   ( disj [ l : ( Formula 'v ) ] [ r : ( Formula 'v ) ]) )

(define (to-nnf fi)
  (cond [(var? fi)
         (nnf-lit #t (var-var fi))]
        [(conj? fi)
         (nnf-conj (to-nnf (conj-l fi))
                   (to-nnf (conj-r fi)))]
        [(disj? fi)
         (nnf-disj (to-nnf (disj-l fi))
                   (to-nnf (disj-r fi)))]
        [else
             (neg-nnf (to-nnf (neg-f fi)))])) ;neg-nnf z 4 zadania
      
(define example-formula
  (conj
   (neg (disj
         (var "x")
         (neg (var "y"))))
   (var "z")))


; Zadanie 7?

(define (eval-formula f rs)
  (eval-nnf f (to-nnf rs))) chyba nie o to chodzilo

; ewewntualnie trudniej
;(define (eval-formula f rs)
;  (if (var? rs)
;     (sigma (var-var rs))
;      (cond [(neg? rs) (not (eval-formula sigma (neg-f rs)))]
;            [(conj? rs) (and (eval-formula sigma (conj-l rs))
;                             (eval-formula sigma (conj-r rs)))]
;            [(disj? rs) (or (eval-formula sigma (disj-l rs))
;                            (eval-formula sigma (disj-r rs)))])))

; Indukcja dla formul:
; 1) P jest spałniona dla var.
; 2) jesli P zachodzi dla pewnych formul fi i psi to zachodzi
;    P dla: (neg fi), (conj fi psi), (disj fi psi).
; Wtedy P zachodzi dla wszystkich formuł

; Wezmy dowolna formule fi i wart. sigma.
; Wtedy z defininicj
; (eval-form sigma fi) = (eval-nnf sigma (to-nnf fi))

; Dziala bo to-nnf przeksztaca do rownowaznej postaci itp.
 
; A TRUDNIEJ? 
; 1) Niech x to dow. zmienna = a sigma to pewne wart. Wtedy
;    (eval-form sigma (var x)) = (sigma x)
;    Z drugiej strony  
;    (eval-nnf sigma (to-nnf (var x))) = (eval-nnf sigma (nnf-lit #t x)) = (sigma x)
;    W obu przyp. to samo wiec git.

; 2) Niech fi i psi to pewne formuły i sigma to pewne wartosciowanie. 
;    Zalozmy ze (eval-form sigma fi) = (eval-nnf sigma (to-nnf fi)) oraz
;    (eval-form sigma psi) = (eval-nnf sigma (to-nnf psi)). Wtedy 

;    Dla koninkcji 
;      (eval-form sigma (conj fi psi)) = (def. eval-form)
;       = (and (eval-form sigma fi) (eval-form sigma psi)) = (z zał.) 
;       = (and (eval-nnf sigma (to-nnf fi)) (eval-nnf sigma (to-nnf psi))) = ('odwrotna' def. eval-nnf)
;       = (eval-nnf (nnf-conj (to-nnf fi) (to-nnf psi))) = ('odwrotna' def. to-nnf)
;       = (eval-nnf (to-nnf (conj fi psi))) - czyli git
;    Dla alternatywy
;       Analogicznie
;    Dla negacji
;      (eval-nnf sigma (to-nnf (neg fi))) = (def. to-nnf)
;      = (not (eval-nnf sigma (to-nnf fi))) = (zał.) = (not (eval-form sigma fi))
;    Od drugiej strony (chcemy dojsc do tego samego)
;      (eval-form sigma (neg fi)) = (def. eval-form)
;      = (not (eval-form sigma fi))
;    Z obu stron to samo wiec git
; Zatem na mocy indukcji (eval-form sigma fi) = (eval-nnf sigma (to-nnf fi)) dla kazdej formuły fi

; Zadanie 8

(define (sorted-help acc xs)
  (if (empty? xs)
      #t
      (if (<= acc (first xs))
          (sorted-help (first xs) (rest xs))
          #f)))

(define (sorted? xs)
  (if (empty? xs)
      #t
      (sorted-help (first xs) (rest xs))))

(define (insert x xs)
  (if (empty? xs)
      (list x)
      (if (< x (first xs))
          (cons x xs)
          (cons (first xs) (insert x (rest xs))))))

; 1) Wezmy dowolny element x i rozwazmy pusta liste xs
;    mamy (sorted? empty)  = #t. Dalej
;    (sorted? (insert x empty)) = (sorted? (list x)) = (sorted-help x '()) = #t
;    zatem git

; 2) Wezmy dowolny element x i liste xs.
;    Załozmy ze (sorted? xs) = #t, chcem pokazac ze (sorted (insert x xs)) = true.
;    Wtedy mamy dwie mozliwosci:
;    1) x jest mniejszy niz (first xs) zatem insert zwroci (cons x xs)
;       co nie zmini faktu ze xs jest posortowana zatem (sorted? (cons x xs)) = true.
;    2) x jest wiekszy lub rowny (first xs), wiec dodajemy rekurencyjnie
;       x do reszty xs, az do momentu gdy 1) lub xs = empty.
;       W obu przypadkach xs dalej bedzie posortowany a x na początku xs nie bedzie
;       tego psuł. Zatem (sorted (insert x xs)) = true.

; Mamy zatem ze jeśli (sorted? xs) = true,
; to (sorted (insert x xs)) = true.

