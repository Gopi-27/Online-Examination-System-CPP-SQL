#include "Student.h"
#include "DBConnection.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;
using namespace oracle::occi;

void Student::menu(int studentId) {
    Connection* conn = DBConnection::connect();
    Statement* stmt = conn->createStatement();

    // 1. Fetch exams for student's section
    ResultSet* rs = stmt->executeQuery(
        "SELECT exam_id, exam_name FROM exams "
        "WHERE section_id = (SELECT section_id FROM users WHERE user_id=" +
        to_string(studentId) + ")"
    );

    cout << "\nAvailable Exams:\n";
    while (rs->next()) {
        cout << rs->getInt(1) << " - " << rs->getString(2) << endl;
    }

    int examId;
    cout << "Enter Exam ID: ";
    cin >> examId;

    // 2. Fetch questions of selected exam
    ResultSet* qs = stmt->executeQuery(
        "SELECT question, option_a, option_b, option_c, option_d, correct_option "
        "FROM questions WHERE exam_id=" + to_string(examId)
    );

    int score = 0, total = 0;
    char ans;

    while (qs->next()) {
        total++;

        cout << "\nQ: " << qs->getString(1) << endl;
        cout << "A. " << qs->getString(2) << endl;
        cout << "B. " << qs->getString(3) << endl;
        cout << "C. " << qs->getString(4) << endl;
        cout << "D. " << qs->getString(5) << endl;

        cout << "Answer (A/B/C/D): ";
        cin >> ans;

        if (toupper(ans) == qs->getString(6)[0])
            score++;
    }

    // 3. Store result
    stmt->executeUpdate(
        "INSERT INTO results(student_id, exam_id, score, total) VALUES(" +
        to_string(studentId) + "," +
        to_string(examId) + "," +
        to_string(score) + "," +
        to_string(total) + ")"
    );

    cout << "\nFinal Score: " << score << "/" << total << endl;

    conn->terminateStatement(stmt);
    DBConnection::close(conn);
}
