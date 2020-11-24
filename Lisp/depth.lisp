;gnu clisp  2.49.60

; Tree ::= nil | (atom Tree Tree)
(defun depth (tree)
    (cond
        ((null tree) 0)
        ((+ 1 (max (depth (cadr tree)) (depth (caddr tree)))))
    )
)

(print
    (depth '(2 (3 () ()) (5 () (5 ()()))))
)