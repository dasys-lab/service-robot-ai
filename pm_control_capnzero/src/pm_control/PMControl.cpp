#include "pm_control/PMControl.h"

#include "pm_control/Communication.h"
#include "pm_control/ControlledExecutable.h"
#include "pm_control/ControlledProcessManager.h"

#include <process_manager/ExecutableMetaData.h>
#include <process_manager/RobotExecutableRegistry.h>

#include <QApplication>

#include <SystemConfig.h>

namespace pm_control
{
PMControl::PMControl()
        : widget_(0)
        , guiUpdateTimer(nullptr)
{
    widget_ = new QWidget();
    widget_->setAttribute(Qt::WA_AlwaysShowToolTips, true);
    ui_.setupUi(widget_);

    // Initialise the GUI refresh timer
    this->guiUpdateTimer = new QTimer();
    QObject::connect(guiUpdateTimer, SIGNAL(timeout()), this, SLOT(run()));
    this->guiUpdateTimer->start(200);

    setCentralWidget(widget_);

    this->sc = essentials::SystemConfig::getInstance();

    this->msgTimeOut = chrono::duration<double>((*this->sc)["ProcessManaging"]->get<unsigned long>("PMControl.timeLastMsgReceivedTimeOut", NULL));

    this->pmRegistry = process_manager::RobotExecutableRegistry::get();

    /* Initialise the registry data structure for better performance
     * with data from Globals.conf and ProcessManaging.conf file. */

    // Register robots from Globals.conf
    const essentials::Identifier* tmpAgentID;
    auto robotNames = (*this->sc)["Globals"]->getSections("Globals.Team", NULL);
    for (auto robotName : (*robotNames)) {
        tmpAgentID = this->pmRegistry->addRobot(robotName);
    }

    // Register executables from ProcessManaging.conf
    int tmpExecID;
    auto processDescriptions = (*this->sc)["ProcessManaging"]->getSections("Processes.ProcessDescriptions", NULL);
    for (auto processSectionName : (*processDescriptions)) {
        tmpExecID = this->pmRegistry->addExecutable(processSectionName);
    }

    this->comm = new Communication(this);
}

PMControl::~PMControl() {
    delete this->comm;
}

const Communication* PMControl::getComm() { return this->comm; }

/**
 * The worker method of PMControl. It processes the received ROS messages and afterwards updates the GUI.
 */
void PMControl::run()
{
    handleProcessStats();

    updateGUI();
}

/**
 * Updates the GUI, after ROS process stat message have been processed.
 */
void PMControl::updateGUI()
{
    chrono::system_clock::time_point now = chrono::system_clock::now();

    // need this kind of loop, in order to delete elements while iterating over the map
    for (auto processMapIter = this->processManagersMap.begin(); processMapIter != this->processManagersMap.end();) {
        if ((now - processMapIter->second->timeLastMsgReceived) > this->msgTimeOut) { // time is over, remove process manager

            std::cout << "PMControl: The process manager on " << processMapIter->second->name << " (ID: " << processMapIter->second->id << ") seems to be dead!"
                      << std::endl;
            delete processMapIter->second;
            this->processManagersMap.erase(processMapIter++);
        } else { // message arrived before timeout, update its GUI
            processMapIter->second->updateGUI(now);
            ++processMapIter;
        }
    }
}

/**
 * Processes all queued ROS process stat messages.
 */
void PMControl::handleProcessStats()
{
    lock_guard<mutex> lck(msgQueueMutex);
    while (!this->processStatMsgQueue.empty()) {
        // unqueue the ROS process stat message
        auto timePstsPair = processStatMsgQueue.front();
        processStatMsgQueue.pop();

        // get the corresponding process manager object
        pm_control::ControlledProcessManager* controlledPM = this->getControlledProcessManager(timePstsPair.second.ownID);
        if (controlledPM != nullptr) {
            // hand the message to the process manager, in order to let him update his data structures
            controlledPM->handleProcessStats(timePstsPair);
        }
    }
}

/**
 * If the process manager, corresponding to the given ID, is known, the process manager is returned. If the
 * ID does not match any known process manager, it searches in the process manager registry for an entry with the
 * given ID and creates the process manager accordingly. If the registry does not include an entry with the given ID,
 * an error message is printed and nullptr is returned.
 * @param processManagerId
 * @return The ControlledProcessManager object, corresponding to the given ID, or nullptr if nothing is found for the
 * given ID.
 */
pm_control::ControlledProcessManager* PMControl::getControlledProcessManager(const essentials::Identifier* processManagerId)
{
    const essentials::Identifier* id = this->pmRegistry->getRobotId(processManagerId->getRaw(), processManagerId->getSize());
    string pmName;
    auto pmEntry = this->processManagersMap.find(id);
    if (pmEntry != this->processManagersMap.end()) { // process manager is already known
        return pmEntry->second;
    }

    // process manager is not known, so create a corresponding instance
    this->pmRegistry->getRobotName(id, pmName);
    cout << "PMControl: Create new ControlledProcessManager " << pmName << " (ID: " << id << ")" << endl;
    pm_control::ControlledProcessManager* controlledPM = new pm_control::ControlledProcessManager(pmName, id, this->ui_.pmHorizontalLayout, this->comm);
    this->processManagersMap.emplace(id, controlledPM);
    return controlledPM;
}

/**
 * The callback of the ROS subscriber on ProcessStats messages.
 * @param psts
 */
void PMControl::receiveProcessStats(process_manager::ProcessStats psts)
{
    lock_guard<mutex> lck(msgQueueMutex);
    this->processStatMsgQueue.emplace(chrono::system_clock::now(), psts);
}

} // namespace pm_control

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationName("Application Example");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    pm_control::PMControl pmControl;
    pmControl.show();

    return app.exec();
}

