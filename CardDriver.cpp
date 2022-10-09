#include <iostream>
#include "Card.h"
#include<string>
using namespace std;

Deck* x = new Deck();

int main()
{
    std::cout << "Welcome everyone!" << std::endl;
    for (int i = 0; i < 50; i++) {
        x->addCardToDeck(new Card());
        vector<Card*> v= x->getDeck();
        cout << *v.at(i) <<endl;
    }

    Hand* myHand = new Hand();

    for (int i = 0; i < 50; i++) {
        x->draw(myHand);
    }

    cout << *x << endl;
    cout << *myHand << endl;

    for (int i = 0; i < 50; i++) {
        vector<Card*> t = myHand->getHand();
        t.at(0)->play(myHand);
    }

    cout << *x << endl;
    cout << *myHand << endl;

    /* vector<Card*> v;
    for (int i = 0; i < 50; i++) {
        v.push_back(new Card());
        cout << *v.at(i);
    }
    Hand* myHand = new Hand(v);
    cout << *myHand;
    
    Card* testCard = new Card();
    cout << *testCard;
    myHand->addCardToHand(testCard);
    cout << *myHand;

    cout << *x;
    testCard->play(myHand);
    cout << *myHand;

    cout << *x;
    delete myHand;
    myHand = NULL;
    cout << *x;
    x->draw(myHand); */
}

void testCards() {
    cout << "test" << endl;
}