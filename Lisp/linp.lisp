;gnu clisp  2.49.60

(defun linp(S)
    (cond
        ((null S) T)
        ((atom S) T)
        ((null (cdr S)) (linp(car S)))
        ((atom (cdr S)) NIL)
        (( and (linp(car S)) (linp(cdr S)) ))
    )
)

(print (linp '(A . (B . nil))))
(print (linp '(A . (B . C))))