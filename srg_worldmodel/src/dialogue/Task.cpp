#include "srg/dialogue/Task.h"

namespace srg
{
namespace dialogue
{
Task::Task()
        : coordinate(0, 0), type(srgsim::TaskType::Idle)
{
}
} // namespace dialogue
} // namespace srg