// Member-function definitions for the Entity class

#include "Entity.h"

Entity::Entity()
{

}

std::string Entity::getName() const
{
	return name;
}

void Entity::setName(std::string n)
{
	name = n;
}

Position2D Entity::getPosition() const
{
	return position;
}

void Entity::setPosition(Position2D p)
{
	position = p;
}

char Entity::getIcon() const
{
	return icon;
}

void Entity::setIcon(char i)
{
	icon = i;
}