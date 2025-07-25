#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include "student.h"
// //****************************************************************
// //                   REQUIRED FUNCTIONALITY IN PROJECT
// //****************************************************************

// 1. You need to implement every detail of the function defined below
// 2. You additionally need to implement getInfo methods in each classes.
// 3. You additionally need to implement 'operator overloading' with '==' which compares two students whether all the members are the same

Manager::Manager()
{
    stu = new Student*[300];
}

Manager::~Manager()
{
    for(int i = 0; i < 300; i++)
    {
        if(stu[i] != NULL)
        {
            delete stu[i];
        }
    }
    delete stu;
}

Student::Student(std::string name, int stunum)
{
    _name = name;
    _stunum = stunum;
}

Grad_Student::Grad_Student(std::string name, int stunum, std::string lab_name):Student(name, stunum)
{
    _lab_name = lab_name;
}

Undergrad_Student::Undergrad_Student(std::string name, int stunum, int freshman_class):Student(name, stunum)
{
    _freshmen_class = freshman_class;
}

int Manager::count = 0;

int Manager::add_student(std::string name, int stunum, std::string labname)
{
  // Adds Grad_Student object with given argument
  // Returns the total number of objects in the student array after adding
  /* if there is not enough space to save info, return false */
  if(count >= 300) 
  {
      std::cout << "false\n";
      return false;
  }
  /* if there is same info object, return false */
  if(find_student(name, stunum, labname) != 0)
  {
      std::cout << "false\n";
      return false;
  }
  for(int i = 0; i < 300; i++){
      if(stu[i] == NULL)
      {
          stu[i] = new Grad_Student(name, stunum, labname);
          break;
      }
  }
  count++;
  std::cout << "add graduate student DONE" << std::endl;
  std::cout << "return count = " << count << std::endl;
  return count;
};

int Manager::add_student(std::string name, int stunum, int freshmenclass)
{
  // Creates Undergrad_Student object with given argument
  // Returns the total number of objects in the student array after adding
  /* if there is not enough space to save info, return false */
  if(count >= 300)
  {
      std::cout << "false\n";
      return false;
  }
  /* if there is smae info object, return false */
  if(find_student(name, stunum, freshmenclass) != 0) 
  {
      std::cout << "false\n";
      return false;
  }
  for(int i = 0; i < 300; i++)
  {
      if(stu[i] == NULL)
      {
          stu[count] = new Undergrad_Student(name, stunum, freshmenclass);
          break;
      }
  }
  count++;
  std::cout << "add undergraduate student DONE" << std::endl;
  std::cout << "return count = " << count << std::endl;
  return count;
};

// You need to implement operator overloading and use it in compare_student

bool Manager::compare_student(int index, std::string name, int stunum, int freshmenclass)
{
  // Compares whether the object with given index argument in the student array is the same to Undergrad_Student object with given arguments followed by index.
  // Returns true if they are the same, false otherwise
  Student* tmp = new Undergrad_Student(name, stunum, freshmenclass);
  if(stu[index] == NULL)
  {
      delete tmp;
      std::cout << "false\n";
      return false;
  }
  if(*stu[index] == *tmp)
  {
      delete tmp;
      std::cout << "true\n";
      return true;
  }
  std::cout << "compare to undergraduate student DONE" << std::endl;
  std::cout << "false\n";
  return false;
};

bool Manager::compare_student(int index, std::string name, int stunum, std::string labname)
{
  // Compares whether the (index argument)th object in the student array is the same to Grad_Student object with given given argument follwed by index.
  // Returns true if they are the same, false otherwise
  Student* tmp = new Grad_Student(name, stunum, labname);
  if(stu[index] == NULL)
  {
      delete tmp;
      std::cout << "false\n";
      return false;
  }
  if(*stu[index] == *tmp)
  {
      delete tmp;
      std::cout << "true\n";
      return true;
  }
  std::cout << "compare to graduate student DONE" << std::endl;
  std::cout << "false\n";
  return false;
};

int Manager::find_student(std::string name, int stunum, std::string labname)
{
  // Finds the Grad_Student object in the student array which is the same to Grad_Student object with given argument
  // This method should print all the information about matched object
  // Returns index of matched object (index of first object = 1), 0 if there's no match
  int i = 0;
  for(i = 0; i < count; i++)
  {
      if(compare_student(i, name, stunum, labname) == true) break; // use == operator
  }
  /* if there is no matched object */
  if(i == count)
  {
      std::cout << "false\n";
      return 0;
  }
  std::cout << std::endl;
  stu[i]->getinfo();
  std::cout << "find graduate student DONE" << std::endl;
  std::cout << "return " << i+1 << std::endl;
  return i+1;
};

int Manager::find_student(std::string name, int stunum, int freshmenclass)
{
  // Finds the Undergrad_Student object in the student array which is the same to Undergrad_Student object with given argument
  // This method should prints all the information about matched object
  // Returns index of matched object (index of first object = 1), 0 if there's no match
  int i = 0;
  for(i = 0; i < count; i++)
  {
      if(compare_student(i, name, stunum, freshmenclass) == true) break; // use == operator
  }
  /* if there is no matched object */
  if(i == count)
  {
      std::cout << "false\n";
      return 0;
  }
  std::cout << std::endl;
  stu[i]->getinfo();
  std::cout << "find undergraduate student DONE" << std::endl;
  std::cout << "return " << i+1 << std::endl;
  return i+1;
};

int Manager::delete_student(std::string name, int stunum, std::string labname)
{
  // Deletes the Grad_Student object in the student array which is the same to Grad_Student object with given argument, does nothing if there's no matching
  // Returns the total number of objects in the student array after deleting
  int res = find_student(name, stunum, labname);
  if(res == false) 
  {
      std::cout << "false\n";
      return false;
  }
  delete stu[res-1];
  stu[res-1] = NULL; // avoid access after delete
  count--;
  std::cout << "delete graduate student DONE" << std::endl;
  std::cout << "return " << count << std::endl;
  return count;
};

int Manager::delete_student(std::string name, int stunum, int freshmenclass)
{
  // Deletes the Undergrad_Student object in the student array which is the same to Undergrad_Student object with given argument, does nothing if there's no matching
  // Returns the total number of objects in the student array after deleting
  int res = find_student(name, stunum, freshmenclass);
  if(res == false)
  {
      std::cout << "false\n";
      return false;
  }
  delete stu[res-1];
  stu[res-1] = NULL; // avoid access after delete
  count--;
  std::cout << "delete undergraduate student DONE" << std::endl;
  std::cout << "return " << count << std::endl;
  return count;
};

int Manager::print_all()
{
  // Prints the all the information of existing object in the student array
  // Returns the total number of objects in the student array
  for(int i = 0; i < count; i++)
  {
      if(stu[i] == NULL) continue;
      stu[i]->getinfo();
  }
  std::cout << "print all DONE" << std::endl;
  std::cout << "return " << count << std::endl;
  return count;
};

bool operator == (const Student& x, const Student& y)
{
  // operating overloading part. 
  // Check whether two students x, y have same information or not. 
  // Return true if two students are same, false otherwise.
  // p.s. this function must be used in at least "find_student ()" and "compare_student ()"
  // compare two student's name
  std::string name1 = x.get_name();
  std::string name2 = y.get_name();
  if(name1 != name2) return false; 
  // compare two student id
  int num1 = x.get_id();
  int num2 = y.get_id();
  if(num1 != num2) return false; 
  // compare two student class
  int fresh1 = x.get_fresh();
  int fresh2 = y.get_fresh();
  if(fresh1 != fresh2) return false;
  // compare two student lab
  std::string lab1 = x.get_lab();
  std::string lab2 = y.get_lab();
  if(lab1 != lab2) return false;  

  return true;
}

void Student::getinfo()
{
    std::cout<< "Information\n";
    std::cout<< "Name: " << _name << std::endl;
    std::cout<< "Student ID: " << _stunum << std::endl;

}

void Grad_Student::getinfo()
{
    std::cout<< "Information" << std::endl;
    std::cout<< "Name: " << _name << std::endl;
    std::cout<< "Student ID: " << _stunum << std::endl;
    std::cout<< "Labname: " << _lab_name << std::endl;
    std::cout<< std::endl;
}

void Undergrad_Student::getinfo()
{
    std::cout<< "Information" << std::endl;
    std::cout<< "Name: " << _name << std::endl;
    std::cout<< "Student ID: " << _stunum << std::endl;
    std::cout<< "Class: " << _freshmen_class << std::endl;
    std::cout<< std::endl;
}

/* -----------------------------
 * function for error handling
 * ----------------------------- */

/* ------------------------------------------------
 * Function isInt
 * argument: string
 * return: boolean
 * function: check whether it is string or integer.
 * if at least one components is not integer -> false
 * ------------------------------------------------
 */
bool isInt(std::string s)
{
    for(int i = 0; i < s.length(); i++)
    {
        if(std::isdigit(s[i]) == false) return false;
    }
    return true;
}
/* ------------------------------------------------
 * Function isName
 * argument: string
 * return: boolean
 * function: check whether it is name (only alphabet)
 * if at least one components is not alphabet -> false
 * ------------------------------------------------
 */
bool isName(std::string s)
{
    for(int i = 0; i < s.length(); i++)
    {
        if(std::isalpha(s[i]) == false)
        {
            if(std::isspace(s[i])) continue;
            else return false;
        }
    }
    return true;
}

/* ----------------------------------------------------------------
 * Function checkInput
 * argument: int
 * return: int
 * function: check whether Input is 0 or 1 only.
 * if not, system get input until it is the right format of the input.
 * ----------------------------------------------------------------
 */
int checkInput(int isgrad)
{
    while(true)
    {
        std::cin >> isgrad;
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(),'\n');
            std::cout << "Enter correct input format (0 or 1)" << std::endl; 
            continue;
        }
        else
        {
            if(isgrad != 0 && isgrad != 1)
            {
                std::cout << "Enter correct input format (0 or 1)" << std::endl; 
                continue;
            }
            break;
        }
    }
    std::cin.ignore(); // discard, flush the standard input stream.
    return isgrad;
}
/* ----------------------------------------------------------------
 * Function checkName
 * argument: string
 * return: string
 * function: check whether input is string of only charcter or not.
 * if not, system get input until it is the right format of input.
 * ----------------------------------------------------------------
 */
std::string checkName(std::string name)
{
    while(true)
    {
        std::getline(std::cin, name);
        if(std::cin.fail() || !isName(name) || name.empty())
        {
            if(name.empty())
            {
                std::cout << "No empty input\n";
                std::cout << "Name: ";
                continue;
            }
            std::cin.clear();
            std::cout << "Enter correct input format (only alphabet)" << std::endl;
            std::cout << "Name: ";
            continue;
        }
        else
        {
            break;
        }
    }
    return name; 
}
/* ----------------------------------------------------------------
 * Function checkStunum
 * argument: int 
 * return: int
 * function: check whether input is integer or not.
 * if not, system get input until it is the right format of input.
 * ----------------------------------------------------------------
 */
int checkStunum(int stunum)
{
    std::string input;
    while(true)
    {
        std::getline(std::cin, input);
        if(std::cin.fail() || !isInt(input) || input.empty())
        {
            if(input.empty())
            {
                std::cout << "No empty input\n";
                std::cout << "Student ID: ";
                continue;
            }
            std::cin.clear();
            std::cout << "Enter correct input format (integer)" << std::endl;
            std::cout << "Student ID: ";
            continue;
        }
        else
        {
            break;
        }
    }
    stunum = std::stoi(input); // convert string to integer.
    return stunum;
}
/* ----------------------------------------------------------------
 * Function checkFresh
 * argument: int
 * return: int
 * function: check whether input is integer or not.
 * if not, system get input until it is the right format of input.
 * ----------------------------------------------------------------
 */
int checkFresh(int freshmenclass)
{
    std::string input;
    while(true)
    {
        std::getline(std::cin, input);
        if(std::cin.fail() || !isInt(input) || input.empty())
        {
            if(input.empty())
            {
                std::cout << "No empty input\n";
                std::cout << "Freshmenclass: ";
                continue;
            }
            std::cin.clear();
            std::cout << "Enter correct input format (integer)" << std::endl;
            std::cout << "Freshmenclass: ";
            continue;
        }
        else
        {
            break;
        }
    }
    freshmenclass = std::stoi(input); // convert string to integer.
    return freshmenclass;
}
/* ----------------------------------------------------------------
 * Function checkLab 
 * argument: string
 * return: string
 * function: check whether input is string or not.
 * if not, system get input until it is the right format of input.
 * ----------------------------------------------------------------
 */

std::string checkLab(std::string labname)
{
    while(true)
    {
        std::getline(std::cin, labname, '\n');
        if(std::cin.fail() || !isName(labname) || labname.empty())
        {
            if(labname.empty())
            {
                std::cout << "No empty input\n";
                std::cout << "Lab Name: ";
                continue;
            }

            std::cin.clear();
            std::cout << "Enter correct input format (string)" << std::endl;
            std::cout << "Lab Name: ";
            continue;
        }
        else
        {
            break;
        }
    }
    return labname;
}
/* ----------------------------------------------------------------
 * Function checkIndex
 * argument: int
 * return: int
 * function: check whether input is integer or not.
 * if not, system get input until it is the right format of input.
 * ----------------------------------------------------------------
 */
int checkIndex(int index)
{
    std::string input;
    while(true)
    {
        std::getline(std::cin, input);
        if(std::cin.fail() || !isInt(input) || input.empty())
        {
            std::cin.clear();
            std::cout << "Enter correct input format (integer)" << std::endl;
            std::cout << "Index: ";
            continue;
        }
        else
        {
            break;
        }
    }
    index = std::stoi(input); // convert string to integer.
    return index;
}




