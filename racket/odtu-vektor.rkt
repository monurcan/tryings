#lang racket
(require "odtu-teachpack.rkt")
;; bu dosyadaki fonksiyonları tamamladıktan sonra,
;; sonraki satırın uncomment edilmesi gerekiyor
(provide v v-x v-y v+ v- v* v-mag v** place-image/v)


;; STRUCT v - vektör
;; x : sayı - x koordinatı
;; y : sayı - y koordinatı
(STRUCT v (x y))

;; v*
;; v sayı -> v
;; vektör skalar ile çarpmak
;; bir vektörün her iki komponentini bir sayı ile çarparak yeni bir vektör,
;; örnekler
(ÖRNEK (v* (v 2 3) 5) (v 10 15))
(ÖRNEK (v* (v -2 -3) 5) (v -10 -15))
(ÖRNEK (v* (v -2 -3) 0) (v 0 0))
(ÖRNEK (v* (v -2 -3) -5) (v 10 15))

;; template
(define (v* vk s)
  (v (* (v-x vk) s) (* (v-y vk) s)))

;; v+
;; v v -> v
;; vektör toplamı
;; iki vektörün her iki komponententi x ler kendi arasında y ler kendi arasında olacak şekilde toplanır yeni bir vektör verir.
;; örnekler
(ÖRNEK (v+ (v 5 8) (v 2 1)) (v 7 9))
(ÖRNEK (v+ (v -6 3) (v 5 4)) (v -1 7))
(ÖRNEK (v+ (v -9 2) (v 9 -2)) (v 0 0))
(ÖRNEK (v+ (v -2 -4) (v -2 -6)) (v -4 -10))

;;template
(define (v+ va vb)
  (v (+ (v-x va) (v-x vb)) (+ (v-y va) (v-y vb))))

;v-
;; v v -> v
;; vektör çıkartma
;;iki vektörün her iki komponenti x ler kendi arasında y ler kendi arasında olacak şekilde çıkartılır yeni bir vektör verir.
;;örnekler
(ÖRNEK (v- (v 6 9) (v 3 5)) (v 3 4))
(ÖRNEK (v- (v 2 0) (v 7 2)) (v -5 -2))
(ÖRNEK (v- (v 3 4) (v 3 4)) (v 0 0))
(ÖRNEK (v- (v -8 10) (v -10 3)) (v 2 7))

;;template
(define ( v- va vb)
 (v (- (v-x va) (v-x vb)) (- (v-y va) (v-y vb))))

;; v. - vektör dot çarpma
;; v v -> sayı
;;iki vektörün her iki kompententi x ler kendi arasında y ler kendi arasında olacak şekilde çarpılır ve iki sonuç toplanır
;;ve toplam değeri verir.
;;örnekler
(ÖRNEK (v. (v 2 5) (v 3 3)) 21)
(ÖRNEK (v. (v -1 4) (v 5 2)) 3)
(ÖRNEK (v. (v -2 -4) (v 3 1)) -10)
(ÖRNEK (v. (v 1 7) (v -8 1)) -1)
(ÖRNEK (v. (v 3 4) (v 3 4)) (+ (* 3 3) (* 4 4)))
(ÖRNEK (v. (v 4 5) (v 4 5)) (+ (* 4 4) (* 5 5)))

;;template
(define (v. va vb)
 (+ (* (v-x va) (v-x vb)) (* (v-y va) (v-y vb))))


;; v-mag - vektör uzunluğu
;; v -> sayı
;;
(ÖRNEK (v-mag (v 6 8)) (sqrt (+ (sqr 6) (sqr 8))))
(ÖRNEK (v-mag (v 3 4)) (sqrt (+ (sqr 3) (sqr 4))))

;;template
(define (v-mag v1)
  (sqrt (+ (sqr (v-x v1)) (sqr (v-y v1)))))

;;v-unit vektör aynı yöne unit vektörüne çevirmek
;; v-unit v -> v 
; (ÖRNEK (v-unit (v 3 4)) (v 0.6 0.8)) 
 (ÖRNEK (v-unit (v 3 4)) (v 3/5 4/5)) 
;;template - hediyem olsun...sadece uncomment yap
;(define (v-unit v)
;  (v* v (max 0.0001 (/ 1 (+ 0.0001 (v-mag v))))))
(define (v-unit v)
  (v* v (/ 1 (v-mag v))))

;; v**
;; v v -> v
;; vektör başka vektör ile orantılamak
;; iki vektörün her iki komponentini birbiriyle çarparak yeni bir vektör,
;; örnekler
(ÖRNEK (v** (v 2 3) (v 1 2)) (v 2 6))
(ÖRNEK (v** (v -2 -3) (v -1 0)) (v 2 0))
(ÖRNEK (v** (v -2 -3) (v 4 -5)) (v -8 15))

;; template
(define (v** v1 v2)
  (v (* (v-x v1) (v-x v2)) (* (v-y v1) (v-y v2))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Hediye vektör çizim fonksiyonu
; STRUCT v tanıttıktan sonra bu fonkisyonları uncomment edebilirsiniz
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; place-image/v
; resim v sahne -> sahne
; bir arkaplana vektöre göre bir imaj yerleştir
; template :
; (define (place-image/v im v1 sahne)
;  (... im ... (v-x v1) ... (v-y v1) ...)
(define test-circle (circle 30 "solid" "red"))
(define test-circle2 (circle 40 "solid" "green"))
(define test-square (circle 300 "solid" "red"))
(define test-square2 (square 40 "solid" "green"))

(ÖRNEK (place-image/v  test-circle (v 5 5) test-square)
       (place-image/align test-circle 5 5 "center" "center" test-square))
(ÖRNEK (place-image/v test-circle (v 3 8) test-square)
       (place-image/align test-circle 3 8 "center" "center" test-square))
(ÖRNEK (place-image/v test-circle (v 1 2) test-square)
       (place-image/align test-circle 1 2 "center" "center" test-square))
(ÖRNEK (place-image/v test-circle (v 2 8) test-square)
       (place-image/align test-circle 2 8 "center" "center" test-square))

(define (place-image/v im v1 arkaplan)
  (place-image/align im (v-x v1) (v-y v1) "center" "center"  arkaplan))

(test)