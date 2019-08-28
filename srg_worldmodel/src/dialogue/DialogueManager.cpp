#include "srg/dialogue/DialogueManager.h"

#include "srg/SRGWorldModel.h"
#include "srg/dialogue/AnswerGraph.h"
#include "srg/dialogue/BasicHumanNeeds.h"
#include "srg/dialogue/InformHandler.h"
#include "srg/dialogue/SpeechAct.h"

#include <gvc.h>
#include <gvcext.h>
#include <supplementary/InformationElement.h>

namespace srg
{
namespace dialogue
{
DialogueManager::DialogueManager(srg::SRGWorldModel* wm)
        : wm(wm)
{
    this->basicHumanNeeds = new BasicHumanNeeds(wm);
    this->informHandler = new InformHandler(wm);
}
DialogueManager::~DialogueManager()
{
    for (auto pair : actMapping) {
        delete pair.second;
    }
}

void DialogueManager::processSpeechAct(std::shared_ptr<supplementary::InformationElement<SpeechAct>> speechAct)
{
    if (speechAct->getInformation().type == SpeechType::request) {
        AnswerGraph* answerGraph = this->basicHumanNeeds->answerNeed(speechAct->getInformation().text);
        this->actMapping.emplace(speechAct, answerGraph);
    } else if (speechAct->getInformation().type == SpeechType::inform) {
        AnswerGraph* answerGraph = this->informHandler->answerInform(speechAct->getInformation().text);
        this->actMapping.emplace(speechAct, answerGraph);
    }

    renderDot();
}

void DialogueManager::renderDot() const
{
    Agraph_t* g;
    /* set up a graphviz context - but only once even for multiple graphs */
    static GVC_t* gvc;
    std::cout << 1 << std::endl;
    if (!gvc) {
        gvc = gvContext();
    }
    /* Create a simple digraph */
    g = agopen("g", Agdirected, NULL);
    agsafeset(g, "rankdir", "RL", "");
    std::cout << 1 << std::endl;
    for (auto pair : actMapping) {
        pair.second->renderDot(g, true);
    }
    std::cout << 1 << std::endl;
    /* Set an attribute - in this case one that affects the visible rendering */

    /* Use the directed graph layout engine */
    gvLayout(gvc, g, "dot");
    std::cout << 1 << std::endl;
    /* Output in .dot format */
    FILE* fptr;
    fptr = fopen("test.dot", "w");

    gvRender(gvc, g, "dot", fptr);
    fclose(fptr);

    gvFreeLayout(gvc, g);
    std::cout << 1 << std::endl;
    agclose(g);

    // call this to translate into ps format and open with evince
    //    dot -Tps ~/test.dot -o outfile.ps
}
} // namespace dialogue
} // namespace srg
