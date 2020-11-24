;gnu clisp  2.49.60

; transpose of the matrix
; ((1 2 3) (4 5 6)) ->
; -> ((1 4) (2 5) (3 6))

(defun trans (l)
    (cond
        ((null (car l)) nil)
        ((cons (mapcar 'car l) (trans (mapcar 'cdr l))))
    )
)

(print
    (trans '((1 2 3) (4 5 6) (7 8 9)))
)