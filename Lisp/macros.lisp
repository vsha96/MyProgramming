;gnu clisp  2.49.60

; function with any count of args
(defun myList(&rest X) X)

; macro
; here we use ',' to place our expression
; and also use `, not '
(defmacro myIf(C E1 E2)
    `(cond (,C ,E1)(T ,E2))
)

(defmacro myFuncall(f &rest Args)
    (cons (eval f) Args)
)

(defmacro myFuncall2(f &rest Args)
    `(,(eval f) ,@Args)
)

(defmacro myAnd(&rest Args)
    (cond
        ((null Args) T)
        ((null (cdr Args)) (car Args))
        ((eval (car Args)) `(myAnd ,@(cdr Args)))
    )
)

(print (list 'A '(s d) 'C '((z))))
(print (mylist 'A '(s d) 'C '((z))))

(if (> 5 0) (print 'yes) (print 'no) )
(myif (< 5 0) (print 'yes) (print 'no) )

(print (myfuncall '+ 1 2 3))
(print (myfuncall 'mapcar 'car '((a s)(d v)(3 6))))
(print (myfuncall2 'mapcar 'car '((a s)(d v)(3 6))))

(print (and 'A NIL T) )
(print (myAnd 'A NIL T) )