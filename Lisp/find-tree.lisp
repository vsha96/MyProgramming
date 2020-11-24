;gnu clisp  2.49.60

(defun find-tree (e tree)
    (cond
        ((null tree) tree)
        ((eql e (car tree)) T)
        ((find-tree e (cadr tree))) 
        ((find-tree e (caddr tree)))
    )
)