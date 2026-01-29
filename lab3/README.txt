Lab 3

Compile: g++ -Wall -Wextra -g -o roads.out roads.cpp line.cpp point.cpp
Run: ./roads.out input_a.txt

Checkpoint 1:
- Program takes in input file, calculates slopes between points, sorts by steepest line between points, and outputs the sorted lines.

- 1. Error: sort is not a member of std in roads.cpp
- 1. Fix: added algorithm library to roads.cpp

- 2. Error: redefinition of class Point
- 2. Fix: added include header guards to point.h

- warning: expression result unused / expression has no effect
- warning: control reaches / may reach end of non-void function
- warning: comparison of integers of different signs: 'int' and 'unsigned int'
- warning: returning reference to local temporary object / reference to stack memory associated with a local variable returned
- warning: unused variable

Checkpoint 2:
- warning: expression always true
- fix: i >= 0 was always true due to i being an unsigned int; removed condition

- warning: statement has no effect
- fix: fabs was used in the previous line, so the line that manually converted to absolute value had no effect; commented

- warning: control reaches / may reach end of non-void function
- fix: happens when the function does not have a return statement for a needed condition; fixed by adding a return statement if none of the conditions are met

- warning: comparison of integers of different signs: 'int' and 'unsigned int'
- fix: changed int to size_t for int i = 0

- warning: returning reference to local temporary object / reference to stack memory associated with a local variable returned
- fix: there was an extra & when declaring the function; removed

- warning: unused variable
- fix: there was an unused answers variable, could be either removed or used; used in the return statement
