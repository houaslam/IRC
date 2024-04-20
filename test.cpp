#include <iostream>
#include <ctime>

int main() {
    // Get the current time as a Unix timestamp
   time_t currentTime =time(NULL);

    // Convert the Unix timestamp to a struct tm
   tm* timeinfo = gmtime(&currentTime);

    // Create a character array to hold the formatted time
    const int bufferSize = 80; // Buffer size for the formatted time
    char buffer[bufferSize];

    // Format the time
   strftime(buffer, bufferSize, "%a %b %d %H:%M:%S %Y", timeinfo);

    // Display the formatted time
   cout << "Formatted time: " << buffer <<endl;

    return 0;
}

