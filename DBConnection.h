#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <occi.h>
using namespace oracle::occi;

class DBConnection {
public:
    static Connection* connect();
    static void close(Connection* conn);
};

#endif
