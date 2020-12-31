;gnu clisp  2.49.60

(defun remove_if (F S)
    (cond
        ((null S) NIL)
        ((atom (car S)) (cond
                            ((funcall F (car S)) (remove_if f (cdr S)) )
                            ((cons (car S) (remove_if f (cdr S))))
                        ))
        ((cons (remove_if f (car S)) (remove_if f (cdr S))))
    )
)


(print
    (remove_if 'null '( (5 () bb) c () (f)))
)