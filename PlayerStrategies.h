#include <vector>

#include "Map.h"

using std::vector;

// Abstract strategy class
class PlayerStrategy {
    public:
        virtual void issueOrder() = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;

        virtual friend ostream& operator<<(ostream&, HumanPlayerStrategy) = 0;
};

// Concrete strategy classes
class HumanPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();

        friend ostream& operator<<(ostream&, HumanPlayerStrategy);
};

class AggressivePlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();

        friend ostream& operator<<(ostream&, HumanPlayerStrategy);
};

class BenevolentPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();

        friend ostream& operator<<(ostream&, HumanPlayerStrategy);
};

class NeutralPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();

        friend ostream& operator<<(ostream&, HumanPlayerStrategy);
};

// ??Not in instructions??
class CheaterPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();

        friend ostream& operator<<(ostream&, HumanPlayerStrategy);
};