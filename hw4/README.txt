HOMEWORK 4: Yelp Businesses


NAME:  Faisal Nageer


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

- jidongxiao/CSCI1200-DataStructures on GitHub (https://github.com/jidongxiao/CSCI1200-DataStructures/blob/master/hws/yelp_businesses/README.md)

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  Timed: 2 hours, 23 minutes


MISC. COMMENTS TO GRADER:
(optional, please be concise!)


## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

- There was an error key_start == std::string::npos, fixed this by casting key_start to size_t.
- There was an issue with the number of arguments due to the categories argument accepting multiple categories. Fixed this by checking for a minimum of 4 arguments (at least 0 categories).
- std::invalid_argument was being thrown when using stoi. After debugging, found that there was a comma at the end of the string, and it was not a string so I needed to denote the end character by the comma instead of the quote. Another issue was a blank string, which threw an error with stoi as well. Fixed by catching RestaurantsPriceRange2 for the "None" value.
- Category names did not match due to the different case types used in the input categories arguments and the input JSON file, so they had to be converted to lowercase and then compared for equality.
- Very nice, easy assignment. Learned more about lists and iterators from this assignment than I thought I would!
