#include <iostream>


#include "../../types.h"

#include "../Satellites/SatActiveArea.h"

#include "FtrPlanet.h"

namespace osp
{

FtrPlanet::FtrPlanet(Object3D& object, PlanetData& data) : AbstractFeature3D(object)
{
    std::cout << "Planet feature created\n";
}

FtrPlanet::~FtrPlanet()
{
}

}
