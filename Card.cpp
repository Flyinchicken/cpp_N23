#pragma once
#include<iostream>
#include "Card.h"
#include<string>
#include<vector>

//Card definitions
int Card::numCards = 0;

Card::Card(){
    numCards++;
    _description = "default";
    _name = "Card " + to_string(numCards);
    _type = "default";
    cout << "card Created" <<endl;
};

Card::Card(string description, string type, string name): _name(name), _description(description), _type(type){
    numCards++;
    cout <<"card created" <<endl;
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
    //Create order
    hand->removeCardFromHand(this);
    x->addCardToDeck(this);
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
    cout << "Deck Created" << endl;
};

Deck::Deck(vector<Card*> input) : _cardDeck(input){
    cout << "Deck created" << endl;
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
    cout << "Hand Created" << endl;
};

Hand::Hand(vector<Card*> input) : _cardHand(input) {
    numHands++;
    _name = to_string(numHands);
    cout << "Hand created" << endl;
};

vector<Card*> Hand::getHand() {
    return _cardHand;
}

string Hand::getName() {
    return _name;
}

Hand::Hand(const Hand& e) {
    this->_cardHand = e._cardHand;
};

Hand& Hand::operator =(const Hand& e) {
    this->_cardHand = e._cardHand;
    return *this;
};

ostream& operator<<(std::ostream& stream, Hand& e) {
    stream << "This is the Hand " << e._name << " and it has " << e._cardHand.size() << endl;
    return stream;
};

void Hand::addCardToHand(Card* e) {
    _cardHand.push_back(e);
};

void Hand::removeCardFromHand(Card* e){
    vector<Card*>::iterator it = find(_cardHand.begin(), _cardHand.end(), e);
    if(it != _cardHand.end()){
        _cardHand.erase(it);
    } else{
        cout << "Incorrect instruction, this Card is not in this Hand";
    }
}

Hand::~Hand() {
    for (int i = 0; i < _cardHand.size(); i++) {
        x->addCardToDeck(_cardHand.at(i));
    }
};