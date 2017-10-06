/**
	KWIC.cpp

	Elias Mera	A01280762
	Gala Islas		A00817135
	María Paula Anastas 	A00817285
	Fabián Montemayor 	A01280156
*/

#include <bits/stdc++.h>
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
using namespace std;

enum SortOrder{
	ASC,
	DESC
};

/**
	sProcessLine
	Method called every time the program finds new line in the input
	if there is a period '.' ignores it
	converts all letters tolower case to match output in example

	@param sLine line that is found on the input file
	@return sNewLine new line processed for the algorithm
*/
std::string sProcessLine(string& sLine){
	string sNewLine = "";

	FOR(i, 0, sLine.length()){
		if(sLine[i] == '.') continue;
		sNewLine += tolower(sLine[i]);
	}

	return sNewLine;
}

/**
	vsBreakLie
	Method that breaks a line of words to a vector of their words
	ex. hello world returns {hello, world}

	@param sLine line to break
	@return vector of words
*/
vector<string> vsBreakALine(string sLine){
	stringstream ssBreaks(sLine);
	string sWord;
	vector<string> vsWords;
	while(ssBreaks >> sWord){
		vsWords.push_back(sWord);
	}
	return vsWords;
}

/**
	vGenerateAnswer
	Method that generates all permutations of the vector of words

	@param vsWords vector of words of a line
	@param answer passed by reference, every time a new permutation is generated it pushes to the answer vector
*/
void vGenerateAnswer(vector<string> vsWords, vector<string>& answer){
	int iSize = vsWords.size();	
	// counts in a circular way
	FOR(i, 0, iSize){
		string sLine = "";
		FOR(j, i, i + iSize){
			sLine += vsWords[j % iSize] + " ";
		}
		answer.push_back(sLine);
	}
}
/** 
	 vSort 
 	Method that sorts depending on the specification. It can be descending or ascending order.
 	It's important to note that the sorting is done in place, due to the passing by reference

	@param vsWords passed by reference, vector of words of a line
*/

void vSort(vector<string> &vsWords, SortOrder soOrder){
	if (soOrder == ASC){
		sort(vsWords.begin(), vsWords.end(), less<string>());
	}
	else{
		sort(vsWords.begin(), vsWords.end(), greater<string>());
	}
}

/**


	vProcessWords
	Method that generates the permutations from a list of words
	

	@param vsWords passed by reference, the vector of words that will be permuted
	@param vsPermutations passed by reference, the vector with the permutations
*/
void vProcessWords(vector<string> &vsWords, vector<string> &vsPermutations){
	FOR(i, 0, vsWords.size()){
		string sNewLine = sProcessLine(vsWords[i]);
		vector<string> vsBrokenWords = vsBreakALine(sNewLine);
		vGenerateAnswer(vsBrokenWords, vsPermutations);
	}
}

int main() {
	ifstream fileInput("input.txt");
	ofstream fileOutput("output.txt");
	vector<string> input;
	vector<string> answer;

 	string sLine;
	while(getline(fileInput, sLine)){
		input.push_back(sLine);
	};

	vProcessWords(input, answer);
	vSort(answer, ASC);

	// Outputs solution
	FOR(i, 0, answer.size()){
		fileOutput << answer[i] << endl;
		cout << answer[i] << endl;
	}

	fileInput.close();
	fileOutput.close();
    return 0;
}
