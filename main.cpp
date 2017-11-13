#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "sudoku_funct.h"
#include <algorithm>
#include <cstdlib>

using std::vector;     using std::cout;
using std::endl;        using std::cin;
using std::stringstream;
using std::string;

int main()
{
    int answer=0;
    vector<string> puzzle;
    string puzz;
    while(getline(cin, puzz)) {
        stringstream ss(puzz);
        puzzle.push_back(puzz);
        if(puzzle.size() == 9){
            solve_or_guess(puzzle);
            int x, y , z;
            char temp[3] = {puzzle[0][0] , puzzle[0][1] , puzzle[0][2]};
            string num(temp, 0, 3);
            cout << num << endl;
            int sudoku_num =atoi( num.c_str() );
            answer += sudoku_num;
            cout << "Current_sum: " << answer<< endl;
            puzzle.clear();

            cin.ignore();   cin.ignore();
            cin.ignore();   cin.ignore();
            cin.ignore();   cin.ignore();
            cin.ignore();   cin.ignore();
        }


    }

    //int a = solve_or_guess(puzzle, answer);
    cout << answer << endl;

}
