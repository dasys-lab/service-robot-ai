#include "srg/dialogue/MoveTask.h"

#include "srg/SRGWorldModel.h"
#include <srgsim/SRGEnums.h>
#include <srgsim/containers/Coordinate.h>
#include <srgsim/world/Cell.h>
#include <srgsim/world/Object.h>
#include <srgsim/world/World.h>

namespace srg
{
namespace dialogue
{
bool MoveTask::checkSuccess(SRGWorldModel* wm) const
{
    auto ownCoord = wm->sRGSimData.getOwnPositionBuffer().getLastValidContent();
    if (!ownCoord.has_value()) {
        return false;
    }

    bool goalIsBlocked = false;
    const srgsim::Cell* goalCell = wm->sRGSimData.getWorld()->getCell(this->coordinate);
    if (goalCell->type == srgsim::Type::Wall) {
        goalIsBlocked = true;
    }

    if (!goalIsBlocked) {
        for (auto object : goalCell->getObjects()) {
            if (object->getType() == srgsim::Type::Door) {
                goalIsBlocked = true;
                break;
            }
        }
    }

    srgsim::Coordinate diff = this->coordinate - ownCoord.value();
    if ((goalIsBlocked && diff.x < 2 && diff.y < 2) || (diff.x == 0 && diff.y == 0)) {
        std::cout << "MoveTask::checkSuccess(): SUCCESS!" << std::endl;
        return true;
    }
    return false;
}
} // namespace dialogue
} // namespace srg
