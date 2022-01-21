#include "FramerateEntity.h"

#include <gf/Coordinates.h>
#include <gf/Shapes.h>
#include <gf/Text.h>
#include <gf/Log.h>
#include <Pomme/Value.h>

namespace bcb
{
    FramerateEntity::FramerateEntity(gf::ResourceManager& manager, int priority)
    : gf::Entity(priority)
    , m_font(manager.getFont("Aquifer.otf"))
    , m_framerate(0u)
    , m_framerateTime(0.f)
    {
    }

    void FramerateEntity::update(gf::Time time)
    {
        m_framerateTime += time.asSeconds();

        if (m_framerateTime >= 0.05f)
        {
            m_framerate = 1.f / time.asSeconds();
            m_framerateTime = 0.f;
        }
    }

    void FramerateEntity::render(gf::RenderTarget& target, const gf::RenderStates& states)
    {
        gf::Coordinates coordinates(target);

        gf::Text text;

        text.setFont(m_font);
        text.setString("Framerate : " + std::to_string(m_framerate));
        text.setPosition(coordinates.getRelativePoint({0.0f, 0.05f}));
        text.setCharacterSize(coordinates.getRelativeCharacterSize(0.05f));
        text.setColor(gf::Color::Red);

        text.draw(target, states);
    }
}