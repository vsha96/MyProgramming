;gnu clisp  2.49.60

(defun prod-tree (tree)
    (cond
        ((null tree) 1)
        ((* (car tree) (prod-tree (cadr tree)) (prod-tree (caddr tree))))
    )
)

(print
    (prod-tree
    '(2 (3 NIL NIL) (8 NIL NIL))
    )
)