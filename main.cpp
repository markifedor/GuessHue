/* CSCI 200: Final Project - Guess Hue?
 *
 * Author: Mark Fedorchuk
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     A lot of sfml documentation and forms.
 *
 * "Guess Hue?"" is a color guessing game. You're given a color and you have to guess it's rgb values. This is the main.cpp which 
 * contains most of the visual and event code.
 */

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
#include <vector>
using namespace std;

#include "Game.hpp"
#include "Logger.hpp"

RenderWindow* createWindow(){
    // create a window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow* pWindow = new RenderWindow( VideoMode(700, 700), "Guess Hue?", sf::Style::Default, settings);
    
    Image icon;
    if(!icon.loadFromFile("data\\logo.png")){}
    pWindow->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    pWindow->setPosition(Vector2i(VideoMode::getDesktopMode().width*1.0f/2.0f, VideoMode::getDesktopMode().height*.8f/5.0f));
    pWindow->requestFocus();
    
    return pWindow;
}

Logger* startNewLog(){
    char answer;
    cout << endl << "Do you want to save a log of this game?(y/N) ";
    cin >> answer;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clearing the rest of the characters that might be placed

    string fileName;
    Logger* pGuessLog;
    if(answer == 'Y' || answer == 'y'){
        cout << endl << "The file will be saved to the logs folder. If the file already exists it will be appended to." << endl;
        cout << "What do you want the file to be called? ";
        cin >> fileName;
        cout << endl;

        pGuessLog = new Logger(fileName);
    }
    else{
        pGuessLog = new Logger;
    }
    return pGuessLog;
}

int main() {
    Logger* pGuessLog = startNewLog();
    
    const int INCREMENT = 15;
    Game game = Game(INCREMENT);

    RenderWindow* pWindow = createWindow();

    Vector2f realMousePosition;

    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    Font font;
    if(!font.loadFromFile("data\\calibrib.ttf")){}
    
    Texture arrowTexture;
    if(!arrowTexture.loadFromFile("data\\Arrow.png")){}
    
    Texture enterTexture;
    if(!enterTexture.loadFromFile("data\\Enter.png")){}
    
    Texture resetTexture;
    if(!resetTexture.loadFromFile("data\\Restart.png")){}

    Texture controlPanelTexture;
    if(!controlPanelTexture.loadFromFile("data\\controlPanel.png"));

    vector<Sprite*> buttons;
    
    Color backgroundColor = Color(20, 17, 17);
    RectangleShape background;
    background.setSize(Vector2f(pWindow->getSize().x, pWindow->getSize().y));
    background.setPosition(0, 0);
    background.setFillColor(backgroundColor);

    CircleShape swatch;
    swatch.setRadius(pWindow->getSize().x/6);
    swatch.setPointCount(100);
    swatch.setFillColor(game.getCorrectColor());
    swatch.setPosition(pWindow->getSize().x/2 - swatch.getRadius(), pWindow->getSize().y/4 - swatch.getRadius());
    swatch.setOutlineThickness(8);
    swatch.setOutlineColor(Color(80, 80, 80));
    // cout << int(game.getCorrectColor().G) << " " << int(game.getCorrectColor().g) << " " << int(game.getCorrectColor().b) << endl;

    Sprite controlPanel;
    controlPanel.setTexture(controlPanelTexture);
    controlPanel.setScale(Vector2f(0.725f, 0.75f));
    controlPanel.setPosition(swatch.getPosition().x + swatch.getRadius() - controlPanel.getGlobalBounds().width/2, pWindow->getSize().y*7.75/12 - swatch.getRadius());
    controlPanel.setColor(backgroundColor/*+Color(10, 10, 10)*/);

    Sprite resetButton;
    bool resetPressed = false;
    buttons.push_back(&resetButton);
    resetButton.setTexture(resetTexture);
    resetButton.setScale(Vector2f(0.1f, 0.1f));
    resetButton.setPosition(swatch.getPosition().x - swatch.getRadius() - resetTexture.getSize().x*resetButton.getScale().x/2, pWindow->getSize().y*3/4 - swatch.getRadius());
    
    Sprite enterButton;
    buttons.push_back(&enterButton);
    enterButton.setTexture(enterTexture);
    enterButton.setScale(Vector2f(0.1f, 0.1f));
    enterButton.setPosition(swatch.getPosition().x + swatch.getRadius()*3 - enterTexture.getSize().x*enterButton.getScale().x/2, pWindow->getSize().y*3/4 - swatch.getRadius());

    const int INITIAL_COLOR_VAL = 255/INCREMENT/2*INCREMENT;
    int rVal = INITIAL_COLOR_VAL; //sets default R value to the most central possible number rounded down
    Text rValText;
    rValText.setFont(font);
    rValText.setFillColor(Color(backgroundColor.r + 150, backgroundColor.g + 150, backgroundColor.b + 150));
    rValText.setCharacterSize(40);
    rValText.setString(to_string(INITIAL_COLOR_VAL));
    rValText.setPosition(enterButton.getPosition().x - (enterButton.getPosition().x - resetButton.getPosition().x)*3/4, enterButton.getPosition().y);
    const Vector2f DEFAULT_R_POSITION = rValText.getPosition();

    Text rLabel;
    rLabel.setFont(font);
    rLabel.setFillColor(Color(150, 50, 50));
    rLabel.setCharacterSize(60);
    rLabel.setString("R");
    rLabel.setPosition(rValText.getPosition().x + rValText.getGlobalBounds().width/2 - rLabel.getGlobalBounds().width/2, enterButton.getPosition().y + 120);
 
    int gVal = rVal;
    Text gValText = rValText;
    gValText.setPosition(enterButton.getPosition().x - (enterButton.getPosition().x - resetButton.getPosition().x) * 2/4, gValText.getPosition().y);
    gValText.setString(to_string(INITIAL_COLOR_VAL));
    const Vector2f DEFAULT_G_POSITION = gValText.getPosition();

    Text gLabel;
    gLabel.setFont(font);
    gLabel.setFillColor(Color(75, 130, 75));
    gLabel.setCharacterSize(60);
    gLabel.setString("G");
    gLabel.setPosition(gValText.getPosition().x + gValText.getGlobalBounds().width/2 - gLabel.getGlobalBounds().width/2, enterButton.getPosition().y + 120);

    int bVal = rVal;
    Text bValText = rValText;
    bValText.setPosition(enterButton.getPosition().x - (enterButton.getPosition().x - resetButton.getPosition().x) * 1/4, gValText.getPosition().y);
    bValText.setString(to_string(INITIAL_COLOR_VAL));
    const Vector2f DEFAULT_B_POSITION = bValText.getPosition();
    
    Text bLabel;
    bLabel.setFont(font);
    bLabel.setFillColor(Color(90, 90, 150));
    bLabel.setCharacterSize(60);
    bLabel.setString("B");
    bLabel.setPosition(bValText.getPosition().x + bValText.getGlobalBounds().width/2 - bLabel.getGlobalBounds().width/2, enterButton.getPosition().y + 120);

    Sprite upArrowR;
    buttons.push_back(&upArrowR);
    upArrowR.setTexture(arrowTexture);
    upArrowR.setScale(Vector2f(0.07f, 0.07f));
    upArrowR.setRotation(180);
    
    const float UP_ARROW_WIDTH = upArrowR.getScale().x*arrowTexture.getSize().x;
    const float UP_ARROW_HEIGHT = upArrowR.getScale().y*arrowTexture.getSize().y;
    upArrowR.setOrigin(UP_ARROW_WIDTH, UP_ARROW_HEIGHT);
    upArrowR.setPosition(rValText.getPosition().x + UP_ARROW_WIDTH - 1.5, rValText.getPosition().y - rValText.getCharacterSize()*1/3);

    Sprite upArrowG = upArrowR;
    buttons.push_back(&upArrowG);
    upArrowG.setPosition(gValText.getPosition().x + UP_ARROW_WIDTH - 1.5, gValText.getPosition().y - gValText.getCharacterSize()*1/3);

    Sprite upArrowB = upArrowR;
    buttons.push_back(&upArrowB);
    upArrowB.setPosition(bValText.getPosition().x + UP_ARROW_WIDTH - 1.5, bValText.getPosition().y - bValText.getCharacterSize()*1/3);

    Sprite downArrowR;
    buttons.push_back(&downArrowR);
    downArrowR.setTexture(arrowTexture);
    downArrowR.setScale(Vector2f(0.07f, 0.07f));
    downArrowR.setPosition(rValText.getPosition().x + 1.5, rValText.getPosition().y + rValText.getCharacterSize()*5/3);

    Sprite downArrowG = downArrowR;
    buttons.push_back(&downArrowG);
    downArrowG.setPosition(gValText.getPosition().x + 1.5, gValText.getPosition().y + gValText.getCharacterSize()*5/3);

    Sprite downArrowB = downArrowR;
    buttons.push_back(&downArrowB);
    downArrowB.setPosition(bValText.getPosition().x + 1.5, bValText.getPosition().y + bValText.getCharacterSize()*5/3);
    
    // Text mouseDebug;
    // mouseDebug.setFont(font);
    // mouseDebug.setFillColor(Color(255, 255, 255));
    // mouseDebug.setCharacterSize(20);

    //  END  ANY FILE LOADING
    /////////////////////////////////////

    // create an event object once to store future events
    Event event;

    // while the window is open
    while( pWindow->isOpen() ) {
        // clear any existing contents
        pWindow->clear();

        /////////////////////////////////////
        // BEGIN DRAWING HERE
        pWindow->draw(background);
        pWindow->draw(swatch);
        if(background.getFillColor() != backgroundColor){ //controlPanel is the same color as background so this is only here for slight optimization
            pWindow->draw(controlPanel);
        }

        const FloatRect ARROW_RECT = upArrowR.getGlobalBounds();

        rValText.setString(to_string(rVal));
        //centering text depending on how many digits in the rVal
        const FloatRect R_TEXT_RECT = rValText.getGlobalBounds();
        rValText.setPosition(DEFAULT_R_POSITION.x + ARROW_RECT.width/2.0f - R_TEXT_RECT.width/2.0f, DEFAULT_R_POSITION.y);
        pWindow->draw(rValText);
        pWindow->draw(rLabel);

        gValText.setString(to_string(gVal));
        //centering text depending on how many digits in the gVal
        const FloatRect G_TEXT_RECT = gValText.getGlobalBounds();
        gValText.setPosition(DEFAULT_G_POSITION.x + ARROW_RECT.width/2.0f - G_TEXT_RECT.width/2.0f, DEFAULT_G_POSITION.y);
        pWindow->draw(gValText);
        pWindow->draw(gLabel);
        
        bValText.setString(to_string(bVal));
        //centering text depending on how many digits in the bVal
        const FloatRect B_TEXT_RECT = bValText.getGlobalBounds();
        bValText.setPosition(DEFAULT_B_POSITION.x + ARROW_RECT.width/2.0f - B_TEXT_RECT.width/2.0f, DEFAULT_B_POSITION.y);
        pWindow->draw(bValText);
        pWindow->draw(bLabel);
        
        // realMousePosition = mouse.getPosition() - pWindow->getPosition();
        realMousePosition = pWindow->mapPixelToCoords(sf::Mouse::getPosition(*pWindow));
        
        // mouseDebug.setString(to_string(realMousePosition.x) + " " + to_string(realMousePosition.y));
        
        // mouseDebug.setFillColor(Color(255, 255, 255));
        for(unsigned int i = 0; i < buttons.size(); i++){ // looking for which button is hovered over
            if(buttons[i]->getGlobalBounds().contains(Vector2f(realMousePosition))){
                buttons[i]->setColor(Color(200, 200, 200)); // set hovered button to a darker color
                // mouseDebug.setFillColor(Color(0, 255, 255));
            }
            else{
                buttons[i]->setColor(Color(255, 255, 255)); // set the rest to normal
            }
            pWindow->draw(*buttons[i]); //draw the button
        }
        // pWindow->draw(mouseDebug);

        //  END  DRAWING HERE
        /////////////////////////////////////

        // display the current contents of the window
        pWindow->display();

        /////////////////////////////////////
        // BEGIN EVENT HANDLING HERE
        // check if any events happened since the last time checked
        while( pWindow->pollEvent(event) ) {
            // if event type corresponds to pressing window X
            if(event.type == Event::Closed) {
                // tell the window to close
                pWindow->close();
            }
            if(event.type == Event::MouseButtonReleased){
                if(event.mouseButton.button == Mouse::Left){
   /*reset button*/ if(resetButton.getGlobalBounds().contains(Vector2f(realMousePosition))){ //reset button has been pressed
                        if(!resetPressed){
                            cout << "You sure you want to get a new color? Click the button again to restart and change the color." << endl;
                            if(pGuessLog->isFileLoaded()){                            
                                if(!game.isGameWon() && pGuessLog->getNumGuesses() > 0){
                                    cout << "You asked to create a log file, so it would be written to."<< endl;
                                }                              
                                cout << "Future games in this session will write in the same log file." << endl << endl;
                            }
                            resetPressed = true;
                        }
                        else{ // if already pressed once reset the game
                            resetPressed = false;
                            background.setFillColor(backgroundColor);
                            if(pGuessLog->isFileLoaded()){  //only write to file if we selected to save a log 
                                string fileName = pGuessLog->getFileName();

                                if(!game.isGameWon()){ //and the enter if statement didn't already generate the log
                                    pGuessLog->generateLog(game.getCorrectColor());
                                }
                                delete pGuessLog;
                                pGuessLog = new Logger(fileName);
                            }
                            else{
                                delete pGuessLog;
                                pGuessLog = new Logger();
                            }

                            rVal = INITIAL_COLOR_VAL; //reset initial values displayed
                            gVal = INITIAL_COLOR_VAL;
                            bVal = INITIAL_COLOR_VAL;
                            game = Game(INCREMENT); // reset game
                            swatch.setFillColor(game.getCorrectColor());
                            cout << "Here's a new color!" << endl << endl;
                        }
                    }
                    if(!game.isGameWon()){ // all buttons but reset should be disabled once game is won
                        resetPressed = false; // if any other button is pressed the reset button will no longer reset the game on the next click 
       /*enter button*/ if(enterButton.getGlobalBounds().contains(Vector2f(realMousePosition))){ //enter button has been pressed                            
                            Color guess = Color(rVal, gVal, bVal);
                            vector<char> hint = game.giveColorHints(guess);

                            pGuessLog->addGuess(guess, hint);
                            pGuessLog->writeOutHint(false, pGuessLog->getNumGuesses()-1); //write out last index's hint

                            if(game.isGameWon()){
                                cout << "You won! That's the rgb value!\n\nPress the red reset button to play again!\nClose out the window to quit." << endl << endl;
                                background.setFillColor(Color(76, 130, 92));
                                if(pGuessLog->isFileLoaded()){
                                    pGuessLog->generateLog(game.getCorrectColor());
                                }
                            }
                        }
       /*Up Arrow Red*/ if(upArrowR.getGlobalBounds().contains(Vector2f(realMousePosition))){ // up arrow red button pressed
                            if(rVal <= 255-INCREMENT){
                                rVal += INCREMENT;
                            }
                        }
     /*Up Arrow Green*/ if(upArrowG.getGlobalBounds().contains(Vector2f(realMousePosition))){ // up arrow green button pressed
                            if(gVal <= 255-INCREMENT){
                                gVal += INCREMENT;
                            }
                        }
     /*Up Arrow Blue*/  if(upArrowB.getGlobalBounds().contains(Vector2f(realMousePosition))){ // up arrow blue button pressed
                            if(bVal <= 255-INCREMENT){
                                bVal += INCREMENT;
                            }
                        }
     /*Up Arrow Blue*/  if(downArrowR.getGlobalBounds().contains(Vector2f(realMousePosition))){ // down arrow red button pressed
                            if(rVal >= INCREMENT){
                                rVal -= INCREMENT;
                            }
                        }
   /*Down Arrow Red*/  if(downArrowG.getGlobalBounds().contains(Vector2f(realMousePosition))){ // down arrow green button pressed
                            if(gVal >= INCREMENT){
                                gVal -= INCREMENT;
                            }
                        }
   /*Down Arrow Blue*/  if(downArrowB.getGlobalBounds().contains(Vector2f(realMousePosition))){ // down arrow blue button pressed
                            if(bVal >= INCREMENT){
                                bVal -= INCREMENT;
                            }
                        }
                    }
                    
                }
            }
        }
        //  END  EVENT HANDLING HERE
        /////////////////////////////////////
    }
    delete pGuessLog;
    cout << "Goodbye!" << endl;
    return 0;
}