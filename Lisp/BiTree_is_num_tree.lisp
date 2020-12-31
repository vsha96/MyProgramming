;gnu clisp  2.49.60

; BiTree ::= NIL | (node BiTree BiTree)

; (is-num-tree  '(1 (2 NIL NIL) (3 (f NIL NIL) NIL)) )  =>  NIL
; (is-num-tree '(1 (2 NIL NIL) (3 NIL NIL)))  =>  T

(defun is-num-tree (Tree)
    (cond
        ((null tree))
        ((numberp (car tree)) (and (is-num-tree (cadr tree)) (is-num-tree (caddr tree))))
    )
)


(print
    (is-num-tree  '(1 (2 NIL NIL) (3 (f NIL NIL) NIL)) )
)

(print
    (is-num-tree '(1 (2 NIL NIL) (3 NIL NIL))) 
)