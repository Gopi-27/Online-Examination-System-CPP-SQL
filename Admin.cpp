#include "Admin.h"
#include "DBConnection.h"
#include <iostream>
#include <string>

using namespace std;

void Admin::menu() {
    int choice;

    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Department\n";
        cout << "2. Add Section\n";
        cout << "3. Add Course\n";
        cout << "4. Add User\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        Connection* conn = DBConnection::connect();
        Statement* stmt = conn->createStatement();

        switch (choice) {

        case 1: {
            string name;
            cout << "Department Name: ";
            cin >> name;

            stmt->executeUpdate(
                "INSERT INTO departments(department_name) VALUES('" + name + "')"
            );

            cout << "Department added\n";
            break;
        }

        case 2: {
            string sec;
            int deptId;
            ResultSet* rs = stmt->executeQuery("SELECT department_id, department_name FROM departments");
            cout << "\n--- Available Departments ---\n";
            cout << "Dept Id\t\t Dept Name\n";
            while(rs->next()){
                cout << rs->getInt(1) << "\t\t " << rs->getString(2) << endl;
            }
            cout << "Section Name: ";
            cin >> sec;
            cout << "Department ID: ";
            cin >> deptId;

            stmt->executeUpdate(
                "INSERT INTO sections(section_name, department_id) VALUES('" +
                sec + "'," + to_string(deptId) + ")"
            );

            cout << "Section added\n";
            break;
        }

        case 3: {
            string cname;
            int deptId;
            ResultSet* rs = stmt->executeQuery("SELECT department_id, department_name FROM departments");
            cout << "\n--- Available Departments ---\n";
            cout << "Dept Id\t\t Dept Name\n";
            while(rs->next()){
                cout << rs->getInt(1) << "\t\t " << rs->getString(2) << endl;
            }
            cout << "Course Name: ";
            cin >> cname;
            cout << "Department ID: ";
            cin >> deptId;

            stmt->executeUpdate(
                "INSERT INTO courses(course_name, department_id) VALUES('" +
                cname + "'," + to_string(deptId) + ")"
            );

            cout << "Course added\n";
            break;
        }

        case 4: {
            string name, email, pwd, role;
            int deptId, secId;
            ResultSet* rs = stmt->executeQuery("SELECT s.section_id,s.section_name,d.department_id,d.department_name FROM sections s FULL JOIN departments d ON s.department_id = d.department_id");
            cout << "\n--- Available Sections & Departments ---\n";
            cout << "Sec Id\t Sec Name\t Dept Id\t Dept Name\n";
            while(rs->next()){
                cout << rs->getInt(1) << "\t " << rs->getString(2) << "\t\t " <<
                rs->getInt(3) << "\t " << rs->getString(4) << endl;
            }
            
            cout << "Name: ";
            cin >> name;
            cout << "Email: ";
            cin >> email;
            cout << "Password: ";
            cin >> pwd;
            cout << "Role (ADMIN/HOD/INSTRUCTOR/STUDENT): ";
            cin >> role;
            cout << "Department ID: ";
            cin >> deptId;

            if (role == "STUDENT") {
                cout << "Section ID: ";
                cin >> secId;
            } else {
                secId = 0;
            }

            stmt->executeUpdate(
                "INSERT INTO users(name,email,password,role,department_id,section_id) VALUES('" +
                name + "','" + email + "','" + pwd + "','" + role + "'," +
                to_string(deptId) + "," + to_string(secId) + ")"
            );

            cout << "User added successfully\n";
            break;
        }
        }

        conn->terminateStatement(stmt);
        DBConnection::close(conn);

    } while (choice != 0);
}



