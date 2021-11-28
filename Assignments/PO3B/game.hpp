#include <iostream>
#include <fstream>
#include <system_error>
#include "fighter.hpp"

using namespace std;

// running output and summary files
ofstream outfile("output.txt");
ofstream summary("summary.txt");

// class to manage attackers
class Attackers
{
    // alive and expired attacker queues
    vector<BaseFighter *> alive;
    vector<BaseFighter *> expired;

public:
    // add a new attacker to the alive queue
    void addNewFighter(BaseFighter *fighter)
    {
        alive.push_back(fighter);
    }

    // return the number of alive attackers
    int getAlive()
    {
        return alive.size();
    }

    // heals active attacker
    void healActive()
    {
        // only for active fighter
        alive.front()->heal();
    }

    // return active attacker
    BaseFighter *getActive()
    {
        return alive.front();
    }

    // returns damage dealt by active fighter
    double attack()
    {
        return this->getActive()->attack();
    }

    // returns total number of attacks including expired
    int getTotalFighters()
    {
        return alive.size() + expired.size();
    }

    // expires active fighter by removing from alive queue and adding to expired queue
    void killActive()
    {
        auto &fighter = alive.front();
        alive.erase(alive.begin());
        expired.push_back(fighter);
    }
};

// helper function to get a fighter by its type
BaseFighter *getFighterByType(string type)
{
    if (type == "warrior")
    {
        return new Warrior;
    }
    else if (type == "wizard")
    {
        return new Wizard;
    }
    else if (type == "archer")
    {
        return new Archer;
    }
    else if (type == "elf")
    {
        return new Elf;
    }
    else if (type == "dragonborn")
    {
        return new DragonBorn;
    }
    else
    {
        outfile << "Invalid fighter type: " << type << endl;
        exit(1);
    }
}

// class to manage defenders
class Defenders
{
    // queue to manage alive and expired defenders
    vector<BaseFighter *> alive;
    vector<BaseFighter *> expired;

public:
    // adds one defender of each type to alive queue
    void addSetOfFighters()
    {
        alive.push_back(new Warrior);
        alive.push_back(new Wizard);
        alive.push_back(new Archer);
        alive.push_back(new Elf);
        alive.push_back(new DragonBorn);
    }

    // returns the number of alive defenders
    int getAlive()
    {
        return alive.size();
    }

    // returns the number of total defenders
    int getTotalFighters()
    {
        return alive.size() + expired.size();
    }

    // heal all alive defenders
    void healAlive()
    {
        for (auto &fighter : alive)
        {
            fighter->heal();
        }
    }

    // returns attack damage of active defender
    double attack()
    {
        return this->getActive()->attack();
    }

    // get active defender
    BaseFighter *getActive()
    {
        return alive.front();
    }

    // kills active defender by removing it from alive queue and adding to expired queue
    void killActive()
    {
        auto &fighter = alive.front();
        alive.erase(alive.begin());
        expired.push_back(fighter);
    }

    // checks if defender should swap, and swaps if possible (only for active defender)
    bool trySwap()
    {
        // logic for swap
        // check if we want to swap
        // if health of active fighter is less than 20% of max health, we swap with fighter of same type
        // if health of new defender is more than 50% of max health
        if (this->getActive()->getHealth() < this->getActive()->getMaxHealth() / 5)
        {
            // find fighter of same type with max health
            int index = getFighterWithMaxHp(this->getActive()->getName());
            // we should not swap with active fighter and waste our turn
            if (index > 0 && alive[index]->getHealth() > this->getActive()->getMaxHealth() / 2)
            {
                swap(alive[0], alive[index]);
                return true;
            }
        }
        return false;
    }

    // given a type of defender, returns index of defender with max health
    // if no defender of given type is alive, returns -1
    int getFighterWithMaxHp(string name)
    {
        int fighterIndex = -1;
        for (int i = 0; i < alive.size(); i++)
        {
            if (alive[i]->getName() == name)
            {
                if (fighterIndex != -1)
                {
                    if (alive[i]->getHealth() > alive[fighterIndex]->getHealth())
                    {
                        fighterIndex = i;
                    }
                }
                else
                {
                    fighterIndex = i;
                }
            }
        }
        return fighterIndex;
    }
};

// game class to setup and play a game
class Game
{
    // attackers
    Attackers attackers;
    // defenders
    Defenders defenders;
    // current round number
    int round;
    // winner of game
    string winner;

public:
    // constructor to create a game object and setup by creating characters (attackers and defenders)
    Game(string filename)
    {
        round = 0;
        // create attackers
        addAttackers(filename);
        // create defenders
        addDefenders();
    }

    void start()
    {

        // game loop
        while (attackers.getAlive() > 0 && defenders.getAlive() > 0)
        {
            // active attacker and defender pointers
            BaseFighter *activeAttacker = attackers.getActive();
            BaseFighter *activeDefender = defenders.getActive();

            // increase round number
            round++;
            // print round number in running output file
            outfile << "Round " << round << endl;

            // attacker's turn
            outfile << "\tAttacker's turn" << endl;
            // printHealth(activeAttacker, activeDefender);
            // get damage dealt by attacker
            double damage = activeAttacker->attack();
            // print damage dealt by attacker to running file
            outfile << "\t\tAttacker deals " << damage << " damage to defender" << endl;
            // deal damage to defender
            activeDefender->takeDamage(damage);
            // printHealth(activeAttacker, activeDefender);
            // check if defender is still alive after taking damage from attacker
            if (!activeDefender->isAlive())
            {
                // if defender is dead, print message to running file and move to expired queue
                outfile << "\t\tkilling defender" << endl;
                defenders.killActive();
            }
            // heal active attacker
            attackers.healActive();

            // refresh activeAttacker and activeDefender pointers after battle
            activeAttacker = attackers.getActive();
            activeDefender = defenders.getActive();
            // defender's turn
            // swap or attack
            outfile << "\tDefender's turn" << endl;
            // check if defender should swap, if swaps, then defender can't attack in this round
            if (defenders.trySwap())
            {
                activeDefender = defenders.getActive();
                outfile << "\t\tChoose to swap" << endl;
                // printHealth(activeAttacker, activeDefender);
            }
            else
            {
                // outfile << "Choose to attack" << endl;
                // printHealth(activeAttacker, activeDefender);
                // get damage dealt by defender
                damage = activeDefender->attack();
                // print damage dealt by defender to running file and deal damage to attacker
                outfile << "\t\tDefender deals " << damage << " damage to attacker" << endl;
                activeAttacker->takeDamage(damage);
                // printHealth(activeAttacker, activeDefender);
                // check if attacker is still alive after taking damage from defender
                if (!activeAttacker->isAlive())
                {
                    // if attacker is dead, print message to running file and move to expired queue
                    outfile << "\t\tkilling attacker" << endl;
                    attackers.killActive();
                }
            }
            // heal all alive defenders
            defenders.healAlive();

            outfile << endl;
        }

        // determine and set winner, print resutl to output file
        if (attackers.getAlive() > 0)
        {
            winner = "Attackers";
            outfile << "Attackers win!" << endl;
        }
        else
        {
            winner = "Defenders";
            outfile << "Defenders win!" << endl;
        }

        // print summary of game to summary file
        printSummary();

        // close files
        outfile.close();
        summary.close();
    }

    // reads attackers by name from input file
    // and creates attackers
    void addAttackers(string file_name)
    {
        ifstream infile;
        infile.open(file_name);

        string attacker;

        while (!infile.eof())
        {
            infile >> attacker;
            transform(attacker.begin(), attacker.end(), attacker.begin(), ::tolower);
            attackers.addNewFighter(getFighterByType(attacker));
        }

        // close file
        infile.close();
        outfile << "Attackers added: " << attackers.getAlive() << endl;
    }

    // creates defenders based on number of attackers
    void addDefenders()
    {
        // add one set of players every 100 attackers
        int toAdd = attackers.getAlive() / 100;

        if (attackers.getAlive() % 100 != 0)
        {
            toAdd++;
        }

        // create and add defenders
        for (int i = 0; i < toAdd; i++)
        {
            defenders.addSetOfFighters();
        }

        outfile << "Attackers added: " << attackers.getAlive() << endl;
    }

    // prints game summary to summary file
    void printSummary()
    {
        summary << "Total Attackers: " << attackers.getTotalFighters() << endl;
        summary << "Total Defenders: " << defenders.getTotalFighters() << endl;
        summary << "Total Rounds: " << round << endl;
        summary << "Attackers alive: " << attackers.getAlive() << endl;
        summary << "Defenders alive: " << defenders.getAlive() << endl;
        summary << "Winner: " << winner << endl;
    }

    void printHealth(BaseFighter *fighter1, BaseFighter *fighter2)
    {
        outfile << "Attacker: " << fighter1->getHealth() << "\tDefender: " << fighter2->getHealth() << endl;
    }
};
