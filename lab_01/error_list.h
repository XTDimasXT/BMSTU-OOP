#ifndef ERROR_LIST_H
#define ERROR_LIST_H

#include <QMessageBox>

enum Error
{
    OK,
    ERR_FILE_OPEN,
    ERR_DATA,
    ERR_MEMORY_ALLOCATE,
    ERR_NO_FIELD,
    ERR_NO_FIGURE,
    ERR_EXTRA_ERROR
};

void catch_error(Error error);


#endif // ERROR_LIST_H
