#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

//#include "dictionary.h"
#include "random_walk.h"
#include "sort_array.h"


//int random_walk( vertex * table[], int counter[NODE_NUM+1][COMB], int m_rw, double score[TABLE_SIZE]){
int random_walk( vertex * table[], int counter[NODE_NUM+1][COMB], int m_rw){

    int ridx = 0;
    int seed_count=floor(NODE_NUM*SEED_RATIO); // seed_count is number of seeds required
    int seedset[seed_count]; // contains the seeds nodes
    int visited[NODE_NUM+1] =  {0};

    /* the following for loop is to create seed set */
    for(int i=0; i<seed_count;i++){
        
        int seed = rand()%(NODE_NUM)+1; /*seed is randomly pick from 1 to NODE_NUM here */

        /* the while loop and visited[] is to make sure that there are seed_count number of unique nodes in in seedset */
        while(visited[seed] == 1){ 
            seed = rand()%(NODE_NUM)+1;
        }
        seedset[ridx] = seed;
        visited[seed] = 1;
        ridx += 1;
    }

    /* the following 3 nested for loop is to fill up the counter[][] 
       counter[NODE_NUM+1][COMB] is a 2D array, it records the number of times a node is visted when specific i step and start node
       COMB is ranging from 0 MAX_STEPS * (NODE_NUM+1); 
    */

    for(int s=0; s<seed_count; s++){
        int startn = hash(seedset[s]); // the variable use slight different naming as below is because it is easier copy the code somewhere else debugging
        int currn = startn;
        /* m times l-step walk for each seed node*/
        for(int m=1; m<=m_rw; m++){
            for(int i=0; i<=MAX_STEPS; i++){
                // y start from 0, y is a funciton of start node and i, which is intended
                int y = (startn-1)*MAX_STEPS + i; 
                counter[currn][y] += 1;  // currn start from 1

                // the following 3 lines is to random walk and pick one neighbour node
                int ri = table[currn]->right;  
                int nnode_index = rand()%(ri+1); 
                int nnode = table[currn]->value[nnode_index];
                currn = nnode;      
                }
        }        
    }

    // the following 3 nested for loop is to caculate the score for each node
    for(int curr=1; curr<=NODE_NUM; curr++){
        int currnode = hash(curr);
        for(int i=0; i<=MAX_STEPS; i++){
            for(int start=1;start<=NODE_NUM; start++){
                int startnode = hash(start); // slight different naming as above
                
                int startnode_degree = table[startnode]->right+1;
                int index = (startnode-1)*MAX_STEPS + i;

                // equation:  (alpha ^ i) * counter[][] * start node's degree
                score[currnode] += pow(ALPHA, i) * counter[currnode][index] * startnode_degree; 

            }
        }
    }

    // And each node's score needs to be divided by its own degree
    for(int i=1; i <= NODE_NUM; i++){
        int curr = hash(i);
        score[curr] /= (table[curr]->right+1);
    }
    return 0;

}


