;gnu clisp  2.49.60

(defun is-prefix (L1 L2)
    (cond
        ((null L1) T)
        ((null L2) NIL)
        ((eq (car L1) (car L2)) (is-prefix (cdr L1) (cdr L2)))
    )
)

;we have atom lists (one-level)
(print (is-prefix
    '(A B )
    '(A B C D)
))