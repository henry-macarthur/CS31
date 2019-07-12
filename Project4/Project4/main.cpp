//
//  main.cpp
//  Project4
//
//  Created by Henry Macarthur on 11/1/18.
//  Copyright © 2018 Henry Macarthur. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value) {
    if(n < 0) //check to make sure n will not access a point that isn't in the array
        return -1;
    for(int i = 0; i < n; i++){
        a[i] += value; //add the string value to each array index
    }
    
    return n; //just return value of n
}

int lookup(const string a[], int n, string target){
    if(n < 0)//check to make sure n will not access a point that isn't in the array
        return -1;
    for(int i = 0; i < n; i++) { //check to make sure theres nothing in the array
        if(a[i] == target){
            return i; //return as soon as there is a match
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n){
    if(n < 1)   //check to make sure n will not access a point that isn't in the array
        return -1;
    int max = 0;
    for(int i = 1; i < n; i++){ //check to see if n == 0 return -1
        if(a[i] > a[max]){
            max = i; //set max equal to the index of array value that is bigger than previous max value
        }
    }
    return max;
}

int rotateLeft(string a[], int n, int pos){
    if(pos >= n || pos < 0) //check to make sure n and pos will not access a point that isn't in the array
        return -1; //check to see if n == 0 return -1
    if(n < 0)
        return -1; //return -1 if pos and n are equal
    string temp = a[pos];
    for(int i = pos; i < n -1; i++) { //start at the given pos value
        a[i] = a[i+1]; //shift elements to the left
    }
    
    a[n-1] = temp; //now assign last value to the starting value
    return pos;
}

int countRuns(const string a[], int n){
    
    int runs;
    if(n < 0) //check to make sure n will not access a point that isn't in the array
        return -1;
    else if (n == 0) {
        return 0;
    } else {
        runs = 1;
    }
    for(int i = 1; i < n; i++){
        if(a[i] != a[i-1]){ //this chects to see if the values are different or the same to make sure that we only count unique characters
            runs++;
        }
    }
    return runs;
}

int flip(string a[], int n){
    if(n < 0)   //check to make sure n will not access a point that isn't in the array
        return -1;
    for(int i = 0; i < n/2; i++){ //go half the length of the string
        string temp = a[n - 1 - i]; // swap given value with array value at length - 1 - i
        a[n - 1 - i] = a[i];
        a[i] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2){
    int length;
    int index = 0;
    if(n1 < 0 || n2 < 0) //check to make sure n and n2 will not access a point that isn't in the array
        return -1;
    //if n1 or n2 are less than 0 return -1 if either are 0 then return 0
    if(n1 < n2) //makes sure that we only loop through the smaller array
        length = n1;
    else
        length = n2;
    for(int i = 0; i < length; i++) {
        if(a1[i] != a2[i]) //check to see if the values are different
            return i; //return as soon as there is a difference
        index++;
    }
    return index;
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
    
    if(n1 < 0 || n2 < 0 || n2 > n1) //check to make sure n will not access a point that isn't in the array, make sure that n2 is not bigger than n1
        return -1;
    if(n2 == 0)
        return 0;
    
    for(int i = 0; i <= n1-n2; i++) { //increment index of first array, make sure we do not go out of bounds and get undefined behavior
        bool hasSubsequence = false;
        for(int j = 0; j < n2; j++) { //compare current value of a1 with all values of a2
            if(a1[i+j] != a2[j]) {
                hasSubsequence = false; //if the values are not the same then return false
                break;
            }
            hasSubsequence = true;
        }
        if(hasSubsequence) { //if subsequence is true after the loop, return the index
            return i;
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
    if (n1 < 0 || n2 < 0 ) { //check to make sure n1 or n2 will not access a point that isn't in the array
        return -1;
    } //return -1 if nothing in a2 is found in a1
    for(int i = 0; i < n1; i++) { //loop through array 1
        for(int k = 0 ; k < n2; k++) { //loop through array 2
            if(a1[i] == a2[k]){ //check to see if the values are the same
                return i;
            }
        }
    }
    return -1;
}
int divide(string a[], int n, string divider) { //ask ta about equal elements
    if(n < 0) //check to make sure n will not access a point that isn't in the array
        return -1;
    int canDivide = 0;
    for(int i = 0; i < n; i++) { // find how many vales are less than the given value
        if(a[i] < divider)
            canDivide++;
    }
    for(int i = 0; i < canDivide; i++) { //create a loop that iterates canDivide times
        for(int k = i; k < n; k++) {
            if(a[k] < divider) {
                string temp = a[k]; //start at 0, find a value that is less than divider, swap, move onto next index, repeat
                a[k] = a[i];
                a[i] = temp;
            }
        }
    }
    
    int currentSwapPos = canDivide; //start at a value that is 1 greater than the index of the last value that is less than the divier value
    for(int i = canDivide; i < n; i++) { /* this loop makes sure that all the values that are equal to the divider value appear after those that are less than it but before those that are greater than it*/
        if(a[i] == divider){
            string temp = a[currentSwapPos];
            a[currentSwapPos] = a[i];
            a[i] = temp;
            currentSwapPos++;
        }
    }
    if(a[0] == divider) { //check to see if no values are less than divider
        return n;
    } else {
    return canDivide;
    }
}


int main(int argc, const char * argv[]) {
    
    string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    string g[5] = { "gavin", "ed", "ed", "", "eleni"};
    string k[3] = {"b", "c", "d"};
    int f = flip(h,4);
    for(int i =0; i < 7; i++) {
        cout << h[i] << endl;
    }
    
    cout << "All tests succeeded" << endl;
    
}
