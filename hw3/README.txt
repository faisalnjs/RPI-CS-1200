HOMEWORK 3: MATRIX CLASS


NAME:  Faisal Nageer


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

- StackOverflow (https://stackoverflow.com/questions/16737298/what-is-the-fastest-way-to-transpose-a-matrix-in-c)
- Stanford University (https://graphics.stanford.edu/~mdfisher/Code/Engine/Matrix4.cpp.html)
- StackOverflow (https://stackoverflow.com/questions/4991638/how-to-implement-c-inequality-operators-for-aggregate-structs)
- jidongxiao/CSCI1200-DataStructures on GitHub (https://github.com/jidongxiao/CSCI1200-DataStructures/blob/master/hws/matrix_class/optimization/matrix_fast.cpp)
- Although I already had prior experience with dealing with matrices, AI was used on this assignment to guide me on how to do the same operations in code as I had not done that before, and the README provided was not sufficient for my understanding. AI was NOT used to complete the assignment for me.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  Timed: 4 hours, 8 minutes


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

- This homework was a bit challenging. I had to learn how to do matrix operations in code, which was a bit difficult. Lots of research happened before the actual start of the homework.
- Memory management and leaks were not that bad to manage.
- The various functions were not that difficult to implement once I understood how to implement them in code. The getter and setter functions were the easiest, quarter() or transpose() may have been the most difficult for me.
- Had some difficulty with supporting the equality and inequality operators == and !=, didn't know how to do that before this homework do had to research how to do that. I believe lecture did not cover this.
- There was an issue where the get function I had made was not setting the input variable to the new value, but that was because I had not passed the variable in by reference - fixed that.
- My output did not match the sample output exactly, but that was due to the fact that there were required newline characters before starting to print the output, as well as after ending the output, which I had not included.
- Same thing as the above but with the space at the beginning of the line.
- UL, UR, LL, and LR were not outputting and instead showed Segmentation fault (core dumped). The cause of this was the quarter() function. Had to use <cmath> library to round up instead of rounding down, but that was not the issue. Using Dr. Memory, found the issues. I had to use the operator= function to reduce errors that happened when memory was freed before accessing it.
- Overall loved this assignment, learning more about matrices was nice and I've always wanted to do this in code. Learning how to use Dr. Memory was also nice and very helpful in finding memory leaks.
