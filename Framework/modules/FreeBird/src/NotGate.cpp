#include "NotGate.h"

namespace freebird
{
    NotGate::NotGate(Entity in, Entity out)
        : LogicGate(in, out)
    {
    }

    void NotGate::Update()
    {
        if (inputEnt1.Has<Wire>() && inputEnt1.Get<Wire>().GetIsPowered())
            output = false;
        else
            output = true;

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
