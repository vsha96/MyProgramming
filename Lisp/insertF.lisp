;gnu clisp  2.49.60

; key in a-list
; if key is not in a-list, then add it
; if key is in a-list, replace value with F effect

(defun insertF (f k v l)
    (cond
        ((null l) (cons (list k v) l))
        ((eq k (caar l)) (cons (list k (funcall f v)) (cdr l)))
        ((cons (car l) (insertF f k v (cdr l))))
    )
)

(print
    (insertf 'list 2 'hh '((1 4)(2 4)(4 x)))
)