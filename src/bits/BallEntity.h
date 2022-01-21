#pragma once

#include <gf/Entity.h>
#include <gf/Grid.h>
#include <gf/ResourceManager.h>
#include <Pomme/Object.h>

namespace bcb
{
    class GameHub;

    class BallEntity: public gf::Entity
    {
    public:
        BallEntity(GameHub& game, int priority = 0);

        virtual void update(gf::Time time) override;

        virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;
    private:
        GameHub& m_game;

        Pomme::ObjInstance* m_ballinstance;
    };
}