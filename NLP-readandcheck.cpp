// NLP-readandcheck.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool dictionaryCheck(string word) {

	transform(word.begin(), word.end(), word.begin(), ::tolower);
	bool found = false;
	ifstream nouns;
	ifstream verbs;
	ifstream adjectives;
	size_t pos;
	string line;

	nouns.open("nouns.txt");
	verbs.open("verbs.txt");
	adjectives.open("adjectives.txt");

	if (!nouns)
		cout << "Unable to open nouns.txt\n";
	if (!verbs)
		cout << "Unable to open verbs.txt\n";
	if (!adjectives)
		cout << "Unable to open adjectives.txt\n";

	while (nouns.good())
	{
		getline(nouns, line); // get line from file
		pos = line.compare(word); // search
		if (pos == 0) // compare returns 0 if they match
		{
			cout << ": found in noun dictionary\n";
			found = true;
		}
	}

	while (verbs.good())
	{
		getline(verbs, line);
		pos = line.compare(word);
		if (pos == 0)
		{
			cout << ": found in verb dictionary\n";
			found = true;
		}
	}

	while (adjectives.good())
	{
		getline(adjectives, line);
		pos = line.compare(word);
		if (pos == 0)
		{
			cout << ": found in adjectives dictionary\n";
			found = true;
		}
	}

	return found;
}

void readSentence() {

	ifstream sentences;

	string delimiter = " ";
	string token;
	string s;
	string line;
	string strArray[1000];

	size_t pos = 0;

	int index = 0;
	int sentencenum = 0;
	int readpoint = 0;

	sentences.open("sentences.txt");
	if (!sentences)
		cout << "Unable to open sentences.txt\n";

	while (getline(sentences, line)) {
		sentencenum++;
		s = s + line;
		readpoint = index;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			strArray[index] = token; // put single word into an array element
			index++;
			s.erase(0, pos + delimiter.length());
		}
		strArray[index] = s; //final word
		s.erase();

		cout << "Sentence " << sentencenum << ":\n";

		for (int i = readpoint; i <= index; i++) {
			cout << "word: " << strArray[i]; //output each word
			if (!dictionaryCheck(strArray[i]))
				cout << ": not found\n";
		}
	}
	

	return;
}
int _tmain(int argc, _TCHAR* argv[])
{
	readSentence();
	return 0;
}

