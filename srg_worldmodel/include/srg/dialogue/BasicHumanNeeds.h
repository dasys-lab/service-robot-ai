#pragma once

#include "srg/conceptnet/Edge.h"

#include <string>
#include <vector>

namespace srg
{
namespace conceptnet {
    class ConceptNet;
}
class SRGWorldModel;
namespace dialogue
{
class AnswerGraph;
class BasicHumanNeeds
{
public:
    BasicHumanNeeds(SRGWorldModel* wm);

    AnswerGraph* answerNeed(std::string need);
    static const int bestWeightedEdges;

private:
    SRGWorldModel* wm;
    conceptnet::ConceptNet* cn;

    void getSynonyms(std::vector<srg::conceptnet::Edge*>& edges, bool useToConcept) const;
    void insertNewEdges(std::vector<conceptnet::Edge*> &from, std::vector<conceptnet::Edge*> &to) const;
    bool compareEdges(const srg::conceptnet::Edge* first , const srg::conceptnet::Edge* second);
};
} // namespace wm
} // namespace srg
