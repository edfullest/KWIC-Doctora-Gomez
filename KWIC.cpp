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

 /**
		 vPrintWithIndex
		 Print a strings array with a 1-based index prefix
	*/
 void vPrintWithIndex(vector<string> vsToPrint) {
		 FOR(i, 0, vsToPrint.size()) {
				 cout << i + 1 << ".- " << vsToPrint[i] << endl;
		 }
 }
 
 /**
		 vRemoveLinesInMenu
		 Reads in GIU all lines to remove
 
		 @return 
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
		 @param vsAnswer Vector to store answer
	*/
 void vMenu(vector<string> vsOriginalLines, vector<string>& vsAnswer) {
		 char cOption;
		 vector<string> vsCurrArr = vsOriginalLines;
		 vector<int> viLinesToRemove;
		 do {
				 cout << "Welcome to the KWIC. This is our menu" << endl;
				 cout << "1. Remove words from input" << endl;
				 cout << "2. Sort ascending" << endl;
				 cout << "3. Sort descending" << endl;
				 cout << "4. Reset input to original file" << endl;
				 cout << "5. Exit" << endl;
 
				 // Validate menu option
				 do {
						 cout << "Please the a valid option number" << endl;
						 cin >> cOption;
				 } while(cOption < '1' || cOption > '5');
				 
				 switch (cOption) {
						 case '1':
								 vPrintWithIndex(vsCurrArr);
								 viLinesToRemove = vRemoveLinesInMenu();
								 // vRemoveLines(vsCurrArr, viLinesToRemove);
								 break;
						 case '2':
						 case '3':
						 		vsAnswer.clear();
								 vProcessWords(vsCurrArr, vsAnswer);
								 if(cOption == '2') {
								     vSort(vsAnswer, ASC);
								 } else {
								     vSort(vsAnswer, DESC);
								 }
								 vPrintWithIndex(vsAnswer);
								 viLinesToRemove = vRemoveLinesInMenu();
								 // vRemoveLines(vAnser, viLinesToRemove);
								 break;
						 case '4':
								 // Reset current array to file from index
								 vsCurrArr = vsOriginalLines;
								 break;
				 }
		 } while (cOption != '5');
 }
 
 int main() {
		 ifstream fileInput("input.txt");
		 ofstream fileOutput("output.txt");
		 vector<string> answer;
		 vector<string> originalLines;
		 
		 string sLine;
		 while(getline(fileInput, sLine)) {
				 originalLines.push_back(sLine);
		 }
		 
		 // vRemoveStopWords
		 vMenu(originalLines, answer);
		 
		 // Outputs solution
		 FOR(i, 0, answer.size()){
				 fileOutput << answer[i] << endl;
		 }
		 
		 fileInput.close();
		 fileOutput.close();
		 return 0;
 }
 
 