HOMEWORK 1: Spotify Playlists


NAME:  Faisal Nageer


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

N/A

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  Timed: 4 hours, 20 mins






MISC. COMMENTS TO GRADER:  
Optional, please be concise!


## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

- One error that I encountered was line.find("\""), which I was using to split the string into the name and (artist and current) parts. It was returning 0, but after debugging, I found this issue to be due to the fact that the lines start with a quote, so I needed to instead search for "\" " (trailing space) so that it would properly split the string as there is no space after the first quote but there is one after the second.
- Another issue I faced was the .find() string function returning 18446744073709551615 when searching for the "current" string. It seemed that it would return that number regardless of whether "current" was found in the string or not. This was solved using != std::string::npos.
- Another issue I faced was when looping through songs, the variable I was using to track the position in the songs vector, i, was not an int. When I used int i = 0, it threw different signedness int and std::vector<PlaylistSong>::size_type. I solved this by changing int to size_t.
- Another issue I faced was when the entire line was the action (next, previous), the action was set to the entire line which includes an ending new line character. This was fixed by using line.substr(0, line.length() - 1) to remove the last character.
- As I split my code into different classes and files, I get different types for variables and am unable to use them in function calls. Turns out I cannot pass a file stream through a function externally, so had to import the file in the external file.
