#include <iostream>
#include <string>
#include <vector>

#include "dice.hpp"
#include "helpers.hpp"

using namespace std;

#pragma once

class Weapon
{
public:
    string name;   // name of weapon
    string damage; // damage per roll or "use"
    Dice *die;
    /**
     * @brief Construct a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     */
    Weapon()
    {
        name = "Fists&Feet";
        damage = "1.d.4";
        die = new Dice(damage);
    }
    /**
     * @brief Overloaded Constructor for a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     * @param choices-vector of string "die" choices like {"2.d.8","2.d.10","3.d.4"}
     */
    Weapon(vector<string> choices)
    {
        name = "Fists&Feet";
        damage = randomChoice(choices);
        die = new Dice(damage);
    }

    /**
     * @brief fuction that determines the damage of the weapon by rolling dice
     * 
     * @return damage dealt by weapon
     */
    double use()
    {
        return die->roll();
    }

    friend ostream &operator<<(ostream &os, const Weapon &w)
    {
        return os << "[" << w.name << " , " << w.damage << "]";
    }
};

class Sword : public Weapon
{
public:
    /**
     * @brief Construct a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     */
    Sword()
    {
        name = "Sword";
        damage = randomChoice({"1.d.12", "2.d.6", "3.d.4"});
        die = new Dice(damage);
    }

    /**
     * @brief Overloaded Constructor for a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     * @param choices-vector of string "die" choices like {"2.d.8","2.d.10","3.d.4"}
     */
    Sword(vector<string> choices)
    {
        name = "Sword";
        damage = randomChoice(choices);
        die = new Dice(damage);
    }
};

class Bow : public Weapon
{
public:
    /**
     * @brief Construct a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     */
    Bow()
    {
        name = "Bow";
        damage = randomChoice({"1.d.8", "2.d.4", "1.d.10"});
        die = new Dice(damage);
    }

    /**
     * @brief Overloaded Constructor for a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     * @param choices-vector of string "die" choices like {"2.d.8","2.d.10","3.d.4"}
     */
    Bow(vector<string> choices)
    {
        name = "Bow";
        damage = randomChoice(choices);
        die = new Dice(damage);
    }
};

class MagicSpell : public Weapon
{
public:
    /**
     * @brief Construct a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     */
    MagicSpell()
    {
        name = "Magic Spell";
        damage = randomChoice({"1.d.20", "2.d.10", "3.d.6", "5.d.4"});
        die = new Dice(damage);
    }

    /**
     * @brief Overloaded Constructor for a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     * @param choices-vector of string "die" choices like {"2.d.8","2.d.10","3.d.4"}
     */
    MagicSpell(vector<string> choices)
    {
        name = "Magic Spell";
        damage = randomChoice(choices);
        die = new Dice(damage);
    }
};

class MagicWeapon : public Weapon
{
public:
    /**
     * @brief Construct a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     */
    MagicWeapon()
    {
        name = "Magic Weapon";
        damage = randomChoice({"1.d.4", "1.d.6"});
        die = new Dice(damage);
    }

    /**
     * @brief Overloaded Constructor for a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     * @param choices-vector of string "die" choices like {"2.d.8","2.d.10","3.d.4"}
     */
    MagicWeapon(vector<string> choices)
    {
        name = "Magic Weapon";
        damage = randomChoice(choices);
        die = new Dice(damage);
    }
};

class FireWeapon : public Weapon
{
public:
    /**
     * @brief Construct a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     */
    FireWeapon()
    {
        name = "Fire Weapon";
        damage = randomChoice({"1.d.6", "1.d.8"});
        die = new Dice(damage);
    }

    /**
     * @brief Overloaded Constructor for a new Base Weapon object
     *  Also invokes the Dice class constructor with the "die" type
     * @param choices-vector of string "die" choices like {"2.d.8","2.d.10","3.d.4"}
     */
    FireWeapon(vector<string> choices)
    {
        name = "Fire Weapon";
        damage = randomChoice(choices);
        die = new Dice(damage);
    }
};