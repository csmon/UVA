#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>

//#define TEST
#ifdef TEST
#include <gtest/gtest.h>
#endif

using namespace std;

class Card {
    public:
        Card(std::string s);
        std::string getCard();
        bool operator== (const class Card &rhs) {
            return (number == rhs.number);
        }
        bool operator<(const class Card &rhs) {
            return (number < rhs.number);
        }
    private:
        int numberOrigToInt(const char c);
        char numberIntToOrig(const int i);
    public:
        int number;
        char suit;
};

Card::Card(std::string s) {
    number = numberOrigToInt(s.at(0));
    suit = s.at(1);
}

std::string Card::getCard() {
    char nu = numberIntToOrig(number);
    std::string s(1, nu);
    return s += suit;
}

int Card::numberOrigToInt(const char c) {
    switch (c) {
    case 'K':
        return 13;
    case 'Q':
        return 12;
    case 'J':
        return 11;
    case 'T':
        return 10;
    case 'A':
        return 1;
    }
    return c - '0';
}

char Card::numberIntToOrig(const int i) {
    switch (i) {
    case 13:
        return 'K';
    case 12:
        return 'Q';
    case 11:
        return 'J';
    case 10:
        return 'T';
    case 1:
        return 'A';
    }
    return i + '0';
}

class PokerRound {
    enum PokerLevel {
        STRAIGHT_FLUSH,
        FOUR_OF_A_KIND,
        FULL_HOUSE,
        FLUSH,
        STRAIGHT,
        THREE_OF_A_KIND,
        TWO_PAIRS,
        ONE_PAIR,
        HIGHEST_CARD,
    };
    public:
        PokerRound(std::string line);
        void generatePossibleHandCards();
        void generateBestCards();
        std::string getCardsStr(std::vector<class Card> cards);
        std::string getResult();
    private:
        std::string levelToStr(PokerLevel);
        void recursiveCombination(int need_drop, int delete_idx_start);
    private:
        std::vector<class Card> cards_on_hand;
        std::vector<class Card> cards_on_deck;
        std::vector<std::vector<class Card>> possible_cards;
        std::vector<int> drops;
        PokerLevel getCategory(std::vector<class Card> & c);
        bool isStraight(std::vector<class Card> & c);
        bool isFlush(std::vector<class Card> & c);
        PokerLevel best_hand;
};

bool PokerRound::isStraight(std::vector<class Card> & cards) {
    int count = 0;

    for (auto it = cards.begin(); it != cards.end() - 1; it++)
        if (((*it).number + 1) == (*(it+1)).number)
            count += 1;
    if (count == 4)
        return true;
    if ((cards[0].number == 1) &&
        (cards[1].number == 10) &&
        (cards[2].number == 11) &&
        (cards[3].number == 12) &&
        (cards[4].number == 13))
        return true;
    return false;
}
bool PokerRound::isFlush(std::vector<class Card> & cards) {
    int same = 0;

    for (auto it = cards.begin(); it != cards.end() - 1; it++)
        if (((*it).suit) == (*(it+1)).suit)
            same += 1;
    if (same == 4)
        return true;

    return false;
}
void PokerRound::recursiveCombination(int need_drop, int delete_idx_start)
{
    if(need_drop == 0)
    {
        // 1->3->5 to 5->3->1
        vector<int> need_drop_cards_idx(drops.rbegin(), drops.rend());
        vector<class Card> temp_cards(cards_on_hand.begin(), cards_on_hand.end());
        for (auto it = need_drop_cards_idx.begin(); it != need_drop_cards_idx.end(); it++)
        {
            temp_cards.erase(temp_cards.begin() + *it);
        }
        int need_number_from_deck = cards_on_hand.size() - temp_cards.size();
        temp_cards.insert(temp_cards.end(), cards_on_deck.begin(), cards_on_deck.begin() + need_number_from_deck);

        possible_cards.push_back(temp_cards);
        return ;
    }

    int len = cards_on_hand.size();
    for (int idx = delete_idx_start; idx < len; idx++)
    {
        drops.push_back(idx);
        recursiveCombination(need_drop - 1, idx + 1);
        drops.pop_back();
    }
}

std::string PokerRound::levelToStr(PokerLevel level) {
    switch(level) {
    case STRAIGHT_FLUSH:
        return "straight-flush";
    case FOUR_OF_A_KIND:
        return "four-of-a-kind";
    case FULL_HOUSE:
        return "full-house";
    case FLUSH:
        return "flush";
    case STRAIGHT:
        return "straight";
    case THREE_OF_A_KIND:
        return "three-of-a-kind";
    case TWO_PAIRS:
        return "two-pairs";
    case ONE_PAIR:
        return "one-pair";
    case HIGHEST_CARD:
        return "highest-card";
    }
    return "highest-card";
}

void PokerRound::generatePossibleHandCards() {
    const int len = cards_on_hand.size();
    for ( int i = 0; i <= len; i++) {
        recursiveCombination(i, 0);
    }
}

void PokerRound::generateBestCards() {
    for (auto it = possible_cards.begin(); it != possible_cards.end(); it++) {
        auto cards = *it;
        std::sort(cards.begin(), cards.end());
        auto tmp = getCategory(cards);
        if (tmp < best_hand)
            best_hand = tmp;
        if (best_hand == STRAIGHT_FLUSH)
            break;
    }
}

PokerRound::PokerLevel PokerRound::getCategory(std::vector<class Card> & cards) {
    bool straight = isStraight(cards);
    bool flush = isFlush(cards);

    if (flush && straight)
        return STRAIGHT_FLUSH;

    // val 1: pair; val 2:three-kind; 4:four-kind
    int same_nu_part1 = 0;
    int same_nu_part2 = 0;
    int *ptr = &same_nu_part1;

    for (auto it = cards.begin(); it != cards.end() - 1; it++)
        if (((*it).number) == (*(it+1)).number) {
                (*ptr)++;
        } else {
            if (same_nu_part1 != 0)
                ptr = &same_nu_part2;
        }

    if (same_nu_part1 == 3)
        return FOUR_OF_A_KIND;
    else if ((same_nu_part1 + same_nu_part2) == 3)
        return FULL_HOUSE;

    if (flush)
        return FLUSH;
    if (straight)
        return STRAIGHT;

    if (same_nu_part1 == 2)
        return THREE_OF_A_KIND;
    if ((same_nu_part1 == 1) && (same_nu_part2 == 1))
        return TWO_PAIRS;
    if ((same_nu_part1 == 1) || (same_nu_part2 == 1))
        return ONE_PAIR;

    return PokerLevel::HIGHEST_CARD;
}

std::string PokerRound::getResult() {
    return "Hand:" + getCardsStr(cards_on_hand) + \
           " Deck:" + getCardsStr(cards_on_deck) + \
           " Best hand: " + levelToStr(best_hand);
}

PokerRound::PokerRound(const std::string line) {
    std::string s = line;
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    auto it = vstrings.begin();
    for (auto it = vstrings.begin(); it != vstrings.begin() + 5; it++) {
        class Card c(*it);
        cards_on_hand.push_back(c);
    }
    for (auto it = vstrings.begin() + 5; it != vstrings.end(); it++) {
        class Card c(*it);
        cards_on_deck.push_back(c);
    }
    best_hand = PokerLevel::HIGHEST_CARD;
}

std::string PokerRound::getCardsStr(std::vector<class Card> cards) {
    std:: string s;
    for (auto it = cards.begin(); it != cards.end(); it++) {
        auto c = *it;
        s += " " + c.getCard();
    }
    return s;
}

void solve(std::istream & is, std::ostream & os) {

    std::string line;
    while(getline(is, line)) {
        class PokerRound r(line);
        r.generatePossibleHandCards();
        r.generateBestCards();
        auto result = r.getResult();
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

TEST( urash16, uva514)
{
    std::istringstream iss(R"(TH JH QC QD QS QH KH AH 2S 6S
2H 2S 3H 3S 3C 2D 3D 6C 9C TH
2H 2S 3H 3S 3C 2D 9C 3D 6C TH
2H AD 5H AC 7H AH 6H 9H 4H 3C
AC 2D 9C 3S KD 5S 4D KS AS 4C
KS AH 2H 3C 4H KC 2C TC 2D AS
AH 2C 9S AD 3C QH KS JS JD KD
6C 9C 8C 2D 7C 2H TC 4C 9S AH
3D 5S 2H QD TD 6S KH 9H AD QH
TH JH QC QD QS QH KH AH 2S 6S
2D 3D 6C 9C TH 2H 2S 3H 3S 3C
2D 9C 3D 6C TH 2H 2S 3H 3S 3C
AH 6H 9H 4H 3C 2H AD 5H AC 7H
5S 4D KS AS 4C AC 2D 9C 3S KD
KC 2C TC 2D AS KS AH 2H 3C 4H
QH KS JS JD KD AH 2C 9S AD 3C
2H TC 4C 9S AH 6C 9C 8C 2D 7C
6S KH 9H AD QH 3D 5S 2H QD TD
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(Hand: TH JH QC QD QS Deck: QH KH AH 2S 6S Best hand: straight-flush
Hand: 2H 2S 3H 3S 3C Deck: 2D 3D 6C 9C TH Best hand: four-of-a-kind
Hand: 2H 2S 3H 3S 3C Deck: 2D 9C 3D 6C TH Best hand: full-house
Hand: 2H AD 5H AC 7H Deck: AH 6H 9H 4H 3C Best hand: flush
Hand: AC 2D 9C 3S KD Deck: 5S 4D KS AS 4C Best hand: straight
Hand: KS AH 2H 3C 4H Deck: KC 2C TC 2D AS Best hand: three-of-a-kind
Hand: AH 2C 9S AD 3C Deck: QH KS JS JD KD Best hand: two-pairs
Hand: 6C 9C 8C 2D 7C Deck: 2H TC 4C 9S AH Best hand: one-pair
Hand: 3D 5S 2H QD TD Deck: 6S KH 9H AD QH Best hand: highest-card
Hand: TH JH QC QD QS Deck: QH KH AH 2S 6S Best hand: straight-flush
Hand: 2D 3D 6C 9C TH Deck: 2H 2S 3H 3S 3C Best hand: full-house
Hand: 2D 9C 3D 6C TH Deck: 2H 2S 3H 3S 3C Best hand: full-house
Hand: AH 6H 9H 4H 3C Deck: 2H AD 5H AC 7H Best hand: flush
Hand: 5S 4D KS AS 4C Deck: AC 2D 9C 3S KD Best hand: two-pairs
Hand: KC 2C TC 2D AS Deck: KS AH 2H 3C 4H Best hand: three-of-a-kind
Hand: QH KS JS JD KD Deck: AH 2C 9S AD 3C Best hand: two-pairs
Hand: 2H TC 4C 9S AH Deck: 6C 9C 8C 2D 7C Best hand: flush
Hand: 6S KH 9H AD QH Deck: 3D 5S 2H QD TD Best hand: one-pair
)", oss.str());
}
#endif
