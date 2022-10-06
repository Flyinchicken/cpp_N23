#pragma once
#include<string>
#include<iostream>
#include<vector>
using namespace std;

class Card

{
private:
    string* _description;
    string* _type;
    string* _name;
public:
    Card();
    Card(string* description, string* type, string* name);
    Card(const Card& e);
    Card& operator =(const Card& e);
    friend ostream& operator<<(std::ostream& stream, Card& e);
    ~Card();

    string getDescription();
    string getType();
    string getName();

    void play();
};

class Deck
{
private:
    vector<Card*> _cardDeck;
public:
    Deck();
    Deck(vector<Card*> e);
    Deck(const Deck& e);
    Deck& operator =(const Deck& e);
    friend ostream& operator<<(std::ostream& stream, Deck& e);
    ~Deck();

    void draw();
};

class Hand
{
private:
    vector<Card*> _cardHand;
    friend ostream& operator<<(std::ostream& stream, const Hand& e);
public:
    Hand();
    Hand(vector<Card*> e);
    Hand(const Hand& e);
    Hand& operator =(const Hand& e);
    ~Hand();
};





