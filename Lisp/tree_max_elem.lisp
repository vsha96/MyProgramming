;gnu clisp  2.49.60

; Tree ::= nil | (atom Tree Tree)
; here we have search tree
(defun tree_max_elem (tree)
    (cond
        ((null tree) NIL)
        ((null (caddr tree)) (car tree))
        ((tree_max_elem (caddr tree)))
    )
)

(print
    (tree_max_elem 
    '(3 (2 () ()) (5 (4()()) (6()())))
    )
)