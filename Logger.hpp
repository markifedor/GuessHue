/* CSCI 200: Final Project - Guess Hue?
 *
 * Author: Mark Fedorchuk
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     A lot of sfml documentation and forms.
 *
 * "Guess Hue?"" is a color guessing game. You're given a color and you have to guess it's rgb values. This is the Logger object which 
 *  keeps the guesses and hints. It prints out the guesses and hints to a file or the console. This object doesn't violate the SRP because
 *  it still only does one thing: write out the guesses and hints. It stores the guesses and hints, so that it can write to file once as
 *  opposed to every enter press.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Logger{
    private:
        vector<Color> guesses; // vector of all the guesses submitted
        vector<vector<char>> hints; // vector of all the hints given the hints are in themselves vectors of characters
        ofstream outFile; // the file to write to
        string fileName; // the name of the file to write to (without the extension)
        bool hasFile; // whether we are saving the log to a file or not
    public:
        /**
         * @brief default constructor. Use for when not saving a file. Technically not needed to be defined, but defined it if new variables 
        */
        Logger();

        /**
         * @brief constructor for when saving to a file.
         * 
         * @param FILE_NAME the name of the file you want created or appended to excluding the extension
        */
        Logger(const string FILE_NAME);

        /**
         * @brief adds a guess to the guess vector and a hint to the hint vector
         * 
         * @param GUESS the color inputted by the user as a guesss
         * @param HINT the hint for that guess (is created by the game class)
         * 
        */
        void addGuess(const Color GUESS, const vector<char> HINT);

        /**
         * @brief writes out the hint given it's hint index in the hint vector (NOTE this is 0 based not 1 based as displayed to the user). IN_FILE determines if it should be written to the file or not. If not it will print to the console.
         * 
         * @param IN_FILE true if writting in the file, false if writting in the console
         * @param HINT_INDEX index of hint to print (base 0)
        */
        void writeOutHint(const bool IN_FILE, const int HINT_INDEX);

        /**
         * @brief writes out all the hints given throughout the game in a nice format into the file, but only if the file was loaded
         * 
         * @param CORRECT_COLOR the correct color the player was trying to guess 
        */
        void generateLog(const Color CORRECT_COLOR);

        /**
         * @brief returns true if a file was loaded, false otherwise (getter for hasFile)
        */
        bool isFileLoaded() const;

        /**
         * @brief getter for fileName, the name of the file
        */
        string getFileName() const;

        /**
         * @brief getter for numGuesses, the number of guesses stored
        */
        int getNumGuesses() const;
};

Logger::Logger(){
    hasFile = false;
    fileName = "";
}

Logger::Logger(const string FILE_NAME){
    this->fileName = FILE_NAME;
    string fullFileName = fileName + ".txt";
    cout << "Creating\\Opening file \"" << fullFileName << "\"" << endl;
    
    // open file for parsing
    outFile.open("log\\" + fullFileName, outFile.app);
    if(outFile.fail()){
        cerr << "Could not create file \"" << fullFileName << "\"" << endl;
        cerr << "Check if a \"log\" folder exists in the same folder as this exe.\nIf not create it. This might fix the issue, otherwise try again." << endl;
        cerr << "Shutting down" << endl;
        exit(-1);
    }

    cout << "File opened successfully!" << endl << endl;
    hasFile = true;
}

void Logger::addGuess(const Color GUESS, const vector<char> HINT){
    guesses.push_back(GUESS);
    hints.push_back(HINT);
}

void Logger::writeOutHint(const bool IN_FILE, const int HINT_INDEX){ 
    int hintNumber = HINT_INDEX + 1;
    if(IN_FILE && hasFile){ //checks if it has file before trying to write into a non instantiated ofstream
        outFile << string(6, ' ') << hintNumber << ". (" << to_string(guesses[HINT_INDEX].r) << ", " << to_string(guesses[HINT_INDEX].g) << ", " << to_string(guesses[HINT_INDEX].b) << ")" << endl;
        outFile << string(9, ' ') << "(" << hints[HINT_INDEX][0] << ", " << hints[HINT_INDEX][1] << ", " << hints[HINT_INDEX][2] << ")" << endl;
        outFile << endl;
    }
    else{ // then print to console
        if(IN_FILE && !hasFile){ // message for if you tried to write to file without one loaded (I could not get this to actually activate no matter how hard I tried) 
            cout << "You tried to print to a file that has not been opened. Writting to console instead." << endl;
        }
        cout << hintNumber << ". (" << to_string(guesses[HINT_INDEX].r) << ", " << to_string(guesses[HINT_INDEX].g) << ", " << to_string(guesses[HINT_INDEX].b) << ")" << endl;
        cout << string(3, ' ') << "(" << hints[HINT_INDEX][0] << ", " << hints[HINT_INDEX][1] << ", " << hints[HINT_INDEX][2] << ")" << endl;
        cout << endl;
    }
}

void Logger::generateLog(const Color CORRECT_COLOR){
    if(hasFile){
        //print out the correct color
        outFile << "Correct: (" << to_string(CORRECT_COLOR.r) << ", " << to_string(CORRECT_COLOR.g) << ", " << to_string(CORRECT_COLOR.b) << ")" << endl;
        outFile << string(25, '~') << endl;
        for(unsigned int i = 0; i < guesses.size(); i++){ //printing out all the guesses and hints
            writeOutHint(true, i); // true because loading into file
        }
        outFile << endl;    
        cout << "Game has been written to file." << endl << endl;
    }
}

bool Logger::isFileLoaded() const{
    return hasFile;
}

string Logger::getFileName() const{
    if(hasFile){
        return fileName;
    }
    else{ //prevents potential problems farther down the line
        cerr << "No file is loaded" << endl;
        exit(-1);
    }
}

int Logger::getNumGuesses() const{
    return guesses.size();
}
#endif