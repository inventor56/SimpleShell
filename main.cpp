#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <sstream>
#include <iterator>
#include <cstring>

using namespace std;

int main() {

    while(true) {
        // Full initial user input (i.e. cd /Documents/SchoolBudget)
        string userInput;
        // Begin by prompting the user for input
        cout << "Hello! Welcome to the Shell. Please enter in your Linux arguments: " << endl;
        //Store input;
        cin >> userInput; // The entire user input
        // Terminate the program if exit is the input
        if (userInput == "exit") {
            exit(0); // Exit with EXIT_SUCCESS returned to the host environment
        }

        // Otherwise, parse user input (split into words delimited by whitespace
        auto * filename = const_cast<char *>("/bin/"); // First element refers to path of executable file
        vector<char *> arguments;

        istringstream inputStream(userInput); // Create input stream out of the user input
        vector<string> items{istream_iterator<string>{inputStream}, istream_iterator<string>{}}; // Iterate through input stream and create new String vector with each individual word

        strcat(filename, items.front()); // Concatenate the filename (i.e. "/bin/") with what the user's first input was (i.e. "pwd")

        for (auto const& item: items) {
            arguments.push_back(const_cast<char *&&>(item.c_str())); // Place each argument into your char *arguments vector
        }
        arguments.push_back(nullptr); // Finally, the last portion of the vector will be a null pointer (a NULL terminator to tell it to end)

        //const char *test = "pwd";
        //strcat(filename, "pwd");

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
                execvp(filename, arguments.data()); // We pass file name and arguments (filename will be, for instance, /bin/ls)

            }
            catch (exception e) {
                cout << "Sorry, but you have entered invalid input: Please try again" << endl;
            }

            exit(0); // Very important! Exit the child process
        }

        wait(&status);  // Busy wait until the child process terminates (shell completion)
    }
}