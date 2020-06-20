#include "Header.h"

BuildMenu::BuildMenu() {

	font.loadFromFile("Resources/font.ttf");
	texture.loadFromFile("Resources/assets.png", sf::IntRect(1275, 498, 324, 398));
	menuBackground.setTexture(texture);
	menuBackground.setPosition(sf::Vector2f(1275, 498));
	text1.setFont(font); text1.setCharacterSize(30); text1.setFillColor(sf::Color::Black); text1.setPosition(sf::Vector2f(1275, 505));
	text2.setFont(font); text2.setCharacterSize(27); text2.setFillColor(sf::Color::Black); text2.setPosition(sf::Vector2f(1275, 580));
	text3.setFont(font); text3.setCharacterSize(27); text3.setFillColor(sf::Color::Black); text3.setPosition(sf::Vector2f(1275, 655));
	text4.setFont(font); text4.setCharacterSize(27); text4.setFillColor(sf::Color::Black); text4.setPosition(sf::Vector2f(1275, 730));
	menu.setSize(sf::Vector2f(324, 398)); menu.setPosition(sf::Vector2f(1275, 498));
	button1.setSize(sf::Vector2f(265, 50)); button1.setPosition(sf::Vector2f(1275, 580));
	button2.setSize(sf::Vector2f(265, 50)); button2.setPosition(sf::Vector2f(1275, 655));
	button3.setSize(sf::Vector2f(265, 50)); button3.setPosition(sf::Vector2f(1275, 730));
}

void BuildMenu::isNotTower(sf::RectangleShape build_position, int tileId) {
	text1.setString(" Build:");
	text2.setString(" Arrow tower (40)");
	text3.setString(" Splash tower (70)");
	text4.setString(" Magic tower (55)");
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
			this->isTower(towers, this->tile_id);
		}
		break;
	case SPLASH:
		if (70 <= *gold) {
			towers.push_back(new CannonTower());
			*gold -= towers[towers.size() - 1]->getCost();
			towers[towers.size() - 1]->setPosition(buildPosition);
			map_layout.Tiles.isTower[this->tile_id] = true;
			towers[towers.size() - 1]->towerId = this->tile_id;
			this->isTower(towers, this->tile_id);
		}
		break;
	case MAGIC:
		if (55 <= *gold) {
			towers.push_back(new MagicTower());
			*gold -= towers[towers.size() - 1]->getCost();
			towers[towers.size() - 1]->setPosition(buildPosition);
			map_layout.Tiles.isTower[this->tile_id] = true;
			towers[towers.size() - 1]->towerId = this->tile_id;
			this->isTower(towers, this->tile_id);
		}
		break;
	}
}

void BuildMenu::isTower(std::vector<Towers*> &towers, int tower_id) {

	unsigned int i;
	for (i = 0; i < towers.size(); i++) {
		if (towers[i]->towerId == tower_id) break;
	}

	tower_index = i;
	this->tile_id = tower_id;

	std::ostringstream os;
	std::string towerInfo;
	if (towers[i]->level <= 5) {
		if (towers[i]->level < 5) {
			switch (towers[i]->getTowerType()) {
			case ARROW:
				os << " Archer tower ";
				break;
			case SPLASH:
				os << " Splash tower ";
				break;
			case MAGIC:
				os << " Magic tower ";
				break;
			}
			os << towers[i]->level;
			towerInfo = os.str();
			text1.setString(towerInfo);

			os.str("");
			os << " Level Up (" << int(towers[i]->getCost() * 0.7) << ")";
			towerInfo = os.str();
			text2.setString(towerInfo);

			os.str("");
			os << " Sell (+" << int(towers[i]->getCost() * 0.5) << ")";
			towerInfo = os.str();
			text3.setString(towerInfo);

			text4.setString("");
		}
		else {
			switch (towers[i]->getTowerType()) {
			case ARROW:
				os << " Archer tower ";
				os << towers[i]->level;
				towerInfo = os.str();
				text1.setString(towerInfo);
				os.str("");

				text2.setString(" Multishot (90)");

				text3.setString(" Ballista (90)");

				os << " Sell (+" << int(towers[i]->getCost() * 0.5) << ")";
				towerInfo = os.str();
				text4.setString(towerInfo);

				break;

			case SPLASH:
				os << " Splash tower ";
				os << towers[i]->level;
				towerInfo = os.str();
				text1.setString(towerInfo);
				os.str("");

				text2.setString(" Mortar (160)");

				text3.setString(" Anti-air (160)");

				os << " Sell (+" << int(towers[i]->getCost() * 0.5) << ")";
				towerInfo = os.str();
				text4.setString(towerInfo);

				break;

			case MAGIC:
				os << " Magic tower ";
				os << towers[i]->level;
				towerInfo = os.str();
				text1.setString(towerInfo);
				os.str("");

				text2.setString(" Magic+ (130)");

				text3.setString(" Plague (130)");

				os << " Sell (+" << int(towers[i]->getCost() * 0.5) << ")";
				towerInfo = os.str();
				text4.setString(towerInfo);

				break;
			}
		}
	}
	else if (towers[i]->level == 6) {
		switch (towers[i]->getTowerType()) {
		case ARROW:
			os << " Multishot ";
			break;
		case SPLASH:
			os << " Mortar ";
			break;
		case MAGIC:
			os << " Magic+ ";
			break;
		}
		towerInfo = os.str();
		text1.setString(towerInfo);
		os.str("");

		os << " Sell (+" << int(towers[i]->getCost() * 0.5) << ")";
		towerInfo = os.str();
		text2.setString(towerInfo);

		text3.setString("");

		text4.setString("");
	}
	else {
	switch (towers[i]->getTowerType()) {
	case ARROW:
		text1.setString(" Ballista");
		break;
	case SPLASH:
		text1.setString(" Anti-air ");
		break;
	case MAGIC:
		text1.setString(" Plague ");
		break;
	}
	os << " Sell (+" << int(towers[i]->getCost() * 0.5) << ")";
	towerInfo = os.str();
	text2.setString(towerInfo);

	text3.setString("");

	text4.setString("");
	}
}

void BuildMenu::sell(int* gold, std::vector<Towers*>& towers, MapLayout &map_layout) {
	map_layout.Tiles.isTower[tile_id] = false;
	*gold += towers[tower_index]->getCost() * 0.5;
	sf::RectangleShape rect;
	rect.setPosition(towers[tower_index]->getSprite().getPosition());
	this->isNotTower(rect, tile_id);
	delete towers[tower_index];
	towers.erase(towers.begin() + tower_index);
}