#pragma once

#include <vector>

#include "Map.h"

using std::vector;

class Territory;

// Abstract strategy class
class PlayerStrategy {
    public:
        virtual void issueOrder() = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;
};

// Concrete strategy classes
class HumanPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
};

class AggressivePlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
};

class NeutralPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
};

// ??Not in instructions??
class CheaterPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();

        friend ostream& operator<<(ostream&, PlayerStrategy);
};