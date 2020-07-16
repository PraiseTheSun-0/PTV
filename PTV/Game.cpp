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
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("Resources/font.ttf");
    sf::Text timeUntilWave; timeUntilWave.setFont(font); timeUntilWave.setCharacterSize(35); timeUntilWave.setPosition(sf::Vector2f(600, 0)); timeUntilWave.setFillColor(sf::Color::Black);
    sf::Text startWave; startWave.setFont(font); startWave.setCharacterSize(50); startWave.setFillColor(sf::Color::Black); startWave.setPosition(sf::Vector2f(676, 660));

    sf::Texture texture1, texture2, background, assets, texturetemp, texturetemp2;
    texture1.loadFromFile("Resources/made_with.bmp");
    sf::Sprite logo(texture1);
    texture2.loadFromFile("Resources/main_menu.bmp");
    sf::Sprite main_menu(texture2);
    background.loadFromFile("Resources/game_background.bmp");
    sf::Sprite game_background(background);
    texturetemp.loadFromFile("Resources/multiplayer.bmp");
    sf::Sprite multiplayer(texturetemp);
    texturetemp2.loadFromFile("Resources/singleplayer_path.png");
    sf::Sprite singleplayerpath(texturetemp2);

    assets.loadFromFile("Resources/assets.png");
    sf::Sprite Bat[3]; 
    Bat[0] = sf::Sprite(assets, sf::IntRect(460, 99, 84, 81)); Bat[1] = sf::Sprite(assets, sf::IntRect(551, 99, 84, 81)); Bat[2] = sf::Sprite(assets, sf::IntRect(640, 99, 84, 81));
    sf::Sprite Orc[3]; 
    Orc[0] = sf::Sprite(assets, sf::IntRect(454, 263, 84, 81)); Orc[1] = sf::Sprite(assets, sf::IntRect(559, 263, 84, 81)); Orc[2] = sf::Sprite(assets, sf::IntRect(644, 263, 84, 81));
    sf::Sprite Goblin[3]; 
    Goblin[0] = sf::Sprite(assets, sf::IntRect(443, 364, 84, 81)); Goblin[1] = sf::Sprite(assets, sf::IntRect(547, 364, 84, 81)); Goblin[2] = sf::Sprite(assets, sf::IntRect(644, 364, 84, 81));

    GAME_STATE gameState = START_SCREEN;
    sf::RectangleShape SinglePlayer(sf::Vector2f(435, 55)), Multiplayer(sf::Vector2f(395, 55)), Quit(sf::Vector2f(165, 50));

    MapLayout map_layout(PLAYING_SOLO);

    BuildMenu build_menu;

    std::vector<Towers*> towers;

    sf::RectangleShape startWaveButton(sf::Vector2f(255, 70)); startWaveButton.setPosition(sf::Vector2f(676, 660));
    Attackers enemies;
    bool showMenu = false, waveStarted = false, bulletsEnded = true, waveGoing = false;;
    int lives = 20, gold = 150, numEnemies = 1, waveNum = 1, timeUntilStart = 30;
    float difficultyMultiplier = 1.0;

    while (window.isOpen()) {

        window.clear();
        sf::StandardCursor Cursor(sf::StandardCursor::NORMAL);
        Cursor.set(window.getSystemHandle());


        if (gameState == START_SCREEN && waveTimer.getElapsedTime().asSeconds() <= 4.0f) { 
            window.draw(logo);
        }else if (gameState == START_SCREEN && waveTimer.getElapsedTime().asSeconds() > 4.0f) {  
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


            if (lives > 0) {
                window.draw(singleplayerpath);

                std::ostringstream text;
                sf::Text Gold; Gold.setFont(font); Gold.setCharacterSize(40); Gold.setFillColor(sf::Color::Black); Gold.setPosition(sf::Vector2f(1290, 0));
                sf::Text Lives; Lives.setFont(font); Lives.setCharacterSize(40); Lives.setFillColor(sf::Color::Black);
                text << "Gold: " << gold;
                std::string string_text = text.str();
                Gold.setString(string_text);
                window.draw(Gold);
                text.str(""); 
                text << "Lives left: " << lives;
                string_text = text.str();
                Lives.setString(string_text);
                window.draw(Lives);

                if (showMenu)window.draw(build_menu.highlight);
                for (int l = 0; l < 209; l++) {
                    if (isMouseIn(window, map_layout.Tiles.tiles[l]) && !map_layout.Tiles.isPath[l]) {
                        sf::StandardCursor Cursor(sf::StandardCursor::HAND);
                        Cursor.set(window.getSystemHandle());


                    }
                }

                std::ostringstream ss;
                if (!waveStarted) {


                    ss << "Wave " << waveNum << " spawns in: " << int(timeUntilStart - this->waveTimer.getElapsedTime().asSeconds());   
                    std::string str = ss.str();
                    timeUntilWave.setString(str);
                    window.draw(timeUntilWave);

                    startWave.setString("Start now");
                    window.draw(startWave);

                    if (timeUntilStart - this->waveTimer.getElapsedTime().asSeconds() < 0) {
                        waveStarted = true;
                        waveTimer.restart();
                        int randomEnemy = rand() % 3;
                        switch (randomEnemy) {
                        case 0:
                            enemies.prepareWave(BAT, Bat, map_layout.Tiles.tiles[19].getPosition(), difficultyMultiplier);
                            break;
                        case 1:
                            enemies.prepareWave(ORC, Orc, map_layout.Tiles.tiles[19].getPosition(), difficultyMultiplier);
                            break;
                        case 2:
                            enemies.prepareWave(GOBLIN, Goblin, map_layout.Tiles.tiles[19].getPosition(), difficultyMultiplier);
                            break;
                        }

                    }
                }
                else {
                    int enemiesAlive = 0;
                    for (unsigned int k = 0; k < enemies.monsters.size(); k++) if (enemies.monsters[k].alive) enemiesAlive++;
                    ss << "Wave " << waveNum << ". Enemies left:" << enemiesAlive;
                    std::string str = ss.str();
                    timeUntilWave.setString(str);
                    window.draw(timeUntilWave);

                    waveGoing = false;
                    for (int i = 0; i < numEnemies; i++) {
                        if (enemies.monsters[i].alive) {

                            if (enemies.monsters[i].checkPointReached[8]) {
                                enemies.monsters[i].alive = false;
                                lives -= enemies.monsters[i].livesTaken;
                            }
                            else if (enemies.monsters[i].checkPointReached[7]) move(enemies.monsters[i].enemy, enemies.monsters[i].movespeed, RIGHT);
                            else if (enemies.monsters[i].checkPointReached[6]) move(enemies.monsters[i].enemy, enemies.monsters[i].movespeed, UP);
                            else if (enemies.monsters[i].checkPointReached[5]) move(enemies.monsters[i].enemy, enemies.monsters[i].movespeed, LEFT);
                            else if (enemies.monsters[i].checkPointReached[4]) move(enemies.monsters[i].enemy, enemies.monsters[i].movespeed, DOWN);
                            else if (enemies.monsters[i].checkPointReached[3]) move(enemies.monsters[i].enemy, enemies.monsters[i].movespeed, LEFT);
                            else if (enemies.monsters[i].checkPointReached[2]) move(enemies.monsters[i].enemy, enemies.monsters[i].movespeed, UP);
                            else if (enemies.monsters[i].checkPointReached[1]) move(enemies.monsters[i].enemy, enemies.monsters[i].movespeed, RIGHT);
                            else if (enemies.monsters[i].checkPointReached[0]) move(enemies.monsters[i].enemy, enemies.monsters[i].movespeed, DOWN);
                            else move(enemies.monsters[i].enemy, enemies.monsters[i].movespeed, RIGHT);
                            if (enemies.monsters[i].enemy[0].getGlobalBounds().intersects(map_layout.Tiles.tiles[22].getGlobalBounds())) enemies.monsters[i].checkPointReached[0] = true;
                            if (enemies.monsters[i].enemy[0].getGlobalBounds().intersects(map_layout.Tiles.tiles[173].getGlobalBounds())) enemies.monsters[i].checkPointReached[1] = true;
                            if (enemies.monsters[i].enemy[0].getGlobalBounds().intersects(map_layout.Tiles.tiles[167].getGlobalBounds())) enemies.monsters[i].checkPointReached[2] = true;
                            if (enemies.monsters[i].enemy[0].getGlobalBounds().intersects(map_layout.Tiles.tiles[72].getGlobalBounds())) enemies.monsters[i].checkPointReached[3] = true;
                            if (enemies.monsters[i].enemy[0].getGlobalBounds().intersects(map_layout.Tiles.tiles[85].getGlobalBounds())) enemies.monsters[i].checkPointReached[4] = true;
                            if (enemies.monsters[i].enemy[0].getGlobalBounds().intersects(map_layout.Tiles.tiles[143].getGlobalBounds())) enemies.monsters[i].checkPointReached[5] = true;
                            if (enemies.monsters[i].enemy[0].getGlobalBounds().intersects(map_layout.Tiles.tiles[118].getGlobalBounds())) enemies.monsters[i].checkPointReached[6] = true;
                            if (enemies.monsters[i].enemy[0].getGlobalBounds().intersects(map_layout.Tiles.tiles[24].getGlobalBounds())) enemies.monsters[i].checkPointReached[7] = true;
                            if (enemies.monsters[i].enemy[0].getGlobalBounds().intersects(map_layout.Tiles.tiles[56].getGlobalBounds())) enemies.monsters[i].checkPointReached[8] = true;
                            enemies.spawn(enemies.monsters[i].enemy, window, this);
                        }
                    }

                    for (int i = 0; i < numEnemies; i++) {
                        if (enemies.monsters[i].alive) {
                            enemies.monsters[i].hpBar.update(enemies.monsters[i].currentHP, enemies.monsters[i].HP, enemies.monsters[i].enemy[0]);
                            window.draw(enemies.monsters[i].hpBar);
                        }
                    }

                    for (unsigned int l = 0; l < enemies.monsters.size(); l++) {
                        if (enemies.monsters[l].alive) {
                            waveGoing = true;
                        }
                    }

                    enemies.monsters[0].spawned = true;
                    if (numEnemies < enemies.monsters.size() && waveTimer.getElapsedTime().asMilliseconds() > enemies.timeBetweenSpawn) {
                        waveTimer.restart();
                        enemies.monsters[numEnemies].spawned = true;
                        numEnemies++;
                    }

                    if (!waveGoing) {
                        waveStarted = false;
                        waveNum++;
                        numEnemies = 1;
                        difficultyMultiplier += 0.1f;
                        waveTimer.restart();
                        enemies.monsters.clear();
                    }

                }
                bulletsEnded = true;
                for (int i = 0; i < towers.size(); i++) {
                    window.draw(towers[i]->getSprite());
                    if (!waveGoing) towers[i]->bullets.clear();
                    if (towers[i]->bullets.size()) bulletsEnded = false;
                    if (!towers[i]->lockedOn) {
                        towers[i]->findTarget(enemies);
                        towers[i]->shoot(enemies);
                        towers[i]->updateBullets(window, enemies);
                        for (unsigned int l = 0; l < enemies.monsters.size(); l++) {
                            if (enemies.monsters[l].killed) {
                                enemies.monsters[l].killed = false;
                                gold += enemies.monsters[l].bounty;
                            }
                        }
                    }
                    towers[i]->loseTarget();
                }

                if (showMenu) {
                    window.draw(build_menu);
                }

                ss.str("");
            }else {
                window.draw(game_background);
                sf::Text lost; lost.setFont(font); lost.setCharacterSize(72); lost.setFillColor(sf::Color::Black); lost.setPosition(sf::Vector2f(676, 400));
                sf::Text quit; quit.setFont(font); quit.setCharacterSize(72); quit.setFillColor(sf::Color::Black); quit.setPosition(sf::Vector2f(1200, 700));
                lost.setString("You lost :(");
                window.draw(lost);
                quit.setString("Quit");
                window.draw(quit);
                Quit.setPosition(sf::Vector2f(1210, 730));
                if (isMouseIn(window, Quit)) {
                    sf::StandardCursor Cursor(sf::StandardCursor::HAND);
                    Cursor.set(window.getSystemHandle());
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) window.close();
                }
            }
        }

        if (gameState == PLAYING_TWO) {
            window.draw(multiplayer);
        }

        timeUntilStart = 30;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){

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
                }
                else if (gameState == PLAYING_SOLO) {
                    if (showMenu && isMouseIn(window, build_menu.menu)) {
                        if (!map_layout.Tiles.isTower[build_menu.tile_id]) {   //building
                            if (isMouseIn(window, build_menu.button1)) {
                                build_menu.build(&gold, towers, ARROW, map_layout);
                            }
                            if (isMouseIn(window, build_menu.button2)) {
                                build_menu.build(&gold, towers, SPLASH, map_layout);
                            }
                            if (isMouseIn(window, build_menu.button3)) {
                                build_menu.build(&gold, towers, MAGIC, map_layout);
                            }
                        }
                        else {  //upgarde
                            if (towers[build_menu.tower_index]->level < 5) {
                                if (isMouseIn(window, build_menu.button1)) {
                                    towers[build_menu.tower_index]->levelUp(&gold);
                                    if (towers[build_menu.tower_index]->upgraded) {
                                        build_menu.isTower(towers, build_menu.tile_id);
                                        towers[build_menu.tower_index]->upgraded = false;
                                    }
                                }
                                if (isMouseIn(window, build_menu.button2)) {
                                    build_menu.sell(&gold, towers, map_layout);
                                    build_menu.isNotTower(map_layout.Tiles.tiles[build_menu.tile_id], build_menu.tile_id);
                                }
                            }
                            else if (towers[build_menu.tower_index]->level == 5) {
                                if (isMouseIn(window, build_menu.button1)) {
                                    towers[build_menu.tower_index]->upgrade1(&gold);
                                    if (towers[build_menu.tower_index]->upgraded) {
                                        build_menu.isTower(towers, build_menu.tile_id);
                                        towers[build_menu.tower_index]->upgraded = false;
                                    }
                                }
                                if (isMouseIn(window, build_menu.button2)) {
                                    towers[build_menu.tower_index]->upgrade2(&gold);
                                    if (towers[build_menu.tower_index]->upgraded) {
                                        build_menu.isTower(towers, build_menu.tile_id);
                                        towers[build_menu.tower_index]->upgraded = false;
                                    }
                                }
                                if (isMouseIn(window, build_menu.button3)) {
                                    build_menu.sell(&gold, towers, map_layout);
                                    build_menu.isNotTower(map_layout.Tiles.tiles[build_menu.tile_id], build_menu.tile_id);
                                }
                            }
                            else {
                                if (isMouseIn(window, build_menu.button1)) {
                                    build_menu.sell(&gold, towers, map_layout);
                                    build_menu.isNotTower(map_layout.Tiles.tiles[build_menu.tile_id], build_menu.tile_id);
                                }
                            }
                        }
                    }
                    else {
                        showMenu = false;
                        for (int l = 0; l < 209; l++) {
                            if (isMouseIn(window, map_layout.Tiles.tiles[l]) && !map_layout.Tiles.isPath[l]) {
                                showMenu = true;
                                if (map_layout.Tiles.isTower[l]) {
                                    build_menu.isTower(towers, l);
                                }
                                else {
                                    build_menu.isNotTower(map_layout.Tiles.tiles[l], l);
                                }
                            }
                        }
                    }
                }
                if (isMouseIn(window, startWaveButton) && !waveStarted) {
                    timeUntilStart = 0;
                }   
            }
            
        }
        window.display();

    }
}


