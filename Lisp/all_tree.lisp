;gnu clisp  2.49.60

(defun all_tree (f tree)
    (cond
        ((null tree) t)
        ((and (funcall f (car tree)) (all_tree f (cadr tree)) (all_tree f (caddr tree))))
    )
)

(print
    (all_tree 'plusp  '(2 (1 (4 nil nil) (6 nil nil)) (2 (4 nil nil) (5 nil nil))))
)

(print
    (all_tree 'zerop  '(0 (0 (0 nil nil) (0 nil nil)) (0 (0 nil nil) (0 nil nil))))
)

(print
    (all_tree 'zerop  '(0 (2 (0 nil nil) (0 nil nil)) (0 (0 nil nil) (0 nil nil))))
)