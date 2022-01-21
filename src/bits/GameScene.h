#pragma once

#include <vector>

#include <gf/Scene.h>
#include <gf/RenderTarget.h>
#include <gf/RenderStates.h>
#include <gf/Action.h>
#include <Pomme/Object.h>

#include "BallEntity.h"
#include "FramerateEntity.h"

namespace bcb
{
    struct GameHub;

    class GameScene : public gf::Scene
    {
    public:

    public:
        GameScene(GameHub& game);

    protected:
        virtual void doHandleActions(gf::Window& window);
        virtual void doShow() override;

    private:
        GameHub& m_game;

        gf::Action m_addBallAction;
        gf::Action m_removeBallAction;

        std::vector<BallEntity> m_balls;

        FramerateEntity m_framerateEntity;
    };
}