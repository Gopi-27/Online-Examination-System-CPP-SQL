#include "DBConnection.h"

using namespace oracle::occi;
using namespace std;

Environment* env = nullptr;

Connection* DBConnection::connect() {
    if (!env)
        env = Environment::createEnvironment(Environment::DEFAULT);

    Connection* conn = env->createConnection("xxxxx","xxxxxx","localhost:xxxx/xxxx");

    return conn;
}

void DBConnection::close(Connection* conn) {
    env->terminateConnection(conn);
}

