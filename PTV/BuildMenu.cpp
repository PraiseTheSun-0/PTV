#include "Header.h"

BuildMenu::BuildMenu() {
	texture.loadFromFile("Resources/assets.psd", sf::IntRect(1275, 498, 324, 398));
	menuBackground.setTexture(texture);
}