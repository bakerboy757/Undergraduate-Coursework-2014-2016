;Tyler Kelly: tck13
(define addStudent
  (lambda (n lst roster og)
    (cond((= n 0) (begin
 		               (display "\tStudent ID: ")
                   (let ((item1 (read-line)))
                    (cond ((in-roster item1 og)

                      (display "\n\t")
                      (display item1)
                      (display " already exists in roster. Try again.\n")
                      (addStudent 0 '() roster og)
                     )
                     (else
                      (addStudent 1 (list item1) roster og))
                     )
                   )

		               )
         )
         ((= n 1) (begin
            		   (display "\n\tStudent name: ")
            		   ;;(addStudent 2 (list (car lst) (read-line)))
                   (let ((item (read-line)))
                    (cond ((in-roster item og)
                     (display "\t")
                     (display item)
                     (display " already exists in roster. Try again.")
                     (addStudent 1 lst roster og))
                     (else
                     (addStudent 2 (cons item lst) roster og)))
                   )
                   )
         )
	       ((= n 2) (begin
            		   (display "\n\tGrade: ")
            		   (cons (read-line) lst)
                  )
         )
    )
  )
)
(define in-roster
  (lambda(item lst)
    (cond((null? lst)
           #f
          )
      ((or (equal? (cadr (car lst)) item) (equal? (caddr (car lst)) item))
        #t)
      (else
       (in-roster item (cdr lst))

      )

    )

  )
)
(define displayStudent
  (lambda (item lst)
	         (cond ((null? lst)
                  (display "\n\tStudent ")
                  (display item)
                  (display " not in roster")
            )
            ((or (equal? (cadr (car lst)) item) (equal? (caddr (car lst)) item))
            				(display "\n\tID=")
            				(display (caddr(car lst)))
                    (display ", Name=")
                    (display (cadr(car lst)))
                    (display ", Grade=")
                    (display (car(car lst)))
            				(newline)
            			)
            (else
                    (cons (car lst) (displayStudent item (cdr lst)))
            )
           )

   )
)
(define removeStudent
  (lambda (item lst)
	         (cond ((null? lst)
                  (display "\n\tStudent ")
                  (display item)
                  (display " not in roster")
            )
            ((equal? (cadr (car lst)) item)
            				(display "\n\tStudent with name ")
            				(display item)
                    (display " deleted")
            				(newline)
            				(cdr lst)
            )
            ((equal? (caddr (car lst)) item)
                    (display "\n\tStudent with ID ")
                    (display item)
                    (display " deleted\n")
                    (cdr lst)
                    )
            (else
                    (cons (car lst) (removeStudent item (cdr lst)))
            )


           )

   )
)
(define smallest-roster-record
  (lambda (min lst)
    (cond ((null? lst)
          min
     )
      ((< (string->number(caddr (car lst))) (string->number (caddr min)))
        (smallest-roster-record (car lst) (cdr lst)) ;new min, lets see if we can find a smaller value

      )
      (else
       (smallest-roster-record min (cdr lst)) ;not the min we are looking for, lets keep searching
      )
    )
  )
)
(define smallest-roster-record-name
  (lambda (min lst)
    (cond ((null? lst)
          min
     )
      ((string<? (cadr (car lst)) (cadr min))
        (smallest-roster-record-name (car lst) (cdr lst)) ;new min, lets see if we can find a smaller value

      )
      (else
       (smallest-roster-record-name min (cdr lst)) ;not the min we are looking for, lets keep searching
      )
    )
  )
)
(define smallest-roster-record-grade
  (lambda (min lst)
    (cond ((null? lst)
          min
     )
      ((> (string->number(car (car lst))) (string->number (car min)))
        (smallest-roster-record-grade (car lst) (cdr lst)) ;new min, lets see if we can find a smaller value

      )
      (else
       (smallest-roster-record-grade min (cdr lst)) ;not the min we are looking for, lets keep searching
      )
    )
  )
)
;sort roster by id
(define list-by-id
  (lambda (lst)
    (cond ((null? lst) '())
      (else
        ;concat the list with new smallest id along with the original list minus the duplicate
        (cons (smallest-roster-record (car lst) lst) (list-by-id(remove-by-id (smallest-roster-record (car lst) lst) lst)))
    )
  )
))
(define list-by-grade
  (lambda (lst)
    (cond ((null? lst) '())
      (else
        ;concat the list with new smallest id along with the original list minus the duplicate
        (cons (smallest-roster-record-grade (car lst) lst) (list-by-grade(remove-by-id (smallest-roster-record-grade (car lst) lst) lst)))
    )
  )
))
(define list-by-name
  (lambda (lst)
    (cond ((null? lst) '())
      (else
        ;concat the list with new smallest id along with the original list minus the duplicate
        (cons (smallest-roster-record-name (car lst) lst) (list-by-name(remove-by-id (smallest-roster-record-name (car lst) lst) lst)))
    )
  )
))
;find duplicate id and remove
(define remove-by-id
  (lambda (item lst)
    (cond ((null? lst)
           '()
     )
     ((equal? (car lst) item)
             (cdr lst)
             )
     (else
             (cons (car lst) (remove-by-id item (cdr lst)))
     )


  )


  )
)
(define list-display
  (lambda (lst)
	         (cond ((null? lst)
                  (newline)
            )
            (else
                    (display "\n\tID=")
                    (display (caddr(car lst)))
                    (display ", Name=")
                    (display (cadr(car lst)))
                    (display ", Grade=")
                    (display (car(car lst)))
                    (list-display (cdr lst))
            )
           )

   )
)
(define performtask
  (lambda (n roster)
    (cond ((= n 0) (begin
                    (display "\n\tResetting roster...\n")
                    (menu '())
                    ))
          ((= n 1) (begin
                    (display "\n\tLoad roster from file: \n")
                    (display "\n\tEnter File to load: ")
                    (menu (read (open-input-file (read-line))))
                  ))
          ((= n 2) (begin
                    (display "\n\tStore roster to a file: \n")
                    (display "\n\tEnter File to store roster to: ")
                    (let ((p (open-output-file (read-line))))
                     (write roster p)
                     (close-output-port p)
                    )
                    (menu roster)))
          ((= n 3) (begin
            		    (display "\n\tDisplay roster sorted by ID:\n")
            		    (list-display (list-by-id roster)) ;not working as intended
                    ;(list-display roster)
             		    (menu roster)
            		   ))
          ((= n 4) (begin
                    (display "\n\tEnter student name or ID: ")
                    (displayStudent (read-line) roster)
             		    (menu roster)
		                ))
	        ((= n 5) (begin
        		        (display "\n\tAdd a student to roster:\n")
        		        (newline)
                    (menu (cons (addStudent 0 '() roster roster) roster))
        	         ))
          ((= n 6) (begin
	                  (display "\n\tEnter a student name or ID: ")
                    (menu (removeStudent (read-line) roster))
	                 ))
          ((= n 7) (begin
                     (display "\n\tDisplay roster sorted by name:\n")
                     (list-display (list-by-name roster)) ;not working as intended
                     ;(list-display roster)
                     (menu roster)
                    ))
          ((= n 8) (begin
                    (display "\n\tDisplay roster sorted by grade:\n")
                    (list-display (list-by-grade roster)) ;not working as intended
                    ;(list-display roster)
                    (menu roster)
                   ))
	        ((= n 9) (begin
		                (display "\n\tExiting...\n")
                    #t
                   ))
          (else (begin
                    (display "\n\ttask no. ")
                    (display n)
                    (display " does not exist.\n\n")
                    (menu roster)
                  )
            )
     )
   )
)
(define menu
  (lambda (roster)
     (begin
	(display "\tClass roster management system\n")
        (display "\t============================\n")
        (display "\t   MENU\n")
        (display "\t============================\n")
        (display "\t0. Reset roster\n")
        (display "\t1. Load roster from file\n")
        (display "\t2. Store roster to file\n")
        (display "\t3. Display roster sorted by ID\n")
        (display "\t4. Display student info\n")
        (display "\t5. Add a student to roster\n")
        (display "\t6. Remove a student from roster\n")
        (display "\t7. Display roster sorted by name\n")
        (display "\t8. Display roster sorted by grade\n")
        (display "\t9. Exit\n\n")
        (display "\tEnter your choice: ")
        (performtask (read) roster)
      )
   )
)
