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
#include "client/systems/civilizationinfopanel.h"

#include "common/components/player.h"
#include "common/components/organizations.h"
#include "common/components/economy.h"
#include "common/util/utilnumberdisplay.h"

#include "client/systems/gui/systooltips.h"

void cqsp::client::systems::CivilizationInfoPanel::Init() {}

void cqsp::client::systems::CivilizationInfoPanel::DoUI(int delta_time) {
    // Get the ui
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    if (to_display) {
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.2,
            ImGui::GetIO().DisplaySize.y * 0.4));
    } else {
        ImGui::SetNextWindowSize(ImVec2(-1, -1));
    }
    ImGui::Begin("Civilization Window");
    if (ImGui::Button("Show/Hide Civilization")) {
        to_display = !to_display;
    }
    if (to_display) {
        CivInfoPanel();
    }
    ImGui::End();
}

void cqsp::client::systems::CivilizationInfoPanel::DoUpdate(int delta_time) {}

void cqsp::client::systems::CivilizationInfoPanel::CivInfoPanel() {
    ImGui::Text("Information");
    // Get player
    entt::entity player = GetUniverse()
                              .view<common::components::Civilization,
                                    common::components::Player>()
                              .front();
    ImGui::TextFmt("{}", player);
    if (player == entt::null) {
        return;
    }
    // Make hoverable
    gui::EntityTooltip(GetUniverse(), player);
    if (GetUniverse().any_of<common::components::Wallet>(player)) {
        auto& wallet = GetUniverse().get<common::components::Wallet>(player);
        ImGui::TextFmt("Reserves: {}", util::LongToHumanString(wallet.GetBalance()));
    }

    // Collate all the owned stuff
    auto view = GetUniverse().view<common::components::Governed>();
    ImGui::Separator();
    ImGui::Text("Owned Cities");

    ImGui::BeginChild("ownedcitiespanel");
    for (auto entity : view) {
        if (GetUniverse().get<common::components::Governed>(entity).governor == player) {
            ImGui::TextFmt("{}", client::systems::gui::GetName(GetUniverse(), entity));
            gui::EntityTooltip(GetUniverse(), entity);
        }
    }
    ImGui::EndChild();
}
