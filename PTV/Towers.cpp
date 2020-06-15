#include "Header.h"

Towers::Towers(sf::Sprite sprite) {
	Towers::setSprite(sprite);
}

void Towers::setSprite(sf::Sprite sprite) {
	this->tower = sprite;
}

sf::Sprite Towers::getSprite() {
	return this->tower;
}