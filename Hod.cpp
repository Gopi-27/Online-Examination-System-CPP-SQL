#include "Hod.h"
#include "DBConnection.h"
#include <iostream>
#include <string>

using namespace std;

void Hod::menu(int hodId) {
    Connection* conn = DBConnection::connect();
    Statement* stmt = conn->createStatement();

    ResultSet* rs = stmt->executeQuery(
        "SELECT u.name, r.score, r.total "
        "FROM results r "
        "JOIN users u ON r.student_id = u.user_id "
        "WHERE u.department_id = (SELECT department_id FROM users WHERE user_id=" +
        to_string(hodId) + ")"
    );

    cout << "\n--- Department Results ---\n";
    while (rs->next()) {
        cout << rs->getString(1) << " : "
             << rs->getInt(2) << "/" << rs->getInt(3) << endl;
    }

    conn->terminateStatement(stmt);
    DBConnection::close(conn);
}
