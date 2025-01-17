/* Conquer Space
* Copyright (C) 2021 Conquer Space
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once

#include "engine/renderer/renderer2d.h"
#include "common/universe.h"
#include "engine/application.h"
#include "engine/graphics/renderable.h"

namespace cqsp::client::systems {
class GalaxyRenderer {
 public:
    GalaxyRenderer(cqsp::common::Universe &, cqsp::engine::Application &);
    void Initialize();
    void OnTick();
    void Render(float deltaTime);
    void Update(float deltaTime);
    void DoUI(float deltaTime);

 private:
    cqsp::common::Universe &m_universe;
    cqsp::engine::Application &m_app;

    cqsp::engine::Renderable star_system;
    cqsp::engine::Renderer2D *renderer;

    double scroll = 1;

    double previous_mouseX;
    double previous_mouseY;

    double view_x = 0;
    double view_y = 0;

    entt::entity mouse_over;

    glm::vec2 ConvertCoords(double x, double y);

    asset::ShaderProgram_t circle_shader;

    cqsp::engine::Mesh *mesh;
};
}  // namespace cqsp::client::systems
