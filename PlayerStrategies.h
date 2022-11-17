#pragma once

#include <vector>

#include "Map.h"

using std::vector;

class Territory;

// Abstract strategy class
class PlayerStrategy {
    friend ostream& operator << (ostream&, const PlayerStrategy&);
    public:
        virtual void issueOrder() = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;
        virtual string getStrategyAsString() const = 0;
};

// Concrete strategy classes
class HumanPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        string getStrategyAsString() const;
};

class AggressivePlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        string getStrategyAsString()const;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        string getStrategyAsString() const;
};

class NeutralPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        string getStrategyAsString() const;
};

// ??Not in instructions??
class CheaterPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        string getStrategyAsString() const;
};