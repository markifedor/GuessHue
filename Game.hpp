/* CSCI 200: Final Project - Guess Hue?
 *
 * Author: Mark Fedorchuk
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     A lot of sfml documentation and forms.
 *
 * "Guess Hue?"" is a color guessing game. You're given a color and you have to guess it's rgb values. This is the Game object which 
 *  keeps the correct color, gives hints, and keeps if the game is won or not. This doesn't violate the SRP because it still only does
 *  one thing: give out hints using the color it created. Winning or not is a "hint" as well.
 */

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include <vector>
#include <ctime>
#include <random>
using namespace std;

class Game{
    private:
        Color color; // the correct color to be guessed
        bool won; // whether the game has been won or not
    public:
        /**
         * @brief constructor for the object. Creates the color to guess. Each value of the color will be a multiple of INCREMENT. If no variables past it will act as the default constructor (since there are not variables), it will use 15 as the increment value
         * 
         * @param INCREMENT the number that all values of color should be a multiple of. The larger, the easier the game. Default of 15. \n Note:**Will break the game if 255 doesn't evenly divide by the increment (Valid increments are 1, 3, 5, 15, 17, 51, 85).**
        */
        Game(const int INCREMENT = 15);

        /**
         * @brief gives out hint for given color that has been guessed
         * 
         * @param GUESSED_COLOR the color that has been guessed
         * 
         * @return a vector of size 3 containing hints associated with each value. For example if the 0th slot (red) is "<", the correct color's red value is smaller than the guessed r value.
        */
        vector<char> giveColorHints(const Color GUESSED_COLOR);

        /**
         * @brief getter for the color to guess
         * 
         * @return Color value equal to the color to guess  
        */
        Color getCorrectColor() const;
        
        /**
         * @brief tells if game has been won or not (true = won, false = not yet)
         * 
         * @return bool won
         * 
        */
        bool isGameWon() const;
};

Game::Game(const int INCREMENT){
    srand(time(0)); 
    rand();
    // randomly generate 3 numbers for each value and manipulate them to be in range and proper multiples
    color = Color(INCREMENT * (rand() % (255/INCREMENT)), INCREMENT * (rand() % (255/INCREMENT)), INCREMENT * (rand() % (255/INCREMENT)));
    won = false;
}
Color Game::getCorrectColor() const{
    return color;
}
vector<char> Game::giveColorHints(const Color GUESSED_COLOR){
    vector<char> hint;
    hint.resize(3);

    if(color.r == GUESSED_COLOR.r ){ hint[0] = '='; }
    else if(color.r > GUESSED_COLOR.r) { hint[0] = '>'; }
    else{ hint[0] = '<'; }

    if(color.g == GUESSED_COLOR.g ){ hint[1] = '='; }
    else if(color.g > GUESSED_COLOR.g) { hint[1] = '>'; }
    else{ hint[1] = '<'; }

    if(color.b == GUESSED_COLOR.b ){ hint[2] = '='; }
    else if(color.b > GUESSED_COLOR.b) { hint[2] = '>'; }
    else{ hint[2] = '<'; }

    if(GUESSED_COLOR == color){
        won = true;
    }

    return hint;
}

bool Game::isGameWon() const{
    return won;
}
#endif