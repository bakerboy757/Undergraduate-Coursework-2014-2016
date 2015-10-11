#include "student.h"

using namespace std;
//default just sets values to null, not really used
Student::Student(){
   fname[20] = '\0';
   lname[20] = '\0';
}
//will set/reset name
Student::Student(char* f, char* l){
   strncpy(fname, f, 20);
   strncpy(lname, l, 20);
}
//virtual functions put here to stop warning/error
int Student::getFinalExam(){return 0;}
char Student::getGrade(){return 'a';}
double Student::getAverage(){return 0;}
int Student::getCourse(){return 0;}
double Student:: Average(){ return 0.0;}

//BiologyC:
//int lab, e1, e2, e3, finalExam;
//char grade;
BiologyC::BiologyC(char* f, char* l, char g, int fexam) : Student(f, l){
   course = Biology;
   grade = g;
   finalExam = fexam;
}
//default
BiologyC::BiologyC(){}

double BiologyC::Average(int lab, int e1, int e2, int e3, int fExam){
   return (lab * .3 + e1 * .15 + e2 * .15 + e3 * .15 + fExam * .25);
}
//int participation, midterm, finalExam;
//   char grade;
TheaterC:: TheaterC(){}
TheaterC::TheaterC(char* f, char* l, char g, int fexam) : Student(f, l){
   course = Theater;
   grade = g;
   finalExam = fexam;
}

double TheaterC::Average(int participation, int midterm, int finalExam){
   return (participation * .4 + midterm * .25 + finalExam * .35);
}

//int ass1, ass2, ass3, ass4, ass5, ass6, test1, test2, finalExam;
//   double proAvg;
//   char grade;
ComputerScienceC::ComputerScienceC(){}
ComputerScienceC::ComputerScienceC(char* f, char* l, char g, int fexam) : Student(f, l){
   course = ComputerScience;
   grade = g;
   finalExam = fexam;
}

double ComputerScienceC::Average(int ass1, int ass2, int ass3, int ass4, int ass5, int ass6, int test1, int test2, int finalExam){
   //divide by 6.0 to not lose precision
	proAvg = (ass1 + ass2 + ass3 + ass4 + ass5 + ass6)/6.0;
   return (proAvg * .3 + test1 * .2 + test2 * .2 + finalExam * .3);
}
//mutator fuunctions
void BiologyC::setFExam(int f){
   finalExam = f;
}
void BiologyC::setGrade(char g){
   grade = g;
}
void BiologyC::setAverage(double a){
   average = a;
}
void TheaterC::setFExam(int f){
   finalExam = f;
}
void TheaterC::setGrade(char g){
   grade = g;
}
void TheaterC::setAverage(double a){
   average = a;
}
void ComputerScienceC::setFExam(int f){
   finalExam = f;
}
void ComputerScienceC::setGrade(char g){
   grade = g;
}
void ComputerScienceC::setAverage(double a){
   average = a;
}
