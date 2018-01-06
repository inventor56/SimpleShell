#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <sstream>
#include <iterator>

using namespace std;

int main() {
    const string strFilename = "/bin/"; // Prefix to where the Linux commands reside
    while(true) {
        string userInput; // Full initial user input (i.e. ls - l)
        vector<char *> arguments; // Arguments provided by the user, which is parsed from userInput

        // Begin by prompting the user for input
        cout << "\nHello! Welcome to the Shell. Please enter in your Linux arguments: " << endl;
        getline(cin, userInput); // The entire user input (all on one line)

        if (userInput == "exit") { // Terminate the program if exit is the input
            exit(0); // Exit with EXIT_SUCCESS returned to the host environment
        }

        // Otherwise, parse user input (split into words delimited by whitespace)
        istringstream inputStream(userInput); // Create input stream out of the user input
        vector<string> items{istream_iterator<string>{inputStream}, istream_iterator<string>{}}; // Iterate through input stream and create new String vector with each individual word

        // Set up filename and arguments for passing into the execvp method in the child process
        char * filename = const_cast<char *>((strFilename + items.front()).c_str()); // Concatenate the filename (i.e. "/bin/") with what the user's first input was (i.e. "pwd")

        for (auto const& item: items) {
            arguments.push_back(const_cast<char *>(item.c_str())); // Place each argument into your char *arguments vector
        }
        arguments.push_back(nullptr); // Finally, the last portion of the vector will be a null pointer (a NULL terminator to tell it to end)

        // Prepare to fork() off child process
        int pid, status; // Process ID and status for potential checks

        pid = fork(); // Fork child process

        if (pid < 0) { // Error during creation
            cout << "Error creating child process" << endl;
            exit(1); // exit
        }

        // Child process
        if (pid == 0) {
            execvp(filename, arguments.data()); // We pass file name and arguments (filename will be, for instance, /bin/ls)
            exit(0); // Very important! Exit the child process
        }
        wait(&status);  // Busy wait until the child process terminates (shell completion)
    }
}