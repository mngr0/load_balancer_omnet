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

#ifndef __SELECTION_STRATEGIES_IN_OUT_H_
#define __SELECTION_STRATEGIES_IN_OUT_H_

#include <omnetpp.h>
#include "SelectionStrategies.h"

using namespace omnetpp;


class SelectionStrategyInOut : public cObject
{
protected:
    bool isInputGate;
    int gateSize;        // the size of the gate vector
    cModule *hostModule; // the module using the strategy
public:
    // on which module's gates should be used for selection
    // if selectOnInGate is true, then we will use "in" gate otherwise "out" is used
    SelectionStrategyInOut(cSimpleModule *module, bool selectOnInGate);
    virtual ~SelectionStrategyInOut();

    static SelectionStrategyInOut * create(const char *algName, cSimpleModule *module, bool selectOnInGate);

    // which gate index the selection strategy selected
    virtual int select() = 0;
    // returns the i-th module's gate which connects to our host module
    cGate *selectableGate(int i);
protected:
    // is this module selectable according to the policy? (queue is selectable if not empty, server is selectable if idle)
    virtual bool isSelectable(cModule *module);
};


class QUEUEING_API PrioritySelectionStrategy : public SelectionStrategyInOut
{
    public:
        PrioritySelectionStrategy(cSimpleModule *module, bool selectOnInGate);
        virtual int select() override;
};

/**
 * Random selection from the selectable modules, with uniform distribution.
 */
class QUEUEING_API RandomSelectionStrategy : public SelectionStrategyInOut
{
    public:
        RandomSelectionStrategy(cSimpleModule *module, bool selectOnInGate);
        virtual int select() override;
};

/**
 * Uses Round Robin selection, but skips any module that is not available currently.
 */
class QUEUEING_API RoundRobinSelectionStrategy : public SelectionStrategyInOut
{
    protected:
        int lastIndex; // the index of the module last time used
    public:
        RoundRobinSelectionStrategy(cSimpleModule *module, bool selectOnInGate);
        virtual int select() override;
};

/**
 * Chooses the shortest queue. If there are more than one
 * with the same length, it chooses by priority among them.
 * This strategy is for output only (i.e. for router module).
 */
class QUEUEING_API ShortestQueueSelectionStrategy : public SelectionStrategyInOut
{
    public:
        ShortestQueueSelectionStrategy(cSimpleModule *module, bool selectOnInGate);
        virtual int select() override;
};

/**
 * Chooses the longest queue (where length>0 of course).
 * Input strategy (for servers).
 */
class QUEUEING_API LongestQueueSelectionStrategy : public SelectionStrategyInOut
{
    public:
        LongestQueueSelectionStrategy(cSimpleModule *module, bool selectOnInGate);
        virtual int select() override;
};



#endif
