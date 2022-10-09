#pragma once
#include<iostream>
#include "Card.h"
#include<string>
#include<vector>
#include "Player.h"

//Card definitions
int Card::numCards = 0;

Card::Card(){
    numCards++;
    _description = "default";
    _name = "Card " + to_string(numCards);
    _type = generateType((rand() % 5) + 1);
};

Card::Card(string description, int type, string name): _name(name), _description(description){
    _type = generateType(type);
    numCards++;
};

Card::Card(const Card& e){
    this->_description = e._description; 
    this->_type = e._type; 
    this->_name = e._name; 
};

Card& Card::operator =(const Card& e){
    this->_description = e._description; 
    this->_type = e._type; 
    this->_name = e._name; 
    return *this;
};

ostream& operator<<(std::ostream& stream, Card& e){
    stream << "This is Card " << e.getName() << " of type " << e.getType() << ".\n Description: " << e.getDescription() << endl;
    return stream;
};

Card::~Card(){

};

void Card::play(Hand* hand) {
    cout << "Playing card " << _name << " from hand " << hand->getName() << endl;
    bool isRemoved;
    isRemoved = hand->removeCardFromHand(this);
    if (isRemoved) {
        x->addCardToDeck(this);
        hand->getPlayer()->issueOrder(generateOrderNumber(_type));
    }
    else {
        cout << "Card could not be played" << endl;
    }
};

string Card::getName() {
    return _name;
};

string Card::getDescription() {
    return _description;
};

string Card::getType(){
    return _type;
};

//Deck Definitions
Deck::Deck() {

};

Deck::Deck(vector<Card*> input) : _cardDeck(input){

};

Deck::Deck(const Deck& e) {
    this->_cardDeck = e._cardDeck;
};

Deck& Deck::operator =(const Deck& e) {
    this->_cardDeck = e._cardDeck;
    return *this;
};

void Deck::addCardToDeck(Card* e) {
    _cardDeck.push_back(e);
};

ostream& operator<<(std::ostream& stream, Deck& e) {
    stream << "This is the Deck and it has "<<e._cardDeck.size() << endl;
    return stream;
};

Deck::~Deck() {

};

vector<Card*> Deck::getDeck() {
    return _cardDeck;
}

void Deck::draw(Hand* hand) {
    int max = _cardDeck.size();
    if (_cardDeck.size() > 0) {
        int index = rand() % _cardDeck.size();
        hand->addCardToHand(_cardDeck.at(index));
        _cardDeck.erase(_cardDeck.begin() + index);
    } 
    else{
        cout << "The Deck is empty, you can't draw from it" << endl;
    }
};

//Hand Definitions
int Hand::numHands = 0;
Hand::Hand() {
    numHands++;
    _name = to_string(numHands);
    _player = new Player(new string("Default"));
};

Hand::Hand(vector<Card*> input) : _cardHand(input) {
    _player = new Player(new string("Default"));
    numHands++;
    _name = to_string(numHands);
};

Hand::Hand(Player* e) {
    numHands++;
    _name = to_string(numHands);
    _player = e;
};

Hand::Hand(Player* e, vector<Card*> input) : _cardHand(input) {
    _player = e;
    numHands++;
    _name = to_string(numHands);
};

vector<Card*> Hand::getHand() {
    return _cardHand;
}

string Hand::getName() {
    return _name;
}

Player* Hand::getPlayer() {
    return _player;
}

Hand::Hand(const Hand& e) {
    this->_cardHand = e._cardHand;
};

Hand& Hand::operator =(const Hand& e) {
    this->_cardHand = e._cardHand;
    return *this;
};

ostream& operator<<(std::ostream& stream, Hand& e) {
    stream << "This is the Hand " << e._name << " and it has " << e._cardHand.size() << " and belongs to " << e._player->getName() <<endl;
    return stream;
};

void Hand::setPlayer(Player* e) {
    delete _player;
    _player = e;
};

void Hand::addCardToHand(Card* e) {
    _cardHand.push_back(e);
};

bool Hand::removeCardFromHand(Card* e){
    vector<Card*>::iterator it = find(_cardHand.begin(), _cardHand.end(), e);
    if(it != _cardHand.end()){
        _cardHand.erase(it);
        return true;
    } else{
        cout << "Incorrect instruction, this Card is not in this Hand";
        return false;
    }
}

Hand::~Hand() {
    for (int i = 0; i < _cardHand.size(); i++) {
        x->addCardToDeck(_cardHand.at(i));
    }
};

string generateType(int type) {
    string cardType = "";
    switch (type) {
    case 1:
        cardType = "bomb";
        break;
    case 2:
        cardType = "reinforcement";
        break;
    case 3:
        cardType = "blockade";
        break;
    case 4:
        cardType = "airlift";
        break;
    case 5:
        cardType = "diplomacy";
        break;
    default:
        cardType = "default";
    }

    return cardType;
}

int generateOrderNumber(string type) {
    if (type == "bomb") {
        return 3;
    }
    else if (type == "reinforcement") {
        return 1;
    }
    else if (type == "blockade") {
        return 4;
    }
    else if (type == "airlift") {
        return 5;
    }
    else if (type == "diplomacy") {
        return 6;
    }
    else {
        return 7;
    }
}