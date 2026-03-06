HOMEWORK 6: INVERSE WORD SEARCH


NAME:  Faisal Nageer


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

- Lecture 12 for word search (https://presentationassistants.com/calendar/view_md.php?file_id=1Rn5mpxiB11yNJUiqxXEEs6_tYK_4pLkU)
- I did not have any prior experience with dealing with reverse recursion, so AI was used on this assignment to guide me on how to do reverse recursion of the Lecture 12 given recursion program. It was also used for learning more about how reverse recursion works and different ways to implement it.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  Timed: 5 hours, 12 minutes


MISC. COMMENTS TO GRADER:  
Optional, please be concise!

- There were no given test case outputs for the test9.txt, test10.txt, test11.txt, test12.txt, test13.txt, test14.txt, and test15.txt input files. When testing this locally, I wanted to use these test files and easily compare to a given output like puzzle*.txt give input files. That would've been useful.

## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

- Everything about this homework was challenging. I don't believe we did reverse recursion in class, and I did not know how to do recursion before this, so a lot of time was spent just learning what recursion really was and how to reverse it. I used the in class word search recursion problem and worked that one backwards, that helped somewhat but I was still confused. I used AI a lot for this homework to learn more about reverse recursion, and different ways to implement it. I also used it to help with getting all the possible direction combinations, I spent a lot of time thinking about that and didn't get it. I think it was pretty helpful. Please note that I didn't include the countless hours of research in the total time estimate.
- Optimizing the program to run faster was fun, I always enjoy doing that. I used what I had learned from previous homeworks to optimize for memory and runtime as much as I could.
- I did not use pointers, instead I used global file variables. There was no rubric limit for this or putting functions in different files thankfully, so I did not need to separate everything into multiple files and worry about the variables being accessed by multiple files and needing to be passed through the functions and returned through them. Very thankful for the lax rubric for this one. I only passed the board width and height when creating a new board using the class, which I put in another file to save some space - should compile with the same time, and the compile time isn't taken into account for this homework anyways.
- For this homework I assumed that the input and output files were valid so as to reduce the file accessing, checking, and closing which would have taken more time. Looking back at the past homework and the test cases, the input and output files were always valid, so I think this was a safe assumption to make.
- Recursion was used twice in this homework. The first was when I needed to generate the boards, it would go through every wanted word and create a board and then add the next wanted word to the board (calling itself) as so to get all possible boards in the end. In every run of that, it would also verify the board to ensure that no unwanted words appeared in the board. The verify function was also recursion because it goes through every letter and reverifies the board for every letter (calling itself).
