#pragma once

#include <gf/Entity.h>
#include <gf/ResourceManager.h>
#include <Pomme/Object.h>

namespace bcb
{
    class GameHub;

    class FramerateEntity: public gf::Entity
    {
    public:
        FramerateEntity(gf::ResourceManager& manager, int priority = 0);

        virtual void update(gf::Time time) override;

        virtual void render(gf::RenderTarget& target, const gf::RenderStates& states) override;
    private:
        gf::Font& m_font;

        std::size_t m_framerate;
        float m_framerateTime;
    };
}