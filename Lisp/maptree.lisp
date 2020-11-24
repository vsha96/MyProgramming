;gnu clisp  2.49.60

; do F with tree elements

(defun maptree (f tree)
    (cond
        ((null tree) tree)
        ((list (funcall f (car tree)) (maptree f (cadr tree)) (maptree f (caddr tree))))
    )
)

(print
    (maptree #'(lambda (n) (+ n 2))  '(2 (1 (4 nil nil) (6 nil nil)) (2 (4 nil nil) (5 nil nil))))
)