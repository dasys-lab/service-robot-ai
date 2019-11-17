#include "Behaviours/Search.h"
#include <memory>

/*PROTECTED REGION ID(inccpp1573419059418) ENABLED START*/
#include <srg/Robot.h>
#include <srg/SRGWorldModel.h>
#include <srg/robot/ObjectSearch.h>
#include <srg/tasks/TaskHandler.h>
#include <srg/world/Cell.h>
/*PROTECTED REGION END*/

namespace alica
{
/*PROTECTED REGION ID(staticVars1573419059418) ENABLED START*/
/*PROTECTED REGION END*/

Search::Search()
        : DomainBehaviour("Search")
{
    /*PROTECTED REGION ID(con1573419059418) ENABLED START*/
    activeTask = nullptr;
    search = nullptr;
    /*PROTECTED REGION END*/
}
Search::~Search()
{
    /*PROTECTED REGION ID(dcon1573419059418) ENABLED START*/
    /*PROTECTED REGION END*/
}
void Search::run(void* msg)
{
    /*PROTECTED REGION ID(run1573419059418) ENABLED START*/
    if (this->isSuccess()) {
        return;
    }

    if (!this->activeTask || this->activeTask->type != srg::tasks::TaskType::Search){// || this->activeTask->foundObject(this->wm)) {
        this->setSuccess();
        return;
    }

    this->search->update();
    const srg::world::Cell* cell = this->search->getNextCell();
    if (cell) {
        this->robot->move(cell->coordinate);
    } else {
        std::cout << "[Search] No cell received!" << std::endl;
    }
    /*PROTECTED REGION END*/
}
void Search::initialiseParameters()
{
    /*PROTECTED REGION ID(initialiseParameters1573419059418) ENABLED START*/
    // clean up
    delete search;
    delete activeTask;

    // init
    std::shared_ptr<const supplementary::InformationElement<srg::tasks::Task*>> task = this->wm->dialogueManager.taskHandler->getActiveTask();
    if (task && task->getInformation()->type == srg::tasks::TaskType::Search) {
        this->activeTask = new srg::tasks::Task(task->getInformation()->type);
        this->activeTask->coordinate = task->getInformation()->coordinate;
        this->activeTask->actID = task->getInformation()->actID;
        this->activeTask->previousActID = task->getInformation()->previousActID;
        this->activeTask->senderID = task->getInformation()->senderID;
        this->activeTask->receiverID = task->getInformation()->receiverID;
        this->activeTask->objectID = task->getInformation()->objectID;
        this->activeTask->objectType = task->getInformation()->objectType;
        this->search = new srg::robot::ObjectSearch(this->activeTask->objectType, this->wm);
    } else {
        this->activeTask = nullptr;
        this->search = nullptr;
    }
    /*PROTECTED REGION END*/
}
/*PROTECTED REGION ID(methods1573419059418) ENABLED START*/
/*PROTECTED REGION END*/

} /* namespace alica */
