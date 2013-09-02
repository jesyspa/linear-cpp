/* We now know how to check whether the input was valid, but sometimes we'd like
 * to let the user provide an arbitrary number of inputs and then do something
 * with them.  For this we introduce the while statement:
 *
 *      while (condition) {
 *          statements...
 *      }
 *
 * It is much like the if statement, but when all the statements in the body are
 * executed, we continue right above the statement, not right below; the
 * condition is again checked, and if it is true we do the same thing again.
 *
 * A problem here is knowing when to stop.  We're going to take the simplest
 * solution and assume that any failed read indicates that there is no input
 * left over.  This is suboptimal, as it means we can't easily have multiple
 * input loops, but the extra checks necessary otherwise would detract from the
 * main point of looping.
 */

#include <iostream>
#include <string>

int main() {
    // When we want to define multiple variables of a simple type, we can write
    // the type once and then write the variables separated by commas.
    int total = 0, x, count = 0;

    std::cout << "Enter as many numbers as you want:\n";

    // We're going to read as much input as the user gives us, and then take the
    // average.
    while (std::cin >> x) {
        // count += 1 is the same thing as count = count + 1.  We need to count
        // how many numbers the user gave us, or we won't know what to divide by
        // to get the average.
        count += 1;
        total += x;
    }
    // If the loop has ended, it means we failed to read a number.  Now, by our
    // assumption, it is useless to ask the user to enter anything.

    // Remember: division by zero is bad.
    if (count == 0) {
        std::cout << "No numbers entered!\n";
    } else {
        // Here we can calculate the average.  Let's illustrate the difference
        // between integer and floating point maths while we're at it:
        std::cout << "Integer average: " << total/count << "\n";
        // You can assign an int to a double; the value is converted as you'd
        // expect it to be, though you may lose some precision if the value
        // can't be stored exactly.
        double double_total = total;
        // Dividing a double by an int works like dividing a double by a double.
        // All other operations work similarly; if either operand is a double,
        // the whole thing becomes a double.
        std::cout << "Floating point average: " << double_total/count << "\n";
    }

    return 0;
}

