#include "Header.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Protect the Village");
    sf::Clock Clock;
    sf::Event event;
    sf::Texture texture1, texture2, texture3, assets, texturetemp;
    texture1.loadFromFile("Resources/made_with.bmp");
    sf::Sprite logo(texture1);
    texture2.loadFromFile("Resources/main_menu.bmp");   
    sf::Sprite main_menu(texture2);
    texture3.loadFromFile("Resources/towers.psd");
    sf::Sprite towers(texture3);
    texturetemp.loadFromFile("Resources/multiplayer.bmp");
    sf::Sprite multiplayer(texturetemp);

    assets.loadFromFile("Resources/assets.psd");
    sf::Sprite arrowTower1(assets, sf::IntRect(93,92,80,80));
    sf::Sprite arrowTower2(assets);
    sf::Sprite arrowTower3(assets);

    game_state gameState = START_SCREEN;
    sf::RectangleShape SinglePlayer(sf::Vector2f(435, 55)), Multiplayer(sf::Vector2f(395, 55)), Quit(sf::Vector2f(165, 50));
    

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        sf::StandardCursor Cursor(sf::StandardCursor::NORMAL);
        Cursor.set(window.getSystemHandle());
        

        if (gameState == START_SCREEN && Clock.getElapsedTime().asSeconds() <= 1.0f) {  //todo 4 sec
            window.draw(logo);          
        }
        if (gameState == START_SCREEN && Clock.getElapsedTime().asSeconds() > 1.0f) {  //todo 4 sec
            gameState = MAIN_MENU;
        }

        if (gameState == MAIN_MENU) {
            window.draw(main_menu);
            SinglePlayer.setPosition(sf::Vector2f(990, 365));
            Multiplayer.setPosition(sf::Vector2f(1032, 522));
            Quit.setPosition(sf::Vector2f(1269, 685));
            if (isMouseIn(window, SinglePlayer) || isMouseIn(window, Multiplayer) || isMouseIn(window, Quit)) {
                sf::StandardCursor Cursor(sf::StandardCursor::HAND);
                Cursor.set(window.getSystemHandle());
            }
            if (isMouseIn(window, SinglePlayer) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                gameState = PLAYING_SOLO;
                window.clear();
            }
            if (isMouseIn(window, Multiplayer) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                gameState = PLAYING_TWO;
                window.clear();
            }
            if (isMouseIn(window, Quit) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                window.close();
            }
        }
        
        if (gameState == PLAYING_SOLO) {
            

        }

        if (gameState == PLAYING_TWO) {
            window.draw(multiplayer);
        }


        window.display();
        
    }
    return 0;
}
