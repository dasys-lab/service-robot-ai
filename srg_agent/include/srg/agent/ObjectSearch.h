#pragma once

#include "srg/agent/SearchCell.h"
#include "srg/agent/SearchCellSorter.h"

#include <srg/world/Coordinate.h>
#include <srg/world/Object.h>
#include <srg/world/ObjectType.h>
#include <srg/world/RoomType.h>

#include <cstdint>
#include <set>
#include <unordered_set>
#include <vector>

namespace essentials
{
class SystemConfig;
}

namespace srg
{
class World;
class SRGWorldModel;
namespace world
{
class Cell;
}
namespace agent
{
class ObjectSearch
{
public:
    ObjectSearch(srg::world::ObjectType objectType, srg::SRGWorldModel* wm);

    void addRoomType(srg::world::RoomType type);
    void update();
    const srg::world::Cell* getNextCell();

private:
    void getVisibleAndFrontCells(srg::world::Coordinate& ownCoord, const srg::World* world, std::unordered_set<const srg::world::Cell*>& visible,
            std::unordered_set<const srg::world::Cell*>& front);
    void trace(const srg::World* world, srg::world::Coordinate& from, srg::world::Coordinate& to, std::unordered_set<const srg::world::Cell*>& visible,
            std::unordered_set<const srg::world::Cell*>& front);

    essentials::SystemConfig* sc;
    srg::SRGWorldModel* wm;
    uint32_t sightLimit;
    uint32_t updateCounter;

    srg::world::ObjectType objectType;
    std::unordered_set<srg::world::RoomType> roomTypes;

    std::set<SearchCell, SearchCellSorter>* fringe;
    std::unordered_set<const srg::world::Cell*>* visited;
};

} // namespace agent
} // namespace srg