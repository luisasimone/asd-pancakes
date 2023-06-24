#ifndef EXAM_220627_PARTITION_H
#define EXAM_220627_PARTITION_H

#include "Graph.h"

struct partition_s {
    int n_part;
    int tot_v;
    int* p;
};

typedef struct partition_s* Partition;

#endif //EXAM_220627_PARTITION_H
