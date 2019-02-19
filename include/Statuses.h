#ifndef STATUSES_H
#define STATUSES_H

//list of error codes for this program
typedef enum {
    STATUS_SUCCESS = 0,
    STATUS_INVALID_PARAMETERS = -1,
    STATUS_MEMORY_ACCESS_ABORT = -2,
    STATUS_FILE_NOT_ALLOWED = -3,
    STATUS_NOT_BMP_HEADER = -4,
    STATUS_UNSUPPORTED_FILE = -5
} Status;

#endif