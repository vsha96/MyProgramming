(defun RevBr (L)
    (cond 
        ((null L) L)
        ((null (cdr L)) L)
        (( cons (revbr (cdr L)) (cons (car L) NIL) ))
    )
)

(print (revbr '(A B C)))