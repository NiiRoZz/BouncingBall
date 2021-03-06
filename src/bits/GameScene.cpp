#include "GameScene.h"

#include "GameHub.h"

namespace bcb
{
    GameScene::GameScene(GameHub& game)
    : gf::Scene(game.getRenderer().getSize())
    , m_game(game)
    , m_addBallAction("AddBall")
    , m_removeBallAction("RemoveBall")
    , m_framerateEntity(game.resources)
    {
        game.getWindow().setFramerateLimit(0u);
        game.getWindow().setVerticalSyncEnabled(false);

        setClearColor(gf::Color::Black);

        m_addBallAction.addKeycodeKeyControl(gf::Keycode::Up);
        m_addBallAction.setInstantaneous();
        addAction(m_addBallAction);

        m_removeBallAction.addKeycodeKeyControl(gf::Keycode::Down);
        m_removeBallAction.setInstantaneous();
        addAction(m_removeBallAction);

        addHudEntity(m_framerateEntity);

        m_balls.reserve(100u);
    }

    void GameScene::doHandleActions([[maybe_unused]] gf::Window& window)
    {
        if (m_addBallAction.isActive() && m_balls.size() < 100u)
        {
            addHudEntity(m_balls.emplace_back(m_game));
        }

        if (m_removeBallAction.isActive() && m_balls.size() > 0u)
        {
            removeHudEntity(&m_balls[m_balls.size() - 1]);
            m_balls.pop_back();
        }
    }

    void GameScene::doShow()
    {
        gf::Scene::doShow();

        bool ok = m_game.vm.linkGlobalNative(m_game.vm.getFunctionName("rand"), [] (Pomme::VirtualMachine& vm, int argCount, Pomme::Value* args)
        {
            assert(argCount == 0);

            return FLOAT_VAL((float) std::rand() / RAND_MAX);
        });

        assert(ok);

        addHudEntity(m_balls.emplace_back(m_game));
    }
}