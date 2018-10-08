# CS 3251: Intermediate Software Design
## Programming Assignment 4


This assignment further focuses on strong exception safety and linked-lists. While similar to Assignment 3, this assignment has you implementing a more complex data structure.  The linked list uses linked nodes to create the list. This linked list is a circular doubly-linked list and uses a dummy node to indicate the beginning/end of the list. You need to be certain that you read and understand all comments in the files.

You are provided with several files.  DO NOT CHANGE THESE FILES:
* _include/AllocationTracker.h_ and _src/AllocationTracker.cpp_
* _include/LinkedList.h_
* _include/LinkedListNode.h_
* _include/LinkedListIter.h_
* _include/LinkedListConstIter.h_

You are also provided with several files for use in testing your implementation.  DO NOT CHANGE THESE FILES EITHER (except grad-students will change linkedListConstIter.cpp):
* _tests/main.cpp_
* _tests/linkedListTest.cpp_
* _tests/linkedListConstIter.cpp_
* _CMakeLists.txt_

### All Students Must:

* Create the file _LinkedList.cpp_ that contains the function implementations outlined in _LinkedList.h_. You need to test your code with _linkedListTest.cpp_.

* Create the file _LinkedListNode.cpp_ that contains the function implementations outlined in _LinkedListNode.h_. You need to test your code with _linkedListTest.cpp_.

* Create the file _LinkedListIter.cpp_ that implements non-const iterators for the linked list container. You need to test your code with _tests/linkedListTest.cpp_ and _tests/linkedListIterTest.cpp_.

* Create the file _LinkedListConstIter.cpp_ that implements const iterators for the linked list container.  You need to test your code with _tests/linkedListTest.cpp_ and _tests/linkedListConstIterTest.cpp_.


### Graduate Students Must:

* Implement six additional unit tests as outlined in _tests/linkedListConstIter.cpp_.  These tests should exercise functionality specific to the const LinkedList iterator.


## WARNING: DO NOT WAIT TO START THIS ASSIGNMENT! IT WILL LIKELY TAKE MORE TIME THAN THE LAST ASSIGNMENT!

The assignment is to be submitted using the link to github.com sent out via email to all class members. DO NOT email your assignment to the professor or the TAs.  Emailed assignments ARE NOT accepted.  We will grade the last commit to your repository before the deadline date and time.  Any commits after that moment will be ignored.  If nothing has been committed at that time you will receive a zero grade. 


### REMINDERS:

* Ensure that your name, vunetid, email address, and the honor code appear in the header comments of all files that you have altered.

* Do not alter any of the project files unless explicitly directed otherwise!  Work only on those files specified above.  You must use the supplied `CMakeLists.txt` file as is.

* All students are required to abide by the CS 3251 coding standard, [available on the course web page](https://vuse-cs3251.github.io/style-guidelines/) and provided to you on the first day of class. Points will be deducted for not following the coding standard.

* For full credit, your program must compile with recent versions of `clang` and `gcc` and run successfully with Travis CI.
  * The Travis build *will* fail if your code is not properly formatted. **This is by design.** If your code is compiling and running successfully, but the build is failing, then your build is most likely failing because your code is not passing the linter. This can be confirmed by checking if a command involving `clang-format` in the Travis build output log has an exit code of 1.

* Your program(s) should always have an exit code of 0.  A non-zero exit code (generally indicative of a segmentation fault or some other system error) is reason to worry and must be corrected for full points.
  
* When submitting the assignment, all files that are provided to you, plus your solution files have been submitted. All files necessary to compile and run your program must reside in the GitHub.com repository.

