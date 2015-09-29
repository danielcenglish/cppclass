// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <unordered_map>

#include "Collatz.h"

using namespace std;

std::unordered_map <int, int> computedValues;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

//Calculate the Collatz number for an input integer
int calculateCollatz(int num)
{
    int cycle = 1;
    int original = num;
    bool found_in_cache = false;
    
    while(num != 1 && !found_in_cache)
    {
        int &stored_val = computedValues[num];
        if(stored_val)
        {
            cout<<"Looking up value " << num << " from cache" << endl;
            cycle = stored_val+cycle-1;
            found_in_cache = true;
        }
        else if(num%2!=0) //if num is odd
        {
            num = ((num*3)+1) >> 1;
            cycle+=2;
        }
        else
        {
            num = num>>1;
            ++cycle;
        }
    }
    computedValues[original]=cycle;
    cout << "Storing value " << original << " with cycle " << cycle << " in cache." << endl;
    return cycle;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    // <your code>
    
    //Calculate the Collatz cycle number for all numbers in range and keep the highest.
    int highest = 0;
    
    if(i>j) //I wish I could say I figured this out myself, but the comments pointed out this case.
    {
        int temp = i;
        i = j;
        j = temp;
    }
    
    for(int current = i; current<=j;current++)
    {
        //Calculate the Collatz number and compare to highest
        int currentCollatz = calculateCollatz(current);
        if(currentCollatz>highest)
        {
            highest=currentCollatz;
        }
    }
    
    //If odd, multiply by 3 and add 1. If even, divide by two.
    
    return highest;}



// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
