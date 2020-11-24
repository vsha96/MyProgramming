;gnu clisp  2.49.60

(defun calln (f n x)
    (cond
        ((> n 0) (calln f (- n 1) (funcall f x)))
        (x)
    )
)

(print
    (calln
         'list 5 '(a b)
    )
)