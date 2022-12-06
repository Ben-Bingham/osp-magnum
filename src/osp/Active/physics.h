/**
 * Open Space Program
 * Copyright © 2019-2020 Open Space Program Project
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

#include "activetypes.h"

#include "../CommonPhysics.h"
#include "../types.h"
#include "../id_map.h"

namespace osp::active
{

//using RigidBodyId_t = uint32_t;

/**
 * @brief Represents the shape of an entity
 */
struct ACompShape
{
    phys::EShape m_shape{phys::EShape::None};
};

/**
 * @brief Generic Mass and inertia intended for entities
 */
struct ACompSubBody
{
    Vector3 m_offset;
    Vector3 m_inertia;
    float m_mass;
};

/**
 * @brief Physics components and other data needed to support physics in a scene
 */
struct ACtxPhysics
{
//    lgrn::IdRegistryStl<RigidBodyId_t>      m_rigidBodyIds;

//    // Each rigid body is given 128 bits to enable/disable 'Factors'
//    // Factors determine which physics calculations are required for a certain
//    // rigid body, such as gravity, thurst, lift, and/or drag.
//    static constexpr std::size_t            smc_intsPerFactor = 2;
//    std::vector<uint64_t>                   m_rigidBodyFactors;

//    IdMap_t<ActiveEnt, RigidBodyId_t>       m_entToRigidBody;
//    std::vector<ActiveEnt>                  m_rigidBodyToEnt;

    std::vector<phys::EShape>       m_shape;
    EntSet_t                        m_hasColliders;

    acomp_storage_t<ACompSubBody>   m_ownDyn;
    acomp_storage_t<ACompSubBody>   m_totalDyn;

    Vector3                         m_originTranslate;
    EntVector_t                     m_bodyDirty;
    EntVector_t                     m_colliderDirty;
    EntVector_t                     m_inertiaDirty;

    std::vector< std::pair<ActiveEnt, Vector3> > m_setVelocity;

}; // struct ACtxPhysics


}
