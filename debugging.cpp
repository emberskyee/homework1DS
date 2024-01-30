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

Book readBook(ifstream& inputFile) {
	Book currentBook;
	string line;
	string contents;
	currentBook.wordCount = 0;
	currentBook.lineCount = 0;

	inputFile.open("MobyDick.txt");

	if (!(inputFile.is_open())) {
		cout << "File is not open!" << endl;
		return currentBook;
	}

	// Read title
	getline(inputFile, currentBook.title);

	// Read author
	getline(inputFile, currentBook.author);

	// Contents line
	getline(inputFile, contents);

	// Count words
	vector<string> words;
	string word;

	while (inputFile >> word) {
		words.push_back(word);
	}

	for (const string& word : words) {
		currentBook.wordCount++;
	}

	// Count letter frequency
	char letter;
	currentBook.letterFrequency[letter] = 0;

	for (const string& word : words) {
		for (char letter : word) {
			letter = tolower(letter);
			if (isalpha(letter)) {
				currentBook.letterFrequency[letter]++;
			}
		}
	}

	// Line count
	while (getline(inputFile, line)) {
		currentBook.lineCount++;
	}

	return currentBook;
}
////

int main() {
	ifstream file;
	//file.open("MobyDick.txt");

	Book MobyDick = readBook(file);

	cout << MobyDick.title << endl << MobyDick.author << endl << MobyDick.wordCount << endl << MobyDick.lineCount << endl;
	for (const auto& pair : MobyDick.letterFrequency) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}

	file.close();

	return 0;
}