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

package test;

import ned.IUnidirectionalChannel;
import org.omnetpp.queueing.Allocate;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.Fork;
import org.omnetpp.queueing.ResourcePool;
import org.omnetpp.queueing.Router;
import org.omnetpp.queueing.Source;
import org.omnetpp.queueing.Queue;
import org.omnetpp.queueing.Sink;
import org.omnetpp.queueing.PassiveQueue;
import org.omnetpp.queueing.Server;
import org.omnetpp.queueing.Delay;

//
// TODO Generated network
//
network Test
{
    @display("bgb=707,279");
    submodules:
        source: Source {
            @display("p=51,128");
        }
        sink: Sink {
            @display("p=613,62");
        }
        sink1: Sink {
            @display("p=589,184");
        }
        router_ws: RouterWS {
            @display("p=170,128");
        }
        server1: Server {
            @display("p=384,184");
        }
        server2: Server {
            @display("p=391,62");
        }
        passiveQueue: PassiveQueue {
            @display("p=308,185");
        }
        passiveQueue1: PassiveQueue {
            @display("p=304,51");
        }
    connections:
        source.out --> router_ws.in++;
        router_ws.out++ --> passiveQueue1.in++;
        passiveQueue1.out++ --> server2.in++;
        server2.out --> sink.in++;
        router_ws.out++ --> passiveQueue.in++;
        passiveQueue.out++ --> server1.in++;
        server1.out --> sink1.in++;
}
