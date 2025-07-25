/* ------------------------------
 * EE205: Data Structure for EE
 * Name: Lee Yongeon
 * Student ID: 20170476
 *-------------------------------
 */
#include <iostream>
#include <stdexcept>
#include <string>
#include "student.h"

// //****************************************************************
// //                   MAIN FUNCTION IN PROJECT
// //****************************************************************

int main()
{
  std::string input;
  std::string int_input;
  char command;
  Manager myman;
  int isgrad;
  std::string name;
  int stunum;
  std::string labname;
  int freshmenclass;
  int index;
  bool isLast = true;

  while(isLast){
      std::cout << "\n\n\n*---------------------Welcome to Student Management System---------------------*" << std::endl;
      std::cout << "What do you want to do?\n1. Add student:a\n2. Compare student:c \n3. Find student:f\n4. Delete student:d\n5. Change student:c\n6. Print all student:p\n7. Quit:q" << std::endl; 
      std::cin >> input;
      // handling wrong 'type' format
      if(input.length() != 1 || std::cin.fail()){ // limit maximum input to 1
          // initalize state of istream
          std::cin.clear();
          // discard input stream
          std::cin.ignore();
          std::cout << "Enter correct input format (input only 1 character)" << std::endl;
          continue;
      }
      else{
          command = input[0]; // parsing the first character of the string input.
          if(isdigit(command) || !isalpha(command)) // only get first alphabet character
          {
              std::cout << "Enter correct input format (input only 1 character)" << std::endl;
              continue;
          }
      }
      switch(command)
	  {
	  case 'a':{
		// Type of student you want to add (Graduate student or Undergraduate student)
		std::cout << "Add student executed\n\nType\nUndergraduate:0 Graduate:1"<< std::endl;
            isgrad = checkInput(isgrad);
            // Graduate
		if (isgrad == 1){
		  std::cout << "\nFormat: [name stunum labname]" << std::endl; 
              std::cout << "Name: ";
              name = checkName(name); 
              std::cout << "Student ID: ";
              stunum = checkStunum(stunum);
              std::cout << "Lab Name: ";
              labname = checkLab(labname);
              myman.add_student(name, stunum, labname);
		}
            // Undergraduate
		else if (isgrad == 0){
		  std::cout << "\nFormat: [name stunum freshmenclass] " << std::endl;
              std::cout << "Name: ";
              name = checkName(name); 
              std::cout << "Student ID: ";
              stunum = checkStunum(stunum);
              std::cout << "Freshmenclass: ";
              freshmenclass = checkFresh(freshmenclass);
              myman.add_student(name, stunum, freshmenclass);
		}
	  }break;

	  case 'c':{
		std::cout << "Compare student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;
            isgrad = checkInput(isgrad);
            // Graduate
		if (isgrad == 1){
		  std::cout << "\nTarget student\nFormat: [index name stunum labname]" << std::endl;
              std::cout << "Index: ";
              index = checkIndex(index);
              std::cout << "Name: ";
              name = checkName(name); 
              std::cout << "Student ID: ";
              stunum = checkStunum(stunum);
              std::cout << "Lab Name: ";
              labname = checkLab(labname);
		  myman.compare_student(index, name, stunum, labname);
		}
            // Undergraduate
		else if (isgrad == 0){
		  std::cout << "\nTarget student\nFormat: [index name stunum freshmenclass] " << std::endl;
              std::cout << "Index: ";
              index = checkIndex(index);
              std::cout << "Name: ";
              name = checkName(name);
              std::cout << "Student ID: ";
              stunum = checkStunum(stunum);
              std::cout << "Freshmenclass: ";
              freshmenclass = checkFresh(freshmenclass);
		  myman.compare_student(index, name, stunum, freshmenclass);
		}
	  }break;

	  case 'f':{
		std::cout << "Find student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;
            isgrad = checkInput(isgrad);
            // Graduate
		if (isgrad == 1){
		  std::cout << "\nFormat: [name stunum labname]" << std::endl;
              std::cout << "Name: ";
              name = checkName(name); 
              std::cout << "Student ID: ";
              stunum = checkStunum(stunum);
              std::cout << "Lab Name: ";
              labname = checkLab(labname);
		  myman.find_student(name, stunum, labname);
		}
            // Undergraduate
		else if (isgrad == 0){
		  std::cout << "\nFormat: [name stunum freshmenclass]" << std::endl;
              std::cout << "Name: ";
              name = checkName(name);
              std::cout << "Student ID: ";
              stunum = checkStunum(stunum);
              std::cout << "Freshmenclass: ";
              freshmenclass = checkFresh(freshmenclass);
		  myman.find_student(name, stunum, freshmenclass);
		}
	  }break;


	  case 'd':{
		std::cout << "Delete student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;
            isgrad = checkInput(isgrad);
            // Grad_Student
		if (isgrad == 1){
		  std::cout << "\nFormat: [name stunum labname]" << std::endl;
              std::cout << "Name: ";
              name = checkName(name); 
              std::cout << "Student ID: ";
              stunum = checkStunum(stunum);
              std::cout << "Lab Name: ";
              labname = checkLab(labname);
		  myman.delete_student(name, stunum, labname);
		}
            // Undergraduate
		else if (isgrad == 0){
		  std::cout << "\nFormat: [name stunum freshmenclass]" << std::endl;
              std::cout << "Name: ";
              name = checkName(name);
              std::cout << "Student ID: ";
              stunum = checkStunum(stunum);
              std::cout << "Freshmenclass: ";
              freshmenclass = checkFresh(freshmenclass);
		  myman.delete_student(name, stunum, freshmenclass);
		}
	  }break;

	  case 'p':{
		std::cout << "Print all executed" << std::endl;
		myman.print_all();
	  }break;

	  case 'q':{
	  std::cout << "Quit" << std::endl;
	  isLast = false;
	  }break;

	  default:{
		std::cout << "Invalid argument" << std::endl;
	  }break;
	  }
  }
  return 0;
}

