#include "entity.hpp"

Entity::Entity(int x, int y, int lifespan)
    : _x(x), _y(y), _age(0), _lifespan(lifespan) {}

Entity::~Entity() {}

int Entity::x() const { return _x; }
int Entity::y() const { return _y; }
bool Entity::alive() const { return _age < _lifespan; }