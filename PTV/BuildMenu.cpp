#include "Header.h"

BuildMenu::BuildMenu() {

	font.loadFromFile("Resources/font.ttf");
	texture.loadFromFile("Resources/assets.psd", sf::IntRect(1275, 498, 324, 398));
	menuBackground.setTexture(texture);
	menuBackground.setPosition(sf::Vector2f(1275, 498));
	text1.setFont(font); text1.setCharacterSize(30); text1.setFillColor(sf::Color::Black); text1.setPosition(sf::Vector2f(1275, 505));
	text2.setFont(font); text2.setCharacterSize(27); text2.setFillColor(sf::Color::Black); text2.setPosition(sf::Vector2f(1275, 580));
	text3.setFont(font); text3.setCharacterSize(27); text3.setFillColor(sf::Color::Black); text3.setPosition(sf::Vector2f(1275, 655));
	text4.setFont(font); text4.setCharacterSize(27); text4.setFillColor(sf::Color::Black); text4.setPosition(sf::Vector2f(1275, 730));
	button1.setSize(sf::Vector2f(265, 50)); button1.setPosition(sf::Vector2f(1275, 580));
	button2.setSize(sf::Vector2f(265, 50)); button2.setPosition(sf::Vector2f(1275, 655));
	button3.setSize(sf::Vector2f(265, 50)); button3.setPosition(sf::Vector2f(1275, 730));
}

void BuildMenu::isNotTower(sf::RectangleShape build_position, int tileId) {
	text2.setString("Arrow tower (40)");
	text3.setString("Splash tower (70)");
	text4.setString("Magic tower (55)");
	buildPosition = build_position.getPosition();
	this->tile_id = tileId;
}

void BuildMenu::build(int* gold, std::vector<Towers*> &towers, TOWER_TYPE tower_type, MapLayout &map_layout) {
	switch (tower_type) {
	case ARROW:
		if (40 <= *gold) {
			towers.push_back(new ArrowTower());
			*gold -= towers[towers.size()-1]->getCost();
			towers[towers.size()-1]->setPosition(buildPosition);
			map_layout.Tiles.isTower[this->tile_id] = true;
			towers[towers.size() - 1]->towerId = this->tile_id;
		}
		break;
	case SPLASH:
		if (70 <= *gold) {
			towers.push_back(new CannonTower());
			*gold -= towers[towers.size() - 1]->getCost();
			towers[towers.size() - 1]->setPosition(buildPosition);
			map_layout.Tiles.isTower[this->tile_id] = true;
			towers[towers.size() - 1]->towerId = this->tile_id;
		}
		break;
	case MAGIC:
		if (55 <= *gold) {
			towers.push_back(new MagicTower());
			*gold -= towers[towers.size() - 1]->getCost();
			towers[towers.size() - 1]->setPosition(buildPosition);
			map_layout.Tiles.isTower[this->tile_id] = true;
			towers[towers.size() - 1]->towerId = this->tile_id;
		}
		break;
	}
}