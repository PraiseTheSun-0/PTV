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