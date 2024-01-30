// Homework1Files.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
/////

Book readBook(ifstream& fileName) {
	Book book;
	string line;
	ifstream inputFile("fileName");

	if (!inputFile.is_open()) {
		cout << "File is not open!" << endl;
		return;
	}

	// Read title
	getline(inputFile, book.title);

	// Read author
	getline(inputFile, book.author);

	// Count words
	vector<string> words;
	string word;

	while (inputFile >> word) {
		words.push_back(word);
	}

	for (const string& word : words) {
		book.wordCount++;
	}

	// Count letter frequency
	char letter;
	for (const string& word : words) {
		for (char letter : word) {
			letter = tolower(letter);
			if (isalpha(letter)) {
				book.letterFrequency[letter]++;
			}
		}
	}

	// Line count
	int lineCount = 0;
	while (getline(inputFile, line)) {
		book.lineCount++;
	}

	// Close file after reading is done
	inputFile.close();

	return book;
}
////


// write book info
void writeToFile(const Book& book, std::ofstream& outputFile) {
	outputFile << "Title: " << book.title << "\n";
	outputFile << "Full Author: " << book.author << "\n";
	std::istringstream authorStream(book.author);
	std::string firstName, lastName;
	authorStream >> firstName >> lastName;
	outputFile << "Author First Name: " << firstName << "\n";
	outputFile << "Author Last Name: " << lastName << "\n";
	outputFile << "Word count: " << book.wordCount << "\n";
	char showLetterFrequency;
	cout << "Do you want to see the letter frequency for this book? (y/n): ";
	cin >> showLetterFrequency;
	if (showLetterFrequency == 'y' || showLetterFrequency == 'Y') {
		outputFile << "Letter frequency:\n";
		for (const auto& entry : book.letterFrequency) {
			double percentage = static_cast<double>(entry.second) / book.wordCount * 100.0;
			outputFile << entry.first << ": " << std::fixed << std::setprecision(2) << percentage << "%\n";
		}
	}

	outputFile << "Line count: " << book.lineCount << "\n";
	outputFile << "\n";

	std::ofstream outFile("CardCatlog.txt", std::ios::app);
	if (!outFile.is_open()) {
		std::cerr << "Error opening output file." << std::endl;
		return;
	}
	// write book info to file 
	outFile << "Title: " << book.title << endl;
}

int main() {
	string fileName;
	cout << "Enter the name of the file to be processed: ";
	cin >> fileName;

	ifstream inputFile("fileName");

	while (!(inputFile.is_open())) {
		cerr << "Error opening the file. Please enter another file name: ";
		cin >> fileName;
		inputFile.open(fileName);
	}
	ofstream outputFile("CardCatalog.txt", ios::app);

	if (!outputFile.is_open()) {
		cerr << "Error opening CardCatalog.txt for writing." << endl;
		return 1;
	}

	while (inputFile.peek() != EOF) {
		Book book = readBook(inputFile);
		writeToFile(book, outputFile);
	}

	std::cout << "Card catalog information has been saved to CardCatalog.txt.\n";

	inputFile.close();
	outputFile.close();

	return 0;
}			
	