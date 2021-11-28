#include <iostream>
#include <vector>
#include <string>
#include "helpers.hpp"

using namespace std;

#pragma once

class Die
{
    int sides;

public:
    Die() : sides{6} {}
    Die(int sides) : sides{sides} {}
    int roll(int rolls = 1)
    {
        int sum = 0;
        while (rolls--)
        {
            sum += (rand() % sides) + 1;
        }
        return sum;
    };
    friend ostream &operator<<(ostream &os, const Die &d)
    {
        return os << "[" << d.sides << "]";
    }
};

class Dice
{
private:
    vector<Die> dice;
    bool average;
    bool best;
    bool constant;
    int constantValue;

public:
    Dice()
    {
        init(1, 6);
    }

    Dice(int n, int s)
    {
        init(n, s);
    }
    
    Dice(string d)
    {
        // this logic can be improved by adding support for parsing best, average, and constant information
        vector<string> parts = tokenize(d, ".");

        int n = stoi(parts[0]);
        int s = stoi(parts[2]);

        init(n, s);
    }

    void init(int n, int s)
    {
        while (n--)
        {
            dice.push_back(Die(s));
        }
    }

    /**
     * @brief Roll the dice
     * 
     * @param rolls 
     * @return int 
     */
    int roll(int rolls = 1)
    {
        vector<int> results;
        while (rolls--)
        {
            for (int i = 0; i < dice.size(); i++)
            {
                results.push_back(dice[i].roll());
            }
        }

        int result = 0;
        if (constant)
        {
            result += constantValue;
        }
        if (average)
        {
            result += calculateAverage(results, rolls);
        }
        else if (best)
        {
            result += calculateBest(results);
        }
        else
        {
            result += calculateSum(results);
        }

        return result;
    }

    /**
     * @brief Calculate the sum of the dice
     * 
     * @param results 
     * @return int 
     */
    int calculateSum(vector<int> results)
    {
        int sum = 0;
        for (int i = 0; i < results.size(); i++)
        {
            sum += results[i];
        }
        return sum;
    }

    /**
     * @brief Calculate the average of the dice
     * 
     * @param results 
     * @param rolls 
     * @return int 
     */
    int calculateAverage(vector<int> results, int rolls)
    {
        return calculateSum(results) / results.size();
    }

    /**
     * @brief Calculate the best of the dice
     * 
     * @param results 
     * @return int 
     */
    int calculateBest(vector<int> results)
    {
        int best = results[0];
        for (int i = 1; i < results.size(); i++)
        {
            if (results[i] > best)
            {
                best = results[i];
            }
        }
        return best;
    }

    friend ostream &operator<<(ostream &os, const Dice &d)
    {
        for (int i = 0; i < d.dice.size(); i++)
        {
            os << d.dice[i];
        }
        return os;
    }
};