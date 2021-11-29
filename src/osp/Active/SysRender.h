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

#include "drawing.h"


namespace osp::active
{

/**
 * Stores the name of the renderer to be used by a rendering agent
 */
struct ACompRenderer
{
    std::string m_name{"default"};
};


class SysRender
{
public:

    /**
     * @brief Adds newly created and updated drawables to RenderGroups using
     *        their DrawAssigners
     *
     * @param rScene [ref] Scene with ACtxRenderGroups
     */
    static void update_material_assign(
            ACtxRenderGroups& rGroups,
            acomp_storage_t<ACompMaterial>& rMaterials);

    /**
     * @brief Remove entities from draw functions
     *
     * @param rScene [ref] Scene with ACtxRenderGroups
     */
    static void update_material_delete(
            ACtxRenderGroups& rGroups,
            acomp_storage_t<ACompMaterial>& rMaterials,
            acomp_view_t<const ACompDelete> viewDelete);

    /**
     * @brief Update the m_transformWorld of entities with ACompTransform and
     *        ACompHierarchy.
     *
     * Intended for physics interpolation
     */
    static void update_hierarchy_transforms(
            acomp_storage_t<ACompHierarchy> const& hier,
            acomp_view_t<ACompTransform> const& viewTf,
            acomp_storage_t<ACompDrawTransform>& rDrawTf);

}; // class SysRender

} // namespace osp::active
