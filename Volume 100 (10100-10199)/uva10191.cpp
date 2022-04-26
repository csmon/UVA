#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>

using hour_minute_t = std::pair<int, int>;

//#define TEST
#ifdef TEST
#include <gtest/gtest.h>
#endif
class OneDay {
    public:
        void addBusyTime(int hour1, int minute1, int hour2, int minute2);
        std::string getLongestNap();
        void clearBusyTime();
    private:
        int makeTimeToMinute(hour_minute_t time);
        hour_minute_t makeTimeToHourMinute(int minute);
        std::string getResultString(int start, int duration);
    public:
        int day_nu;
    private:
        std::map<int,int> busy_time;

};
void OneDay::clearBusyTime()
{
    busy_time.clear();
}
std::string OneDay::getResultString(int start, int duration)
{
    hour_minute_t s = this->makeTimeToHourMinute(start);
    hour_minute_t d = this->makeTimeToHourMinute(duration);
    std::string start_hour = std::to_string(s.first);
    std::string start_minute = std::to_string(s.second);
    if (start_minute.length() < 2)
        start_minute = "0" + start_minute;
    std::string duration_hour = (d.first == 0)? "":std::to_string(d.first) + " hours and ";
    std::string duration_minute = std::to_string(d.second);

    std::string result = "Day #" + std::to_string(day_nu) + ": the longest nap starts at " 
     + start_hour + ":" + start_minute \
     + " and will last for " + duration_hour + duration_minute + " minutes.";
     return result;
}

int OneDay::makeTimeToMinute(hour_minute_t time)
{
    return time.first * 60 + time.second;
}

hour_minute_t OneDay::makeTimeToHourMinute(int minute)
{
    hour_minute_t result(minute/60, minute%60);
    return result;
}

void OneDay::addBusyTime(int hour1, int minute1, int hour2, int minute2)
{
    int start = makeTimeToMinute(hour_minute_t(hour1, minute1));
    int end = makeTimeToMinute(hour_minute_t(hour2, minute2));
    busy_time[start] = end;
}

std::string OneDay::getLongestNap()
{
    int final_start;
    int final_end;
    int start_minute = makeTimeToMinute(hour_minute_t(10,0));
    int duration = 0;

     for (auto it = busy_time.begin(); it != busy_time.end(); ++it) {
         int temp_start = it->first;
         int temp_end = it->second;
         if ((temp_start - start_minute) > duration) {
             final_start = start_minute;
             final_end = temp_start;
             duration = final_end - final_start;
         }
         start_minute = temp_end;
        
     }
    int day_end = makeTimeToMinute(hour_minute_t(18,0));
    if ((day_end - start_minute) > duration) {
         final_start = start_minute;
         final_end = day_end;
         duration = final_end - final_start;
    }
    return getResultString(final_start, duration);
}

void solve(std::istream & is, std::ostream & os) {
   int count = 0;
   
   std::string line;
    while(true) {
        int num;

        std::getline(is, line);
        if (sscanf(line.c_str(), "%d", &num) == EOF)
            break;
        OneDay day;
        count++;
        day.day_nu = count;

        for (int i = 0; i < num; i++) {
            int h1,h2,m1,m2;
            std::getline(is, line);
            sscanf(line.c_str(), "%d:%d %d:%d", &h1, &m1, &h2, &m2);
            day.addBusyTime(h1, m1, h2, m2);
        }
        std::string result = day.getLongestNap();
        std::cout << result << std::endl;
        day.clearBusyTime();
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
    std::istringstream iss(R"(4
10:00 12:00 Lectures
12:00 13:00 Lunch, like always.
13:00 15:00 Boring lectures...
15:30 17:45 Reading
4
10:00 12:00 Lectures
12:00 13:00 Lunch, just lunch.
13:00 15:00 Lectures, lectures... oh, no!
16:45 17:45 Reading (to be or not to be?)
4
10:00 12:00 Lectures, as everyday.
12:00 13:00 Lunch, again!!!
13:00 15:00 Lectures, more lectures!
15:30 17:15 Reading (I love reading, but should I schedule it?)
1
12:00 13:00 I love lunch! Have you ever noticed it? :)
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(Day #1: the longest nap starts at 15:00 and will last for 30 minutes.
Day #2: the longest nap starts at 15:00 and will last for 1 hours and 45 minutes.
Day #3: the longest nap starts at 17:15 and will last for 45 minutes.
Day #4: the longest nap starts at 13:00 and will last for 5 hours and 0 minutes.
)", oss.str());
}

TEST(uDebug Batman, uva10954)
{
    std::istringstream iss(R"(5
12:01 13:00 Meeting with Lucius Fox
13:00 15:00 Repairing batmobile
15:30 15:31 Posing for Financial Times
11:00 12:00 Exercise
12:00 12:01 Owning Joker
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(Day #1: the longest nap starts at 15:31 and will last for 2 hours and 29 minutes.
)", oss.str());
}

#endif