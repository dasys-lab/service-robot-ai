#include "srg/tasks/TaskFactory.h"
#include "srg/SRGWorldModel.h"
#include "srg/tasks/Task.h"

#include <engine/AlicaEngine.h>

#include <iterator>
#include <sstream>
namespace srg
{
namespace tasks
{
TaskFactory::TaskFactory(srg::SRGWorldModel* wm)
        : wm(wm)
{
}

Task* TaskFactory::createTask(const control::SpeechAct& speechAct)
{
    Task* curTask;
    std::vector<std::string> tokens = split(speechAct.text);
    if (tokens[0].find("move") != std::string::npos) {
        curTask = new Task(TaskType::Move);
        setCoordinate(tokens[1], curTask);
    } else if (tokens[0].find("put") != std::string::npos){
        curTask = new Task(TaskType::PutDown);
        setCoordinate(tokens[1], curTask);
    } else if (tokens[0].find("pick") != std::string::npos) {
        curTask = new Task(TaskType::PickUp);
        setObjectID(tokens[1], curTask);
    } else if (tokens[0].find("close") != std::string::npos) {
        curTask = new Task(TaskType::Close);
        setObjectID(tokens[1], curTask);
    } else if (tokens[0].find("open") != std::string::npos) {
        curTask = new Task(TaskType::Open);
        setObjectID(tokens[1], curTask);
    } else if (tokens[0].find("search") != std::string::npos) {
        curTask = new Task(TaskType::Search);
        setObjectType(tokens[1], curTask);
    } else if (tokens[0].find("transport") != std::string::npos) {
        curTask = new Task(TaskType::Search);
        setObjectType(tokens[1], curTask);

        // The first move task depends on the location of the found object
        Task* nextTask = new Task(TaskType::Move);
        setIDFields(speechAct, nextTask);
        curTask->nextTask = nextTask;
        Task* tmpTask = nextTask;

        // The pick up task depends on the location of the found object
        nextTask = new Task(TaskType::PickUp);
        setIDFields(speechAct, nextTask);
        tmpTask->nextTask = nextTask;
        tmpTask = nextTask;

        nextTask = new Task(TaskType::Move);
        setIDFields(speechAct, nextTask);
        setCoordinate(tokens[2], nextTask);
        tmpTask->nextTask = nextTask;
        tmpTask = nextTask;

        nextTask = new Task(TaskType::PutDown);
        setIDFields(speechAct, nextTask);
        setCoordinate(tokens[2], nextTask);
        tmpTask->nextTask = nextTask;
    }

    if (curTask) {
        setIDFields(speechAct, curTask);
    }
    return curTask;
}

void TaskFactory::setObjectType(const std::string& objecTypeToken, Task* task)
{
    if (objecTypeToken == "CupBlue") {
        task->objectType = srg::world::ObjectType::CupBlue;
    } else if (objecTypeToken == "CupYellow") {
        task->objectType = srg::world::ObjectType::CupYellow;
    } else if (objecTypeToken == "CupRed") {
        task->objectType = srg::world::ObjectType::CupRed;
    }
}

void TaskFactory::setObjectID(const std::string& objectIDToken, Task* task)
{
    uint32_t idInt = std::stoi(objectIDToken);
    task->objectID = this->wm->getEngine()->getId<uint32_t>(idInt);
}

void TaskFactory::setCoordinate(const std::string& coordToken, Task* task)
{
    std::string xCoordString = coordToken.substr(0, coordToken.find(","));
    std::string yCoordString = coordToken.substr(coordToken.find(",") + 1);
    srg::world::Coordinate coord = srg::world::Coordinate(std::stoi(xCoordString), std::stoi(yCoordString));
    if (!isValid(coord, task->type)) {
        std::cerr << "[TaskFactory] This coordinates are outside of the world: " << coord << std::endl;
    }
    task->coordinate = coord;
}

void TaskFactory::setIDFields(const control::SpeechAct& speechAct, Task* task)
{
    task->senderID = speechAct.senderID;
    task->receiverID = speechAct.receiverID;
    task->actID = speechAct.actID;
    task->previousActID = speechAct.previousActID;
}

std::vector<std::string> TaskFactory::split(const std::string& taskText)
{
    std::istringstream iss(taskText);
    std::vector<std::string> tokens((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
    return tokens;
}

bool TaskFactory::isValid(const srg::world::Coordinate& coord, TaskType type)
{
    if (!this->wm->sRGSimData.getWorld()->getCell(coord)) {
        std::cerr << "[TaskFactory] Coordinates are outside of the world: " << coord << std::endl;
        return false;
    }
    if (type == TaskType::PutDown || type == TaskType::PickUp || type == TaskType::Close || type == TaskType::Open) {
        auto ownPos = this->wm->sRGSimData.getOwnPositionBuffer().getLastValidContent();
        auto diff = (ownPos.value() - coord).abs();
        if (diff.x > 2 && diff.y > 2) {
            std::cerr << "[TaskFactory] Coordinates are out of reach: " << coord << std::endl;
            return false;
        }
    }
    return true;
}
} // namespace tasks
} // namespace srg