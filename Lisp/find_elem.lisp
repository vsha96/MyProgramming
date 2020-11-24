;gnu clisp  2.49.60

; Tree ::= nil | (atom Tree Tree)
; here we have search tree
(defun find_elem (a tree)
    (cond
        ((null tree) NIL)
        ((= a (car tree)) T)
        ((< a (car tree)) (find_elem a (cadr tree)))
        ((find_elem a (caddr tree)))
    )
)

(print
    (find_elem 
        4
        '(3 (2 () ()) (5 (4()()) (6()())))
    )
)