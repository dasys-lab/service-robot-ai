#include "BehaviourCreator.h"
#include "Behaviours/Spawn.h"
#include "Behaviours/Stop.h"
#include "engine/BasicBehaviour.h"

namespace alica
{

BehaviourCreator::BehaviourCreator() {}

BehaviourCreator::~BehaviourCreator() {}

std::shared_ptr<BasicBehaviour> BehaviourCreator::createBehaviour(long behaviourConfId)
{
    switch (behaviourConfId) {
    case 1555602210283:
        return std::make_shared<Stop>();
        break;
    case 1558533534825:
        return std::make_shared<Spawn>();
        break;
    default:
        std::cerr << "BehaviourCreator: Unknown behaviour requested: " << behaviourConfId << std::endl;
        throw new std::exception();
        break;
    }
}
} // namespace alica
