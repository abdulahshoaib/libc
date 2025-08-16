#include "log.h"
#define bufsize 20

char *
now()
{
  static char buf[bufsize];
  time_t      t = time(0);
  struct tm  *tm = localtime(&t);
  strftime(buf, sizeof(buf), "%H:%M:%S", tm);

  return buf;
}
