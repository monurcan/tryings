#lang racket
; odtu teachpack - bu dosyayı değiştirmeyiniz...
; otomatik inspect edilen STRUCT, ÖRNEK (yani check-expect ,ve structlerle çalışıyor)

(require 2htdp/universe)
(require 2htdp/image)
(require (only-in racket/gui/base play-sound))
(require test-engine/racket-tests)

(provide STRUCT yut
         (all-from-out 2htdp/universe)
         (all-from-out 2htdp/image)
         (all-from-out test-engine/racket-tests)
         play-sound)
(provide (rename-out (check-expect ÖRNEK)))

(define-syntax-rule (STRUCT id body)
  (struct id body  #:inspector (make-inspector (current-inspector))))

(define (yut x)
  (display ""))




