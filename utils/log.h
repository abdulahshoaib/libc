#ifndef LOG
#define LOG

#include <stdio.h>
#include <time.h>

char* now ();

#define plog(fmt, ...) printf("[%s] " fmt  "\n", now(), ##__VA_ARGS__);

#endif // !LOG
