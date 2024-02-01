#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip> 
using namespace std;

struct Book {
	string title;
	string author;
	int wordCount;
	map<char, int> letterFrequency;
	int lineCount;
};

int main() {
	char processAnother;
	do {
		Book bookInfo;
		string fileName;
		cout << "Enter the name of the file to be processed: ";
		cin >> fileName;

		ifstream inputFile(fileName);

		while (!(inputFile.is_open())) {
			cerr << "Error opening the file. Please enter a valid file name: ";
			cin >> fileName;
			inputFile.open(fileName);
		}

		string line;
		string contents;
		bookInfo.wordCount = 0;
		bookInfo.lineCount = 0;

		// Read title
		getline(inputFile, bookInfo.title);

		// Read author
		getline(inputFile, bookInfo.author);

		// Contents line to be ignored
		getline(inputFile, contents);

		// Count words
		vector<string> words;
		string word;

		while (inputFile >> word) {
			words.push_back(word);
		}

		for (const string& word : words) {
			bookInfo.wordCount++;
		}

		// Count letter frequency
		for (const string& word : words) {
			for (char letter : word) {
				letter = tolower(letter);
				if (isalpha(letter)) {
					bookInfo.letterFrequency[letter]++;
				}
			}
		}

		// Reset line reading back to the beginning for line count
		inputFile.clear();
		inputFile.seekg(0, ios::beg);

		// Line count
		while (getline(inputFile, line)) {
			bookInfo.lineCount++;
		}

		// obtain the last line of the file that doesn't have a new line character at the end
		if (inputFile.eof()) {
			++bookInfo.lineCount;
		}

		// Prepare to write to file since book info has been read in
		ofstream outputFile("CardCatalog.txt", ios::app);

		if (!outputFile.is_open()) {
			cerr << "Error opening CardCatalog.txt for writing." << endl;
			return 1;
		}

		// Once file is opened/created successfully, begin writing book info
		outputFile << "Title: " << bookInfo.title << "\n\n";
		outputFile << "Full Author: " << bookInfo.author << "\n\n";

		// Split the author's full name into first & last
		istringstream authorStream(bookInfo.author);
		string firstName, lastName;
		authorStream >> firstName >> lastName;

		outputFile << "Author First Name: " << firstName << "\n\n";
		outputFile << "Author Last Name: " << lastName << "\n\n";
		outputFile << "Word count: " << bookInfo.wordCount << "\n\n";
		outputFile << "Line count: " << bookInfo.lineCount << "\n\n";

		char showLetterFrequency;
		cout << "Do you want to see the letter frequency for this book? (y/n): ";
		cin >> showLetterFrequency;

		if (showLetterFrequency == 'y' || showLetterFrequency == 'Y') {
			cout << bookInfo.title << " letter frequency:\n";
			for (const auto& entry : bookInfo.letterFrequency) {
				double percentage = (static_cast<double>(entry.second) / bookInfo.wordCount) * 100.0;
				cout << entry.first << ": " << fixed << setprecision(2) << percentage << "%\n";
			}
		}

		cout << "Card catalog information has been saved to CardCatalog.txt.\n";

		inputFile.close();
		outputFile.close();

		cout << "Would you like to process another book? (y/n)\n";
		cin >> processAnother;

	} while (processAnother == 'y' || processAnother == 'Y');

	return 0;
}
