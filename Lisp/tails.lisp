;gnu clisp  2.49.60

(defun tails (L)
    (cond
        ((null L) (cons L NIL))
        ((cons L (tails (cdr L))))
    )
)

(print
    (tails
        '(a b c)
    )
)

(print
    (tails
        '()
    )
)