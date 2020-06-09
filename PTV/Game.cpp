#include "Header.h"

bool isMouseIn(sf::RenderWindow &window, sf::RectangleShape &rectangle) {
	sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
	if (cursorPos.x >= rectangle.getGlobalBounds().left
		&& cursorPos.x <= rectangle.getGlobalBounds().left + rectangle.getSize().x
		&& cursorPos.y >= rectangle.getGlobalBounds().top
		&& cursorPos.y <= rectangle.getGlobalBounds().top+ rectangle.getSize().y) {
		return true;
	}
	return false;
}

bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Protect the Village");

    sf::Font font;
    font.loadFromFile("Resources/font.ttf");
    sf::Text timeUntilWave; timeUntilWave.setFont(font); timeUntilWave.setCharacterSize(50); timeUntilWave.move(400, 0); timeUntilWave.setFillColor(sf::Color::Black);


    sf::Texture texture1, texture2, texture3, assets, texturetemp, texturetemp2;
    texture1.loadFromFile("Resources/made_with.bmp");
    sf::Sprite logo(texture1);
    texture2.loadFromFile("Resources/main_menu.bmp");
    sf::Sprite main_menu(texture2);
    texture3.loadFromFile("Resources/towers.psd");
    sf::Sprite towers(texture3);
    texturetemp.loadFromFile("Resources/multiplayer.bmp");
    sf::Sprite multiplayer(texturetemp);

    texturetemp2.loadFromFile("Resources/singleplayer path.psd"); //todo remove
    sf::Sprite singleplayerpath(texturetemp2);

    assets.loadFromFile("Resources/assets.psd");
    sf::Sprite arrowTower1(assets, sf::IntRect(93, 92, 80, 80));
    sf::Sprite arrowTower2(assets);
    sf::Sprite arrowTower3(assets);
    sf::Sprite Bat[3]; Bat[0] = sf::Sprite(assets, sf::IntRect(472, 118, 56, 44)); Bat[1] = sf::Sprite(assets, sf::IntRect(534, 118, 54, 34)); Bat[2] = sf::Sprite(assets, sf::IntRect(591, 111, 60, 45));
    

    GAME_STATE gameState = START_SCREEN;
    sf::RectangleShape SinglePlayer(sf::Vector2f(435, 55)), Multiplayer(sf::Vector2f(395, 55)), Quit(sf::Vector2f(165, 50)), BuildMenu(sf::Vector2f(350, 600));

    BuildMenu.setFillColor(sf::Color(144)); BuildMenu.setPosition(sf::Vector2f(1600, 900)); //todo remove

    MapLayout map_layout(PLAYING_SOLO);
    Attackers enemies;
    static bool showMenu = false, waveStarted = false;
    static int numEnemies = 0;
    static float difficultyMultiplier = 1.0;

    while (window.isOpen()) {

        window.clear();
        sf::StandardCursor Cursor(sf::StandardCursor::NORMAL);
        Cursor.set(window.getSystemHandle());


        if (gameState == START_SCREEN && waveTimer.getElapsedTime().asSeconds() <= 1.0f) {  //todo 4 sec
            window.draw(logo);
        }else if (gameState == START_SCREEN && waveTimer.getElapsedTime().asSeconds() > 1.0f) {  //todo 4 sec
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

        }

        if (gameState == PLAYING_SOLO) {
            
            window.draw(singleplayerpath);
            if (showMenu)window.draw(BuildMenu);

            for (int l = 0; l < 209; l++) {
                if (isMouseIn(window, map_layout.Tiles.tiles[l]) && !map_layout.Tiles.isPath[l]) {
                    sf::StandardCursor Cursor(sf::StandardCursor::HAND);
                    Cursor.set(window.getSystemHandle());


                }
            }

            if (!waveStarted) {
                std::ostringstream ss;
                ss << "Wave spawns in: " << int(2 - this->waveTimer.getElapsedTime().asSeconds());
                std::string str = ss.str();
                timeUntilWave.setString(str);
                window.draw(timeUntilWave);

                if (2 - this->waveTimer.getElapsedTime().asSeconds() < 0) {
                    waveStarted = true;
                    waveTimer.restart();
                    enemies.prepareWave(10, Bat);
                }
            }
            else {
                for (int i = 0; i < numEnemies; i++) {
                    if(enemies.monsters[i].alive) enemies.spawn(enemies.monsters[i].enemy, window, this);
                }
                if (numEnemies < 10 && waveTimer.getElapsedTime().asMilliseconds() > 1000) {
                    waveTimer.restart();
                    numEnemies++;
                }
            }

        }

        if (gameState == PLAYING_TWO) {
            window.draw(multiplayer);
        }


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {

                if (gameState == MAIN_MENU) {
                    if (isMouseIn(window, SinglePlayer)) {
                        gameState = PLAYING_SOLO;
                        this->waveTimer.restart();
                        window.clear();
                    }
                    if (isMouseIn(window, Multiplayer)) {
                        gameState = PLAYING_TWO;
                        this->waveTimer.restart();
                        window.clear();
                    }
                    if (isMouseIn(window, Quit)) {
                        window.close();
                    }
                }else if (gameState == PLAYING_SOLO) {
                    if (showMenu) {
                        BuildMenu.setPosition(sf::Vector2f(1600, 900));
                        showMenu = false;
                    }
                    else for (int l = 0; l < 209; l++) {
                        if (isMouseIn(window, map_layout.Tiles.tiles[l]) && !map_layout.Tiles.isPath[l]) {
                            BuildMenu.setPosition(sf::Vector2f(1250, 300));
                            showMenu = true;
                        }

                    }
                    
                }
            }
        }
        window.display();

    }
}


