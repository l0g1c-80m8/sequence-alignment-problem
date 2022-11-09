//
// Created by rutvik-patel on 1/11/22.
//

#ifndef SEQ_PERF_MEASURE_H
#define SEQ_PERF_MEASURE_H

#include <errno.h>
#include <stdio.h>
#include <sys/resource.h>

extern int errno;

// getrusage() is available in linux. Your code will be evaluated in Linux OS.
long getTotalMemory() {
    struct rusage usage{};
    int returnCode = getrusage(RUSAGE_SELF, &usage);
    if (returnCode == 0) {
        return usage.ru_maxrss;
    } else {
        // It should never occur. Check man getrusage for more info to debug.
        // printf("error %d", errno);
        return -1;
    }
}

double getExecTime(struct timeval ts1, struct timeval ts2) {
    long seconds = ts2.tv_sec - ts1.tv_sec;
    long microseconds = ts2.tv_usec - ts1.tv_usec;
    return (double) seconds * 1000 + (double) microseconds * 1e-3;
}

#endif //SEQ_PERF_MEASURE_H
