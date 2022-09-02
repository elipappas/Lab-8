
//Caesar code



// A   B   C   D   E   F   G  H  I  J  K L M  N  O  P  Q  R  S  T  U  V  W   X  Y  Z

//65  66                                                                           90 (Ascii code)

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

//The following function is used to encode a char by shifting RIGHT (shift positive) as a parameter
//lower case must be converted to upper case for shifting and then convert back to lower case

char rotateChar (char in_char, int shift){
   if (!isalpha (in_char)) return in_char;
   bool lower_flag = false;
   if (islower (in_char)) {
      in_char = toupper (in_char);
      lower_flag = true;
   }
   //cout << "Test before offer inside rotation " << in_char << endl;
   
   in_char = in_char + shift;
   if (in_char < 'A') {
      int num = 26 + shift;
      in_char = 'A' + num;
      cout << "Answer 1 " << in_char;
   }
   if (in_char > 'Z'){
      in_char = 'A' + (in_char - 'A') % 26;
      // in_char = in_char - 'Z' + 'A' - 1; (either this one or above will work)
      cout << "Answer 1 " << in_char;
   }
   
   


    if (lower_flag)
        in_char = tolower (in_char);

    return in_char;

}

//Given a line of string and cipher_key, encopher the string to another string NOT readable

string codeWordGen(string cipher_key){
   string codeWord = "";
   int offset = 0;
   for(int i = 0; i < cipher_key.length(); i++){
      if (!isalpha (cipher_key[i])) {
         return codeWord;
      }
      offset = offset + cipher_key[i];
   }
   
   int numShift = (offset%23)+3;  // calculates the shift
   int numSwap = (numShift%9)+2; // uses shift to calculate number of swaps
   
   for(int i = 0; i < 26; ++i){
      codeWord = codeWord + rotateChar(65+i, numShift); // shifts each letter in the code word
   }
   
   int newNum = 26/(2*numSwap);
   int i = 0;
   
   for(int j = 0; j < numSwap; j++, i = i + newNum){
      char temp = codeWord[i]; 
      codeWord[i] = codeWord[25-i];
      codeWord[25-i] = temp;
   }
   return codeWord;
}



char encodeChar(char in_char, string codeWord)
{
   int temp;
   char cipher;
   bool lower_flag = false;
   if (islower (in_char)) {
      temp = 1;  // used to store whether letter was originally lowercase
   }
   if (islower (in_char)) {
      in_char = toupper (in_char);
      lower_flag = true;
   }
   if (!isalpha (in_char)) return in_char;
   cipher = codeWord[in_char-65];
   if (temp == 1) {
      cipher = tolower(cipher); // checks if it was originally lowercase and will reconvert back to lowercase
   }
   return cipher;
   
}


string caesarString (string caesar_string, string cipher_key){
    if (caesar_string.length() == 0) return caesar_string;

    
    //computer offset (i.e., shift) using cipher_key as a parameter
    int offset = 0;
    for (int i = 0; i < cipher_key.length(); i++){
        offset = offset + cipher_key [i];
    }
    offset = (offset % 23) + 3;
    cout << "The shift is " << offset << endl;


    /*pass each char in the caesar string to rotateChar() for enciphering
    for (int i = 0; i < caesar_string.length(); i++){
        //cout << "Test with the caesarString for loop \n";
        caesar_string [i] = rotateChar (caesar_string [i], offset);
    } */
    
    for(int i = 0; i < caesar_string.length(); i++){
      int temp;
      bool lower_flag = false;
      if (islower (caesar_string[i])) {
       temp = 1;
      }
      if (islower (caesar_string[i])) {
         caesar_string[i] = toupper (caesar_string[i]); 
         lower_flag = true;
      }
      if(caesar_string[i] == ' '){ // checks if there is a space
         caesar_string[i] = caesar_string[i];
      }
      else {
         caesar_string[i] = cipher_key[toupper(caesar_string[i])-65]; // converts each letter
      }
      if (temp == 1) {
         caesar_string[i] = tolower(caesar_string[i]); // converts back to lower if it was originally
      }
      temp = 0;
    }
    cout << caesar_string;
    return caesar_string;
}


//Given 

int encrypt (string in_file, string out_file, string cipher_key){
    ifstream inputFile;
    ofstream outputFile;
    string inputString;

    inputFile.open (in_file.c_str());
    outputFile.open (out_file.c_str());
   int x = -1; // for if the file can't be read
    if (!inputFile) {
        cout << "input file cannot be opened \n";
        return x;
    }

    if (!outputFile){
        cout << "output file cannot be opened \n";
        return x;
    }
    //cout << "Get into while loop of Encrypt" << endl;


    //Read a line from the input file, call CaesarString to encipher the line of string
    while (getline(inputFile,  inputString)){
        outputFile << caesarString (inputString, cipher_key) << endl;
        //cout << "Test at encrypt while loop " << inputString << endl;
    }

    inputFile.close();
    outputFile.close();
    x = 29;
    return x;

}

int main(){
    int Text;
    string smallFile = "C:\\Users\\Jone PC\\Documents\\Jone-Courses-UC\\CS121\\2019_before\\2019\\Labs\\01-Qt\\Lab1\\small-file.txt";
    string largeFile = "C:\\Users\\Jone PC\\Documents\\Jone-Courses-UC\\CS121\\2019_before\\2019\\Labs\\01-Qt\\Lab1\\large-file.txt";
    string out_file = "C:\\Users\\Jone PC\\Documents\\Jone-Courses-UC\\CS121\\2019_before\\2019\\Labs\\01-Qt\\Lab1\\caesar-out-file.txt";

    cout << "Which text do you want to read? \n 1. for short \n 2. for long \n";
    cin >> Text;
    if (Text == 1)
       encrypt (smallFile, out_file, "toobusy"); else
       encrypt (largeFile, out_file, "toobusy");

}