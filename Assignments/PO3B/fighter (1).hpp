#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "weapon.hpp"
#include "helpers.hpp"

using namespace std;

#pragma once

class BaseFighter
{
protected:
    string name;
    Weapon *weapon;
    double health;
    double maxHealth;
    double regen;

public:
    /**
     * @brief Construct a new Base Fighter object
     * 
     */
    BaseFighter()
    {
        name = "None";
        weapon = new Weapon;
        health = rand() % 6 + 3; // random from 3 - 8
        maxHealth = 100;
        regen = (rand() % 61 + 15) / 100.0; // random from 0.15 - 0.75
    }

    virtual double attack()
    {
        return weapon->use();
    }

    void takeDamage(double damage)
    {
        health -= damage;
    }

    void heal()
    {
        health += regen;
    }

    bool isAlive()
    {
        return health > 0;
    }

    // get current health
    double getHealth()
    {
        return health;
    }

    // return max health of fighter
    double getMaxHealth()
    {
        return maxHealth;
    }

    // returns the name of the fighter
    string getName()
    {
        return name;
    }

    /**
     * @brief overloads the << operator to print the BaseFighter object
     * 
     * @param os output stream
     * @param f BaseFighter object
     * @return ostream& 
     */
    friend ostream &operator<<(ostream &os, const BaseFighter &f)
    {
        return os << "[" << f.name << " , " << *f.weapon << "]";
    }
};

class Warrior : public BaseFighter
{
public:
    /**
     * @brief Construct a new Warrior object with Sword as weapon
     * 
     */
    Warrior()
    {
        name = "Warrior";
        weapon = new Sword;
    }
};

class Wizard : public BaseFighter
{
public:
    /**
     * @brief Construct a new Wizard object with MagicSpell as weapon
     * 
     */
    Wizard()
    {
        name = "Wizard";
        weapon = new MagicSpell;
    }
};

class Archer : public BaseFighter
{
public:
    /**
     * @brief Construct a new Archer object with Bow as weapon
     * 
     */
    Archer()
    {
        name = "Archer";
        weapon = new Bow;
    }
};

class Elf : public BaseFighter
{
    Weapon *weapon2;

public:
    /**
     * @brief Construct a new Elf object with MagicSpell as primary weapon and Sword as secondary weapon
     * 
     */
    Elf()
    {
        name = "Elf";
        weapon = new MagicSpell;
        weapon2 = new Sword;
    }

    // return damage that can be dealt by elf
    double attack()
    {
        return weapon->use() + weapon2->use();
    }
};

class DragonBorn : public BaseFighter
{
    Weapon *weapon2;

public:
    /**
     * @brief Construct a new DragonBorn object with MagicSpell as primary weapon and FireWeapon as secondary weapon
     * 
     */
    DragonBorn()
    {
        name = "DragonBorn";
        weapon = new MagicSpell;
        weapon2 = new FireWeapon;
    }

    // return damage that can be dealt by DragonBorn 
    double attack()
    {
        return weapon->use() + weapon2->use();
    }
};