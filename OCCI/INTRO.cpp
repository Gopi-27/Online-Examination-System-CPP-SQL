
// OCCI -> ORACLE CPP CALL INTERFRENCE
// USING THIS YOU CAN COMMUNUCATE BETWEEN YOUR DATABASE FROM C++ CODE
#include<occi.h>
// it includes the libraries that contains the required class
using namespace oracle :: occi

// IMPORTANT CLASSES
// 1. Environment
// 2. Connection
// 3. Statement
// 4. ResultSet

// 1. Environment
// this class will not allow us to creat objects directly 
// instead it provides static fucntion to create objects
// we can create the environment is differenct modes
// like default(mostly used), threaded_mutexed, threaded_unmutexed

// SYNTAX :
// ENVIRONMENT *environment_name(pointer) = ENVIRONMENT::creatEnvironment(ENVIROMENT :: MODE_NAME);
ENVIRONMENT *env = ENVIRONMENT::createEnvironment(ENVIRONMENT::DEFALUT);

// DESTROY THE ENVIROMENT
// IT WILL NOT ALLOW US TO DESTROY THE OBJECTS DIRECTLY LIKE DELETE obj
// INSTEAD IT PROVIDES STATIC FUNCTION TO DESTORY OBJECT
// SYNTAX :
//  terminateEnvironment(environment_name);
terminateEnvironment(env);

// 2. Connection
// without environment, connection does not exist
// you can only create the connection inside an enviroment with the reference of the environment
// SYNTAX:
// Connection *(connection_name) = (environment_name)->createConnection(username,password,"hostname:port/service_name");
Connection *con = env->createConnection("system","xxxxx","localhost:1289/XEPB1);
// DESTORY CONNECTION
// SYNTAX :
// terminateConnection(connection_name);
terminateConnection(con);

// commit & rollback
// by default oracle asks commit to confirm the updates
// rollback is used to undo the last updated operation

con->commit();
con->rollback();

// 2. Statement
// statement can only be created within the connection with connnection reference
// it stores the sql command that need to be perfromed
// SYNTAX :
// Statement *(statement_name) = (connection_name)->createStatement("sql command");
Statement * stmt = con->createStatement("INSERT INTO students VALUES("24B11CS374","GOPI","AUS")");
// IT JUST HOLDS THE SQL COMMAND WHICH IS GOING TO BE EXCUTED

// IF IT IS DML COMMAND LIKE INSERT,UPDATE,DELETE
// USE excuteUpdate(statement_name);
excuteUpdate(stmt);

// IF IT IS DQL COMMAD LIKE SELECT
// SELECT WILL RETURN SOME DATA THAT NEED TO BE STORED
// TO STORE THE DATA OCCI PROVIDES ResulSet class












