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

class CardGame {
public:
    enum game_result {
        UNKNOW,
        WIN,
        DRAW,
        LOSS,
    };

    CardGame(std::deque<int> deck) {
        hand = deck;
        r = UNKNOW;
        dealt_times = 0;
    };

    enum game_result get_result() {
        return r;
    };

    void set_result(enum game_result result) {
        r = result;
    };

    typedef std::vector<std::deque<int> > snapshot;
    std::map<snapshot, bool> all_snapshot;
    std::deque<int> hand, pile[7];
    int dealt_times;
    enum game_result r;
};

class Person {
    enum snapshot_status {
        ADD_SUCCESS,
        ALREADY_EXIST,
    };
    enum pickup_result {
        THREE_CARDS_PICKED,
        NO_CARD_PICKED,
    };
public:
    void startUva246(class CardGame &g) {

        for (int i = 0; i < 7; i++) {
            deal_to_pile(g, i);
        }
        add_snapshot(g);
        int idx = 0;

        while (1) {

            if(is_all_pile_empty(g)) {
                g.set_result(CardGame::WIN);
                break;
            }

            while (g.pile[idx].empty())
                idx = (idx + 1) % 7;

            deal_to_pile(g, idx);

            if (ALREADY_EXIST == add_snapshot(g)) {
                g.set_result(CardGame::DRAW);
                g.dealt_times--;
                break;
            }

            if (g.pile[idx].size() > 2) {
                while (THREE_CARDS_PICKED == pickup_three_card(g.pile[idx], g.hand));
            }

            if (g.hand.empty()) {
                g.set_result(CardGame::LOSS);
                break;
            }
            idx = (idx + 1) % 7;
        }
    };

    std::string getUva246Answer(const class CardGame &g) {
        std::string result;
        if (g.r == CardGame::WIN)
            result = "Win : ";
        else if (g.r == CardGame::LOSS)
            result = "Loss: ";
        else if (g.r == CardGame::DRAW)
            result = "Draw: ";
        return result + std::to_string(g.dealt_times);
    };

private:
    void deal_to_pile(class CardGame &g, const int idx) {
        g.pile[idx].push_back(g.hand.front());
        g.hand.pop_front();
        g.dealt_times++;
    }

    bool is_all_pile_empty(class CardGame &g) {
        bool all_empty = true;
        for (int i = 0; i < 7; i++)
            if (!g.pile[i].empty())
                all_empty  = false;
        if (all_empty == true)
            return true;
        return false;
    }

    enum pickup_result pickup_three_card(std::deque<int> &q, std::deque<int> &hand) {
        if (q.size() < 3)
            return NO_CARD_PICKED;
        int first = q.front(), last = q.back();
        q.pop_front(), q.pop_back();
        if (first + q.front() + last == 10 || first + q.front() + last == 20 || first + q.front() + last == 30) {
            hand.push_back(first);
            hand.push_back(q.front());
            hand.push_back(last);
            q.pop_front();
            return THREE_CARDS_PICKED;
        }
        if (first + q.back() + last == 10 || first + q.back() + last == 20 || first + q.back() + last == 30) {
            hand.push_back(first);
            hand.push_back(q.back());
            hand.push_back(last);
            q.pop_back();
            return THREE_CARDS_PICKED;
        }
        q.push_front(first);
        first = q.back();
        q.pop_back();
        if (first + q.back() + last == 10 || first + q.back() + last == 20 || first + q.back() + last == 30) {
            hand.push_back(q.back());
            hand.push_back(first);
            hand.push_back(last);
            q.pop_back();
            return THREE_CARDS_PICKED;
        }
        q.push_back(first), q.push_back(last);
        return NO_CARD_PICKED;
    };

    enum snapshot_status add_snapshot(class CardGame &g) {
        CardGame::snapshot tmp = { g.hand };
        for (int i = 0; i < 7; i++)
            tmp.push_back(g.pile[i]);
        if (g.all_snapshot[tmp])
            return ALREADY_EXIST;

        g.all_snapshot[tmp] = 1;
        return ADD_SUCCESS;
    };
};

void solve(std::istream & is, std::ostream & os) {

    int card;
    while(is >> card) {
        if (card == 0)
            break;
        std::deque<int> d;
        d.push_back(card);
        for (int i = 1; i < 52; i++) {
            is >> card;
            d.push_back(card);
        }

        class CardGame g(d);
        class Person chunhung;

        chunhung.startUva246(g);
        std::string result = chunhung.getUva246Answer(g);
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
#include "uva246.h"
#endif
