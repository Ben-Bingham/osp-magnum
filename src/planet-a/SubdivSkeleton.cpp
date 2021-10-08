/**
 * Open Space Program
 * Copyright © 2019-2021 Open Space Program Project
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

#include "SubdivSkeleton.h"

using namespace planeta;

static SubdivSkeleton create_skeleton_icosahedron(float rad)
{
    // Create an Icosahedron. Blender style, so there's a vertex directly on
    // top and directly on the bottom. Basicly, a sandwich of two pentagons,
    // rotated 180 apart from each other, and each 1/sqrt(5) above and below
    // the origin.
    //
    // Icosahedron indices viewed from above (Z)
    //
    //          5
    //  4
    //
    //        0      1
    //
    //  3
    //          2
    //
    // Useful page from wolfram:
    // https://mathworld.wolfram.com/RegularPentagon.html
    //
    // The 'radius' of the pentagons are NOT 1.0, as they are slightly above or
    // below the origin. They have to be slightly smaller to keep their
    // distance to the 3D origin as 1.0.
    //
    // it works out to be (2/5 * sqrt(5)) ~~ 90% the size of a typical pentagon
    //
    // Equations 5..8 from the wolfram page:
    // c1 = 1/4 * ( sqrt(5) - 1 )
    // c2 = 1/4 * ( sqrt(5) + 1 )
    // s1 = 1/4 * sqrt( 10 + 2*sqrt(5) )
    // s2 = 1/4 * sqrt( 10 - 2*sqrt(5) )
    //
    // Now multiply by (2/5 * sqrt(5)), using auto-simplify
    // let m = (2/5 * sqrt(5))
    // cxA = m * c1 = 1/2 - sqrt(5)/10
    // cxB = m * c2 = 1/2 + sqrt(5)/10
    // syA = m * s1 = 1/10 * sqrt( 10 * (5 + sqrt(5)) )
    // syN = m * s2 = 1/10 * sqrt( 10 * (5 - sqrt(5)) )

    using std::sqrt; // if only sqrt was constexpr

    float const pnt = rad * ( 2.0f/5.0f * sqrt(5.0f) );
    float const hei = rad * ( 1.0f / sqrt(5.0f) );
    float const cxA = rad * ( 1.0f/2.0f - sqrt(5.0f)/10.0f );
    float const cxB = rad * ( 1.0f/2.0f + sqrt(5)/10.0f );
    float const syA = rad * ( 1.0f/10.0f * sqrt( 10.0f*(5.0f + sqrt(5.0f)) ) );
    float const syB = rad * ( 1.0f/10.0f * sqrt( 10.0f*(5.0f - sqrt(5.0f)) ) );

    std::array<osp::Vector3, 12> const icosahedronVrtx
    {{
        {0.0f,   0.0f,    rad}, // top point

        { pnt,   0.0f,    hei}, // 1 top pentagon
        { cxA,   -syA,    hei}, // 2
        {-cxB,   -syB,    hei}, // 3
        {-cxB,    syB,    hei}, // 4
        { cxA,    syA,    hei}, // 5

        {-pnt,   0.0f,   -hei}, // 6 bottom pentagon
        {-cxA,   -syA,   -hei}, // 7
        { cxB,   -syB,   -hei}, // 8
        { cxB,    syB,   -hei}, // 9
        {-cxA,    syA,   -hei}, // 10

        {0.0f,   0.0f,   -rad}  // 11 bottom point
    }};

    // Create the skeleton

    SubdivSkeleton skeleton;

    for (osp::Vector3 const vec : icosahedronVrtx)
    {
        VrtxId vrtx = skeleton.m_vrtxTree.add_root();
    }

    return skeleton;
}
