;gnu clisp  2.49.60

(defun decart (l1 l2)
    (cond 
        ((null l1) l1)
        ((null l2) l2)
        ((append (comp (car l1) l2) (decart (cdr l1) l2)))
    )
)

(defun comp (e l)
    (cond
        ((null e) e)
        ((null l) l)
        ((cons (list e (car l)) (comp e (cdr l))))
    )
        
)


(print (decart '(A B C) '(1 2)))