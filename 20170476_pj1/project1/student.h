// //***************************************************************
// //                   CLASS USED IN PROJECT
// //****************************************************************

class Student{
	// ******Modify here******
	// You need to properly define member variable in Student class
 private:
     std::string _name;
     int _stunum;
 protected:
 public:
	// ******Modify here******
	// You need to implement get function which prints out every information about student argument in pure virtual function here
      virtual void getinfo();
      std::string get_name() const{ return _name;};
      int get_id() const{ return _stunum;};
      virtual std::string get_lab() const{ return "";};
      virtual int get_fresh() const{ return -1;};
      Student(std::string name, int stunum);
      friend class Grad_Student;
      friend class Undergrad_Student;

};
class Manager{
	// ******Modify here******
	// You need to properly define member variable in Manager class
 private:
 protected:
 public:
      Student** stu = NULL;
      static int count;
	// ******Modify here******
	// You need to implement every methods in Manager class
	int add_student(std::string name, int stunum, std::string labname);
	int add_student(std::string name, int stunum, int freshmenclass);
	bool compare_student(int index, std::string name, int stunum, std::string labname);
	bool compare_student(int index, std::string name, int stunum, int freshmenclass);
	int find_student(std::string name, int stunum, std::string labname);
	int find_student(std::string name, int stunum, int freshemenclass);
	int delete_student(std::string name, int stunum, std::string labname);
	int delete_student(std::string name, int stunum, int freshmenclass);
	int print_all();
      Manager();
      ~Manager();

};



class Grad_Student: public Student{
	// ******Modify here******
	// You need to properly define member variable in Grad_Student class
 private:
      std::string _lab_name;
 protected:
 public:
	// ******Modify here******
	// You need to implement get function in detail
      Grad_Student(std::string name, int stunum, std::string lab_name);
      void getinfo();
      std::string get_lab() const{ return _lab_name;};
};

class Undergrad_Student: public Student{
	// ******Modify here******
	// You need to properly define member variable in Undergrad_Student class
 private:
      int _freshmen_class;
 protected:
 public:
	// ******Modify here******
	// You need to implement get function in detail
      Undergrad_Student(std::string name, int stunum, int freshman_class);
      void getinfo();
      int get_fresh() const{ return _freshmen_class;};
};

bool operator == (const Student& x, const Student& y); 

/* -------------------------------------
 * function prototype for error handling
 * ------------------------------------- */

bool isInt(std::string s);
bool isName(std::string s);
int checkInput(int isgrad);
std::string checkName(std::string name);
int checkStunum(int stunum);
int checkFresh(int freshemenclass);
std::string checkLab(std::string labname);
int checkIndex(int index);

