;gnu clisp  2.49.60

(defun any_tree (f tree)
    (cond
        ((null tree) tree)
        ((funcall f (car tree)))
        ((any_tree f (cadr tree)))
        ((any_tree f (caddr tree)))
    )
)

(print
    (any_tree
         'zerop '(1 (10 nil (8 nil nil)) nil)
    )
)

(print
    (any_tree
         'zerop '(1 (0 nil (8 nil nil)) nil)
    )
)

(print
    (any_tree
         'plusp '(-5 (-10 nil (8 nil nil)) (-5 nil nil))
    )
)