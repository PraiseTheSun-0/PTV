#include "Header.h"

void move(sf::Sprite enemy[3], float movespeed, DIRECTION direction) {
    switch (direction){
    case UP:
        for (int i = 0; i < 3; i++) {
            enemy[i].move(sf::Vector2f(0, -movespeed));
        }
        break;
    case RIGHT:
        for (int i = 0; i < 3; i++) {
            enemy[i].move(sf::Vector2f(movespeed, 0));
        }
        break;
    case DOWN:
        for (int i = 0; i < 3; i++) {
            enemy[i].move(sf::Vector2f(0, movespeed));
        }
        break;
    case LEFT:
        for (int i = 0; i < 3; i++) {
            enemy[i].move(sf::Vector2f(-movespeed, 0));
        }
        break;
    }
}

void Attackers::spawn(sf::Sprite enemy[3], sf::RenderWindow& window, Game* game) {

    if (game->animation.getElapsedTime().asSeconds() / 0.15f > 4)game->animation.restart();
    else if (game->animation.getElapsedTime().asSeconds() / 0.15f > 3)window.draw(enemy[2]);
    else if (game->animation.getElapsedTime().asSeconds() / 0.15f > 2)window.draw(enemy[1]);
    else if (game->animation.getElapsedTime().asSeconds() / 0.15f > 1)window.draw(enemy[0]);
    else if (game->animation.getElapsedTime().asSeconds() / 0.15f > 0)window.draw(enemy[1]);
}

void Attackers::prepareWave(ENEMY_TYPE enemyType, sf::Sprite attacker[], sf::Vector2f spawn, float waveMultiplier) {
    int enemiesNum = 3, HPmultiplier = 1, moveSpeedMultiplier = 1, livesTakenMultiplier = 1;
    double bountyMultiplier = 1.0;
    bool armored = false, flying = false;

    switch (enemyType) {
    case BAT:
        enemiesNum = this->numOfEnemies[0];
        HPmultiplier = 2;
        moveSpeedMultiplier = 3;
        bountyMultiplier = 1.4;
        flying = true;
        this->timeBetweenSpawn = 1000;
        break;
    case ORC:
        enemiesNum = this->numOfEnemies[1];
        HPmultiplier = 4;
        moveSpeedMultiplier = 1;
        bountyMultiplier = 2.1;
        livesTakenMultiplier = 3;
        armored = true;
        this->timeBetweenSpawn = 3000;
        break;
    case GOBLIN:
        enemiesNum = this->numOfEnemies[2];
        HPmultiplier = 1;
        moveSpeedMultiplier = 2;
        bountyMultiplier = 1.2;
        this->timeBetweenSpawn = 400;
        break;
    }
    enemiesNum = int(enemiesNum * waveMultiplier);

    std::vector<std::array<sf::Sprite, 3>> sprites;
    for (int i = 0; i < enemiesNum; i++) {
        sprites.push_back(std::array<sf::Sprite, 3>());
        sprites[i][0] = attacker[0]; sprites[i][1] = attacker[1]; sprites[i][2] = attacker[2];
    }

    enemies enmy;
    for (int i = 0; i < enemiesNum; i++) {
        
        this->monsters.push_back(enmy);

        this->monsters[i].enemy[0] = sprites[i][0]; this->monsters[i].enemy[1] = sprites[i][1]; this->monsters[i].enemy[2] = sprites[i][2];
        this->monsters[i].enemy[0].setPosition(spawn);  this->monsters[i].enemy[1].setPosition(spawn);  this->monsters[i].enemy[2].setPosition(spawn);
        this->monsters[i].alive = true;
        this->monsters[i].HP = int(this->monsters[i].HP * HPmultiplier * (waveMultiplier * waveMultiplier * waveMultiplier));
        this->monsters[i].currentHP = this->monsters[i].HP;
        this->monsters[i].movespeed *= moveSpeedMultiplier;
        this->monsters[i].bounty *= bountyMultiplier;
        this->monsters[i].livesTaken *= livesTakenMultiplier;
        this->monsters[i].armored = armored;
        this->monsters[i].flying = flying;
    }

}