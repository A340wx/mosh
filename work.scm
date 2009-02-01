#!mosh
(import (rnrs)
        (mosh)
        (mosh config)
        (srfi :1))

(define (main args)
  (cond
   [(null? (cdr args))
    (display " Usage: mosh_config <option>\n" (current-error-port))
    (display "   ex) % mosh_config library-path\n\n" (current-error-port))
    (display " Options:\n" (current-error-port))
    (for-each
     (lambda (x)
       (format (current-error-port) "    ~a: ~a\n" (first x) (second x)))
     (get-configs))]
   [else
    (display (get-config (second args)))]))

(main (command-line))
