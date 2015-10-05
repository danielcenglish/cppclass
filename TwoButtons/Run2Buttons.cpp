// --------
// includes
// --------

#include <iostream> // cin, cout
#include <utility>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>
using namespace std;



// ----
// main
// ----

void two_buttons_solve (istream& r, ostream& w);

int main () {
    
    two_buttons_solve(cin, cout);
    return 0;}

int two_buttons_eval(int n, int m)
{
    //If n is less than m, multiply n by 2.
    //If n is greater than m, subtract 1.
    //If n = m, return.
    list<int>numsChecked(n);
    
    if(n==m) //base case
    {
        return 0;
    }
    else
    {
        if(n > m)
        {
            cout << "n (" << n << ") is greater than m (" << m << ")" << endl;
            //need to subtract 1 always
            return two_buttons_eval(n-1,m) + 1;
        }
        else if ((n*2) == m)
        {
            cout << "n (" << n << ") * 2 is equal to m (" << m << ")" << endl;
            return 1;
        }
        else if (n-1 == m)
        {
            cout << "n (" << n << ") - 1 is equal to m (" << m << ")" << endl;
            return 1;
        }
        else
        {
            cout << "n (" << n << ") is less than m (" << m << ")" << endl;
            //may multiply by 2 or subtract 1. How to know which?
            //the two options are to subtract 1 or multiply by 2. Do both!
            int answer_by_multiplying = two_buttons_eval(n*2,m);

            int answer_by_subtracting = two_buttons_eval(n-1,m);
            return min(answer_by_subtracting, answer_by_multiplying) + 1;
        }
        
    }
}

pair<int, int> two_buttons_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

void two_buttons_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = two_buttons_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = two_buttons_eval(i, j);
        w << v << endl;
    }
}
/*
% g++ -pedantic -std=c++11 -Wall Collatz.c++ RunCollatz.c++ -o RunCollatz



% cat RunCollatz.in
1 10
100 200
201 210
900 1000



% RunCollatz < RunCollatz.in > RunCollatz.out



% cat RunCollatz.out
1 10 1
100 200 1
201 210 1
900 1000 1



% doxygen -g
// That creates the file Doxyfile.
// Make the following edits to Doxyfile.
// EXTRACT_ALL            = YES
// EXTRACT_PRIVATE        = YES
// EXTRACT_STATIC         = YES



% doxygen Doxyfile
// That creates the directory html/.
*/
