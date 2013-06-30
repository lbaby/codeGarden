(define (square x) (* x x ) )
(define (sum-of-squares x y)
  (+ (square x) (square y ) ))

(define (f a)
    (sum-of-square (+ a 1) (+ a 2)))

f(5)


(define (abs x)
  (cond ( ( > x 0) x)
        ( (= x  0) 0)
        ( (< x 0)  (- x))))

(define (abs x )
  (cond (( < x 0) (- x))
        (else x)))

(define (abs x)
  (if (< x 0)
      (- x)
     x))

(and  x y z a b c )
(or a b c )
(not e)

(define (>= x y)
  (or (> x y) (= x y)))

(define (>= x y)
  (not (< x y) ))


(/ (+ 5 4 (- 2 (- 3 (+ 6 (/ 4 5)))))  (* 3 (- 6 2 ) (- 2 7)))


(define (p) (p))

(define (test x y)
  (if (= x 0)
      0
      y))

(test 0 (p))

