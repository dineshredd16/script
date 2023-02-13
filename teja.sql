
DROP TABLE rating;
DROP TABLE preRequisite;
DROP TABLE subjectProfessorRegistration;
DROP TABLE registration;
DROP TABLE studentGrade;
DROP TABLE subjectAssignment;
DROP TABLE sectionProfessor;
DROP TABLE subjectSection;
DROP TABLE subject;
DROP TABLE course;
DROP TABLE department;
DROP TABLE user;


CREATE TABLE user(
    userID varchar(225),
    SSN  varchar(124) NOT NULL UNIQUE,
    gmuID  varchar(124) NOT NULL UNIQUE,
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
    subjectCode varchar(124), term varchar(124),
    isActive bool,
    PRIMARY KEY (subjectID),
    FOREIGN KEY (courseID) REFERENCES course(courseID)
                    );

CREATE TABLE subjectSection(
    subjectSectionID varchar(124) NOT NULL UNIQUE,
    subjectID varchar(124) NOT NULL,
    SSN  varchar(124) NOT NULL UNIQUE,
    subjectMode varchar(124),
    sectionDescription varchar(1024),
    PRIMARY KEY (subjectSectionID),
    FOREIGN KEY (subjectID) REFERENCES subject(subjectID)
                           );

CREATE TABLE sectionProfessor(
    sectionProfessorID varchar(124) NOT NULL UNIQUE,
    SSN  varchar(124) NOT NULL UNIQUE,
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
    sectionProfessorID varchar(124) NOT NULL,
    PRIMARY KEY (subjectAssignmentID),
    FOREIGN KEY (sectionProfessorID) REFERENCES sectionProfessor(sectionProfessorID)
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
    SSN  varchar(124) NOT NULL UNIQUE,
    status varchar(124)  NOT NULL,
    priorityOrderNo varchar(124)  NOT NULL,
    PRIMARY KEY (registrationID),
    FOREIGN KEY (sectionProfessorID) REFERENCES sectionProfessor(sectionProfessorID)
                         );

CREATE TABLE rating(
    subjectSectionID varchar(124) NOT NULL UNIQUE,
    SSN  varchar(124) NOT NULL UNIQUE,
    rating float  NOT NULL,
    FOREIGN KEY (subjectSectionID) REFERENCES subjectSection(subjectSectionID)
                   );

CREATE TABLE subjectProfessorRegistration(
    subjectProfessorRegistrationID varchar(124) NOT NULL UNIQUE,
    subjectSectionID varchar(124) NOT NULL UNIQUE,
    totalLimit int NOT NULL,
    waitingList int NOT NULL,
    FOREIGN KEY (subjectSectionID) REFERENCES subjectSection(subjectSectionID)
                                         );