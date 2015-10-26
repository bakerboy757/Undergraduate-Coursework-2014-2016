#include "Types.h"

using namespace std;

void countElement(vector<Types>&);
void moveToVector(vector<char> &, vector<Types> &, vector<Types> &);
void moveToCharVector(vector<char>&, vector<Types>&);
void checkMostUsed(vector<Types>&, int&);
void display(vector<Types>&, int);
bool compareCount(const Types&, const Types&);
bool compareChar(const Types&, const Types&);
bool compareCharFirst(const Types&, const Types&);
bool compareLocation(const Types& , const Types& ); 

int main() {
    //stores each indvidiual character of the file
    char ch;
    int mostUsedWords;
    int mostUsedNumbers;
    int mostUsedChars;
    //will be used to hold all the characters in a vector
    vector<char> allCharVector;

    //will hold all string values found in file
    vector<Types> wordVector;
    vector<Types> numberVector;
    vector<Types> charVector;

    //fill vector with chars
    while (cin.get(ch)) {
        allCharVector.push_back(ch);
    }

    //charVector done differently due to charVector needing to consume all of allCharVector
    moveToCharVector(allCharVector, charVector);

    //go through each character and place in appropriate vector
    moveToVector(allCharVector, wordVector, numberVector);

    //sorting before array by overloaded compareLocation, comparing by string value and location to get ordered list for quicker counting
    sort(wordVector.begin(), wordVector.end(), compareLocation);
    sort(numberVector.begin(), numberVector.end(), compareLocation);
    sort(charVector.begin(), charVector.end(), compareLocation);
    
    //sets counter for elements
    countElement(wordVector);
    countElement(numberVector);
    countElement(charVector);

    //delete duplicate strings, count how many unique elements
    wordVector.erase(unique(wordVector.begin(), wordVector.end()), wordVector.end());
    int differentWords = wordVector.size();

    numberVector.erase(unique(numberVector.begin(), numberVector.end()), numberVector.end());
    int differentNumbers = numberVector.size();
    
    charVector.erase(unique(charVector.begin(), charVector.end()), charVector.end());
    int differentChars = charVector.size();
    
    //sorts elements via how many times they occur and if equal, by their location
    sort(wordVector.begin(), wordVector.end(), compareCount);
    sort(numberVector.begin(), numberVector.end(), compareCount);

    //compare char used for comparison of ASCII values
    sort(charVector.begin(), charVector.end(), compareChar);

    //for output purposes, if less than ten elements, then store how many elements there are
    checkMostUsed(wordVector, mostUsedWords);
    checkMostUsed(numberVector, mostUsedNumbers);
    checkMostUsed(charVector, mostUsedChars);

    cout << "Total " << differentChars << " different characters, " << mostUsedChars << " most used characters:" << endl;
    display(charVector, mostUsedChars);

    cout << "Total " << differentWords << " different words, " << mostUsedWords << " most used words:" << endl;
    display(wordVector, mostUsedWords);

    cout << "Total " << differentNumbers << " different numbers, " << mostUsedNumbers << " most used numbers:" << endl;
    display(numberVector, mostUsedNumbers);

}

void countElement(vector<Types> &vectorIn) {
    //make sure there are values to count
    if (vectorIn.size() == 0)
        return;
    unsigned int j = 0;
    for (unsigned int i = 0; i < vectorIn.size(); i=j) {
        int count = 1;
        //vectorIn[i].setLocation(i);
        j = i + 1;
        while (j != vectorIn.size() && vectorIn[i].getStr() == vectorIn[j].getStr()) {
            vectorIn[i].setCounter(++count);
            j++;
        }	
    }
}
void moveToCharVector(vector<char>& allCharVectorIn, vector<Types>& charVectorIn) {
    for (unsigned int i = 0; i < allCharVectorIn.size(); i++) {
        string tempStr = "";
        tempStr = allCharVectorIn[i];
        charVectorIn.push_back(tempStr);
    }
}

void moveToVector(vector<char> &allCharVectorIn, vector<Types> &wordVectorIn, vector<Types> &numberVectorIn){
    //wordPlacement keeps track of the index of the element in the word vector, same for numberPLacement
    int wordPlacement = -1;
    int numberPlacement = -1;
    for (unsigned int i = 0; i < allCharVectorIn.size(); i++) {
        string tempStr;
        //if you find an alpha
        if(isalpha(allCharVectorIn[i]) != 0){
            //then go through next characters from initial location until no longer alpha
            while (i < allCharVectorIn.size() && isalpha(allCharVectorIn[i]) != 0 ) {
                allCharVectorIn[i] = tolower(allCharVectorIn[i]);
                tempStr += allCharVectorIn[i];
                i++;
            }
            wordPlacement++;
            wordVectorIn.push_back(tempStr);
            wordVectorIn[wordPlacement].setLocation(wordPlacement);
            
        }
        tempStr = "";
        //need to check if there is still character to check
        if ( i!= allCharVectorIn.size() && isdigit(allCharVectorIn[i]) != 0) {
            //then go through next characters from initial location until no longer alpha
            while (i < allCharVectorIn.size() && isdigit(allCharVectorIn[i]) != 0 ) {
                tempStr += allCharVectorIn[i];
                i++;
            }
            numberPlacement++;
            numberVectorIn.push_back(tempStr);
            numberVectorIn[numberPlacement].setLocation(numberPlacement);
            //need to subtract one from i to get back to right position after number, 
            //since i++ counts one more than we need at the end
            i--;
        }
    }

}
void checkMostUsed(vector<Types>& vectorIn, int& mostUsed) {
    if (vectorIn.size() <= 10)
        mostUsed = vectorIn.size();
    else
        mostUsed = 10;
}

void display(vector<Types>& vectorIn, int mostUsed) {
    for (int i = 0; i < mostUsed; i++) {
        if (vectorIn[i].getStr() == "\n")
            vectorIn[i].setStr("\\n");
        if (vectorIn[i].getStr() == "\t")
            vectorIn[i].setStr("\\t");
        cout << "No. " << i << ": " << setw(21) << left << vectorIn[i] << vectorIn[i].getCounter() << endl;
    }
    cout << "\n";

}

bool compareCount(const Types& t1, const Types & t2) {
    if (t2.getCounter() == t1.getCounter())
        return t2.getLocation() > t1.getLocation();
    return t2.getCounter() < t1.getCounter();
}

bool compareChar(const Types& t1, const Types& t2) {
    if (t1.getCounter() == t2.getCounter())
        return t1.getStr().at(0) < t2.getStr().at(0);
    return t2.getCounter() < t1.getCounter();
}

bool compareCharFirst(const Types& t1, const Types& t2) {
    return t1.getStr().at(0) < t2.getStr().at(0);

}
bool compareLocation(const Types& t1, const Types& t2) {
    if (t2.getStr() == t1.getStr())
        return t2.getLocation() > t1.getLocation();
    return t2.getStr() < t1.getStr();
}
