; keywords list
(setq keywords (list "and" "or" "not" "equal" "less" "nil" "list" "append" "concat" "set" "def" "for" "if" "exit" "load" "display" "true" "false"))
(setq kw (list "KW_AND" "KW_OR" "KW_NOT" "KW_EQUAL" "KW_LESS" "KW_NIL" "KW_LIST" "KW_APPEND" "KW_CONCAT" "KW_SET" "KW_DEF" "KW_FOR" "KW_IF" "KW_EXIT" "KW_LOAD" "KW_DISPLAY" "KW_TRUE" "KW_FALSE"))

; operators list
(setq operators (list "+" "-" "/" "*" "(" ")" ","))
(setq op (list "OP_PLUS" "OP_MINUS" "OP_DIV" "OP_MULT" "OP_OP" "OP_CP" "OP_COMMA"))

;comment
(defvar comment ";")

(setq exit1 0)

(setq exit2 0)

(defun gppinterpreter()
    (loop
        (defparameter str (read-line))

        (let
            ((words (list)))
            (setq words (split-string str))

            (loop for word in words
                do
                (if (string= word "EXIT")
                    (progn
                        (setq exit1 1)
                        (return)
                    )
                )
                (write-string "(")

                (if (equal (word-analyzer word) 2)
                    (progn
                        (write-line ")")
                        (return)
                    )
                )
                (write-line")")
            )
        )
        (if (equal exit1 1)
            (progn
                (setq exit1 0)
                (return)
            )
        )
    )
)


; Splits strings into words using whitespaces
(defun split-string (str &optional rs)
    (let
        ((i
            (position " " str
            :from-end t
            :test #'
            (lambda (a b) (find b a :test #'string=)))
        ))
        (if i
            (split-string (subseq str 0 i) (cons (subseq str (1+ i)) rs))
            (cons str rs)
        )
    )
)

; Word analyzer function 
(defun word-analyzer (word)
    (let ((len (length word)) (word1) (j 0) (index))
        (setq exit2 0)
        (loop for i from 1 to len
            do
            (if (equal exit2 1) (setq exit2 0))
            (setq word1 (string-downcase (subseq word j i)))

            ; comment analysis
            (if (and (equal exit2 0) (>= len 2) (string= (subseq word 0 1) comment))
                (if (string= (subseq word 1 2) comment)
                    (progn
                        write-line("COMMENT")
                        (setq exit2 2)
                    )
                )
            )

            ; operator analysis
            (if (not (equal (is-operator word word1) nil ))
                (progn
                    (setq j i)
                    (setq exit2 1)
                )
            )

            ; valuef analysis
            (setq valuef_analysis (is-valuef word word1 i j len ))
            (if (and (equal exit2 0) (not (equal valuef_analysis nil)))
                (progn
                    (setq i valuef_analysis)
                    (setq j i)
                    (setq exit2 1)
                )
            )

            ; keyword analysis
            (setq keyword_analysis (is-keyword word word1 i len))
            (if (and (equal exit2 0) (not (equal keyword_analysis nil)))
                (progn
                    (if (equal keyword_analysis 1)
                        (setq j i)
                    )
                    (setq exit2 1)
                )
            )

            ; identifier analysis
            (if (equal exit2 0)
                (progn
                    (setq id_analysis (is-identifier word word1 i j len))
                    (if (not (equal id_analysis nil))
                        (progn
                            (if (equal id_analysis 1)
                                (setq j i)
                            )
                            (setq exit2 1)
                        )
                    )
                )
        
            )
            (if (or (= exit2 -1) (= exit2 2)) (return exit2))
        )
    )
)


(defun is-keyword (word word1 i len)
    (setq rv nil)
    (setq index (searchList word1 keywords))

    (if (not (equal index nil))
        (if (>= i len)
            (progn
                (write word)
                (write-string ":")
                (write (nth index kw))
                (setq rv 0)
            )
        )
    )
)

(defun is-operator (word word1)
    (setq index (searchList word1 operators))
    (if (not (equal index nil))
        (progn
            (write word1)
            (write-string ":")
            (write (nth index op))
        )
    )
)

(defun is-identifier (word word1 i j len)
    (if (and (equal exit2 0))
        (if (= i len)
            (progn
                (write word)
                (write-string ":")
                (write-string "IDENTIFIER")
            )
        )
        (progn
            (format t "SYNTAX ERROR ~S cannot be tokenized.~%" (subseq word j len))
            (setq exit2 -1)
        )
    )
)

(defun is-valuef (word word1 i j len)
    (and (string= word1 "b")
       (> i 1)
       (string= (subseq word 0 i) (subseq word 0 (1- i)))
       (string= (subseq word (1+ i) len) (subseq word (1+ i) len))
    )
)

; Searches the list_ whether it has word in it
(defun searchList (word list_ &optional (i 0))
    (if (null list_)
        nil
        ; Checks for the first element in the list
        (if (string= word (car list_))
            i
            ; Recursively checks for the rest of the list by excluding the first element in the list_
            (searchList word (cdr list_) (+ i 1))
        )
    )
)

(write-line "Lexer started. Type EXIT to terminate")
; Main program
(gppinterpreter)

(write-line "Lexer ended.")