
CREATE TABLE users (
    user_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    name VARCHAR2(50),
    email VARCHAR2(50) UNIQUE,
    password VARCHAR2(50),
    role VARCHAR2(20) CHECK (role IN ('ADMIN','HOD','INSTRUCTOR','STUDENT')),
    department_id NUMBER,
    section_id NUMBER
);

INSERT INTO users(name,email,password,role,department_id,section_id) VALUES ('Admin Gopi','Adm123@gmail.com','Adm@123','ADMIN',1,1);
INSERT INTO users(name,email,password,role,department_id,section_id) VALUES ('Demo','demo','demo','ADMIN',1,1);
SELECT * FROM users;

CREATE TABLE departments (
    department_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    department_name VARCHAR2(50)
);
INSERT INTO departments(department_name) VALUES('Test');
SELECT * FROM departments;
CREATE TABLE sections (
    section_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    section_name VARCHAR2(10),
    department_id NUMBER,
    FOREIGN KEY (department_id) REFERENCES departments(department_id)
);

INSERT INTO sections (section_name,department_id) VALUES ('AIML-1',3);
SELECT * FROM sections;

CREATE TABLE courses (
    course_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    course_name VARCHAR2(50),
    department_id NUMBER,
    FOREIGN KEY (department_id) REFERENCES departments(department_id)
);

INSERT INTO courses(course_name,department_id) VALUES ('JAVA',3);
SELECT * FROM courses;

COMMIT;
CREATE TABLE instructor_section (
    instructor_id NUMBER,
    section_id NUMBER,
    PRIMARY KEY (instructor_id, section_id),
    FOREIGN KEY (instructor_id) REFERENCES users(user_id),
    FOREIGN KEY (section_id) REFERENCES sections(section_id)
);
SELECT * FROM instructor_section;

CREATE TABLE exams (
    exam_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    exam_name VARCHAR2(30),
    course_id NUMBER,
    section_id NUMBER,
    FOREIGN KEY (course_id) REFERENCES courses(course_id),
    FOREIGN KEY (section_id) REFERENCES sections(section_id)
);

SELECT * FROM exams;
CREATE TABLE questions (
    question_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    exam_id NUMBER,
    question VARCHAR2(300),
    option_a VARCHAR2(100),
    option_b VARCHAR2(100),
    option_c VARCHAR2(100),
    option_d VARCHAR2(100),
    correct_option CHAR(1),
    FOREIGN KEY (exam_id) REFERENCES exams(exam_id)
);
SELECT * FROM questions;

CREATE TABLE results (
    result_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    student_id NUMBER,
    exam_id NUMBER,
    score NUMBER,
    total NUMBER,
    exam_date DATE DEFAULT SYSDATE,
    FOREIGN KEY (student_id) REFERENCES users(user_id),
    FOREIGN KEY (exam_id) REFERENCES exams(exam_id)
);

SELECT * FROM results;
