#include <iostream>
#include <fstream>
#include <string>
#include <map>     // Enables the use of std::map, a container for key-value pairs
#include <limits>  // For numeric_limits

using namespace std;

class DataHandler {
private:
    map<string, int> itemFrequency;

    // Function to save data to 'frequency.dat'
    void saveDataToFile() {
        ofstream outputFile("frequency.dat");
        if (!outputFile.is_open()) {
            cerr << "Error opening output file." << endl;
            exit(1);
        }

        for (const auto& pair : itemFrequency) {
            outputFile << pair.first << " " << pair.second << endl;
        }

        outputFile.close();
        cout << "Data saved to 'frequency.dat'." << endl;
    }

public:
    // Function to add data from the input file
    void readDataFromFile() {
        ifstream inputFile("CS210_Project_Three_Input_File.txt");
        if (!inputFile.is_open()) {
            cerr << "Error opening input file." << endl;
            exit(1);
        }

        string item;
        while (inputFile >> item) {
            // Increment the frequency each time the same item is encountered
            itemFrequency[item]++;
        }

        inputFile.close();  // Close the file after reading

        if (itemFrequency.empty()) {
            cout << "No data read from the file." << endl;
        }
    }

    // Function to find the frequency of a specific word
    void findFrequency(const string& searchItem) {
        if (itemFrequency.find(searchItem) != itemFrequency.end()) {
            cout << "Frequency of " << searchItem << ": " << itemFrequency[searchItem] << endl;
        }
        else {
            cout << "Item not found in the list." << endl;
        }
    }

    // Function to print the list of items with their frequencies
    void printItemList() {
        cout << "LIST OF ITEMS WITH FREQUENCIES:" << endl;
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Function to print a histogram of item frequencies
    void printHistogram() {
        cout << "HISTOGRAM OF ITEM FREQUENCIES:" << endl;
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

    // Function to save data to file
    void saveDataToFileAndExit() {
        saveDataToFile();
        cout << "Exiting the program." << endl;
    }
};

// Function to display the menu options
void displayMenu() {
    cout << "\nMENU OPTIONS:" << endl;
    cout << "1. Find the frequency of a specific word." << endl;
    cout << "2. Print the list of items with their frequencies." << endl;
    cout << "3. Print a histogram of item frequencies." << endl;
    cout << "4. Save data to 'frequency.dat' and exit." << endl;
    cout << "Enter your choice (1-4): ";
}

// Function for numeric input validation
int getValidIntegerInput() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail() || input < 0) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 4: ";
        }
        else {
            break;
        }
    }
    return input;
}

int main() {
    DataHandler dataHandler;
    dataHandler.readDataFromFile();

    int choice;
    bool shouldExit = false;  // Flag to determine if the program should exit

    do {
        displayMenu();
        choice = getValidIntegerInput();

        switch (choice) {
        case 1: {
            string searchItem;
            cout << "Enter the item to look for: ";
            cin >> searchItem;
            dataHandler.findFrequency(searchItem);
            break;
        }

        case 2: {
            dataHandler.printItemList();
            break;
        }

        case 3: {
            dataHandler.printHistogram();
            break;
        }

        case 4: {
            dataHandler.saveDataToFileAndExit();
            shouldExit = true;  // Set the flag to exit the program
            break;
        }

        default:
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
        }

    } while (!shouldExit);

    cin.get();  // Wait for user input before closing the console window

    return 0;
}
