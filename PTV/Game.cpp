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

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Protect the Village");
    /*sf::Clock animation;
    sf::Clock waveTimer;
    sf::Event event;*/
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
    sf::Sprite Bat1(assets, sf::IntRect(479, 123, 50, 40));
    sf::Sprite Bat2(assets, sf::IntRect(529, 123, 50, 40));
    sf::Sprite Bat3(assets, sf::IntRect(582, 123, 50, 40));
    

    GAME_STATE gameState = START_SCREEN;
    sf::RectangleShape SinglePlayer(sf::Vector2f(435, 55)), Multiplayer(sf::Vector2f(395, 55)), Quit(sf::Vector2f(165, 50)), BuildMenu(sf::Vector2f(350, 600));

    BuildMenu.setFillColor(sf::Color(144)); BuildMenu.setPosition(sf::Vector2f(1600, 900)); //todo remove

    MapLayout map_layout(PLAYING_SOLO);
    Enemies enemies;
    static bool showMenu = false;

    while (window.isOpen()) {

        window.clear();
        sf::StandardCursor Cursor(sf::StandardCursor::NORMAL);
        Cursor.set(window.getSystemHandle());


        if (gameState == START_SCREEN && waveTimer.getElapsedTime().asSeconds() <= 1.0f) {  //todo 4 sec
            window.draw(logo);
        }
        if (gameState == START_SCREEN && waveTimer.getElapsedTime().asSeconds() > 1.0f) {  //todo 4 sec
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
            enemies.spawn(window, Bat1, Bat2, Bat3, this);

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
                        window.clear();
                    }
                    if (isMouseIn(window, Multiplayer)) {
                        gameState = PLAYING_TWO;
                        window.clear();
                    }
                    if (isMouseIn(window, Quit)) {
                        window.close();
                    }
                }

                if (gameState == PLAYING_SOLO) {
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

MapLayout::MapLayout(GAME_STATE game_state) {
	int tile_number = 0;

	for (int i = 0; i < 209; i++) {
		Tiles.tiles.push_back(sf::RectangleShape(sf::Vector2f(84, 81)));
		Tiles.isPath.push_back(false);
		Tiles.isTower.push_back(false);

	}

	if (game_state == PLAYING_SOLO) {
		for (float k = bound_y; k < 900; k += 81) {
			for (float i = bound_x; i < 1600; i += 84) {
				Tiles.tiles[tile_number].setPosition(sf::Vector2f(i, k));
				tile_number++;
			}
		}
		for (int i = 19; i < 22; i++)Tiles.isPath[i] = true;
		Tiles.isPath[40] = true;
		for (int i = 43; i < 57; i++)Tiles.isPath[i] = true;
		Tiles.isPath[59] = true; Tiles.isPath[62] = true; Tiles.isPath[78] = true; Tiles.isPath[81] = true;
		for (int i = 86; i < 91; i++)Tiles.isPath[i] = true;
		Tiles.isPath[97] = true; Tiles.isPath[100] = true; Tiles.isPath[105] = true; Tiles.isPath[109] = true; Tiles.isPath[116] = true;
		for (int i = 119; i < 125; i++)Tiles.isPath[i] = true;
		Tiles.isPath[128] = true; Tiles.isPath[135] = true; Tiles.isPath[105] = true; Tiles.isPath[147] = true;
		for (int i = 154; i < 167; i++)Tiles.isPath[i] = true;
	}

	if (game_state == PLAYING_TWO) {	//todo
		for (float k = bound_y; k < 900; k += 81) {
			for (float i = bound_x; i < 1600; i += 84) {
				Tiles.tiles[tile_number].setPosition(sf::Vector2f(i, k));
				tile_number++;
			}
		}

	}

}


void Enemies::spawn(sf::RenderWindow &window, sf::Sprite &enemies1, sf::Sprite &enemies2, sf::Sprite &enemies3, Game *game) {
    enemies1.move(sf::Vector2f(0.05, 0)); enemies2.move(sf::Vector2f(0.05, 0)); enemies3.move(sf::Vector2f(0.05, 0));
    if (game->animation.getElapsedTime().asSeconds() / 0.15f > 4)game->animation.restart();
    else if (game->animation.getElapsedTime().asSeconds()/0.15f > 3)window.draw(enemies3);
    else if (game->animation.getElapsedTime().asSeconds()/0.15f > 2)window.draw(enemies2);
    else if (game->animation.getElapsedTime().asSeconds()/0.15f > 1)window.draw(enemies1);
    else if (game->animation.getElapsedTime().asSeconds() / 0.15f > 0)window.draw(enemies2);
}