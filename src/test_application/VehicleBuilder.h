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

#include <osp/Resource/blueprints.h>

namespace testapp
{

using partindex_t = uint32_t;
using machindex_t = uint32_t;

/**
 * Used to easily create Vehicle blueprints
 */
class VehicleBuilder
{
public:

    /**
     * Emplaces a BlueprintPart. This function searches the prototype vector
     * to see if the part has been added before.
     * @param part
     * @param translation
     * @param rotation
     * @param scale
     * @return Resulting blueprint part
     */
    partindex_t add_part(osp::DependRes<osp::PrototypePart>& part,
                  const osp::Vector3& translation,
                  const osp::Quaternion& rotation,
                  const osp::Vector3& scale);

    /**
     * Emplace a BlueprintWire
     * @param fromPart
     * @param fromMachine
     * @param fromPort
     * @param toPart
     * @param toMachine
     * @param toPort
     */
    void add_wire(partindex_t fromPart, machindex_t fromMachine, osp::WireOutPort fromPort,
                  partindex_t toPart, machindex_t toMachine, osp::WireInPort toPort);

    partindex_t part_count() const noexcept { return m_vehicle.m_blueprints.size(); }

    template<typename MACH_T>
    osp::BlueprintMachine* find_machine_by_type(partindex_t part)
    {
        osp::machine_id_t const id = osp::mach_id<MACH_T>();
        if (id >= m_vehicle.m_machines.size())
        {
            return nullptr; // no machines of type
        }

        for (osp::BlueprintMachine& machineBp : m_vehicle.m_machines[id])
        {
            if (machineBp.m_blueprintIndex == part)
            {
                return &machineBp;
            }
        }
        return nullptr;
    }

    osp::BlueprintVehicle&& export_move() { return std::move(m_vehicle); };
    osp::BlueprintVehicle export_copy() { return m_vehicle; };

private:
    osp::BlueprintVehicle m_vehicle;

};


}
