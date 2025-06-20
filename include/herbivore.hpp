#pragma once
#include "entity.hpp"

class HerbivoreFish : public Entity {
public:
    HerbivoreFish(int x, int y);
    HerbivoreFish(const HerbivoreFish& other);
    HerbivoreFish(HerbivoreFish&& other) noexcept;
    HerbivoreFish& operator=(const HerbivoreFish& other);
    HerbivoreFish& operator=(HerbivoreFish&& other) noexcept;
    ~HerbivoreFish() override;
    void tick(Ocean& ocean) override;
    Type type() const override;
    static const char* name() noexcept { return "HerbivoreFish"; }
private:
    int _hunger;
};