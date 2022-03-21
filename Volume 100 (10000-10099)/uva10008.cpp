#include <iostream>
#include <vector>
#include<string>
#include <algorithm>
using namespace std;

#ifdef TEST
#include <gtest/gtest.h>
#endif

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

void solve(std::istream & is, std::ostream & os) {
    string input_all;
    string str;
    int input_lines;

    std::getline(is, str);
    input_lines = stoi(str);
    cin.ignore();
    for (int i = 0; i < input_lines; i++) {
        string input;
        getline(is, input);
        //getline(cin, input);
        input_all = input_all + input;
    }
    vector<letter_number> letters;
    for (int i = 0; i < input_all.length(); i++) {
        char c = input_all[i];
        if (isalpha(c)) {
            save_letter_char(toupper(c), letters);
        }
    }
    sort(letters.begin(), letters.end(), uva10008_compare);

    for (int i = 0; i < letters.size(); i++)
        os << letters[i].letter << " " << letters[i].number << endl;
}

int main(int argc, char* argv[]) {

#if defined(TEST)
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    solve(std::cin, std::cout);
#endif
    return 0;
}
#ifdef TEST

TEST(full_function, solve)
{
    std::istringstream iss(R"(3
that's Asif's book "The Outsider".

Go to 29th page.Let's play !!!!   [[((well enough))]]
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(T 7
E 6
O 6
S 5
A 4
H 4
L 4
G 3
I 2
P 2
U 2
B 1
D 1
F 1
K 1
N 1
R 1
W 1
Y 1
)", oss.str());
}

TEST(full_function, debugster4)
{
    std::istringstream iss(R"(3
This is a test.
Count me 1 2 3 4 5.
Wow!!!! Is this question easy?
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(S 7
T 6
I 5
E 4
O 3
A 2
H 2
N 2
U 2
W 2
C 1
M 1
Q 1
Y 1
)", oss.str());
}
TEST(full_function, udebug1)
{
    std::istringstream iss(R"(16
Its had resolving otherwise she contented therefore;"./. Afford relied warmth out sir hearts 
sister use garden. Men day warmth formed admire former simple.             Humanity declared vicinity 
continue supplied no an. He hastened am no property exercise of. D
issimilar comparison no terminated devonshire no literature on. Say most yet head room such just easy. 

The QUICK brown fox JumpEd over the LazY doG!@@@

Reached suppose our whether. Oh really by an manner sister so. One sportsman tolerably him extensive put she immediate. 
He abroad of cannot looked in. #()Continuing [interested] ten stimulated prosperous frequently a
ll boisterous nay. Of oh reall!!!!

y he extent horses wicket. 
Picture removal detract earnest is by. Esteems met joy attempt way clothes yet demesne tedious. 
                                     Replying an marianne do it an entrance advanced. Two dare say play when hold. Required bringing me material stanhill 
jointure is as he. Mutual indeed yet her living result matter him bed 
whence.
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(E 115
T 66
R 61
A 56
N 55
O 54
I 52
S 51
D 36
H 33
M 32
L 30
U 25
Y 22
C 18
P 17
F 10
W 10
B 8
G 8
V 8
J 4
X 4
K 3
Q 3
Z 1
)", oss.str());
}

#endif