// --------
// includes
// --------

#include <iostream> // cin, cout
#include <utility>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;



// ----
// main
// ----

void two_buttons_solve(istream& r, ostream& w);

int main() {

	two_buttons_solve(cin, cout);
	return 0;
}

int two_buttons_eval(int n, int m)
{
	//Starting at m and moving toward n, do a breadth first search of all options to see which ones move closer to n.
	//use a pair to store: (current number, distance down path)

	queue<pair<int,int>> possiblePaths;
	possiblePaths.push(make_pair(m,0));
	pair<int,int> currentVal;
	int best_cycle_found = INT_MAX;
	int min_cycle_in_queue = 1;
	int next_cycle = 0;

	while (!possiblePaths.empty() && best_cycle_found > min_cycle_in_queue)
	{
		currentVal = possiblePaths.front();
		possiblePaths.pop();
		//cout << "Testing value " << currentVal.first << " at cycle length " << currentVal.second << endl;
		if (currentVal.first == n) //this is a solution, no need to keep going
		{
			cout << "Found solution at " << currentVal.second << endl;
            if(currentVal.second < best_cycle_found)
            {
                best_cycle_found = currentVal.second;
            }
			//break;
		}
		else
		{
			next_cycle = currentVal.second + 1;
			if (next_cycle < min_cycle_in_queue)
			{
				min_cycle_in_queue = next_cycle;
			}
			//compute two possible paths from the next value
            //Only add things to the queue if there is a possibility of them beating the best cycle
			if (currentVal.second + 1 < best_cycle_found)
			{
                //if m is greater than n and m can be evenly divided by 2, try dividing.
				if (currentVal.first > n && currentVal.first%2==0)
				{
					possiblePaths.push(make_pair(currentVal.first >> 1, currentVal.second + 1));
				}
				
                //If m/4 is still greater than n, there is no reason to try subtracting 1.
				if (!(currentVal.first % 4 == 0 && (currentVal.first >> 2) > n))
				{
					possiblePaths.push(make_pair(currentVal.first + 1, currentVal.second + 1));
				}
			}
		}
	}

	/*
	while (!possiblePaths.empty())
	{
		currentVal = possiblePaths.front();
		possiblePaths.pop();
		//cout << "Testing value " << currentVal.first << " at cycle length " << currentVal.second << endl;
		if (currentVal.first == m)
		{
			//cout << "Found solution at " << currentVal.second << endl;
			best_cycle_found = min(best_cycle_found,currentVal.second);
			break;
		}
		else
		{
			//compute two possible paths from the next value
			if (currentVal.second + 1 < best_cycle_found)
			{
				if (currentVal.first < m)
				{
					possiblePaths.push(make_pair(currentVal.first << 1, currentVal.second + 1));
				}

				possiblePaths.push(make_pair(currentVal.first - 1, currentVal.second + 1));
			}
		}
	}
	*/


	return currentVal.second;
}

pair<int, int> two_buttons_read(const string& s) {
	istringstream sin(s);
	int i;
	int j;
	sin >> i >> j;
	return make_pair(i, j);
}

void two_buttons_solve(istream& r, ostream& w) {
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
