;gnu clisp  2.49.60

(defmacro myevery (F &rest Args)
    (cond
        ((null Args))
        ((null (cdr Args)) (funcall (eval F) (car Args)))
        ((funcall (eval F) (eval (car Args))) `(myevery ,F ,@(cdr Args)))
    )
)

(print (myevery 'listp 5 'c 'f) )
(print (myevery 'listp '(5) 'c 'f) )
(print (myevery 'listp '(5 7) '(c) '(f)))