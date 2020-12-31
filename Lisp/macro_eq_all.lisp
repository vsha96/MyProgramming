;gnu clisp  2.49.60

(defmacro eq_all (&rest Args)
    (cond
        ((null Args))
        ((null (cdr Args)))
        ((equal (car Args) (cadr Args)) `(eq_all ,@(cdr Args)))
    )
)

(print
    (eq_all '(a()()) '(a()()) '(a()()) '(a()()))
)

(print
    (eq_all '(a()()) '(c()(d)) '(a()()) '(a()()))
)