;gnu clisp  2.49.60

; we have search tree
(defun leaf-list (tree)
    (LL tree NIL)
)

(defun LL (tree Res)
    (cond
        ((null tree) Res)
        ((LL 
            (cadr tree) 
            (cons 
                 (car tree) 
                 (LL (caddr tree)  Res)
            ) 
        ))
    )
)

(print
    (leaf-list
    '(2 (1 NIL NIL) (8 NIL NIL))
    )
)

(print
    (leaf-list
    '(8 (2 (1 NIL NIL) (3 NIL NIL)) (13 NIL (10 NIL NIL)))
    )
)