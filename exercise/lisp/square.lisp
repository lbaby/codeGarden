(define (sqrt-iter guess x)
  (if (good-enough ? guess x)
      guess
      (sqrt-iter (improve guess guess x)
                 x)))

(define (improve  guess x )
  (/  (+ x y) 2))


(define (good-enough? guess x )
(< (abs (- (* guess guess)  x))  0.001))

