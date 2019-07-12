//
//  main.cpp
//  Project 5
//
//  Created by Henry Macarthur on 11/7/18.
//  Copyright © 2018 Henry Macarthur. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_DOCUMENT_LENGTH = 250;
const int MAX_WORD_LENGTH = 20;
int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns);
int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns);
using namespace std;

int d[3] =                      {    1,    0,    2 };
char w1[3][MAX_WORD_LENGTH+1] = { "aa", "bb", "cc" };
char w2[3][MAX_WORD_LENGTH+1] = { "dd", "ee", "ff" };

int e[2] =                      {    3,    3 };
char x1[2][MAX_WORD_LENGTH+1] = { "aa", "cc" };
char x2[2][MAX_WORD_LENGTH+1] = { "bb", "dd" };

const int THREE_LETTERS = 26*26*26;
int dd[THREE_LETTERS];
char ww1[THREE_LETTERS][MAX_WORD_LENGTH+1];
char ww2[THREE_LETTERS][MAX_WORD_LENGTH+1];

bool eq(int c, int dist, const char wd1[], const char wd2[])
{
    return d[c] == dist  &&  strcmp(w1[c], wd1) == 0  &&
    strcmp(w2[c], wd2) == 0;
}

void testone(int n)
{
    switch (n)
    {
        case  1: {
            assert(makeProper(w1, w2, d, 0) == 0);
        } break; case  2: {
            assert(makeProper(w1, w2, d, 1) == 1  &&
                   eq(0, 1, "aa", "dd"));
        } break; case  3: {
            d[0] = -1;
            assert(makeProper(w1, w2, d, 1) == 0);
        } break; case  4: {
            d[0] = -1;
            assert(makeProper(w1, w2, d, 2) == 1  &&
                   eq(0, 0, "bb", "ee"));
        } break; case  5: {
            d[1] = -1;
            assert(makeProper(w1, w2, d, 2) == 1  &&
                   eq(0, 1, "aa", "dd"));
        } break; case  6: {
            d[1] = -1;
            d[2] = -1;
            assert(makeProper(w1, w2, d, 3) == 1  &&
                   eq(0, 1, "aa", "dd"));
        } break; case  7: {
            d[0] = -1;
            d[1] = -1;
            assert(makeProper(w1, w2, d, 3) == 1  &&
                   eq(0, 2, "cc", "ff"));
        } break; case  8: {
            d[0] = -1;
            d[1] = -1;
            d[2] = -1;
            assert(makeProper(w1, w2, d, 3) == 0);
        } break; case  9: {
            strcpy(w1[1], "");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                    )
                   );
        } break; case 10: {
            strcpy(w2[1], "");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                    )
                   );
        } break; case 11: {
            strcpy(w1[1], "bb@");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                    )
                   );
        } break; case 12: {
            strcpy(w1[1], "bb ");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                    )
                   );
        } break; case 13: {
            strcpy(w1[1], "bBBb");
            assert(makeProper(w1, w2, d, 2) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 0, "bbbb", "ee"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 0, "bbbb", "ee"))
                    )
                   );
        } break; case 14: {
            strcpy(w1[1], "bBBb");
            strcpy(w2[1], "EeEeE");
            assert(makeProper(w1, w2, d, 2) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 0, "bbbb", "eeeee"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 0, "bbbb", "eeeee"))
                    )
                   );
        } break; case 15: {
            strcpy(w2[1], "bb");
            assert(makeProper(w1, w2, d, 2) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 0, "bb", "bb"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 0, "bb", "bb"))
                    )
                   );
        } break; case 16: {
            strcpy(w2[0], "aa");
            strcpy(w1[1], "aa");
            strcpy(w2[1], "aa");
            assert(makeProper(w1, w2, d, 2) == 1  &&
                   eq(0, 1, "aa", "aa")
                   );
        } break; case 17: {
            strcpy(w1[1], "aa");
            strcpy(w2[1], "dd");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                    )
                   );
        } break; case 18: {
            strcpy(w1[1], "aa");
            strcpy(w2[1], "dd");
            d[1] = 1;
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                    )
                   );
        } break; case 19: {
            strcpy(w1[1], "aa");
            strcpy(w2[1], "dd");
            d[1] = 4;
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 4, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 4, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                    )
                   );
        } break; case 20: {
            strcpy(w1[1], "aa");
            strcpy(w2[1], "dd");
            strcpy(w1[2], "aa");
            strcpy(w2[2], "dd");
            
        } break; case 21: {
            strcpy(w1[2], "aa");
            strcpy(w2[2], "dd");
            d[1] = -1;
            assert(makeProper(w1, w2, d, 3) == 1  &&
                   eq(0, 2, "aa", "dd")
                   );
        } break; case 22: {
            strcpy(w1[1], "abcdefghijklmnopqrst");
            strcpy(w2[1], "abcdefghijklmnopqrsu");
            d[0] = -1;
            assert(makeProper(w1, w2, d, 2) == 1  &&
                   eq(0, 0, "abcdefghijklmnopqrst",
                      "abcdefghijklmnopqrsu")
                   );
        } break; case 23: {
            strcpy(w2[0], "DD");
            strcpy(w1[1], "AA");
            strcpy(w2[1], "dD");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                    )
                   );
        } break; case 24: {
            strcpy(w1[1], "dd");
            strcpy(w2[1], "aa");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                    )
                   );
        } break; case 25: {
            strcpy(w1[1], "dd");
            strcpy(w2[1], "aa");
            d[1] = 1;
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   (((eq(0, 1, "aa", "dd")  ||  eq(0, 1, "dd", "aa")
                      )  &&  eq(1, 2, "cc", "ff")
                     )  ||
                    ((eq(1, 1, "aa", "dd")  ||  eq(1, 1, "dd", "aa")
                      )  &&  eq(0, 2, "cc", "ff")
                     )
                    )
                   );
        } break; case 26: {
            strcpy(w1[1], "Dd");
            strcpy(w2[1], "aA");
            assert(makeProper(w1, w2, d, 3) == 2  &&
                   ((eq(0, 1, "aa", "dd")  &&  eq(1, 2, "cc", "ff"))  ||
                    (eq(1, 1, "aa", "dd")  &&  eq(0, 2, "cc", "ff"))
                    )
                   );
        } break; case 27: {
            int dx[7] = { 1, 3, 0, 2, 1, 0, 12 };
            char w1x[7][MAX_WORD_LENGTH+1] = { "mad", "deranged",
                "NEFARIOUS", "half-witted", "robot", "plot", "have" };
            char w2x[7][MAX_WORD_LENGTH+1] = { "scientist", "robot",
                "PLOT", "assistant", "deranged", "Nefarious", "mad" };
            assert(makeProper(w1x, w2x, dx, 7) == 4);
        } break; case 28: {
            assert(rate("", x1, x2, e, 2) == 0);
        } break; case 29: {
            assert(rate(" ", x1, x2, e, 2) == 0);
        } break; case 30: {
            assert(rate("aa bb", x1, x2, e, 2) == 1);
        } break; case 31: {
            e[0] = 0;
            assert(rate("aa bb", x1, x2, e, 2) == 1);
        } break; case 32: {
            e[0] = 0;
            assert(rate("aa     bb", x1, x2, e, 2) == 1);
        } break; case 33: {
            assert(rate(" aa bb", x1, x2, e, 2) == 1);
        } break; case 34: {
            assert(rate("aa bb ", x1, x2, e, 2) == 1);
        } break; case 35: {
            assert(rate("aa bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 36: {
            assert(rate("aa bb cc dd xx", x1, x2, e, 1) == 1);
        } break; case 37: {
            assert(rate("aa xx cc bb xx dd xx", x1, x2, e, 2) == 2);
        } break; case 38: {
            assert(rate("xx dd bb cc aa xx", x1, x2, e, 2) == 2);
        } break; case 39: {
            assert(rate("aa xx xx xx bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 40: {
            assert(rate("aa xx xx xx xx bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 41: {
            e[0] = 0;
            e[1] = 0;
            assert(rate("aa xx bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 42: {
            e[0] = 1;
            e[1] = 1;
            assert(rate("aa cc bb dd xx", x1, x2, e, 2) == 2);
        } break; case 43: {
            assert(rate("aa bb aa bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 44: {
            assert(rate("aa aa bb bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 45: {
            strcpy(x2[0], "aa");
            assert(rate("aa xx xx aa", x1, x2, e, 2) == 1);
        } break; case 46: {
            strcpy(x2[0], "aa");
            assert(rate("xx aa xx", x1, x2, e, 2) == 0);
        } break; case 47: {
            assert(rate("aA bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 48: {
            assert(rate("aa @@ ## $$ %% ^^ bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 49: {
            assert(rate("aa b@@b cc dd xx", x1, x2, e, 2) == 2);
        } break; case 50: {
            assert(rate("aa b123456789012345678901234567890b cc dd xx", x1, x2, e, 2) == 2);
        } break; case 51: {
            e[0] = 0;
            assert(rate("aa abcdefghijklmnopqrstuvwxyz bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 52: {
            e[0] = 1;
            assert(rate("aa abcdefghijklmnopqrstuvwxyz bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 53: {
            strcpy(x1[0], "abcdefghijklmnopqrst");
            assert(rate("abcdefghijklmnopqrst bb cc dd xx", x1, x2, e, 2) == 2);
        } break; case 54: {
            strcpy(x1[0], "abcdefghijklmnopqrst");
            assert(rate("abcdefghijklmnopqrstu bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 55: {
            assert(rate("aaa bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 56: {
            assert(rate("aa@bb cc dd xx", x1, x2, e, 2) == 1);
        } break; case 57: {
            assert(rate("aa bb@cc dd xx", x1, x2, e, 2) == 0);
        } break; case 58: {
            e[0] = 1000;
            assert(rate("xx aa xx", x1, x2, e, 2) == 0);
        } break; case 59: {
            strcpy(x1[0], "a");
            strcpy(x2[0], "b");
            e[0] = 123;
            char doc[250+1];
            strcpy(doc, "a ");
            for (int k = 0; k < 123; k++)
                strcpy(doc+2+2*k, "x ");
            strcpy(doc+248, "b ");
            
           
            assert(rate(doc, x1, x2, e, 2) == 1);
        } break; case 60: {
            for (int k = 0; k < THREE_LETTERS; k++)
            {
                dd[k] = (k % 2) - 1;
                strcpy(ww1[k], "a");
                strcpy(ww2[k], "aaa");
                int kk = k;
                ww2[k][2] += kk % 26;
                kk /= 26;
                ww2[k][1] += kk % 26;
                kk /= 26;
                ww2[k][0] += kk;
            }
            assert(makeProper(ww1, ww2, dd, THREE_LETTERS) == THREE_LETTERS / 2);
            for (int k = 0; k < THREE_LETTERS / 2; k++)
                assert(dd[k] == 0 && strcmp(ww1[k], "a") == 0 &&
                       islower(ww2[k][2]) &&
                       (ww2[k][2] - 'a') % 2 == 1);
        } break; case 61: {
            for (int k = 0; k < THREE_LETTERS; k++)
            {
                dd[k] = 0;
                strcpy(ww1[k], "a");
                strcpy(ww2[k], "aaa");
                int kk = k;
                ww2[k][2] += kk % 26;
                kk /= 26;
                ww2[k][1] += kk % 26;
                kk /= 26;
                ww2[k][0] += kk;
            }
            assert(rate("a aaa a iaa a pzz a zzz", ww1, ww2, dd, THREE_LETTERS) == 4);
            assert(rate("a aaaa a iaaa a pzzz a zzzz", ww1, ww2, dd, THREE_LETTERS) == 0);
        } break;
    }
}

int main()
{
    cout << "Enter a test number (1 to 61): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 61)
    {
        cout << "Bad test number" << endl;
        return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
}



bool checkString(char s[]) {
    if(s[0] == '\0')
        return false;
    for(int i = 0; s[i] != '\0'; i++) { //loop through the array till we find nullbyte
        if(!isalpha(s[i])){
            return false; //return false if we find a non-alpha character
        }
    }
    return true; //return true if everything is ok
}

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns) {
    if(nPatterns <= 0) {
        return 0; //if nPatterns is less than 0, so improper, we return 0 right away
    }
    for(int i = 0; i < nPatterns; i++) {
        for(int k = 0; word1[i][k] != '\0'; k++) {
            word1[i][k] = tolower(word1[i][k]);
        }
        for(int j = 0; word2[i][j] != '\0'; j++) {
            word2[i][j] = tolower(word2[i][j]);
        }
        
    }
   
    int length = nPatterns;
    for(int i = 0; i < length; i++) { //loop though the length of the word arrays
        if(i < 0) //make sure i doesn't go below zero
            i = 0;
        
        if(checkString(word1[i]) && checkString(word2[i]) && separation[i] >= 0) { //proper form is a word with a proper sepparation
            for(int j = i+1; j < length; j++) { //start at i+1 and go to the end of the array
                if((strcmp(word1[i],word1[j]) == 0 && strcmp(word2[i],word2[j]) == 0)
                   ||(strcmp(word1[i],word2[j]) == 0 && strcmp(word2[i],word1[j]) == 0)) { //check to see if we have any matching word cases
                    length -= 1; //decrement length  because we know one of the word cases needs to be removed
                    if(separation[i] < separation[j]) { //find which one has the bigger length
                        strcpy(word1[i], word1[j]);
                        strcpy(word2[i], word2[j]); //copy words
                        int temp = separation[i];
                        separation[i] = separation[j]; //copy sepparation value
                        separation[j] = temp;
                    }
                    for(int k = j; k < nPatterns - 1; k ++) { //loop through the rest of the array
                        strcpy(word1[k], word1[k+1]); //shift everything to the left so it seems as if we are removing the improper element
                        strcpy(word2[k], word2[k+1]);
                        separation[k] = separation[k+1];
                    }
                    i--; //keep i at the same location because we need to check the value that is shifted over
                    if(i < 0)
                        i = 0;
                    
                }
            }
        } else {
            for(int k = i; k < nPatterns - 1; k++) { //loop through the rest of the array
                strcpy(word1[k], word1[k+1]);
                strcpy(word2[k], word2[k+1]); //shift words to the left in order to remove the improper index
                separation[k] = separation[k+1];
            }
            length--; //decrease length by 1 because we are removing an improper length
            i--; //decrease i because we want to check the index that has been shifted over
        }
    }
    
    
    return length; //return the new length that has been modified based on the number of improper words
}


int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns) {
    if(nPatterns <= 0) {
        return 0; // return 0 if there are no words that need to be checked
    }
    char copyOfDocument[MAX_DOCUMENT_LENGTH] = {}; //make a copy of the document, we know that 250 is the max length
    char breakByWords[MAX_DOCUMENT_LENGTH][MAX_DOCUMENT_LENGTH] ={}; //make a 2d array that will store all the words
    int rows = 0;
    int count = 0; //set count = 0; this variable will hold the documents rating
    int l = 0;
    
    for(int i = 0; document[i] != '\0'; i++) {
        if(isalpha(document[i]) || document[i] == ' ') {
            copyOfDocument[l] = tolower(document[i]); //if the current character is a letter or a space, copy it into the proper document
            l++;
        }
    }
    cout << l << endl;
    copyOfDocument[l] = '\0'; //make sure to add a nullbyte
    int start = 0;
    int indexOfWords = 0;
    for(int i = 0; i < l; i++) { //loop through the entire array
        bool found = false;
        if(copyOfDocument[i] == ' ' && i < l - 1 && isalpha(copyOfDocument[i+1])){  //if we find a space with a letter after
            int j = 0;
            for(int k = start; k < i; k++){ //loop from the location of the last index where we have a space then a letter
                if(isalpha(copyOfDocument[k])){ //if it is a letter
                    breakByWords[indexOfWords][j] = copyOfDocument[k]; //add the current character to the index of the 2d word array
                    start = k;// set the next start location to the end of the array
                    j++;
                    found = true; //set found equal to true if we find a word we want to store
                } //need to add a nullbyte at the end!
            }
            if(found) {
                breakByWords[indexOfWords][j] = '\0'; //add a nullbyte to the end so we dont get undefined behavior
                rows++; //we increment rows because we know we have another word to store
                start += 2; //increment where we want to start looking by two because we want to skip over our current location and the space
                indexOfWords++; //increment the row by one because we wanna start adding the new characters to the next row
            }
        } else if (i == l-1) { //if we are at the end
            int f = 0; //f corresponds to the index we are going to add the next character to in the breakbywords array
            for(int k = start; k < l; k++){ //go to the end, not out of bounds
                if(isalpha(copyOfDocument[k])){
                    breakByWords[indexOfWords][f] = copyOfDocument[k]; //load the characters into the current row
                    start = k;
                    f++; //increase f so the next character gets stored in the desired location
                }
            }
            breakByWords[indexOfWords][f] = '\0'; //add a nullbyte at the end
            indexOfWords++;
            rows++; //increment how many rows we have!
        }
        
    }
    
    for(int i = 0; i < nPatterns; i++) { //loop through the word arrays
        int breakOut = false;
        for(int k = 0; k < rows; k++) { //loop through the ammound of rows in the 2d word array based on the document
            if(strcmp(word1[i], breakByWords[k]) == 0){ //if the current word matches a word in the document
                for(int f = k + 1; f <= (separation[i] + k + 1) && f < rows; f++) { //check sepparation value forward to see if we find the matching word
                    if(strcmp(word2[i], breakByWords[f]) == 0) { //if we find the right word
                        count++; //increase count(rating) that we will return later
                        breakOut = true;
                        break; //break because we find what we are looking for, no need to keep looking
                    }
                }
                if(breakOut) //break if we find it because we we dont need go keep looking
                    break;
                
                for(int f = k-1; f >= 0 && f >= k - separation[i] - 1; f--){ //check backwards sepparation value to see if we find the matching word
                    
                    if(strcmp(word2[i], breakByWords[f]) == 0) { //if the current word matches what we are looking for in the document
                        count++; //increase count(rating)
                        breakOut = true;
                        break; //b reak because we find what we are looking for, no need to keep looking
                    }
                }
                if(breakOut)
                    break;
            }
        }
    }
    
    return count; //return how many words we find
}
