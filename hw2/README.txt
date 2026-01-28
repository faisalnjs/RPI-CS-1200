HOMEWORK 2: Ride Sharing


NAME:  Faisal Nageer


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

- GeeksForGeeks (https://www.geeksforgeeks.org/cpp/how-to-split-string-by-delimiter-in-cpp/#using-stdfind-and-stringsubstr)
- jidongxiao/CSCI1200-DataStructures on GitHub (https://github.com/jidongxiao/CSCI1200-DataStructures/tree/master/hws/ride_sharing#calculate-distance-based-on-haversine-formula)

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # hours >


MISC. COMMENTS TO GRADER:
(optional, please be concise!)


## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

- Faced a 'comparison of integer expressions of different signedness' error when comparing int to size_type. Fixed it by casting the int to size_type.
- Faced an error where the last attribute of the rider was not being added to the attributes vector correctly. Fixed - realized that I had a duplicate line.
- Didn't know how to convert a string to a double, but realized that the std::stod() function could be used for this homework as we are allowed to use all functions in the std namespace.