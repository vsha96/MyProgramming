;gnu clisp  2.49.60

; Tree ::= nil | (atom Tree Tree)
(defun count_of_elements (tree)
    (cond
        ((null tree) 0)
        ((+ 1 (count_of_elements (cadr tree)) (count_of_elements (caddr tree))))
    )
)

(print
    (count_of_elements 
    '(2 (3 () ()) (5 () (5 (5()())()))))
)