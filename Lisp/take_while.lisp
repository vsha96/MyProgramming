;gnu clisp  2.49.60

(defun take_while (f l)
    (cond
        ((null l) l)
        ((funcall f (car l)) (cons (car l) (take_while f (cdr l))))
    )
)

(print
    (take_while
         'atom  '(1 2 3 (4 5) 6)
    )
)