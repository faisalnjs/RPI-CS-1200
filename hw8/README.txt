HOMEWORK 8: Youtube Comments


NAME:  Faisal Nageer


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

N/A

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  Timed: 4 hours, 53 minutes


MISC. COMMENTS TO GRADER:
(optional, please be concise!)


## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

- Very nice, smooth, easy homework. Had fun working on this one. Great culmination of previous homeworks and pointers. Learned a lot about trees and traversing them using recursion.
- We worked with JSON in a previous homework, so I easily got through parsing the input files. I stored the comments in a regular vector first, then built the tree after as we now had all of the parent comment IDs. I assembled the tree as a N-ary tree, with the top-level comments as different roots and the video as the parent of the top-level comments (listed in a vector). This worked quite well and was easy to use. Not sure it was the right way though, I thought a tree was required to have a single root? Maybe I'm getting this wrong, but this way does use trees and recursion and it works so I think I'm good.
- Recursion was used in this homework to find a comment, delete a comment, get all comment IDs, and output the comments. Several helper functions were used so that recursion could be used.
- Deletion of comments was tricky, eventually figured that I could only delete comments that were on the heap, and some were not on the heap. Had to do this for the children as well and ensure all were in the heap before deleting them.
- The last field in a comment line, the actual comment, took a few minutes to parse alone because there was another field that included the word "comment". Ended up wrapping the field in quotes to find it specifically.
