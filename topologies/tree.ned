package topologies;
import modules.*;

network tree_network {

    parameters:
    	int n = 15;
	double degree = default(4);

	int c = 8;

    submodules:
	routing: routing{
	}


	request_generator[c]: request_generator{
	        @display("i=block/routing");
	    
	}

	global_generator: global_generator{
	        @display("i=block/routing");
	    
	}

    	content_distribution: content_distribution{
	    parameters:
		repository_num = default(1);
	
	}

        ccn_node[n]: ccn_node{
            parameters:
	        @display("i=block/broadcast_s;is=s");
            //    @display("p=50,50,ri,200,200");
        }

 	statistics: statistics{

	}



connections allowunconnected:
	ccn_node[0].face++ <--> { delay = 1ms; } <--> ccn_node[1].face++;
	ccn_node[0].face++ <--> { delay = 1ms; } <--> ccn_node[2].face++;
	ccn_node[1].face++ <--> { delay = 1ms; } <--> ccn_node[3].face++;
	ccn_node[1].face++ <--> { delay = 1ms; } <--> ccn_node[4].face++;
	ccn_node[2].face++ <--> { delay = 1ms; } <--> ccn_node[5].face++;
	ccn_node[2].face++ <--> { delay = 1ms; } <--> ccn_node[6].face++;
	ccn_node[3].face++ <--> { delay = 1ms; } <--> ccn_node[7].face++;
	ccn_node[3].face++ <--> { delay = 1ms; } <--> ccn_node[8].face++;
	ccn_node[4].face++ <--> { delay = 1ms; } <--> ccn_node[10].face++;
	ccn_node[4].face++ <--> { delay = 1ms; } <--> ccn_node[9 ].face++;
	ccn_node[5].face++ <--> { delay = 1ms; } <--> ccn_node[11].face++;
	ccn_node[5].face++ <--> { delay = 1ms; } <--> ccn_node[12].face++;
	ccn_node[6].face++ <--> { delay = 1ms; } <--> ccn_node[13].face++;
	ccn_node[6].face++ <--> { delay = 1ms; } <--> ccn_node[14].face++;

	ccn_node[10].reqPort<--request_generator[3].reqPort;
	ccn_node[11].reqPort<--request_generator[4].reqPort;
	ccn_node[12].reqPort<--request_generator[5].reqPort;
	ccn_node[13].reqPort<--request_generator[6].reqPort;
	ccn_node[14].reqPort<--request_generator[7].reqPort;
	ccn_node[7].reqPort<--request_generator[0].reqPort;
	ccn_node[8].reqPort<--request_generator[1].reqPort;
	ccn_node[9].reqPort<--request_generator[2].reqPort;
}
