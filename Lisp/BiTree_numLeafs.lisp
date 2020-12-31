;gnu clisp  2.49.60

; BiTree ::= NIL | (number BiTree BiTree)

; (numLeafs #’(lambda(x)(> x 0)) ’(7(4 NIL NIL)(11(-5 NIL NIL)NIL)) ) => 1

(defun numLeafs (f tree)
    (cond
        ((null tree) 0)
        ((and (null (cadr tree)) (null (caddr tree)) (funcall f (car tree))) 1)
        ((+ (numLeafs f (cadr tree))  (numLeafs f (caddr tree)) ))
    )
)



(print
     (numLeafs #'(lambda(x)(> x 0)) '(7 (4 nil nil) (11(-5 (5 nil nil) NIL) (5 nil nil))) )
 )