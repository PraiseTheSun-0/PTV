#include "Header.h"

HPBar::HPBar() {
	back.setSize(sf::Vector2f(44, 10));
	max.setSize(sf::Vector2f(40, 6));
	current.setSize(sf::Vector2f(40, 6));
	back.setFillColor(sf::Color::Black);
	max.setFillColor(sf::Color::White);
	current.setFillColor(sf::Color::Red);
}

void HPBar::update(int currentHP, int maxHP, sf::Sprite sprite) {
	this->back.setPosition(sprite.getPosition());
	this->back.move(sf::Vector2f(20, -8));
	this->max.setPosition(back.getPosition());
	this->max.move(sf::Vector2f(2, 2));
	this->current.setPosition(this->max.getPosition());
	this->current.setSize(sf::Vector2f(currentHP / float(maxHP) * 40, 6));
}