#lang racket
(require "odtu-teachpack.rkt")


(define hw (lambda (x) "hello world"))

(define KÜÇÜK 0.00001)
(define DELTA 0.000001)

; küçük-mü? sayı -> boolean
(ÖRNEK (küçük-mü? 1000) false)
(ÖRNEK (küçük-mü? -1000) false)
(ÖRNEK (küçük-mü? 0.00000000001) true)
(ÖRNEK (küçük-mü? -0.000000000001) true)

(define (küçük-mü? x)
  (< (magnitude x) KÜÇÜK))

(define (hgw x)
(cond
  (
   (< x 2) "hello")
   (else "goodbye")
  )
  )

; sayi -> boolean
(define (iyi-mi-sqrt7? x)
  (küçük-mü? (- (sqr x) 7)))

; sayi -> sayı
(define (iyisi-sqrt7 x)
  (/ (+ x (/ 7 x)) 2))

; bul (sayı->bool) (sayı->sayı) sayı -> sayı
(define (bul iyi-mi? iyisi tahmin)
  (cond
    ((iyi-mi? tahmin) tahmin)
     (else (bul iyi-mi? iyisi (iyisi tahmin)))))

; türev (sayı->sayı) -> (sayı->sayı)
(define (türev f)
  (λ (x)
    (/ (- (f (+ x DELTA)) (f x) DELTA))))

(define (iyi-mi?-yap f)
  (λ (t)
    (küçük-mü? (f t))))

(define (iyisi-yap f)
    (λ (t)
          (- t (/ (f t) ((türev f) t)))))

(define (çöz-f f tahmin)
  (bul (iyi-mi?-yap f) (iyisi-yap f) tahmin))

(define (fold comb null-v xC)
  (cond
    ((empty? xC) null-v)
    (else (comb (first xC) (fold comb null-v (rest xC))))))

(fold (λ (f r) (cons (+ f 1) r)) empty '(1 2 3))

(define (poly-eval p x)
  (foldr (λ (L r) (+ L (* x r))) empty p))

; (map (curry + 2) '(1 2 3 4))

; curry bazı argümanları doldurup yeni bir fonksiyon döndürüyor
; mesela + normalde 2 parametre alıyor ama (curry + 10) tek bir değişken alıyor ilk değişkeni stabilize ediyor



;;;;;bu dosyanın sonunda kalsın....
(test)
