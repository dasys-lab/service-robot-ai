#include "srg/SRGWorldModel.h"

namespace srg
{

SRGWorldModel* SRGWorldModel::getInstance()
{
    static SRGWorldModel instance;
    return &instance;
}

SRGWorldModel::SRGWorldModel()
        : WorldModel()
        , sRGSimData(this)
        , conceptNet(this)
{
    this->agentName = sc->getHostname();
}

SRGWorldModel::~SRGWorldModel()
{
}

std::string SRGWorldModel::getAgentName()
{
    return this->agentName;
}

void SRGWorldModel::init()
{

}

void SRGWorldModel::setSolver(reasoner::asp::Solver* solver) {
    this->knowledgeManager.setSolver(solver);
}
} /* namespace wumpus */
