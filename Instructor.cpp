#include "Instructor.h"
#include "DBConnection.h"
#include <iostream>
#include <string>

using namespace std;

void Instructor::menu(int instructorId) {
    int choice;

    do {
        cout << "\n--- Instructor Menu ---\n";
        cout << "1. View My Sections\n";
        cout << "2. Create Exam\n";
        cout << "3. Add Questions\n";
        cout << "4. View Section Results\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        Connection* conn = DBConnection::connect();
        Statement* stmt = conn->createStatement();

        switch (choice) {

        case 1: {
            ResultSet* rs = stmt->executeQuery(
                "SELECT s.section_id, s.section_name "
                "FROM instructor_section i "
                "JOIN sections s ON i.section_id = s.section_id "
                "WHERE i.instructor_id = " + to_string(instructorId)
            );

            cout << "\nMy Sections:\n";
            while (rs->next()) {
                cout << rs->getInt(1) << " - Section "
                     << rs->getString(2) << endl;
            }
            break;
        }

        case 2: {
            int sectionId, courseId;
            string examName;

            cout << "Section ID: ";
            cin >> sectionId;
            cout << "Course ID: ";
            cin >> courseId;
            cout << "Exam Name (Test1/Test2): ";
            cin >> examName;

            stmt->executeUpdate(
                "INSERT INTO exams(exam_name, course_id, section_id) VALUES('" +
                examName + "'," + to_string(courseId) + "," +
                to_string(sectionId) + ")"
            );

            cout << "Exam created successfully\n";
            break;
        }

        case 3: {
            int examId;
            string q, a, b, c, d;
            char correct;

            cout << "Exam ID: ";
            cin >> examId;
            cin.ignore();

            cout << "Question: ";
            getline(cin, q);
            cout << "Option A: ";
            getline(cin, a);
            cout << "Option B: ";
            getline(cin, b);
            cout << "Option C: ";
            getline(cin, c);
            cout << "Option D: ";
            getline(cin, d);
            cout << "Correct Option (A/B/C/D): ";
            cin >> correct;

            stmt->executeUpdate(
                "INSERT INTO questions "
                "(exam_id, question, option_a, option_b, option_c, option_d, correct_option) "
                "VALUES(" + to_string(examId) + ",'" + q + "','" + a + "','" +
                b + "','" + c + "','" + d + "','" + correct + "')"
            );

            cout << "Question added successfully\n";
            break;
        }

        case 4: {
            ResultSet* rs = stmt->executeQuery(
                "SELECT u.name, r.score, r.total "
                "FROM results r "
                "JOIN users u ON r.student_id = u.user_id "
                "JOIN instructor_section i ON u.section_id = i.section_id "
                "WHERE i.instructor_id = " + to_string(instructorId)
            );

            cout << "\nSection Results:\n";
            while (rs->next()) {
                cout << rs->getString(1) << " "
                     << rs->getInt(2) << "/" << rs->getInt(3) << endl;
            }
            break;
        }
        }

        conn->terminateStatement(stmt);
        DBConnection::close(conn);

    } while (choice != 0);
}
