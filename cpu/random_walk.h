#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

#include "dictionary.h"

/*
All the hyper parameter are here from line 11 to 16, tuning should be done in here
*/

// cora_adj.txt has 2708 nodes; For other graphs, it can set it to be same as TABLE_SIZE if number of nodes is not known
#define NODE_NUM 2708 
#define MAX_STEPS 5
#define ALPHA 0.95
#define M_RW 500 // 4000 random walks
#define SEED_RATIO 0.05
#define COMB MAX_STEPS*(NODE_NUM+1)
#define SEED_COUNT 20

// counter is used to keep track of number of times of visting node "u" starting from node "v" at step i 
// Therefore, the counter Y column will have to be COMB = MAX_STEPS * (NODE_NUM+1)
// counter x index will go from 1 to NODE_NUM, y index will to from 0 to COMB-1
int counter[NODE_NUM+1][COMB]; // by default, it should also be 0 without assigning 
double score[TABLE_SIZE];

//int random_walk( vertex * table[], int counter[NODE_NUM+1][COMB], int m_rw, double score[TABLE_SIZE]);
int random_walk( vertex * table[], int counter[NODE_NUM+1][COMB], int m_rw, int sc, int max_steps, int node_num);

#endif
