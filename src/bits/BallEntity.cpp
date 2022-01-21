#include "BallEntity.h"

#include "GameScene.h"
#include "GameHub.h"

#include <gf/Coordinates.h>
#include <gf/Shapes.h>
#include <gf/Text.h>
#include <gf/Log.h>
#include <Pomme/Value.h>

namespace bcb
{
    BallEntity::BallEntity(GameHub& game, int priority)
    : gf::Entity(priority)
    , m_game(game)
    , m_ballinstance(nullptr)
    {
        m_ballinstance = m_game.vm.newInstance("Ball");
        m_game.vm.interpretMethodFunction(m_ballinstance, m_game.vm.getFunctionName("init"), {});
    }

    void BallEntity::update(gf::Time time)
    {
        m_game.vm.interpretMethodFunction(m_ballinstance, m_game.vm.getFunctionName("update", "float"), {FLOAT_VAL(time.asSeconds())});
    }

    void BallEntity::render(gf::RenderTarget& target, const gf::RenderStates& states)
    {
        gf::Coordinates coordinates(target);

        Pomme::Value* positionValue = m_ballinstance->getField(m_game.vm, "position");
        assert(positionValue != nullptr && IS_OBJ_PTR(*positionValue));

        Pomme::ObjInstance* positionInstance = m_game.vm.getObject<Pomme::ObjInstance>(AS_OBJ_PTR(*positionValue));
        assert(positionInstance != nullptr);

        gf::Vector2f pos(AS_FLOAT(*(positionInstance->getField(m_game.vm, "x"))), AS_FLOAT(*(positionInstance->getField(m_game.vm, "y"))));

        //gf::Log::debug("pos.x : %f, pos.y : %f\n", AS_FLOAT(*(positionInstance->getField(m_game.vm, "x"))), AS_FLOAT(*(positionInstance->getField(m_game.vm, "y"))));

        gf::CircleShape ball;

        ball.setColor(gf::Color::White);
        ball.setAnchor(gf::Anchor::Center);
        ball.setRadius(coordinates.getRelativeSize({0.05f, 0.f}).x);
        ball.setPosition(coordinates.getRelativePoint(pos));

        ball.draw(target, states);
    }
}