#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <queue>
using namespace std;

//#define TEST
#ifdef TEST
#include <gtest/gtest.h>
#endif

std::priority_queue<int, vector<int>, greater<int>> save_data(const std::string &line) {
    std::priority_queue<int, vector<int>, greater<int>> inputs;
    int number;
    std::stringstream stream(line);
    while (stream >> number) {
        inputs.push(number);
    }
    return inputs;
}

int get_total_cost(std::priority_queue<int, vector<int>, greater<int>> &inputs) {
    int cost = 0;
    int min_1, min_2;
    while (inputs.empty() == false) {
        min_1 = inputs.top();
        inputs.pop();
        min_2 = inputs.top();
        inputs.pop();
        cost += (min_1 + min_2);
        inputs.push(min_1 + min_2);
        if (inputs.size() == 1) {
            return cost;
            break;
        }
    }
    return 0;
}

void solve(std::istream & is, std::ostream & os) {
   
    while(true) {
        std::string line;
        std::getline(is, line);
        int length = stoi(line);
        if (length == 0)
            break;

        std::getline(is, line);
        std::priority_queue<int, vector<int>, greater<int>> inputs = save_data(line);

        int cost = get_total_cost(inputs);

        os << cost << std::endl;
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

TEST(sample, uva10954)
{
    std::istringstream iss(R"(3
1 2 3
4
1 2 3 4
0
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(9
19
)", oss.str());
}

TEST(Shah_Shishir, uDebug)
{
    std::istringstream iss(R"(5
5 4 3 1 2
0
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(33
)", oss.str());
}

TEST(caffeines, uDebug)
{
    std::istringstream iss(R"(3
6 5 4
10
9 5 48 2 4 5 6 3 5 4
10
3 4 5 4 7 2 3 8 4 5
0
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(24
224
147
)", oss.str());
}

TEST(Eduardo_Figueiredo, uDebug)
{
    std::istringstream iss(R"(8
4 4 6 6 8 8 10 10
8
4 6 6 7 7 8 8 9
8
3 4 6 6 6 8 8 9
8
3 4 5 5 5 5 8 9
2
99999 0
4
99997 49999 49999 49999
4
49999 99998 49999 49999
0
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(166
165
148
130
99999
499988
499990
)", oss.str());
}
#endif