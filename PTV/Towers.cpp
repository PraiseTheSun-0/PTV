#include "Header.h"

float findRange(sf::Sprite tower, sf::Sprite enemy) {
	float x = abs(tower.getPosition().x + tower.getLocalBounds().width/2 - enemy.getPosition().x - enemy.getLocalBounds().width/2);
	float y = abs(tower.getPosition().y + tower.getLocalBounds().height / 2 - enemy.getPosition().y - enemy.getLocalBounds().height / 2);
	return sqrt(x * x + y * y);
}

void Towers::setTowerType(TOWER_TYPE tower_type) {
	this->towerType = tower_type;
}

TOWER_TYPE Towers::getTowerType() {
	return this->towerType;
}

void Towers::setSprite(sf::Sprite sprite) {
	this->tower = sprite;
}

sf::Sprite Towers::getSprite() {
	return this->tower;
}

void Towers::setPosition(sf::Vector2f position) {
	this->tower.setPosition(position);
	this->tower.move(sf::Vector2f(0, -8));
};

void Towers::setCost(int cost) {
	this->cost = cost;
}

int Towers::getCost(){
	return this->cost;
}

void Towers::setDamage(int damage) {
	this->damage = damage;
}

int Towers::getDamage() {
	return this->damage;
}

void Towers::setAttackSpeed(float attack_speed) {
	this->attackSpeed = attack_speed;
}

float Towers::getAttackSpeed() {
	return this->attackSpeed;
}

void Towers::setRange(float range) {
	this->range = range;
}

float Towers::getRange() {
	return this->range;
}

void Towers::findTarget(Attackers enemies) {
	int lockedOnTo = 0;
	if (this->hitsFlying || (enemies.monsters.size() > 0 && !enemies.monsters[0].flying)) {
		for (unsigned int i = 0; i < enemies.monsters.size(); i++) {
			if (enemies.monsters[i].alive && enemies.monsters[i].spawned && findRange(this->getSprite(), enemies.monsters[i].enemy[0]) < this->getRange()) {

				this->targetId.push_back(i);
				lockedOnTo++;
			}
			if (lockedOnTo == this->hitsTargets) break;
		}
	}
}

void Towers::loseTarget() {
	this->targetId.clear();
}

void Towers::updateBullets(sf::RenderWindow& window, Attackers& enemies) {
	for (int i = 0; i < this->bullets.size(); i++) {
		bullets[i]->update();
		if (!bullets[i]->reached) {
			window.draw(bullets[i]->projectile);
		}
		else {
			if (this->hitsThroughArmor || !enemies.monsters[bullets[i]->targetId].armored) {
				enemies.monsters[bullets[i]->targetId].currentHP -= this->getDamage();
				if (this->hasSplash) {
					for (unsigned int l = 0; l < enemies.monsters.size(); l++) {
						if (l == bullets[i]->targetId || !enemies.monsters[l].alive) continue;
						if(findRange(enemies.monsters[bullets[i]->targetId].enemy[0], enemies.monsters[l].enemy[0]) < 60 && enemies.monsters[l].alive) enemies.monsters[l].currentHP -= this->getDamage() * this->splashDamage;
					}
				}
			}
			else {
				enemies.monsters[bullets[i]->targetId].currentHP -= this->getDamage() / 2;
				if (this->hasSplash) {
					for (unsigned int l = 0; l < enemies.monsters.size(); l++) {
						if (l == bullets[i]->targetId || !enemies.monsters[l].alive) continue;
						if (findRange(enemies.monsters[bullets[i]->targetId].enemy[0], enemies.monsters[l].enemy[0]) < 60) enemies.monsters[l].currentHP -= this->getDamage() / 2 * this->splashDamage;
					}
				}
			}
			for (unsigned int p = 0; p < enemies.monsters.size(); p++) {
				if (enemies.monsters[p].currentHP <= 0 && enemies.monsters[p].alive) {
					enemies.monsters[p].alive = false;
					enemies.monsters[p].killed = true;
				}
			}
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}

void Towers::levelUp(int* gold) {
	if (int(this->getCost() * 0.7) <= *gold) {
		*gold -= int(this->getCost() * 0.7);
		this->level++;
		this->setCost(this->getCost() * 1.5);
		this->setDamage(this->getDamage() * 1.5);
		this->setAttackSpeed(this->getAttackSpeed() * 0.95);
		this->setRange(this->getRange() * 1.15);
		this->upgraded = true;
	}
}

ArrowTower::ArrowTower() {
	texture.loadFromFile("Resources/assets.png");
	sf::Sprite arrowTower(texture, sf::IntRect(93, 92, 80, 80));
	this->setSprite(arrowTower); 
	sf::Sprite projectile(texture, sf::IntRect(114, 195, 40, 40));
	this->projectile = projectile;

	this->setTowerType(ARROW);
	this->level = 1;
	this->setCost(40);
	this->setDamage(37);
	this->setAttackSpeed(0.7f);
	this->hitsFlying = true;
}

void ArrowTower::upgrade1(int* gold) {
	if (*gold >= 90) {
		*gold -= 90;
		sf::Sprite multishot(texture, sf::IntRect(175, 82, 80, 88));
		multishot.setPosition(this->getSprite().getPosition());
		this->setSprite(multishot);
		sf::Sprite projectile(texture, sf::IntRect(195, 195, 40, 40));
		this->projectile = projectile;

		this->level++;
		this->hitsTargets = 3;
		this->setDamage(int(this->getDamage() * 0.8));
		this->setAttackSpeed(this->getAttackSpeed() * 1.15);
		this->upgraded = true;
	}
}

void ArrowTower::upgrade2(int* gold) {
	if (*gold >= 90) {
		*gold -= 90;
		sf::Sprite ballista(texture, sf::IntRect(258, 92, 80, 80));
		ballista.setPosition(this->getSprite().getPosition());
		this->setSprite(ballista);
		sf::Sprite projectile(texture, sf::IntRect(274, 195, 40, 40));
		this->projectile = projectile;

		this->level += 2;
		this->hitsThroughArmor = true;
		this->setDamage(int(this->getDamage() * 2.7));
		this->setAttackSpeed(this->getAttackSpeed() * 1.2);
		this->upgraded = true;
	}
}

void ArrowTower::shoot(Attackers& enemies) {
	if (this->timer.getElapsedTime().asSeconds() > this->getAttackSpeed()) {
		for (unsigned int i = 0; i < this->targetId.size(); i++) {
			this->bullets.push_back(new Bullet(this->projectile, this->getSprite(), enemies.monsters[this->targetId[i]].enemy[0], this->targetId[i]));
			bullets[i]->isProjectile = true;
		}
		this->timer.restart();
	}
	
}

CannonTower::CannonTower() {
	texture.loadFromFile("Resources/assets.png");
	sf::Sprite cannonTower(texture, sf::IntRect(93, 251, 80, 80));
	this->setSprite(cannonTower);
	sf::Sprite projectile(texture, sf::IntRect(121, 338, 40, 40));
	this->projectile = projectile;

	this->setTowerType(SPLASH);
	this->level = 1;
	this->setCost(70);
	this->hasSplash = true;
	this->setDamage(210);
	this->setAttackSpeed(1.5f);
	this->setRange(130.0f);
}

void CannonTower::upgrade1(int* gold) {
	if (*gold >= 160) {
		*gold -= 160;
		sf::Sprite mortar(texture, sf::IntRect(175, 252, 80, 80));
		mortar.setPosition(this->getSprite().getPosition());
		this->setSprite(mortar);
		sf::Sprite projectile(texture, sf::IntRect(202, 338, 40, 40));
		this->projectile = projectile;

		this->level++;	
		this->setDamage(int(this->getDamage() * 1.5));
		this->splashDamage = 0.7;
		this->upgraded = true;
	}
}

void CannonTower::upgrade2(int* gold) {	
	if (*gold >= 160) {
		*gold -= 160;
		sf::Sprite anti_air(texture, sf::IntRect(263, 252, 80, 88));
		anti_air.setPosition(this->getSprite().getPosition());
		this->setSprite(anti_air);
		sf::Sprite projectile(texture, sf::IntRect(291, 338, 40, 40));
		this->projectile = projectile;

		this->level += 2;
		this->hitsFlying = true;
		this->setAttackSpeed(this->getAttackSpeed() * 0.8);
		this->upgraded = true;
	}
}

void CannonTower::shoot(Attackers& enemies) {
	if (this->timer.getElapsedTime().asSeconds() > this->getAttackSpeed()) {
		for (unsigned int i = 0; i < this->targetId.size(); i++) {
			this->bullets.push_back(new Bullet(this->projectile, this->getSprite(), enemies.monsters[this->targetId[i]].enemy[0], this->targetId[i]));
			bullets[i]->isProjectile = true;
			if (this->level == 6) bullets[i]->speed = 70;
		}
		this->timer.restart();
	}
}

MagicTower::MagicTower() {
	texture.loadFromFile("Resources/assets.png");
	sf::Sprite magicTower(texture, sf::IntRect(93, 411, 80, 84));
	this->setSprite(magicTower);
	sf::Sprite projectile(texture, sf::IntRect(110, 503, 40, 40));
	this->projectile = projectile;

	this->setTowerType(MAGIC);
	this->level = 1;
	this->setCost(55);
	this->setDamage(80);
	this->setAttackSpeed(1.1f);
	this->hitsFlying = true;
	this->hitsThroughArmor = true;
}

void MagicTower::upgrade1(int* gold) {
	if (*gold >= 130) {
		*gold -= 130;
		sf::Sprite magic(texture, sf::IntRect(173, 406, 80, 88));
		magic.setPosition(this->getSprite().getPosition());
		this->setSprite(magic);
		sf::Sprite projectile(texture, sf::IntRect(195, 502, 40, 40));
		this->projectile = projectile;

		this->level++;
		this->setDamage(int(this->getDamage() * 1.3));
		this->hasSplash = true;
		this->upgraded = true;
	}
}

void MagicTower::upgrade2(int* gold) {
	if (*gold >= 130) {
		*gold -= 130;
		sf::Sprite plague(texture, sf::IntRect(265, 408, 80, 88));
		plague.setPosition(this->getSprite().getPosition());
		this->setSprite(plague);

		this->level += 2;
		this->setDamage(int(this->getDamage() * 0.05));
		this->setRange(100.0f);
		this->setAttackSpeed(50);
		this->hitsTargets = 20;
		this->upgraded = true;
	}
}

void MagicTower::shoot(Attackers &enemies) {
	if (this->level <= 6) {
		if (this->timer.getElapsedTime().asSeconds() > this->getAttackSpeed()) {
			for (unsigned int i = 0; i < this->targetId.size(); i++) {
				this->bullets.push_back(new Bullet(this->projectile, this->getSprite(), enemies.monsters[this->targetId[i]].enemy[0], this->targetId[i]));
				bullets[i]->isBeam = true;
			}
			this->timer.restart();
		}
	}
	else {
		if (this->timer.getElapsedTime().asMilliseconds() > this->getAttackSpeed()) {
			for (unsigned int i = 0; i < this->targetId.size(); i++) {
				enemies.monsters[this->targetId[i]].currentHP -= this->getDamage();
				if (enemies.monsters[this->targetId[i]].currentHP < 0) {
					enemies.monsters[this->targetId[i]].alive = false; 
					enemies.monsters[this->targetId[i]].killed = true;
				}
			}
			this->timer.restart();
		}
	}
}
