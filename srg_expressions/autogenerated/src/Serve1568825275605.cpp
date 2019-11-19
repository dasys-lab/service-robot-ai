#include "Serve1568825275605.h"
/*PROTECTED REGION ID(eph1568825275605) ENABLED START*/
#include <srg/tasks/TaskHandler.h>
/*PROTECTED REGION END*/

using namespace alica;

namespace alicaAutogenerated
{
// Plan:Serve
/**
 *   Task: Serve  -> EntryPoint-ID: 1568825285315
 */
shared_ptr<UtilityFunction> UtilityFunction1568825275605::getUtilityFunction(Plan* plan)
{
    /*PROTECTED REGION ID(1568825275605) ENABLED START*/
    std::shared_ptr<UtilityFunction> defaultFunction = std::make_shared<DefaultUtilityFunction>(plan);
    return defaultFunction;
    /*PROTECTED REGION END*/
}
/**
 * Outgoing transition:
 *   - Name: 1568825457853, ConditionString: MovingTask received!, Comment: MISSING_COMMENT
 *
 * Abstractplans in current state:
 *   - Stop (1555602210283)
 *
 * Tasks in plan:
 *   - Serve (1555601344076) (Entrypoint: 1568825285315)
 *
 * States in plan:
 *   - WaitForTask (1568825288640)
 *   - MoveToPosition (1568825309813)
 *   - ManipulateObject (1571661663929)
 *   - TransportToPosition (1573418710533)
 *
 * Variables of plan:
 */
bool PreCondition1568825457853::evaluate(shared_ptr<RunningPlan> rp)
{
    /*PROTECTED REGION ID(1568825336792) ENABLED START*/
    auto taskSequence = this->wm->dialogueManager.taskHandler->getActiveTaskSequence();
    if (!taskSequence) {
        return false;
    }
    auto activeTask = taskSequence->getActiveTask();
    return activeTask && activeTask->type == srg::tasks::TaskType::Move && !activeTask->checkSuccess(this->wm);
    /*PROTECTED REGION END*/
}
/**
 * Outgoing transition:
 *   - Name: 1571661980674, ConditionString: Manipulate command!, Comment: MISSING_COMMENT
 *
 * Abstractplans in current state:
 *   - Stop (1555602210283)
 *
 * Tasks in plan:
 *   - Serve (1555601344076) (Entrypoint: 1568825285315)
 *
 * States in plan:
 *   - WaitForTask (1568825288640)
 *   - MoveToPosition (1568825309813)
 *   - ManipulateObject (1571661663929)
 *   - TransportToPosition (1573418710533)
 *
 * Variables of plan:
 */
bool PreCondition1571661980674::evaluate(shared_ptr<RunningPlan> rp)
{
    /*PROTECTED REGION ID(1571661739802) ENABLED START*/
    auto taskSequence = this->wm->dialogueManager.taskHandler->getActiveTaskSequence();
    if (!taskSequence) {
        return false;
    }
    auto activeTask = taskSequence->getActiveTask();
    return activeTask &&
           (activeTask->type == srg::tasks::TaskType::Open || activeTask->type == srg::tasks::TaskType::Close ||
                   activeTask->type == srg::tasks::TaskType::PutDown || activeTask->type == srg::tasks::TaskType::PickUp) &&
           !activeTask->checkSuccess(this->wm);
    /*PROTECTED REGION END*/
}
/**
 * Outgoing transition:
 *   - Name: 1573418732991, ConditionString: Received a transport task!, Comment: MISSING_COMMENT
 *
 * Abstractplans in current state:
 *   - Stop (1555602210283)
 *
 * Tasks in plan:
 *   - Serve (1555601344076) (Entrypoint: 1568825285315)
 *
 * States in plan:
 *   - WaitForTask (1568825288640)
 *   - MoveToPosition (1568825309813)
 *   - ManipulateObject (1571661663929)
 *   - TransportToPosition (1573418710533)
 *
 * Variables of plan:
 */
bool PreCondition1573418732991::evaluate(shared_ptr<RunningPlan> rp)
{
    /*PROTECTED REGION ID(1573418725423) ENABLED START*/
    auto taskSequence = this->wm->dialogueManager.taskHandler->getActiveTaskSequence();
    if (!taskSequence) {
        return false;
    }
    auto activeTask = taskSequence->getActiveTask();
    return activeTask && activeTask->type == srg::tasks::TaskType::Search && !activeTask->checkSuccess(this->wm);
    /*PROTECTED REGION END*/
}
/**
 * Outgoing transition:
 *   - Name: 1568825476581, ConditionString: Movement successful!, Comment: MISSING_COMMENT
 *
 * Abstractplans in current state:
 *   - Move (1568825137528)
 *
 * Tasks in plan:
 *   - Serve (1555601344076) (Entrypoint: 1568825285315)
 *
 * States in plan:
 *   - WaitForTask (1568825288640)
 *   - MoveToPosition (1568825309813)
 *   - ManipulateObject (1571661663929)
 *   - TransportToPosition (1573418710533)
 *
 * Variables of plan:
 */
bool PreCondition1568825476581::evaluate(shared_ptr<RunningPlan> rp)
{
    /*PROTECTED REGION ID(1568825392354) ENABLED START*/
    return rp->isAnyChildStatus(PlanStatus::Success);
    /*PROTECTED REGION END*/
}
/**
 * Outgoing transition:
 *   - Name: 1571661864299, ConditionString: Manipulation successful!, Comment: MISSING_COMMENT
 *
 * Abstractplans in current state:
 *   - Manipulate (1571687572903)
 *
 * Tasks in plan:
 *   - Serve (1555601344076) (Entrypoint: 1568825285315)
 *
 * States in plan:
 *   - WaitForTask (1568825288640)
 *   - MoveToPosition (1568825309813)
 *   - ManipulateObject (1571661663929)
 *   - TransportToPosition (1573418710533)
 *
 * Variables of plan:
 */
bool PreCondition1571661864299::evaluate(shared_ptr<RunningPlan> rp)
{
    /*PROTECTED REGION ID(1571661809581) ENABLED START*/
    return rp->isAnyChildStatus(PlanStatus::Success);
    /*PROTECTED REGION END*/
}
/**
 * Outgoing transition:
 *   - Name: 1573418838905, ConditionString: Any children success, Comment: MISSING_COMMENT
 *
 * Abstractplans in current state:
 *   - Transport (1573418869596)
 *
 * Tasks in plan:
 *   - Serve (1555601344076) (Entrypoint: 1568825285315)
 *
 * States in plan:
 *   - WaitForTask (1568825288640)
 *   - MoveToPosition (1568825309813)
 *   - ManipulateObject (1571661663929)
 *   - TransportToPosition (1573418710533)
 *
 * Variables of plan:
 */
bool PreCondition1573418838905::evaluate(shared_ptr<RunningPlan> rp)
{
    /*PROTECTED REGION ID(1573418821209) ENABLED START*/
    for (auto entry : rp->getChildren()) {
        if (std::string("Success").compare(getPlanStatusName(entry->getStatus())) == 0) {
            std::cout << "Plan: " << entry->getActivePlan()->getName() << " is "
                      << getPlanStatusName(entry->getStatus()) << std::endl;
        } else {
//            std::cout << ".";
        }
    }
    return rp->isAnyChildStatus(PlanStatus::Success);
    /*PROTECTED REGION END*/
}
} // namespace alicaAutogenerated
