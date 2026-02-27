HOMEWORK 5: Online Dating


NAME:  Faisal Nageer


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

- Lab 6 for merge sort

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  Timed: 7 hours


MISC. COMMENTS TO GRADER:
(optional, please be concise!)


## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

- When dealing with multiple input text files, I had to take into account the possibility that the input phone number could not exist in the list of users. Fixed by checking if the user exists in the list before proceeding.
- There was an issue with the distance calculation, I was using integers when doubles were needed. Fixed by changing the data types to double.
- Memory leaks needed to be fixed by deconstructing the users list at the end of the program.
- I had to figure out how to sort the matches by phone number when the number was a string, so that was difficult. I decided on just storing the phone numbers as integers without dashes and just sort by integer value, which worked well. It took a lot of time to create the sortByPhone function manually though. Later I found that manually doing this broke the structure, so I just used a temporary user and swapped nodes that way. Lots of time wasted there. Ended up using merge sort from Lab 6.
- There was a loss of users when sorting, fixed by sorting at the beginning of the program and only if the output needed the sorted view of the matches.
- To output to the same file multiple times, I needed to make the file stream a global variable and open it from a function only when it was not already open, and then modify that file stream.
- This homework was confusing, it took a lot of thinking and a lot of time. But overall, this assignment was nice - no research needed.
