#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>
#include <map>

//#define TEST
#ifdef TEST
#include <gtest/gtest.h>
#endif

using namespace std;

enum Direction {
    North,
    East,
    South,
    West,
};

class Map {
public:
    Map() {
    }
    Map(int row, int column) {
        m.resize(row + 1, std::vector<char>(column + 1, 0));
    }
    void setWall(int x, int y) {
        m[x][y] = wall;
    }
    void setRoad(int x, int y) {
        m[x][y] = ' ';
    }
    bool isWall(int x, int y) {
        if (m[x][y] == wall)
            return true;
        return false;
    }
private:
    vector<vector<char>> m;
    int row;
    int column;
    char wall = '*';
};

class Robot {
public:
    Robot(class Map &map) {
        m = map;
    }
    void setPosition(int inputX, int inputY) {
        x = inputX;
        y = inputY;
    }
    int getPositionX() {
        return x;
    }
    int getPositionY() {
        return y;
    }
    enum Direction getDirection() {
        return d;
    }
    void setDirection(enum Direction direction) {
        d = direction;
    }
    void addCommands(const std::vector<char> &commands) {
        cmds.insert(cmds.end(), commands.begin(), commands.end());
    }
    void turnRight() {
        switch (d) {
        case North:
            d = East;
            break;
        case East:
            d = South;
            break;
        case South:
            d = West;
            break;
        case West:
            d = North;
            break;
        }
    }
    void turnLeft() {
        switch (d) {
        case North:
            d = West;
            break;
        case East:
            d = North;
            break;
        case South:
            d = East;
            break;
        case West:
            d = South;
            break;
        }
    }
    void moveForward() {
        int next_x = x;
        int next_y = y;
        switch (d) {
        case North:
            next_x--;
            break;
        case East:
            next_y++;
            break;
        case South:
            next_x++;
            break;
        case West:
            next_y--;
            break;
        }
        if (!m.isWall(next_x, next_y)) {
            x = next_x;
            y = next_y;
        }
    }
    void runCommands() {
        for (auto c: cmds) {
            if (c == 'R')
                turnRight();
            else if (c == 'L')
                turnLeft();
            else if (c == 'F')
                moveForward();
            else if (c == 'Q')
                break;
        }
    }
private:
    class Map m;
    std::vector<char> cmds;
    int x;
    int y;
    enum Direction d;
};

void solve(std::istream & is, std::ostream & os) {

    int count;
    is >> count;
    while(count--) {
        int row, column;
        is >> row >> column;
        is.ignore();

        class Map m(row, column);
        std::string s;
        for (int i = 1; i <= row; i++) {
            getline(is, s);
            for (int j = 1; j <= column; j++) {
                char input = s[j - 1];
                if (input == '*')
                    m.setWall(i, j);
                else
                    m.setRoad(i, j);
            }
        }

        int x, y;
        is >> x >> y;
        is.ignore();

        std::vector<char> commands;
        while (getline(is, s))
        {
            for (size_t i = 0; i < s.size(); ++i)
                commands.push_back(s[i]);
            if (s[s.size() - 1] == 'Q')
                break;
        }

        class Robot r(m);
        r.setPosition(x, y);
        r.setDirection(Direction::North);
        r.addCommands(commands);

        r.runCommands();

        x = r.getPositionX();
        y = r.getPositionY();

        string d;
        switch (r.getDirection()) {
        case North:
            d = "N";
            break;
        case East:
            d = "E";
            break;
        case South:
            d = "S";
            break;
        case West:
            d = "W";
            break;
        }
        os << std::to_string(x) << " " << std::to_string(y) << " " << d << std::endl;
        if (count)
            os << std::endl;
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
#include "uva10377.h"
#endif
