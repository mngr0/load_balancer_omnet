//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <omnetpp.h>

#include "RouterWS.h"
#include "SelectionStrategies.h"

Define_Module(RouterWS);

void RouterWS::initialize()
{
    // TODO - Generated method body
    //Router::initialize();
    //selectionStrategy = queueing::SelectionStrategy::create("random", this, false);
    //selectionStrategy = queueing::SelectionStrategy::create("roundRobin", this, false);
    selectionStrategy = queueing::SelectionStrategy::create("shortestQueue", this, false);
    if (!selectionStrategy)
        throw cRuntimeError("invalid selection strategy");
}

void RouterWS::handleMessage(cMessage *msg)
{

    //Router::handleMessage(msg);
    // TODO - Generated method body
    int outGateIndex = -1;  // by default we drop the message
    outGateIndex = selectionStrategy->select();
    // send out if the index is legal
    if (outGateIndex < 0 || outGateIndex >= gateSize("out"))
       throw cRuntimeError("Invalid output gate selected during routing");
    send(msg, "out", outGateIndex);
}
