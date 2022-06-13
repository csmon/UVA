#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>
#include <set>

//#define TEST
#ifdef TEST
#include <gtest/gtest.h>
#endif

using namespace std;

class Blanace {
    enum status {
        UP,
        DOWN,
        EVEN,
        UNKNOWN,
    };

public:
    Blanace(const int number = 3) {
        weighing_number = number;
        counterfeit_status = UNKNOWN;
    }
    std::string getResult() {
        std::string c(1, counterfeit);
        std::string w(counterfeit_weight());
        return c + " is the counterfeit coin and it is " + w + "." ;
    }

    void updateCoinResult(std::string line) {
        istringstream in(line);
        std::string left, right, balance_status;
        in >> left >> right >> balance_status;
        if (balance_status == "even") {
            for (char c: left)
                updateCoinStatus(c, EVEN);
            for (auto c: right)
                updateCoinStatus(c, EVEN);
                return;
        }

        // switch left/right to become up status
        if (balance_status == "down") {
            std::string tmp;
            tmp = left;
            left = right;
            right = tmp;
        }

        std::set<char> coins;
        for (char c: left) {
            updateCoinStatus(c, DOWN);
            coins.insert(c);
        }
        down_group.push_back(coins);
        coins.clear();
        for (auto c: right) {
            updateCoinStatus(c, UP);
            coins.insert(c);
        }
        up_group.push_back(coins);
    }

    char updateGroupToEven(char c) {

        for (auto it = coins_status.begin(); it != coins_status.end(); it++) {
            if (it->second == EVEN) {
                // remove even in group
                for (auto i = up_group.begin(); i != up_group.end(); i++) {
                    std::set<char> s = *i;
                    (*i).erase((char)c);

                    if (s.size() == 1)
                    {
                        char coin = *(s.begin());
                        if (coins_status[coin] != EVEN) {
                            counterfeit_status = coins_status[coin];
                            counterfeit = coin;
                            return counterfeit;
                        }
                    }
                }

                for (auto i = down_group.begin(); i != down_group.end(); i++) {
                    std::set<char> s = *i;
                    (*i).erase((char)c);

                    if (s.size() == 1)
                    {
                        char coin = *(s.begin());
                        if (coins_status[coin] != EVEN) {
                            counterfeit_status = coins_status[coin];
                            counterfeit = coin;
                            return counterfeit;
                        }
                    }
                }
            }
        }
        return 0;
    }
    void findCounterfeitCoin() {

        std::vector<char> up, down;
        for (auto it = coins_status.begin(); it != coins_status.end(); it++) {
            if (it->second == DOWN)
                down.push_back(it->first);
            if (it->second == UP)
                up.push_back(it->first);
        }

        if (down.size() == 1) {
            counterfeit_status = DOWN;
            counterfeit = *(down.begin());
            return;
        } else if (up.size() == 1) {
            counterfeit_status = UP;
            counterfeit = *(up.begin());
            return;
        }

        for (auto it = coins_status.begin(); it != coins_status.end(); it++) {
            char c = it->first;
            if (it->second == EVEN) {
                if(updateGroupToEven(c) != 0)
                    break;
            }
        }

    }

    std::string counterfeit_weight() {
        if (counterfeit_status == UP)
            return "light";
        return "heavy";
    }
private:
    void updateCoinStatus(char c, enum status s) {
        if (coins_status.find(c) != coins_status.end()) {
            if (coins_status[c] != s)
                coins_status[c] = EVEN;
        } else {
            coins_status[c] = s;
        }
    }
public:
    int weighing_number;
private:
    char counterfeit;
    enum status counterfeit_status;
    std::map<char, enum status> coins_status;
    std::vector<std::set<char>> up_group, down_group;
};

void solve(std::istream & is, std::ostream & os) {

    std::string line;
    getline(is, line);
    int case_number;
    case_number = stoi(line);

    for (int i = 0; i < case_number; i++) {
        Blanace b;
        std::string line;
        for (int j = 0; j < b.weighing_number; j++)
        {
            getline(is, line);
            b.updateCoinResult(line);
        }
        b.findCounterfeitCoin();
        std::string result = b.getResult();
        os << result << std::endl;
    }
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

TEST( urash16, uva608)
{
    std::istringstream iss(R"(15
ABC DEF up 
GHI JKL even 
EF DA up 
AFG JKL down 
A J down 
A D even 
ED FG even 
AB CI up 
A D up 
IL JK even 
A B even 
E L down 
BEF JIL down 
J A even 
CEF BJI even 
AC BD down
AC EF down
A F even
IJK ABC even
C L even
L F up
IJK ABC even
C L even
L F down
ABCDE FGHIJ even
EIL ADJ down
K J even
CBA DEF up
AF BC up
BA CD up
CBA DEF up
A B up
BA CD up
CBA DEF up
B A down
BA CD up
CBA DEF down
AF BC down
BA CD down
CBA DEF down
A B down
BA CD down
CBA DEF down
B A up
BA CD down
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(D is the counterfeit coin and it is light.
J is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
E is the counterfeit coin and it is light.
L is the counterfeit coin and it is heavy.
C is the counterfeit coin and it is light.
F is the counterfeit coin and it is light.
F is the counterfeit coin and it is heavy.
L is the counterfeit coin and it is light.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is heavy.
A is the counterfeit coin and it is light.
A is the counterfeit coin and it is light.
A is the counterfeit coin and it is light.
)", oss.str());
}
#endif
