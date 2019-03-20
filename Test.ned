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
import org.omnetpp.queueing.Fork;
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
    @display("bgb=707,261");
    submodules:
        source: Source {
            @display("p=51,128");
        }
        server: Queue {
            @display("p=289,68");
        }
        sink: Sink {
            @display("p=445,68");
        }
        queue: Queue {
            @display("p=289,184");
        }
        sink1: Sink {
            @display("p=445,184");
        }
        router: RouterWS {
            @display("p=213,128");
        }
    connections:
        server.out --> sink.in++;
        queue.out --> sink1.in++;
        source.out --> router.in++;
        router.out++ --> server.in++;
        router.out++ --> queue.in++;
}
