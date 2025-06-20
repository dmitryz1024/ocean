#pragma once
#include <memory>
#include <stdexcept>

class Ocean;

class Entity {
public:
    enum class Type { Sand, Algae, Herbivore, Predator };
    Entity(int x, int y, int lifespan);
    virtual ~Entity();
    virtual void tick(Ocean& ocean) = 0;
    virtual Type type() const = 0;
    int x() const;
    int y() const;
    bool alive() const;
protected:
    int _x, _y;
    int _age, _lifespan;
};