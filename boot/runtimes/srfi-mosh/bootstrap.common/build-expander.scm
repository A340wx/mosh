
(define *SYMS* '())

(define (add-debug! fn r)
  (set! *SYMS* (cons (list
		       (cons 'DBG-SOURCE (car r))
		       (cons 'DBG-FILENAME fn)
		       (cons 'DBG-SYMS (cadr r))) *SYMS*))
  (car r))

(define (ex-6 fn)
  (define (foldprog l)
    (define (itr cur l)
      (if (pair? l)
	(if (eq? (caar l) 'library)
	  (itr (cons (car l) cur) (cdr l))
	  (reverse (cons (cons 'program l) cur)))
	(reverse cur)))
    (itr '() l))
  (define (register l)
    (let ((sig (car l))
	  (name (cadr l)))
      (case sig
	((library)
	 (display " library ")
	 (display name) (newline)
	 (add-debug! fn (ex:expand-sequence/debug (list l) #t)))
	((program)
	 (display " program")(newline)
	 (add-debug! fn (ex:expand-sequence/debug (cdr l) #t)))
	(else
	  (assertion-violation 'ex-6 "invalid expression" l)))))
  (display "expanding(R6RS) ")
  (display fn) (newline)
  (let ((l (foldprog (read-all fn))))
    (apply append (map register l))))

(define (expand-6 l)
  (apply append (map ex-6 l)))

(define (ex-5 fn . libs)
  (display "expanding(R5RS) ")
  (display fn)
  (unless (null? libs)
    (display " with ")
    (display libs))
  (newline)
  (add-debug! fn (ex:expand-sequence-r5rs/debug (read-all fn) (apply ex:environment libs))))