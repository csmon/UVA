#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>

using hour_minute_t = std::pair<int, int>;

//#define TEST
#ifdef TEST
#include <gtest/gtest.h>
#endif
class Station {
    public:
	Station(int max, std::string &trains);
    void init_station(const int size, std::string &trains);
    bool is_direction_b_possible();
    private:
        void reset_station();
        bool station_empty();
        bool direction_b_empty();
        int next_train_in_station();
        int next_train_in_direction_b();
        std::stack<int> trains_in_station;
        std::queue<int> trains_direction_b;
        int max_train;

};
Station::Station(int size, std::string &trains) {
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    max_train = size;
    for (int i = 1; i <= max_train; i++) {
        pos = trains.find(delimiter);
        token = trains.substr(0, pos);
        trains_direction_b.push(stoi(token));
        trains.erase(0, pos + delimiter.length());
    }
}
void Station::reset_station() {
    std::queue<int> empty;
    swap(empty, trains_direction_b);
    trains_in_station = std::stack<int>();
}
bool Station::station_empty() {
    return trains_in_station.empty();
}
bool Station::direction_b_empty() {
    return trains_direction_b.empty();
}
int Station::next_train_in_direction_b() {
    return trains_direction_b.front();
}

int Station::next_train_in_station() {
    return trains_in_station.top();
}

bool Station::is_direction_b_possible() {
    while (!trains_direction_b.empty()) {
        for (int arrival_train = 1; arrival_train <= max_train; arrival_train++) {
            if ((arrival_train) == next_train_in_direction_b()) {
                trains_direction_b.pop();
                continue;
            }
            while (!station_empty() && !direction_b_empty() \
                && (next_train_in_station() == next_train_in_direction_b())) {
                    trains_in_station.pop();
                    trains_direction_b.pop();
            }
            if (direction_b_empty())
                return true;
            trains_in_station.push(arrival_train);
        }


        while (!station_empty() && !direction_b_empty() \
            && (next_train_in_station() == next_train_in_direction_b())) {
             trains_in_station.pop();
             trains_direction_b.pop();
         }
         if (!trains_direction_b.empty())
             return false;

    }
    return true;
}

void Station::init_station(const int size, std::string &trains) {
    reset_station();
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    max_train = size;
    for (int i = 1; i <= max_train; i++) {
        pos = trains.find(delimiter);
        token = trains.substr(0, pos);
        trains_direction_b.push(stoi(token));
        trains.erase(0, pos + delimiter.length());
    }
}

void solve(std::istream & is, std::ostream & os) {

   std::string line;
    while(true) {
        int num;

        std::getline(is, line);
        int number_n = stoi(line);
        if (number_n == 0) break;

        while(true) {
            std::getline(is, line);
            if (line[0] == '0') {
                os << std::endl;
                break;
            }
        	class Station s(number_n, line);
//            s.init_station(number_n, line);

            if (s.is_direction_b_possible() == true) {
                os << "Yes" << std::endl;
            } else {
                os << "No" << std::endl;
            }

        }
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
TEST( a123, uva514)
{
    std::istringstream iss(R"(5
1 2 3 4 5
5 4 1 2 3
1 4 3 2 5
3 4 2 5 1
3 4 2 1 5
4 3 5 2 1
0
0)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(Yes
No
Yes
Yes
Yes
Yes

)", oss.str());
}
TEST( mnesia, uva514)
{
    std::istringstream iss(R"(5
1 2 3 4 5
5 4 1 2 3
0
6
6 5 4 3 2 1
0
0
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(Yes
No

Yes

)", oss.str());
}

TEST( urash16, uva514)
{
    std::istringstream iss(R"(5
1 2 3 4 5
5 4 1 2 3
3 5 4 2 1
3 4 2 5 1
0
6
6 5 4 3 2 1
0
0
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(Yes
No
Yes
Yes

Yes

)", oss.str());
}
TEST( uvaonlineJudge, uva514)
{
    std::istringstream iss(R"(5
1 2 3 4 5
5 4 1 2 3
1 4 3 2 5
3 4 2 5 1
3 4 2 1 5
4 3 5 2 1
0
3
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
0
4
1 2 3 4
1 2 4 3
1 3 2 4
1 3 4 2
1 4 2 3
1 4 3 2
2 1 3 4
2 1 4 3
2 3 1 4
2 3 4 1
2 4 1 3
2 4 3 1
3 1 2 4
3 1 4 2
3 2 1 4
3 2 4 1
3 4 1 2
3 4 2 1
4 1 2 3
4 1 3 2
4 2 1 3
4 2 3 1
4 3 1 2
4 3 2 1
0
10
5 7 10 9 8 6 4 3 2 1
5 6 4 8 7 3 2 9 1 10
0
0

)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(Yes
No
Yes
Yes
Yes
Yes

Yes
Yes
Yes
Yes
No
Yes

Yes
Yes
Yes
Yes
No
Yes
Yes
Yes
Yes
Yes
No
Yes
No
No
Yes
Yes
No
Yes
No
No
No
No
No
Yes

Yes
Yes

)", oss.str());
}
#endif
