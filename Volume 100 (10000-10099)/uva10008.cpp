#include <iostream>
#include <vector>
#include<string>
#include <algorithm>
using namespace std;

struct letter_number
{
    char letter;
    int number;
};
vector<letter_number>::iterator find_if_letters_has_c(vector<letter_number>& ln, const char c) {
    for(vector<letter_number>::iterator it = ln.begin(); it != ln.end(); it++) {
        if (it->letter == c) {
            return it;
        }
    }
    return ln.end();
}
void save_letter_char(char c, vector<letter_number>& ln) {
    vector<letter_number>::iterator it = find_if_letters_has_c(ln, c);
    if (it != ln.end())
        it->number++;
    else {
        struct letter_number s;
        s.letter = c;
        s.number = 1;
        ln.push_back(s);
    }
}

bool uva10008_compare(struct letter_number& a, struct letter_number& b) {
    if (a.number == b.number)
        return a.letter < b.letter;
    else
        return a.number > b.number;
}

int main(int, char**) {
    string input_all;
    int input_lines;
    cin >> input_lines;
    cin.ignore();
    for (int i = 0; i < input_lines; i++) {
        string input;
        getline(cin, input);
        input_all = input_all + input;
    }
    vector<letter_number> letters;
    for (int i = 0; i < input_all.length(); i++) {
        char c = input_all[i];
        if (isalpha(c)) {
            save_letter_char(toupper(c), letters);
            //cout << c << endl;
        }
    }
    sort(letters.begin(), letters.end(), uva10008_compare);

    for (int i = 0; i < letters.size(); i++)
        cout << letters[i].letter << " " << letters[i].number << endl;

    return 0;
}
