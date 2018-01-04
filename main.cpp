#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

using namespace std;

int main() {

    while(true) {

        string command; // Full initial user input (i.e. cd /Documents/SchoolBudget)
        // Begin by prompting the user for input
        cout << "Hello! Welcome to the Shell. Please enter in your Linux command: " << endl;
        //Store input;
        cin >> command; // The entire command to execute in the shell, including arguments

        // Terminate the program if exit is the input
        if (command == "exit") {
            exit(0); // Exit with EXIT_SUCCESS returned to the host environment
        }

        // Otherwise, parse out input

        // Enter into fork

        int pid, status; // Process ID and status for potential checks

        pid = fork(); // Fork child process

        if (pid < 0) { // Error during creation
            cout << "Error creating child process" << endl;
            exit(1); // exit
        }

        if (pid == 0) { // Child process
            try {
                cout << "we made it inside the child process" << endl;
                //execvp("ERERER"); // "useful when the number  of  arguments is unknown in advance" (Marshall). We pass file name and arguments

            }
            catch (exception e) {
                cout << "Sorry, but you have entered invalid input: Please try again" << endl;
            }

            exit(1); // Very important! Exit the child process
        }

        wait(&status);  // Busy wait until the child process terminates (shell completion)
    }
}