;gnu clisp  2.49.60

; (full '((a b r 18)(b c a 7)(a c r 15)))   =>   T
; (full '((a b r 18)(b c a 7)(a c r 15)(a d a 13)(c d r 16)))    =>  NIL

(defun cities (G) (cit2 G (cit G nil)))

(defun cit (G Res)
    (cond
        ((null G) Res)
        ((member (caar G) Res) (cit (cdr G) Res))
        ((cit (cdr G) (cons (caar G) Res)))
    )
)

(defun cit2 (G Res)
    (cond
        ((null G) Res)
        ((member (cadar G) Res) (cit2 (cdr G) Res))
        ((cit2 (cdr G) (cons (cadar G) Res)))
    )
)

;make pairs
(defun pairs (L)
    (pairs2 L nil)
)

(defun pairs2 (L Res)
    (cond
        ((null L) Res)
        ((pairs2 (cdr L) (append (make_pair (car L) (cdr L)) Res)))
    )
)

(defun make_pair (E L)
    (cond
        ((null L) nil)
        ((cons (list E (car L)) (make_pair E (cdr L))))
    )
)

;'((a b r 18)(b c a 7)(a c r 15))
(defun clean_g (G)
    (cond
        ((null G) nil)
        ((cons (list (caar G) (cadar G))  (clean_g (cdr G)) ) )
    )
)

(defun eqpair (P1 P2)
     (nil)
)