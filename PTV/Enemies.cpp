#include "Header.h"

void Attackers::spawn(sf::Sprite enemy[3], sf::RenderWindow& window, Game* game) {
    enemy[0].move(sf::Vector2f(0.05, 0)); enemy[1].move(sf::Vector2f(0.05, 0)); enemy[2].move(sf::Vector2f(0.05, 0));
    if (game->animation.getElapsedTime().asSeconds() / 0.15f > 4)game->animation.restart();
    else if (game->animation.getElapsedTime().asSeconds() / 0.15f > 3)window.draw(enemy[2]);
    else if (game->animation.getElapsedTime().asSeconds() / 0.15f > 2)window.draw(enemy[1]);
    else if (game->animation.getElapsedTime().asSeconds() / 0.15f > 1)window.draw(enemy[0]);
    else if (game->animation.getElapsedTime().asSeconds() / 0.15f > 0)window.draw(enemy[1]);
}

void Attackers::prepareWave(int numberOfEnemies, sf::Sprite attacker[]) {
    std::vector<std::array<sf::Sprite, 3>> sprites;
    for (int i = 0; i < numberOfEnemies; i++) {
        sprites.push_back(std::array<sf::Sprite, 3>());
        sprites[i][0] = attacker[0]; sprites[i][1] = attacker[1]; sprites[i][2] = attacker[2];
    }
    enemies enmy;
    for (int i = 0; i < numberOfEnemies; i++) {
        
        this->monsters.push_back(enmy);
        this->monsters[i].enemy[0] = sprites[i][0]; this->monsters[i].enemy[1] = sprites[i][1]; this->monsters[i].enemy[2] = sprites[i][2];
        this->monsters[i].alive = true;
    }

}