HOMEWORK 10: Instagram Notifications


NAME:  Faisal Nageer


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

N/A

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  Timed: 1 hours, 47 minutes


MISC. COMMENTS TO GRADER:
(optional, please be concise!)

## Reflection and Self Assessment

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your
own? What kinds of errors did you get? How did you fix them?

What parts of the assignment did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this assignment? How well
did the development and testing process go for you?

- Really liked this homework, it was pretty easy and it let me learn how to use inheritance - never needed to use it before so I hadn't learned how to. Hadn't gone to the past few lectures so I didn't use polymorphism in this assignment, I don't really understand how to use it. It was not required to be used anyways.
- I initially made a Posts class for the posts, but that was not necessary. Storing the users and post details were unnecessary, I just got the needed information from the files once and stored it, skipping the rest. That sped up the executable a lot.
- I didn't use much of inheritance in this assignment, I'm sure it could've been used more but I used it to the minimum. There was no requirement as to how much inheritance needed to be used. I did extend a main Notification class to the 5 different types.
- I struggled a bit with creating the extended classes as I wanted to redeclare variables which I could not do. Fixed this by modifying the already created variables when the extended class item was initialized.
- Even though it was not actually used, I learned how to implement a "default" constructor for inheritance, never used that before. It was needed to create the constructors for the extended classes.
- Importing the posts and users was straightforward, the parts where I struggled (or spent more time on) the most were importing the events and outputting the notifications. I initially chose to use a priority queue to store the users in a notification, but I ran into issues with that as I needed to be able to push to the other side of the queue and fetch from the opposite side (and I didn't want to use a separate queue and a loop to reverse it), so I just used a vector which worked quite fine.
- When outputting the notifications, I ran into a few issues with reversing the grouped events. Most were easy fixes that just took a minute to fix and test after identifying them.
- I'm used to pushing to vectors, so I had to re-learn how to push to the front of a vector using insert and begin, hadn't done that in a while - I've only used it twice on homeworks...
- Counting the notification output lines was a small issue as some went over the 100 limit by ~1 as I didn't check for overage in the non-grouped notification loop, I had only added the check for the notification itself.
