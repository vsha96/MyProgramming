;gnu clisp  2.49.60

(defun filter (f l)
    (cond
        ((null l) l)
        ((funcall f (cadar l))
         (cons (car l) (filter f (cdr l))))
        ((filter f (cdr l)))
    )
)

(print
    (filter
         'plusp '((-2 -3) (3 1) (-1 4) (2 3))
    )
)