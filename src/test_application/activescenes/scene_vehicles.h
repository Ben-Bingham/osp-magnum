/**
 * Open Space Program
 * Copyright © 2019-2022 Open Space Program Project
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

#include "scenarios.h"

namespace testapp { struct VehicleData; }

namespace testapp::scenes
{

osp::Session setup_parts(
        Builder_t& rBuilder,
        osp::ArrayView<entt::any> const topData,
        osp::Tags& rTags,
        osp::Session const& scnCommon,
        osp::TopDataId const idResources);

osp::Session setup_vehicle_spawn(
        Builder_t& rBuilder,
        osp::ArrayView<entt::any> topData,
        osp::Tags& rTags,
        osp::Session const& scnCommon,
        osp::Session const& parts);

osp::Session setup_vehicle_spawn_vb(
        Builder_t& rBuilder,
        osp::ArrayView<entt::any> topData,
        osp::Tags& rTags,
        osp::Session const& scnCommon,
        osp::Session const& prefabs,
        osp::Session const& parts,
        osp::Session const& vehicleSpawn,
        osp::TopDataId const idResources);

osp::Session setup_vehicle_spawn_rigid(
        Builder_t& rBuilder,
        osp::ArrayView<entt::any> topData,
        osp::Tags& rTags,
        osp::Session const& scnCommon,
        osp::Session const& physics,
        osp::Session const& prefabs,
        osp::Session const& parts,
        osp::Session const& vehicleSpawn);

osp::Session setup_test_vehicles(
        Builder_t& rBuilder,
        osp::ArrayView<entt::any> topData,
        osp::Tags& rTags,
        osp::Session const& scnCommon,
        osp::TopDataId const idResources);

}
