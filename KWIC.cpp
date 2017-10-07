/**
 KWIC.cpp
 
	Elias Mera	A01280762
	Gala Islas		A00817135
	María Paula Anastas 	A00817285
	Fabián Montemayor 	A01280156
 */

 #include <bits/stdc++.h>
 #define CARRIAGE_RETURN char(13)
 #define FOR(i, a, b) for(int i=int(a); i<int(b); i++)



 using namespace std;
 
 /** SortOrder
 
  This enum is used by the sorting functionality to sort depending on the
  specification. ASC for ascending sort order, and DESC for descending sort order.

 **/
 enum SortOrder{
		 ASC,
		 DESC
 };
 
/** vReadFromFile
 	Method that recieves file name and destination vector to store all lines 
 	Removes the Carrage-Return character at the end of all the lines and then the lines are pushed
  .
	@param sFileName Recieves the name of the file to open
	@param vsLines String vector that stores the lines of the file
 **/ 
void vReadFromFile(string sFileName, vector<string> &vsLines){
	ifstream file(sFileName);
	string sLine;
	string sNewLine;
	while(getline(file, sLine, CARRIAGE_RETURN)) {
		std::stringstream ssStream(sLine);
		ssStream >> ws; // Eliminates white spaces at the end of the string
		getline(ssStream,sNewLine); // The new line will have the filtered string without carriage returns/white spaces at the end
		vsLines.push_back(sNewLine);
	}
	file.close();
}

/** sProcessLine
	
	Method called to save in a file the conents of a vector
	
	@@param sFileName Recieves the name of the file to open to write
	@param vsAnswer String vector provides the lines to be written
*/
void vSaveToFile(string sFileName, vector<string> &vsAnswer){
	ofstream fileOutput(sFileName);
	// Outputs solution
	 FOR(i, 0, vsAnswer.size()){
			 fileOutput << vsAnswer[i] << endl;
	 }
	 fileOutput.close();
}

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
		 vPrintWithIndex
		 Print a strings array with a 1-based index prefix
	*/
 void vPrintWithIndex(vector<string> &vsToPrint) {
		 FOR(i, 0, vsToPrint.size()) {
				 cout << i + 1 << ".- " << vsToPrint[i] << endl;
		 }
 }

 /** 
	 vSort 
 	Method that sorts depending on the specification. It can be descending or ascending order.
 	It's important to note that the sorting is done in place, due to the passing by reference

	@param vsWords passed by reference, vector with the lines
*/

void vSort(vector<string> &vsWords, SortOrder soOrder){
	if (soOrder == ASC){
		sort(vsWords.begin(), vsWords.end(), less<string>());
	}
	else{
		sort(vsWords.begin(), vsWords.end(), greater<string>());
	}
}

/** vRemoveBreakWords
	  
 	Method that recieves a vector of Words and filters the BreakWords(stopWords) of a vector 
	
	@param vsWords passed by reference, vector of words of a line to filter
	@param vsBreakWords vector passed by reference to get all the stop words to be removed
*/
void vRemoveBreakWords(vector<string> &vsWords, vector<string> &vsBreakWords){
	vector<string> *vsFilteredWords = new vector<string>();
	bool bIsWordABreakWord = false;
	FOR(i, 0, vsWords.size()){

		FOR(j, 0, vsBreakWords.size()){
			bIsWordABreakWord = vsWords[i] == vsBreakWords[j];
			if (bIsWordABreakWord){
				break;
			}
		}

		if (!bIsWordABreakWord){
			vsFilteredWords -> push_back(vsWords[i]);
		}
	}

	vsWords.swap(*vsFilteredWords);
	delete vsFilteredWords;
}

/**
	vProcessWords
	Method that 
	1. Processes the lines to make them lower case
	2. Breaks the line into vector of single words
	3. Removes the stop words from each line
	4. Generates the permutation

	@param vsWords passed by reference, the vector of words that will be permuted
	@param vsPermutations passed by reference, the vector with the permutations
	@param vsStopWords passed by reference, the vector with the stop words
*/

 void vProcessWords(vector<string> &vsWords, vector<string> &vsPermutations,
				   vector<string> &vsStopWords){
	FOR(i, 0, vsWords.size()){
		string sNewLine = sProcessLine(vsWords[i]);
		vector<string> vsBrokenWords = vsBreakALine(sNewLine);

		vRemoveBreakWords(vsBrokenWords, vsStopWords);
		vGenerateAnswer(vsBrokenWords, vsPermutations);
	}
}

/** vRemoveLines
	  
 	Method recives a Words vector, to filter and remove the lines of the indexes from 
 	the LinesToRemove vector
	
	@param vsWords passed by reference, vector of words of a line to filter
	@param viLinesToRemove indexes of the lines to delete
*/
void vRemoveLines(vector<string> &vsWords, vector<int> &viLinesToRemove){
	if (viLinesToRemove.empty()){
		return;
	}
	else{
		vector<string> *vsFilteredLines = new vector<string>();
		sort(viLinesToRemove.begin(), viLinesToRemove.end());
		vector<int>::iterator itNextToRemove = viLinesToRemove.begin();
		FOR(i, 0, vsWords.size()){
			if (i == *itNextToRemove){
				++itNextToRemove;
			}
			else{
				vsFilteredLines -> push_back(vsWords[i]);
			}
		}
		vsWords.swap(*vsFilteredLines);
		vPrintWithIndex(vsWords);
		delete vsFilteredLines;
	}	
}

 
 /**
		 vRemoveLinesInMenu
		 Reads in GUI the indexes from the lines to remove
 
		 @return int Vector of the indexes to be removed
 */
 vector<int> vRemoveLinesInMenu() {
		 cout << "Which lines do you want to remove?" << endl;
		 cout << "Enter the lines separated by spaces. When ready, enter '-1'" << endl;
		 vector<int> viLinesToRemove;
		 do {
				 int toRemove;
				 cin >> toRemove;
				 if(toRemove == -1) {
					 break;
				 }
				 viLinesToRemove.push_back(toRemove - 1);
		 } while(true);
 
		 return viLinesToRemove;
 }
 


 /**
		 vMenu
		 Method to print the initial menu
		 
		 @param vsOriginalLines Vector of original sentences from file
		 @param vsStopWords vector passed by reference of stop words
		 @param vsAnswer vector passed by reference to store answer
	*/
 void vMenu(vector<string> vsOriginalLines, vector<string> &vsStopWords ,vector<string>& vsAnswer) {
		 char cOption;
		 vector<string> vsCurrArr = vsOriginalLines;
		 vector<int> viLinesToRemove;
		 do {
				 cout << "Welcome to the KWIC. This is our menu" << endl;
				 cout << "1. Remove lines from input" << endl;
				 cout << "2. Sort ascending" << endl;
				 cout << "3. Sort descending" << endl;
				 cout << "4. Reset input to original file" << endl;
				 cout << "5. Exit" << endl;
 
				 // Validate menu option
				 do {
						 cout << "Please enter a valid option number" << endl;
						 cin >> cOption;
				 } while(cOption < '1' || cOption > '5');
				 
				 switch (cOption) {
						 case '1':
								 vPrintWithIndex(vsCurrArr);
								 viLinesToRemove = vRemoveLinesInMenu();
								 vRemoveLines(vsCurrArr, viLinesToRemove);
								 break;
						 case '2':
						 case '3':
						 		vsAnswer.clear();
								 vProcessWords(vsCurrArr, vsAnswer, vsStopWords);
								 if(cOption == '2') {
								     vSort(vsAnswer, ASC);
								 } else {
								     vSort(vsAnswer, DESC);
								 }
								 vPrintWithIndex(vsAnswer);
								 // We ask if the user wants to remove a line from the output
								 viLinesToRemove = vRemoveLinesInMenu();
								 vRemoveLines(vsAnswer, viLinesToRemove);
								 cout << "<<<< These will be saved to output.txt. Please wait <<<<" << std::endl;
								 vSaveToFile("output.txt", vsAnswer);
								 cout << ">>>> These lines were saved to output.txt >>>>" << endl;
								 break;
						 case '4':
								 // Reset current array to file from index
								 vsCurrArr = vsOriginalLines;
								 break;
				 }
		 } while (cOption != '5');
 }

 
 int main() {
		 vector<string> vsAnswer;
		 vector<string> vsOriginalLines;
		 vector<string> vsStopWords;
		 vReadFromFile("stopwords.txt", vsStopWords);
		 vReadFromFile("input.txt", vsOriginalLines);
		 vMenu(vsOriginalLines,vsStopWords,vsAnswer);
		 return 0;
 }
 
 