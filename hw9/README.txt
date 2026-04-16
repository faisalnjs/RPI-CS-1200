HOMEWORK 9: Tiktok Trends


NAME:  Faisal Nageer


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

N/A

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  Timed: 2 hours, 30 minutes


MISC. COMMENTS TO GRADER:
(optional, please be concise!)
- Try/throw/catch was implemented when importing the videos from the input file.
- std::priority_queue was used to sort videos and groups by their total views.

## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

- Easy homework. Parsing the input JSON was similar to how we did it in other homeworks, easy to parse an inner object as well.
- The double hashtag use for one of the videos messed me up for a bit, so until I realized that was allowed I was stuck.
- Experimented with using std::unordered_map, std::unordered_set, and std::priority_queue for various collection implementations, and switched between them to find the best fit for the data as the assignment progressed.
- Sorting hashtags/sounds by their name was the opposite from described in the README (or maybe my implementation was the opposite), so that took a few seconds extra to figure out.
- Hash functions were created for std::unordered_map and std::unordered_set.
