HOMEWORK 7: Search Engine


NAME:  Faisal Nageer


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

N/A

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  Timed: 7 hours, 11 minutes


MISC. COMMENTS TO GRADER:
(optional, please be concise!)


## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

- A lot of time was spent on getting the full path of files from relative paths in the .html files, learning how to normalize URL paths, split them into parts, etc. but I eventually learned how to do it after a lot of debugging.
- Recursive functions were used for crawling the pages through the index.html's references to start, and subsequent references. The references were added first and then they were crawled which is less memory efficient but there was no limit on time.
- Circular includes were also an issue I ran into, solution for that was to not have the Result include Page which includes Query which includes Result and instead create an empty Page struct to use in Result.
