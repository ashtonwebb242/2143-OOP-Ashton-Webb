/*
Author: Ashton Webb
Email: ashtonwebb46@gmail.com
Program : 3A
Course: 2143
Semester Fall 2021


Description: This Program provides players with either rock, paper, scissors, lizard or spock and lets them battle.
*/





#include <iostream>
#include <functional> // needed for `bind`
#include <map>
#include <random>
#include <string>

#define ROCK u8"\U0001F5FB"
#define PAPER u8"\U0001F4C3"
#define SCISSORS u8"\U0001F52A"
#define LIZARD u8"\U0001F438"
#define SPOCK u8"\U0001F596"

using namespace std;

/**
 * Hands
 * 
 * @description: A static class that only has references to
 *      emojis for printing out Rock Paper Scissors Lizard Spock
 * 
 * @methods:
 *      string RandHand()   : returns a random hand (emoji) 
 *      string Rock()       : returns the emoji for "rock" 
 *      string Paper()      : returns the emoji for "paper" 
 *      string Scissors()   : returns the emoji for "scissors" 
 *      string Lizard()     : returns the emoji for "lizard" 
 *      string Spock()      : returns the emoji for "spock" 
 */
struct Hands
{
    const string rock = ROCK;
    const string paper = PAPER;
    const string scissors = SCISSORS;
    const string lizard = LIZARD;
    const string spock = SPOCK;

    static map<string, string> Emojis; // stl map
    //         name  , emoji

    static map<string, string> Names; // stl map
    //         emoji  , name

    static string RandHand()
    {
        auto it = Emojis.begin(); // iterator to front of map

        std::advance(it, rand() % Emojis.size()); // advance some random amnt
                                                  //   of steps

        string random_hand = it->second; // grab emoji from map

        return random_hand; // return rand emoji
    }

    static string Rock()
    {
        return Emojis["rock"];
    }
    static string Paper()
    {
        return Emojis["paper"];
    }
    static string Scissors()
    {
        return Emojis["scissors"];
    }
    static string Lizard()
    {
        return Emojis["lizard"];
    }
    static string Spock()
    {
        return Emojis["spock"];
    }
};

// initialize static data member for
// hands struct (class)
map<string, string> Hands::Emojis = {
    {"rock", ROCK},
    {"paper", PAPER},
    {"scissors", SCISSORS},
    {"lizard", LIZARD},
    {"spock", SPOCK}};
// initialize static data member for
// hands struct (class)
map<string, string> Hands::Names = {
    {ROCK, "rock"},
    {PAPER, "paper"},
    {SCISSORS, "scissors"},
    {LIZARD, "lizard"},
    {SPOCK, "spock"}};

/**
 * Player
 * 
 * @description: A class that represents a player in 
 *      Rock Paper Scissors Lizard Spock game
 * 
 * @methods:
 *      Player(string name) : constructor that creates a player with given name
 *          and randomly intializes two weapons from 5 available weapons
 */
struct Player
{
    string weapon1;
    string weapon2;
    // other possible stuff
    string name;

    /**
     * Constructor guarantees a player has two different "weapons"
     */
    Player(string name)
    {
        this->name = name;
        weapon1 = Hands::RandHand();
        weapon2 = Hands::RandHand();

        while (weapon2 == weapon1)
        {
            weapon2 = Hands::RandHand();
        }
    }

    /**
     * Default constructor
     */
    Player() {}
    // other possible methods
};

/**
 * Rock Paper Scissors Lizard Spock
 * 
 * @description: A class to run the rock papers scissors game
 * 
 * Scissors cuts Paper
 * Paper covers Rock
 * Rock crushes Lizard
 * Lizard poisons Spock
 * Spock smashes Scissors
 * Scissors decapitates Lizard
 * Lizard eats Paper
 * Paper disproves Spock
 * Spock vaporizes Rock
 * Rock crushes Scissors
 * 
 * 
 * @methods:
 *    RPSLS(): constructor that creates a game with two players
 *    void reset_game(): resets the game
 *    void start(): starts the game
 *    void fight(string weapon1, string weapon2): given two weapons, determine which player wins 
 *          or if its a tie
 */
class RPSLS : public Hands
{
    Player player1;
    Player player2;
    Player winner;
    bool is_tie;

public:
    RPSLS()
    {
        this->is_tie = false;
        player1 = Player("P1");
        player2 = Player("P2");
    }
    void reset_game();
    void start();
    void fight(string weapon1, string weapon2);
};

/**
 * Public : start
 * 
 * Description:
 *      Starts the game. Players fight using their weapons. If a tie occurs,
 *      they fight using second weapon. If a tie occurs again, the game is a tie.
 *      Prints the results of the game.
 */
void RPSLS::start()
{
    this->fight(player1.weapon1, player2.weapon1);
    if (this->is_tie)
    {
        this->is_tie = false;
        this->fight(player1.weapon2, player2.weapon2);
    }

    if (this->is_tie)
    {
        cout << "Game Tied" << endl;
    }
    else
    {
        cout << "Winner: " << this->winner.name << endl;
    }
    cout << endl;
}

/**
 * Public : reset_game
 * 
 * Description:
 *      Resets the game. Intitializes the players with new weapons
 */
void RPSLS::reset_game()
{
    this->is_tie = false;
    player1 = Player(this->player1.name);
    player2 = Player(this->player2.name);
}

/**
 * Public : fight
 * 
 * Description:
 *      Given two weapons, determine which player wins or if its a tie and 
 *      prints out the result
 * 
 * Params:
 *      string    :  weapon of first player
 *      string    :  weapon of second player
 */
void RPSLS::fight(string emoji_weapon1, string emoji_weapon2)
{
    string weapon1 = Hands::Names[emoji_weapon1];
    string weapon2 = Hands::Names[emoji_weapon2];
    if (weapon1 == weapon2)
    {
        is_tie = true;
    }
    else
    {
        if (weapon1 == "rock")
        {
            string emoji1 = Hands::Rock();
            if (weapon2 == "scissors" || weapon2 == "lizard")
            {
                string emoji2;
                if (weapon2 == "scissors")
                    emoji2 = Hands::Scissors();
                else
                    emoji2 = Hands::Lizard();
                winner = player1;
                cout << emoji1 << " crushes " << emoji2 << endl;
            }
            else
            {
                winner = player2;
                if (weapon2 == "paper")
                {
                    string emoji2 = Hands::Paper();
                    cout << emoji2 << " covers " << emoji1 << endl;
                }
                else
                {
                    string emoji2 = Hands::Spock();
                    cout << emoji2 << " vaporizes " << emoji1 << endl;
                }
            }
        }
        else if (weapon1 == "scissors")
        {
            string emoji1 = Hands::Scissors();
            if (weapon2 == "paper")
            {
                string emoji2 = Hands::Paper();
                winner = player1;
                cout << emoji1 << " cuts " << emoji2 << endl;
            }
            else if (weapon2 == "lizard")
            {
                string emoji2 = Hands::Lizard();
                winner = player1;
                cout << emoji1 << " decapitates " << emoji2 << endl;
            }
            else
            {
                winner = player2;
                if (weapon2 == "rock")
                {
                    string emoji2 = Hands::Rock();
                    cout << emoji2 << " crushes " << emoji1 << endl;
                }
                else
                {
                    string emoji2 = Hands::Spock();
                    cout << emoji2 << " smashes " << emoji1 << endl;
                }
            }
        }
        else if (weapon1 == "paper")
        {
            string emoji1 = Hands::Paper();
            if (weapon2 == "rock")
            {
                string emoji2 = Hands::Rock();
                winner = player1;
                cout << emoji1 << " covers " << emoji2 << endl;
            }
            else if (weapon2 == "spock")
            {
                string emoji2 = Hands::Spock();
                winner = player1;
                cout << emoji1 << " disproves " << emoji2 << endl;
            }
            else
            {
                winner = player2;
                if (weapon2 == "scissors")
                {
                    string emoji2 = Hands::Scissors();
                    cout << emoji2 << " cuts " << emoji1 << endl;
                }
                else
                {
                    string emoji2 = Hands::Lizard();
                    cout << emoji2 << " eats " << emoji1 << endl;
                }
            }
        }
        else if (weapon1 == "lizard")
        {
            string emoji1 = Hands::Lizard();
            if (weapon2 == "spock")
            {
                string emoji2 = Hands::Spock();
                winner = player1;
                cout << emoji1 << " poisons " << emoji2 << endl;
            }
            else if (weapon2 == "paper")
            {
                string emoji2 = Hands::Paper();
                winner = player1;
                cout << emoji1 << " eats " << emoji2 << endl;
            }
            else
            {
                winner = player2;
                if (weapon2 == "scissors")
                {
                    string emoji2 = Hands::Scissors();
                    cout << emoji2 << " decapitates " << emoji1 << endl;
                }
                else
                {
                    string emoji2 = Hands::Rock();
                    cout << emoji2 << " crushes " << emoji1 << endl;
                }
            }
        }
        else
        {
            string emoji1 = Hands::Spock();
            if (weapon2 == "rock")
            {
                string emoji2 = Hands::Rock();
                winner = player1;
                cout << emoji1 << " vaporizes " << emoji2 << endl;
            }
            else if (weapon2 == "scissors")
            {
                string emoji2 = Hands::Scissors();
                winner = player1;
                cout << emoji1 << " smashes " << emoji2 << endl;
            }
            else
            {
                winner = player2;
                if (weapon2 == "lizard")
                {
                    string emoji2 = Hands::Lizard();
                    cout << emoji2 << " poisons " << emoji1 << endl;
                }
                else
                {
                    string emoji2 = Hands::Paper();
                    cout << emoji2 << " disproves " << emoji1 << endl;
                }
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    cout << "Welcome to Rock Paper Scissors Lizard Spock" << endl;
    int num_rounds = 25;
    RPSLS game;
    for (int round = 1; round <= num_rounds; round++)
    {
        cout << "Round " << round << endl;
        game.start();
        game.reset_game();
    }

    return 0;
}
