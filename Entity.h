// Entity class declaration

#pragma once
#include <string>
#include "Position2D.h"

class Entity
{
public:
	Entity(); // default constructor

	// Get and set entity attributes (icon, name, position)
	char getIcon() const;
	void setIcon(char icon);

	std::string getName() const;
	void setName(std::string name);

	Position2D getPosition() const;
	void setPosition(Position2D position);

private:
	// Entity representation on the map
	char icon = 'E';
	std::string name = "Entity";
	Position2D position = Position2D{ 1, 1 };

};

