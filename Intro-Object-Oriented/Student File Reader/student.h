#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>

class Student{
public:

   //constructors
   Student();
   Student(char* f, char* l);
   //accessors
   char * getFName() {return fname;};
   char * getLName() {return lname;};
   //virtual accessors/functions
   virtual double Average();
   virtual int getFinalExam();
   virtual char getGrade();
   virtual double getAverage();
   virtual int getCourse();
   //mutators
   void setFName(char * fname);
   void setLName(char * lname);

protected:
   //enum used slightly
   enum Course{Biology, Theater, ComputerScience};
   char fname[20];
   char lname[20];
   Course course; 
};

class BiologyC: public Student{
public:
   BiologyC();
   BiologyC(char* f, char* l, char g, int fexam);
  
   double Average(int, int, int, int, int);
   //defined inline as to not take up a lot of room in imp file
   int getFinalExam() {return finalExam;};
   char getGrade() {return grade;};
   double getAverage() {return average;};
   int getCourse() {return 0;};

   void setFExam(int f);
   void setGrade(char g);
   void setAverage(double a);
   

private:
   int lab, e1, e2, e3, finalExam;
   double average;
   char grade;
   Course course;
};

class TheaterC: public Student{
public:
   
   TheaterC();
   TheaterC(char* f, char* l, char g, int fexam);

   double Average(int, int, int);
   int getFinalExam() {return finalExam;};
   char getGrade() {return grade;};
   double getAverage() {return average;};
   int getCourse() {return 1;};

   void setFExam(int f);
   void setGrade(char g);
   void setAverage(double a);

private:
   int participation, midterm, finalExam;
   double average;
   char grade;
   Course course;
};
class ComputerScienceC: public Student{
public:
   ComputerScienceC();
   ComputerScienceC(char* f, char* l, char g, int fexam);

   double Average(int, int, int, int,int, int, int ,int, int);

   int getFinalExam() {return finalExam;};
   char getGrade() {return grade;};
   double getAverage() {return average;};
   int getCourse() {return 2;};

   void setFExam(int f);
   void setGrade(char g);
   void setAverage(double a);


private:
   int ass1, ass2, ass3, ass4, ass5, ass6, test1, test2, finalExam;
   double proAvg, average;
   char grade;
   Course course;
};
