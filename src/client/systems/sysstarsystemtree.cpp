/*
 * Copyright 2021 Conquer Space
 */
#include "client/systems/sysstarsystemtree.h"

#include <string>

#include "client/systems/sysstarsystemrenderer.h"
#include "common/components/bodies.h"
#include "common/components/name.h"

void conquerspace::client::systems::SysStarSystemTree::Init() {}

void conquerspace::client::systems::SysStarSystemTree::DoUI(int delta_time) {
    namespace cqspb = conquerspace::components::bodies;
    using RenderingStarSystem =
        conquerspace::client::systems::RenderingStarSystem;
    // Get star system
    entt::entity ent =
        GetApp().GetUniverse().view<RenderingStarSystem>().front();
    if (ent == entt::null) {
        return;
    }
    auto& star_system = GetApp().GetUniverse().get<cqspb::StarSystem>(ent);
    ImGui::SetNextWindowPos(ImVec2(30, ImGui::GetIO().DisplaySize.y - 30),
                            ImGuiCond_Always, ImVec2(0.f, 1.f));
    ImGui::SetNextWindowSize(ImVec2(200, 400), ImGuiCond_Always);
    ImGui::Begin("Star System (Will add name soon)",
                NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    if (ImGui::BeginListBox("Star Systems", ImVec2(-FLT_MIN, -FLT_MIN))) {
        int index = 0;
        for (auto entity : star_system.bodies) {
            bool is_selected = (selected_index == index);
            std::string star_system_name = fmt::format("{}", entity);
            if (GetApp().GetUniverse().all_of<conquerspace::components::Name>(entity)) {
                star_system_name = fmt::format(
                    "{}", GetApp().GetUniverse().get<conquerspace::components::Name>(entity)
                            .name);
            }

            if (ImGui::Selectable(fmt::format("{}", entity).c_str(), is_selected)) {
                // Selected object
                selected_index = index;
            }
            index++;
        }
        ImGui::EndListBox();
    }
    ImGui::End();
}

void conquerspace::client::systems::SysStarSystemTree::DoUpdate(
    int delta_time) {}
