#include "sudoku_funct.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

using std::vector;      using std::istream;
using std::getline;     using std::string;
using std::cout;        using std::endl;
using std::cin;         using std::stringstream;



int solve_or_guess(vector<string>& puzzle){
    string reference_string = "123456789";
    vector<int> indices;


    //Break puzzle
    break_puzzle(puzzle);

    //Find the important indicies
    int main_index = find_max_given(puzzle);
    vector<int> zeros = find_zero_pos(puzzle[main_index]);
    int max_element_index = find_max_given(puzzle, main_index, zeros);

    indices = find_indices(main_index, max_element_index);
    int row_index = indices[0];
    int col_index = indices[1];
    int box_index = indices[2];
    int k = 0;
    vector<int> possible_answers;

    //Eliminate given numbers from reference string
    for (int i = 0; i != 9; i++){
        for (int k = 0; k != 9; k++) {
            if (reference_string[i] == puzzle[row_index][k] || reference_string[i] == puzzle[col_index][k] || reference_string[i] == puzzle[box_index][k] ){
                possible_answers.push_back(0);
                break;
            }

            else if ( k == 8 ){
                possible_answers.push_back(1);
            }
        }
    }

    string answers;

    for (int i = 0; i != 9; i++){
        if (possible_answers[i] != 0){
            answers+=convertInt(i+1);
        }
    }

    if (!finished_puzzle(puzzle) && answers.size() == 0){
        return -2;           //Contradiction, no answers available with unfinished puzzle.
    }

    else if (finished_puzzle(puzzle) && answers.size() == 0){
        return 10;          //Puzzle is complete
    }

    //Guess or solve?
    else if (answers.size() > 1){         //Guess

        for (string::iterator iter = answers.begin();iter != answers.end(); ++iter){
            puzzle[row_index][col_index - 9] = *iter;
            int guess = -1;
            puzzle.erase(puzzle.begin()+9, puzzle.end());
            int value = solve_or_guess(puzzle);

            //Coming out of recursion
            if (value == 10){
                return 10;              //Complete, do not change anything or continue
           }

            if (value == -2){
            }
        }
        puzzle[row_index][col_index - 9] = '0';
        return -2;
    }

    else if (answers.size() == 1) {
         puzzle[row_index][col_index - 9] = answers[0];
         puzzle.erase(puzzle.begin()+9, puzzle.end());
         int value = solve_or_guess(puzzle);
         if (value == 10){
            return 10;              //Puzzle complete.
         }

         else if (value == -2){
            puzzle.erase(puzzle.begin()+9, puzzle.end());
            puzzle[row_index][col_index - 9] = '0';
            return -2;
         }
    }

return 0;
}


bool finished_puzzle(const vector<string>& puzzle){
    for (int i = 0; i != 9; i++){
        for (int j = 0; j != 9; j++){
            if (puzzle[i][j] == '0'){
                return false;
            }

        }
    }
    return true;
}


string convertInt(int number){
   stringstream ss;
   ss << number;
   return ss.str();
}


/*003..020..600
900..305..001
001..806..400

008..102..900
700..000..008
006..708..200

002..609..500
800..203..009      8 2 3 9 5 4   1 6 7
005..010..300
*/

vector<int> find_indices (const int& main_index, const int& element_index){
    vector<int> ret;
    int col_index, row_index, box_index;
    if (main_index < 9){                            //row
        row_index = main_index;
        col_index = element_index + 9;

            //What box are we in?
            if (main_index < 3 && element_index < 3){
                box_index = 18;
            }
            else if (main_index < 3 && element_index >= 3 && element_index < 6){
                box_index = 19;
            }
            else if (main_index < 3 && element_index >= 6){
                box_index = 20;
            }
            else if (main_index >= 3 && main_index < 6 && element_index < 3) {
                box_index = 21;
            }
            else if (main_index >= 3 && main_index < 6 && element_index >= 3 && element_index <6){
                box_index = 22;
            }
            else if (main_index >= 3 && main_index < 6 && element_index >= 6){
                box_index = 23;
            }
            else if (main_index >= 6 && element_index < 3){
                box_index = 24;
            }
            else if (main_index >=6 && element_index >= 3 && element_index < 6){
                box_index = 25;
            }
            else if (main_index >= 6 && element_index >= 6){
                box_index = 26;
            }
            else {
                box_index = 27;
            }
    }

    else if (main_index >= 9 && main_index < 18) {   //Column
        col_index = main_index;
        row_index = element_index;

            //What box are we in?
            if (main_index >= 9 && main_index < 12 && element_index < 3){
                box_index = 18;
            }
            else if (main_index >= 12 && main_index < 15 &&  element_index < 3){
                box_index = 19;
            }
            else if (main_index >=15 && element_index < 3){
                box_index = 20;
            }
            else if (main_index >= 9 && main_index < 12 && element_index >= 3 && element_index < 6) {
                box_index = 21;
            }
            else if (main_index >= 12 && main_index < 15 && element_index >= 3 && element_index < 6){
                box_index = 22;
            }
            else if (main_index >= 15 && element_index >= 3 && element_index < 6){
                box_index = 23;
            }
            else if (main_index >= 9 && main_index < 12 && element_index >= 6){
                box_index = 24;
            }
            else if (main_index >= 12 && main_index < 15 && element_index >= 6){
                box_index = 25;
            }
            else if (main_index >= 15 && element_index >= 6){
                box_index = 26;
            }
            else {
                box_index = 27;
            }
     }

     else{                                           //Box
         box_index = main_index;
         col_index = find_col_box(main_index, element_index);
         row_index = find_row_box(main_index, element_index);
    }

    ret.push_back(row_index);
    ret.push_back(col_index);
    ret.push_back(box_index);

    return ret;
}





vector<int> find_zero_pos (string& s){
    vector<int> zero_indices;
    for (int i = 0; i != 9; i++){
        if (s[i] == '0'){
            zero_indices.push_back(1);
        }
        else {
            zero_indices.push_back(0);
        }
    }
    //for (vector<int>::const_iterator print = zero_indices.begin(); print != zero_indices.end(); ++print){
    //    cout << *print << endl;
    //}
    return zero_indices;
}




int find_max_given (vector<string>& puzzle){
    int max_index = 0;
    int current_count = 0;
    int max_count = 0;
    int counter = 0;

    for (vector<string>::iterator iter = puzzle.begin();
                iter != puzzle.end(); ++iter){
        current_count = count_given(*iter);
        if (current_count >= max_count && current_count != 9){
            max_index = counter;
            max_count = current_count;
        }
        counter++;
    }
    return max_index;
}




int count_given(const string& s){
    int counter = 0;
    for (int i = 0; i != 9; i++){
        if (s[i]!='0'){
            counter++;
        }
    }

    return counter;
}





int find_max_given(const vector<string>& puzzle, const int& main_index, const std::vector<int>& zero_indices ){
    string main_string = puzzle[main_index];
    vector<int> indices;
    int row_index = 0, col_index = 0, box_index = 0, current_count = 0, max_count = 0, max_index = 0;

    for (int i = 0; i != 9; i++){
            //cout << i << endl;
        if (zero_indices[i] == 1){
            indices = find_indices(main_index, i);
            row_index = indices[0];
            col_index = indices[1];
            box_index = indices[2];
            current_count = count_given(puzzle[row_index]) + count_given(puzzle[col_index]) + count_given(puzzle[box_index]);
        }

        if (current_count > max_count){
            max_count = current_count;
            max_index = i;
           // cout << max_index << " , " << max_count << endl;
        }
    }
    //cout << "Max element index: " << max_index  << endl;
    return max_index;
}





int find_col_box(const int& main_index, const int& zero_index){
    int col_index = 0;
    if (main_index == 18 || main_index == 21 || main_index == 24){
        col_index = zero_index % 3 + 9;
    }
    else if (main_index == 19 || main_index == 22 || main_index == 25){
        col_index = zero_index % 3 + 3 + 9;
    }
    else {
        col_index = zero_index % 3 + 6 + 9;
    }
    return col_index;
}





int find_row_box(const int& main_index, const int& zero_index){
    int row_index = 0;
    if (main_index == 18 || main_index == 19 || main_index == 20){
        if (zero_index < 3){
            row_index = 0;
        }
        else if (zero_index >= 3 && zero_index < 6){
            row_index = 1;
        }
        else {
            row_index = 2;
        }
    }
    else if (main_index == 21 || main_index == 22 || main_index == 23){
        if (zero_index < 3){
            row_index = 3;
        }
        else if (zero_index >= 3 && zero_index < 6){
            row_index = 4;
        }
        else {
            row_index = 5;
        }
    }
    else if (main_index == 24 || main_index == 25 || main_index == 26){
        if (zero_index < 3){
            row_index = 6;
        }
        else if (zero_index >= 3 && zero_index < 6){
            row_index = 7;
        }
        else {
            row_index = 8;
        }
    }
    return row_index;
}





void break_puzzle (vector<string>& puzzle){

    //Form the columns, and push_back
    for (int i = 0; i != 9; i++){
        char col[9] = {puzzle[0][i] , puzzle[1][i] , puzzle[2][i] , puzzle[3][i] , puzzle[4][i] , puzzle[5][i] , puzzle[6][i] , puzzle[7][i] , puzzle[8][i]};
        string col_string(col, 0 , 9);
        puzzle.push_back(col_string);

    }

    //Form the squares, and push_back
    char box1[9] = {puzzle[0][0] , puzzle[0][1] , puzzle[0][2] , puzzle[1][0] , puzzle[1][1] , puzzle[1][2] , puzzle[2][0] , puzzle[2][1] , puzzle[2][2]};
    char box2[9] = {puzzle[0][3] , puzzle[0][4] , puzzle[0][5] , puzzle[1][3] , puzzle[1][4] , puzzle[1][5] , puzzle[2][3] , puzzle[2][4] , puzzle[2][5]};
    char box3[9] = {puzzle[0][6] , puzzle[0][7] , puzzle[0][8] , puzzle[1][6] , puzzle[1][7] , puzzle[1][8] , puzzle[2][6] , puzzle[2][7] , puzzle[2][8]};
    char box4[9] = {puzzle[3][0] , puzzle[3][1] , puzzle[3][2] , puzzle[4][0] , puzzle[4][1] , puzzle[4][2] , puzzle[5][0] , puzzle[5][1] , puzzle[5][2]};
    char box5[9] = {puzzle[3][3] , puzzle[3][4] , puzzle[3][5] , puzzle[4][3] , puzzle[4][4] , puzzle[4][5] , puzzle[5][3] , puzzle[5][4] , puzzle[5][5]};
    char box6[9] = {puzzle[3][6] , puzzle[3][7] , puzzle[3][8] , puzzle[4][6] , puzzle[4][7] , puzzle[4][8] , puzzle[5][6] , puzzle[5][7] , puzzle[5][8]};
    char box7[9] = {puzzle[6][0] , puzzle[6][1] , puzzle[6][2] , puzzle[7][0] , puzzle[7][1] , puzzle[7][2] , puzzle[8][0] , puzzle[8][1] , puzzle[8][2]};
    char box8[9] = {puzzle[6][3] , puzzle[6][4] , puzzle[6][5] , puzzle[7][3] , puzzle[7][4] , puzzle[7][5] , puzzle[8][3] , puzzle[8][4] , puzzle[8][5]};
    char box9[9] = {puzzle[6][6] , puzzle[6][7] , puzzle[6][8] , puzzle[7][6] , puzzle[7][7] , puzzle[7][8] , puzzle[8][6] , puzzle[8][7] , puzzle[8][8]};


    string box_string1(box1, 0 , 9);
    string box_string2(box2, 0 , 9);
    string box_string3(box3, 0 , 9);
    string box_string4(box4, 0 , 9);
    string box_string5(box5, 0 , 9);
    string box_string6(box6, 0 , 9);
    string box_string7(box7, 0 , 9);
    string box_string8(box8, 0 , 9);
    string box_string9(box9, 0 , 9);

    puzzle.push_back(box_string1);
    puzzle.push_back(box_string2);
    puzzle.push_back(box_string3);
    puzzle.push_back(box_string4);
    puzzle.push_back(box_string5);
    puzzle.push_back(box_string6);
    puzzle.push_back(box_string7);
    puzzle.push_back(box_string8);
    puzzle.push_back(box_string9);


}
