#include "AndGate.h"

namespace freebird
{
    AndGate::AndGate(Entity ent1, Entity ent2, Entity out)
        : LogicGate(ent1, ent2, out)
    {
    }

    void AndGate::Update()
    {
        if (inputEnt1.Has<Wire>() && inputEnt1.Get<Wire>().GetIsPowered() && inputEnt2.Has<Wire>() && inputEnt2.Get<Wire>().GetIsPowered())
            output = true;
        else
            output = false;

        if (outputEnt.Has<Door>() && output)
            outputEnt.Get<Door>().SetOpen(true);

        if (outputEnt.Has<Door>() && !output)
            outputEnt.Get<Door>().SetOpen(false);

        if (outputEnt.Has<Wire>() && output)
            outputEnt.Get<Wire>().SetIsPowered(true);

        if (outputEnt.Has<Wire>() && !output)
            outputEnt.Get<Wire>().SetIsPowered(false);
    }
}
