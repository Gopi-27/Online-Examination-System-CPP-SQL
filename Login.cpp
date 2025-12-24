#include "Login.h"
#include "DBConnection.h"
#include "Admin.h"
#include "Hod.h"
#include "Instructor.h"
#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

void Login::authenticate() {
    string email, password;

    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    cin >> password;
    Connection* conn = DBConnection::connect();
    Statement* stmt = conn->createStatement();
    string query = "SELECT user_id, role FROM users "
                    "WHERE email='" + email + "' AND password='" + password + "'";
    ResultSet* rs = stmt->executeQuery(query);
    if (rs->next()) {
        int id = rs->getInt(1);
        string role = rs->getString(2);

        if (role == "ADMIN") Admin::menu();
        else if (role == "HOD") Hod::menu(id);
        else if (role == "INSTRUCTOR") Instructor::menu(id);
        else if (role == "STUDENT") Student::menu(id);
    } else {
        cout << "Invalid login credentials\n";
    }

    conn->terminateStatement(stmt);
    DBConnection::close(conn);
}
