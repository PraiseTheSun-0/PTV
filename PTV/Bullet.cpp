#include "Header.h"

Bullet::Bullet(sf::Sprite projectile, sf::Sprite from, sf::Sprite target, int target_id) {
	this->projectile = projectile;
	this->from.x = from.getPosition().x + from.getLocalBounds().width/2;
	this->from.y = from.getPosition().y + from.getLocalBounds().height / 2;
	this->target.x = target.getPosition().x + from.getLocalBounds().width / 2;
	this->target.y = target.getPosition().y + target.getLocalBounds().height / 2;
	this->targetId = target_id;
	this->projectile.setPosition(this->from.x, this->from.y);
}

void Bullet::update(){
	if (this->isBeam) {
		float X = this->target.x - this->from.x;
		float Y = this->target.y - this->from.y;
		float rotation = (atan2(Y, X)) * 180 / 3.14159265 - 45;
		this->projectile.setRotation(rotation);
		if (time.getElapsedTime().asMilliseconds() > 600) {
			this->reached = true;
		}
	}
	else if (this->isProjectile) {
		this->projectile.setOrigin(this->projectile.getLocalBounds().width / 2, (this->projectile.getLocalBounds().height / 2));
		float X = this->target.x - this->from.x;
		float Y = this->target.y - this->from.y;
		float rotation = (atan2(Y, X) * 180 / 3.14159265 + 135);
		this->projectile.setRotation(rotation);

		float distance = sqrt((this->projectile.getPosition().x - this->target.x) * (this->projectile.getPosition().x - this->target.x) + (this->projectile.getPosition().y - this->target.y) * (this->projectile.getPosition().y - this->target.y));

		if (distance > 10) {

			this->projectile.setPosition(this->projectile.getPosition().x - 0.1 * this->speed * (this->projectile.getPosition().x - this->target.x) / distance,
										 this->projectile.getPosition().y - 0.1 * this->speed * (this->projectile.getPosition().y - this->target.y) / distance);
		}
		else { 
			this->reached = true;
		}

	}
}
