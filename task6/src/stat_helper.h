#ifndef STAT_HELPER_H
#define STAT_HELPER_H

#include <sys/stat.h>

void print_file_type(unsigned int st_mode);

void print_device(unsigned int st_dev);

#endif//STAT_HELPER_H
