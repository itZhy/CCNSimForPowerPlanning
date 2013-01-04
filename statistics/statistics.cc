/*
 * ccnSim 
 *	ccnSim is a scalable chunk-level simulator of Content Centric Networks (CCN), 
 * 	that we developed in the context of ANR Connect (http://www.anr-connect.org/)
 * 
 * Contact us:
 * 	Email: ccnsim@lincs.fr 
 *  	Web: http://www.enst.fr/~drossi/ccnSim
 * 
 * People:
 *  	Giuseppe Rossini (lead developer)
 * 	Raffele Chiocchetti (developer)
 * 	Dario Rossi (occasional debugger) 
 * 
 *                                                                                                  
 *                                                    #                                             
 *                            #                     ;##                                             
 *                         `#+##                   +##:                                             
 *                         #` .#                 ### ##                                             
 *                         + `#.                 ;   #+ .                                           
 *                          ##,                    ,+#####                                          
 *                         +#  `                  `++#;                                             
 *                        ;#####`             ;+`                                                   
 *                        +#, `:             +###`                                                  
 *                              `.########; `####+                                                  
 *                      ###+################  +#+                                                   
 *                     `###########;.,,,:;#                                                         
 *                      :##:                                                                        
 *                   `;.                                                                            
 *            ` :####   								    									   
 *       +#####`####    							    `###,   									   
 *       +  #+ ,###.    							    ,###    										  
 *         +#+ ####     							    ;###    	    
 *     +    #+;###      							    ###`    	    
 *     ##;;## ####      							   .###     							 
 *       ###  ###.      							    ###`    								
 *                      		       `.;###:, 			    ###     								
 *           ###:       		      ;########  .##			    ###
 *          #####       		     ##########  :##`			    ###
 *          #####       		     ###;    `;  ```			    ###
 *           +##:          #####` ###`;###  `###,	 ###  ###`###` ;###	    ##;
 *              .        ,######  ########:  #######.	 ##,  #############,	   `###     	 
 *           :#.        `###`  .  ###. `###  #########. .##`  ###` #### `###	   .###     	 
 *          `###        ###	 `##;	##:   ######### ;##  `##:  ###   ##:	   .##+     	   
 *           ###        ###	 .##   `##`	.;##### ###  ,##`  ###  `##`	   .##,     	   
 *         #:###        ###	 ###   ,##	   .### ###  ###   ##;  ,##	   .##.     	   
 *        ## ###`       ###	 ###   ;##  ##`    ;### ##:  ###   ##.  ;##	   .###     	   
 *       ##+ ,##;       #######  ###   ###  ##########:.##`  ###  .##	###		    	   
 *     :#,.#..###;       ######  ##,   ### `#########: ;##   ##,  ;##	###		    	   
 *    +##+#+,,####        `		     `,;##;`	    `			   +##+     	    
 *        #:  :###.     							,#####      	    
 *        +.   ;.       							;#####      	  
 *               ,###   							.#####      	  
 *               +###+  							`####`      	  
 *               #####  								    										
 *               :###                                                                               
 *                 . :#                              ###                                            
 *                  ;##,                            +###;                                           
 *                 `####.                         # ####+                                           
 *                  #####;                     #### ####`                                           
 *                    ######### ,#+,     `,########                                                 
 *                      ######: ####`###########;                                                   
 *                         ###. ####`########+.                                                     
 *                              +###. ##;.`         ;##,                                            
 *                 	   `	 	           #  						  
 *                 	####.	 		  `#:`` 					    
 *                 	+#`	 		   ####+					    
 *                 	#:	 		   #;  ##					    
 *                     +###	 		   +# +#					    
 *                 	 .#+	 		    +##.					    
 *                 	   +	 								    
 *                    .` `#+	 								    
 *                    ####+	 								    
 *                 								      
 *
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 */
#include "statistics.h"
#include "statistics/stat_util.h"

Register_Class(statistics);

void statistics::initialize(){
    vector<string> ccn_types;
    ccn_types.push_back("modules.ccn_node");
    cTopology ccn_topo;
    ccn_topo.extractByNedTypeName(ccn_types);
    N = ccn_topo.getNumNodes();
    

    div_size = 0;
    tot_size = 0;
    ft = 0;
    _sim_time = par("sim_time");

    div_cache.clear();
    hit_time.setName("cache_hit");
    node_unstable=N;
    node_steady=N;

    convergence_threshold = par("convergence_threshold_avg");
    string convergence_type=par("convergence_type");
    if(convergence_type.compare("wc")==0)
	convergence_type_avg=false;
    else
	convergence_type_avg=true;
	
    //cout<<endl<<"convergence type avg "<<convergence_type_avg; 



}

void statistics::activity(){
    double hit_rate_global;
    if(convergence_type_avg ){
	//cout<<endl<<"Statistics start stabilization phase"<<endl;
	while ( true ){
	
	if (enable_stat){
	    
	    hit_rate_global = hit/(hit+miss);

	    hit_time.record(hit_rate_global);

	    if (checkStabilization(hit_rate_global)) //in this case stabilization is checked from each node
		break;
	}
	wait(0.1);
    }
	hit=0;
	
	miss=0;
	cout<<"STEADY PHASE"<<endl;
	wait(_sim_time);
    	endSimulation();
    }

}

bool statistics::checkStabilization(double hit_rate_global){
    bool end = false;

    static double last;
    static vector<double> samples;

    samples.push_back(hit_rate_global);

    if (samples.size() == 60/0.1){ //sample each 60 seconds every 100ms
	if (variance(samples) <= convergence_threshold) // || ( simTime() - ft ) >= _sim_time )
	    end = true;
	samples.clear();
    }

    return end;

}

void statistics::inspectCache(Cache *c, int owner){
    //if (!enable_stat)
	//return;

    deque<uint64_t> chunks = c->getCache();

    uint32_t size =chunks.size();
    for (int i = 0; i < size;i++){
        div_cache[chunks[i]] = true;
    }
    tot_size += size;

}

void statistics::cache_hit(int P,uint64_t chunk){
    if (!enable_stat)
	return;
    hit++;
    hit_level[P]++;
    uint32_t name=::getName(chunk);
    hit_stat[name]++;
}

void statistics::cache_miss(int P, uint64_t chunk){
    if (!enable_stat)
	return;
    miss++;
    miss_level[P]++;
    uint32_t name=::getName(chunk);
    miss_stat[name]++;

}

void statistics::stretch(int s,int d){
    if (!enable_stat)
	return;
    this->shortest+=s;
    this->distance+=d;
}

void statistics::fullStamping(int node){

    if (full_time.find(node)==full_time.end()){
	full_time[node]=simTime();
	if ( (int)full_time.size()==N && !enable_stat){
	    ft = simTime();
	    recordScalar("full_time",ft);
	    hit=0;
	    miss=0;
	    cout<<endl<<"Transient Phase"<<endl;
	    enable_stat=true;
	}
    }

}


void statistics::nodeStabilize(int node){

node_unstable--;
if(node_unstable==0){
	
	cout<<"Steady State Phase"<<endl;
	hit=0;
	miss=0;
 	recordScalar("transient_time",simTime());
 	}
	
}

void statistics::nodeFinalize(int node){

    node_steady--;
    if(node_steady==0){
	        endSimulation();
		        }

}


	
void statistics::finish(){
   
    recordScalar("div_ratio", div_cache.size()/tot_size);
    recordScalar("cache_hit", ( hit/(hit+miss)) );
    cout<<endl<<"Global Hit rate: "<<hit/(hit+miss)<<endl;
    recordScalar("stretch", distance/shortest );

    for (map<int,double>::iterator it= hit_level.begin(); it != hit_level.end();it++){

	char name[10];
	sprintf ( name, "hl[%d]", it->first );
	recordScalar(name,it->second/(it->second+miss_level[it->first]));

    }
}