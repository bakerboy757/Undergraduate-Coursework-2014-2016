//most work done in in main file

#include "student.h"
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>//included to use exit() and ignore() etc...

using namespace std;
//function put here instead of being in imp file due to errors with g++
char calcGrade(double average);

int main(){

   ifstream input;
   ofstream output;
   //file names
   char inputName[200], outputName[200];
   int numStudents;
   int ass1, ass2, ass3, ass4, ass5, ass6, 
      test1, test2, finalExam, midTerm, participation,
      lab, test3;
   
   cout << "Please enter the name of a the input file. \nFilename: ";
   cin >> inputName;
   input.open(inputName);
   if(!input){
      cout << "Sorry, bad file.";
      exit(0);
   }
   cout << "Please enter the name of a the output file. \nFilename: ";
   cin >> outputName;
   output.open(outputName);
   if(!output){
      cout << "Sorry, bad file.";
      exit(0);
   }
   
   input >> numStudents;
   
   Student ** list = new Student * [numStudents];
 
   char lname[20], fname[20];

   char firstChar;
   //count used to determine which index of list will be changed
   int count = 0;
   
   do{
      input.ignore();//ignores first new line(fixed error where last name would be on line below)
      input.getline(lname, 20, ',');
      input.ignore();
      input.getline(fname, 20);
      //looks at first char and determines what it is
      firstChar = input.peek();
      double average = 0.0;
      char grade;
      switch(firstChar){
         case 'C':
            {
		    //creates two  temp strings to 'eat' the Comp Sci part at beginning
            string temp1, temp2;
            input >> temp1 >> temp2;
            
            input >> ass1 >> ass2 >> ass3 >> ass4 >> ass5 >> ass6 >> test1 >> test2 >> finalExam;
            //creates new Comp sci object
            ComputerScienceC *c1 = new ComputerScienceC(fname, lname, grade, finalExam);
             
            average = c1->Average(ass1, ass2, ass3, ass4, ass5, ass6, test1, test2, finalExam);
            grade = calcGrade(average);
			//mutates new data
            c1->setGrade(grade);
            c1->setFExam(finalExam);
            c1->setAverage(average);
			//sets count index to this new compsci object
            list[count] = c1;
            break;
            }
         case 'B':
            {
            //temp to eat up bio
            string temp;
            input >> temp;
            input >> lab >> test1 >> test2 >> test3 >> finalExam;
          
            //same process as with comp sci
            BiologyC *b1 = new BiologyC(fname, lname, grade, finalExam);

            average = b1->Average(lab, test1, test2, test3, finalExam);
            grade = calcGrade(average);

            b1->setGrade(grade);
            b1->setFExam(finalExam);
            b1->setAverage(average);

            list[count] = b1;
            break;
            }
         case 'T':
            {
			//same process as previous two cases
            string temp;
            input >> temp;
            input >> participation >> midTerm >> finalExam;
           
            TheaterC *t1 = new TheaterC(fname, lname, grade, finalExam);

            average = t1->Average(participation, midTerm, finalExam);
            grade = calcGrade(average);

            t1->setGrade(grade);
            t1->setFExam(finalExam);
            t1->setAverage(average);

            list[count] = t1;
            
            break;
            }
      }
      count++;

   
   }while( count < numStudents && !input.eof());
   
   output << "Student Grade Summary\n";
   output << "---------------------\n\n";
   output << "BIOLOGY CLASS\n\n";
   output << "Student                                   Final   Final   Letter\n";
   output << "Name                                      Exam    Avg     Grade\n";
   output << "----------------------------------------------------------------\n";
   //full name used to make setw work    
   char fullname[41];
   for(int i = 0; i < numStudents; i ++){
	  //checks to make sure to put out biology students only here(bio = 0 thanks to enum)
      if(list[i]->getCourse() == 0){
		//copy over the name to full name
		 strcpy(fullname, list[i]->getFName());
		 strcat(fullname, " ");
		 strcat(fullname, list[i]->getLName());

         output << left << setw(42) << fullname << setw(8) << list[i]->getFinalExam() 
			    << fixed << setprecision(2) << setw(8)<< list[i]->getAverage() 
                << list[i]->getGrade() << "\n";
      }
   }
   output << "\n\nTHEATER CLASS\n\n";
   output << "Student                                   Final   Final   Letter\n";
   output << "Name                                      Exam    Avg     Grade\n";
   output << "----------------------------------------------------------------\n";
            
   //same process as previous
   for(int i = 0; i < numStudents; i ++){
      if(list[i]->getCourse() == 1){
		 strcpy(fullname, list[i]->getFName());
		 strcat(fullname, " ");
		 strcat(fullname, list[i]->getLName());

         output << left << setw(42) << fullname << setw(8) << list[i]->getFinalExam() 
			    << fixed << setprecision(2) << setw(8)<< list[i]->getAverage() 
                << list[i]->getGrade() << "\n";
		 
      }
   }
   output << "\n\nCOMPUTER SCIENCE CLASS\n\n";
   output << "Student                                   Final   Final   Letter\n";
   output << "Name                                      Exam    Avg     Grade\n";
   output << "----------------------------------------------------------------\n";
            
   //same process as previous
   for(int i = 0; i < numStudents; i ++){
      if(list[i]->getCourse() == 2){
		 strcpy(fullname, list[i]->getFName());
		 strcat(fullname, " ");
		 strcat(fullname, list[i]->getLName());

         output << left << setw(42) << fullname << setw(8) << list[i]->getFinalExam() 
			    << fixed << setprecision(2) << setw(8)<< list[i]->getAverage() 
                << list[i]->getGrade() << "\n";
		 
      }
   }
   //counts up how many times a grade is seen
   int totalA = 0, totalB = 0, totalC = 0, totalD = 0, totalF = 0;
   for(int i = 0; i < numStudents; i ++){
      if(list[i]->getGrade() == 'A')
         totalA++;
      if(list[i]->getGrade() == 'B')
         totalB++;
      if(list[i]->getGrade() == 'C')
         totalC++;
      if(list[i]->getGrade() == 'D')
         totalD++;
      if(list[i]->getGrade() == 'F')
         totalF++;
   }
   output << "\n\n\nOVERALL GRADE DISTRIBUTION\n\n";
   output << "A: " << totalA << endl;
   output << "B: " << totalB << endl;
   output << "C: " << totalC << endl;
   output << "D: " << totalD << endl;
   output << "F: " << totalF << endl;
   
   input.close();
   output.close();
}
//determines grade
char calcGrade(double average){
   char grade;
   //changes double to int
   int avg = static_cast<int>(average);
   //divides avg by 10 to make switch 10 times easier to make)dont need to mkae 100 cases)
   switch(avg / 10){
      case 10:
      case 9: grade = 'A'; break;
      case 8: grade = 'B'; break;
      case 7: grade = 'C'; break;
      case 6: grade = 'D'; break;
      default: grade = 'F';
   }
   return grade;


}
