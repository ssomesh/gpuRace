#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>

struct CPUTimer
{
  int err;
  double start;
  double stop;
  struct timeval Tv;

  CPUTimer()
  {
    start = 0.0;
    stop = 0.0;
    err = 0;

  }

  void Start()
  {
    err = gettimeofday(&Tv, NULL);
    if (!err)
      start = Tv.tv_sec + Tv.tv_usec * 1.0e-6;
  }

  void Stop()
  {
    err = gettimeofday(&Tv, NULL);
    if (!err)
      stop = Tv.tv_sec + Tv.tv_usec * 1.0e-6;
  }

  double Elapsed()
  {
    double elapsed;
    elapsed = stop - start;
    return elapsed;
  }
};



#endif


/* Note on usage */

/*
 * CPUTimer cputimer;
 * cputimer.Start();
 * < piece of code to be timed >
 * cputimer.Stop();
 * printf("time taken for piece of code to run = %f (s)", cputimer.Elapsed());

 **************************************************************************

*/
