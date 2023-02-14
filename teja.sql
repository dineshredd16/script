

# @TODO
#     REMOVE FROM HERE
# DROP TABLE rating;
# DROP TABLE preRequisite;
# DROP TABLE subjectProfessorRegistration;
# DROP TABLE registration;
# DROP TABLE studentGrade;
# DROP TABLE subjectAssignment;
# DROP TABLE sectionProfessor;
# DROP TABLE subjectSection;
# DROP TABLE subject;
# DROP TABLE course;
# DROP TABLE department;
# DROP TABLE user;
#     REMOVE UNTIL HERE


CREATE TABLE user(
    userID varchar(225) NOT NULL UNIQUE,
    SSN varchar(124) NOT NULL UNIQUE,
    gmuID varchar(124) NOT NULL UNIQUE,
    email varchar(1024) NOT NULL,
    isActive bool,
    firstName varchar(1024) NOT NULL,
    middleName varchar(1024),
    lastName varchar(1024),
    userType ENUM('professor', 'gta', 'ra', 'passedOut', 'dropped', 'student', 'removed') NOT NULL,
    phoneNumber varchar(1024),
    address varchar(1024),
    PRIMARY KEY (SSN)
                 );

CREATE TABLE department(
    departmentID varchar(255) NOT NULL UNIQUE,
    name varchar(255) NOT NULL UNIQUE,
    email varchar(1024) NOT NULL,
    isActive bool,
    PRIMARY KEY (departmentID)
                       );

CREATE TABLE course(
    courseID varchar(124) NOT NULL UNIQUE,
    departmentID varchar(124),
    name varchar(124) NOT NULL UNIQUE,
    email varchar(1024) NOT NULL,
    isActive bool,
    PRIMARY KEY (courseID),
    FOREIGN KEY (departmentID) REFERENCES department(departmentID)
                   );

CREATE TABLE subject(
    subjectID varchar(124) NOT NULL UNIQUE,
    courseID varchar(124),
    name varchar(124) NOT NULL UNIQUE,
    subjectCode varchar(124),
    term varchar(124),
    isActive bool,
    PRIMARY KEY (subjectID),
    FOREIGN KEY (courseID) REFERENCES course(courseID)
                    );

CREATE TABLE subjectSection(
    subjectSectionID varchar(124) NOT NULL UNIQUE,
    subjectID varchar(124) NOT NULL,
    subjectMode ENUM('online', 'offline', 'hybrid') NOT NULL,
    sectionDescription varchar(1024),
    PRIMARY KEY (subjectSectionID),
    FOREIGN KEY (subjectID) REFERENCES subject(subjectID)
                           );

CREATE TABLE sectionProfessor(
    sectionProfessorID varchar(124) NOT NULL UNIQUE,
    SSN  varchar(124) NOT NULL,
    userType ENUM('professor', 'gta') NOT NULL,
    subjectSectionID varchar(124) NOT NULL,
    FOREIGN KEY (SSN) REFERENCES user(SSN),
    FOREIGN KEY(subjectSectionID) REFERENCES subjectSection(subjectSectionID)
                             );

CREATE TABLE subjectAssignment(
    subjectAssignmentID varchar(124) NOT NULL UNIQUE,
    sectionProfessorID varchar(124) NOT NULL UNIQUE,
    assignmentType varchar(124),
    totalMarks float NOT NULL,
    totalPercentage float,
    PRIMARY KEY (subjectAssignmentID),
    FOREIGN KEY (sectionProfessorID) REFERENCES sectionProfessor(sectionProfessorID)
                              );

CREATE TABLE studentGrade(
    studentGradeID varchar(124) NOT NULL UNIQUE,
    subjectAssignmentID varchar(124) NOT NULL UNIQUE,
    marks float NOT NULL,
    percentage float,
    SSN varchar(124) NOT NULL,
    PRIMARY KEY (subjectAssignmentID),
    FOREIGN KEY (SSN) REFERENCES user(SSN)
                         );

CREATE TABLE preRequisite(
    preRequisiteID varchar(124) NOT NULL,
    subjectID varchar(124) NOT NULL,
    FOREIGN KEY (preRequisiteID) REFERENCES subject(subjectID),
    FOREIGN KEY (subjectID) REFERENCES subject(subjectID)
                         );

CREATE TABLE registration(
    registrationID varchar(124) NOT NULL UNIQUE,
    sectionProfessorID varchar(124) NOT NULL UNIQUE,
    SSN  varchar(124) NOT NULL,
    status ENUM ('registered', 'pending', 'web drop') NOT NULL,
    priorityOrderNo varchar(124)  NOT NULL,
    PRIMARY KEY (registrationID),
    FOREIGN KEY (sectionProfessorID) REFERENCES sectionProfessor(sectionProfessorID),
    FOREIGN KEY (SSN) REFERENCES user(SSN)
                         );

CREATE TABLE rating(
    subjectSectionID varchar(124) NOT NULL UNIQUE,
    SSN  varchar(124) NOT NULL,
    rating float  NOT NULL,
    FOREIGN KEY (subjectSectionID) REFERENCES subjectSection(subjectSectionID),
    FOREIGN KEY (SSN) REFERENCES user(SSN)
                   );

CREATE TABLE subjectProfessorRegistration(
    subjectProfessorRegistrationID varchar(124) NOT NULL UNIQUE,
    subjectSectionID varchar(124) NOT NULL UNIQUE,
    totalLimit int NOT NULL,
    waitingList int NOT NULL,
    FOREIGN KEY (subjectSectionID) REFERENCES subjectSection(subjectSectionID)
                                         );



INSERT INTO
    user
        (userID, SSN, gmuID, email, isActive, firstName, middleName, lastName, userType, phoneNumber, address)
    VALUES
        ("1","123-45-6701","G01111101","gmustudentr1@gmu.edu",true,"gmu","student","1",'student',"91123456701","4401 University Dr,Fairfax"),
        ("2","123-45-6702","G01111102","gmustudent2@gmu.edu",true,"gmu","student","2",'student',"9112345602","4402 University Dr,Fairfax"),
        ("3","123-45-6710","G01111110","gmustudent3@gmu.edu",true,"gmu","student","3",'student',"9112345610","4410 University Dr,Fairfax"),
        ("4","123-45-6703","G01111103","gmuprofessor1@gmu.edu",true,"gmu","professor","1",'professor',"9112345603","4403 University Dr,Fairfax"),
        ("5","123-45-6704","G01111104","gmuprofessor2@gmu.edu",true,"gmu","professor","2",'professor',"9112345604","4404 University Dr,Fairfax"),
        ("6","123-45-6705","G01111105","gmugta1@gmu.edu",true,"gmu","gta","1",'gta',"9112345605","4405 University Dr,Fairfax"),
        ("7","123-45-6706","G01111106","gmugta2@gmu.edu",true,"gmu","gta","2",'gta',"9112345606","4406 University Dr,Fairfax")
    ;

INSERT INTO
    department
        (departmentID, name, email, isActive)
    VALUES
        ("1","Computer and Information Sciences","engineering@gmu.edu",true),
        ("2","Biology","biology@gmu.edu",true),
        ("3","Computational and Data Sciences","computationalanddatasciences@gmu.edu",true)
    ;

INSERT INTO
    course
        (courseID, departmentID, name, email, isActive)
    VALUES
        ("1","1","Computer Science","computerscience@gmu.edu",true),
        ("2","1","Data Analytics and Engineering","dataanalyticsandengineering@gmu.edu",true),
        ("3","2","Introduction to Biology I","introductiontobiology@gmu.edu",true),
        ("4","2","Science Writing","sciencewriting@gmu.edu",true),
        ("5","3","Data Science","datascience@gmu.edu",true),
        ("6","3","Software Engineering","computerscience@gmu.edu",true)
    ;

INSERT INTO
    subject
        (subjectID, courseID, name, subjectCode, term, isActive)
    VALUES
        ("1","1","Database Systems","1234","Spring2023",true),
        ("2","1","Mathematical Foundation of Computer Sciences","1235","Spring2023",true),
        ("3","2","Math Statistics","5678","Spring2023",true),
        ("4","3","Anatomy","2345","Spring2023",true),
        ("5","4","Human Science","3456","Spring2023",true),
        ("6","5","Machine Learning","4567","Spring2023",true),
        ("7","6","Computer Architecture","5678","Spring2023",true)
    ;

INSERT INTO
    subjectSection
        (subjectSectionID, subjectID, subjectMode, sectionDescription)
    VALUES
        ("1","1",'offline',"CS 550 001"),
        ("2","1",'online',"CS 550 002"),
        ("3","2",'online',"MFCS 530 002"),
        ("4","3",'online',"MS 210 001"),
        ("5","4",'offline',"AT 335 002"),
        ("6","5",'online',"HS 427 001"),
        ("7","6",'offline',"ML 632 002"),
        ("8","7",'hybrid',"CA 765 001")
    ;

INSERT INTO
    sectionProfessor
        (sectionProfessorID, SSN, userType, subjectSectionID)
    VALUES
        ("1", "123-45-6703", 'professor', "1"),
        ("2", "123-45-6705", 'gta', "1"),
        ("3", "123-45-6704", 'professor', "2"),
        ("4", "123-45-6706", 'gta', "2"),
        ("5", "123-45-6703", 'professor', "3"),
        ("6", "123-45-6706", 'gta', "3"),
        ("7", "123-45-6703", 'professor', "4"),
        ("8", "123-45-6704", 'professor', "5"),
        ("9", "123-45-6703", 'professor', "6"),
        ("10", "123-45-6704", 'professor', "7"),
        ("11", "123-45-6703", 'professor', "8")
    ;


INSERT INTO
    subjectAssignment
        (subjectAssignmentID, sectionProfessorID, assignmentType, totalMarks, totalPercentage)
    VALUES
        ("1","1","MCQ","100",5),
        ("2","2","MCQ","25",5),
        ("3","3","Homework","50",10),
        ("4","4","Project Part 1","20",15),
        ("5","5","MCQ","10",3),
        ("6","6","Project","100",20),
        ("7","7","Homework 1","10",2),
        ("8","8","MCQ","50",5)
    ;

INSERT INTO
    studentGrade
        (studentGradeID, subjectAssignmentID, marks, percentage, SSN)
    VALUES
        ("1","1","8.2","82","123-45-6701"),
        ("2","3","45","90","123-45-6702")
    ;

INSERT INTO
    preRequisite
        (preRequisiteID, subjectID)
    VALUES
        ("1", "2"),
        ("4", "5")
    ;

INSERT INTO
    registration
        (registrationID, sectionProfessorID, SSN, status, priorityOrderNo)
    VALUES
        ("1","1","123-45-6701",'registered',"0"),
        ("2","2","123-45-6702",'registered',"0"),
        ("3","3","123-45-6710",'pending',"1")
    ;

INSERT INTO
    rating
        (subjectSectionID, SSN, rating)
    VALUES
        ("1", "123-45-6701", 9.2),
        ("2", "123-45-6702", 9.7)
    ;

INSERT INTO
    subjectProfessorRegistration
        (subjectProfessorRegistrationID, subjectSectionID, totalLimit, waitingList)
    VALUES
        ("1","3",10,2)
    ;


# question 1:
SELECT
    CONCAT(user.firstName, " ", user.middleName, " ", user.lastName) as name, user.gmuID, user.SSN, subject.name as subjectName, subject.term
FROM
    user
LEFT OUTER JOIN sectionProfessor on user.SSN = sectionProfessor.SSN
LEFT OUTER JOIN subjectSection on sectionProfessor.subjectSectionID = subjectSection.subjectSectionID
LEFT OUTER JOIN subject on subjectSection.subjectID = subject.subjectID
WHERE
    user.isActive = 1 AND user.userType = 'professor' AND subject.term = "Spring2023";

#question 2:
SELECT
    subjectAssignment.assignmentType, subject.name as subjectName, subject.term, CONCAT(user.firstName, " ", user.middleName, " ", user.lastName) as professorName
FROM
    subjectAssignment
LEFT OUTER JOIN sectionProfessor on subjectAssignment.sectionProfessorID = sectionProfessor.sectionProfessorID
LEFT OUTER JOIN subjectSection on sectionProfessor.subjectSectionID = subjectSection.subjectSectionID
LEFT OUTER JOIN subject on subjectSection.subjectID = subject.subjectID
LEFT OUTER JOIN user on sectionProfessor.SSN = user.SSN
WHERE
    subjectAssignment.assignmentType = 'MCQ' AND user.userType = 'professor';
