#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;
class Hand;
class Deck;
class Player;

extern Deck* x;

class Card

{
private:
    static int numCards;
    string _description;
    string _type;
    string _name;
    friend ostream& operator<<(std::ostream& stream, Card& e);
public:
    Card();
    Card(string description, int type, string name);
    Card(const Card& e);
    Card& operator =(const Card& e);
    ~Card();

    string getDescription();
    string getType();
    string getName();

    void play(Hand* hand);
};

ostream& operator<<(std::ostream& stream, Card& e);

class Deck
{
private:
    vector<Card*> _cardDeck;
    friend ostream& operator<<(std::ostream& stream, Deck& e);
public:
    Deck();
    Deck(vector<Card*> e);
    Deck(const Deck& e);
    Deck& operator =(const Deck& e);
    ~Deck();
    vector<Card*> getDeck();
    void addCardToDeck(Card* e);
    void draw(Hand* hand);

};

ostream& operator<<(std::ostream& stream, Deck& e);


class Hand
{
private:
    Player* _player;
    string _name;
    static int numHands;
    vector<Card*> _cardHand;
    friend ostream& operator<<(std::ostream& stream, Hand& e);
public:
    Hand();
    Hand(vector<Card*> e);
    Hand(Player* e);
    Hand(Player* e, vector<Card*> v);
    Hand(const Hand& e);
    Hand& operator =(const Hand& e);
    ~Hand();

    Player* getPlayer();
    vector<Card*> getHand();
    string getName();

    void setPlayer(Player* e);

    void addCardToHand(Card* e);
    bool removeCardFromHand(Card* e);
};

ostream& operator<<(std::ostream& stream, Hand& e);

int generateOrderNumber(string type);
string generateType(int type);






