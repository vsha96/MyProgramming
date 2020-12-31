;gnu clisp  2.49.60

;(ChangeRoad '((A B r 3) (B C a 5) (C F r 1))) => 2

(defun ChangeRoad (L) (croad (cdr L) (caddar L) 0))

(defun croad (L Type Res)
    (cond
        ((null L) Res)
        ((eq (caddar L) Type) (croad (cdr L) Type Res))
        ((croad (cdr L) (caddar L) (+ 1 Res)))
    )
)


(print
    (ChangeRoad  '((A B r 3) (B C a 5) (C F r 1) (C F r 1)) )
)