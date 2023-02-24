#include <iostream>
#include <string>
using namespace std;
int ts;		   // total students
int tt;		   // total teachers
int tc;		   // total courses
struct Address // Nested structure to store address of each individual of institute
{
	string street;
	string city;
	string state;
};
enum education_level
{
	Bachelors = 1,
	Masters,
	Phd
};
struct Person
{
	string name;
	int age;
	Address address;
};
enum department
{
	CE = 1,
	ME,
	CS,
	DS,
	CYS,
	CME,
	EEE,
	AI,
	EEP,
	MTN,
	ES
};
struct Student // Passkey for any student to open LMS is 1234
{
	int roll_no;
	Person details;
	education_level level;
	department dept;
	string register_course[50]; // A single student can enroll in many courses
	int num_course_registered;
	int marks = 0;
	string grade;
};
enum Department
{
	ENG_S = 1,
	M_E,
	FCSE,
	NAB,
	BB
};
struct Teacher // Passkey for any teacher to open LMS is 12345
{
	string employee_num;
	Person details;
	int salary;
	Department faculty;
};
struct Admin // Passkey for any admin officer to open LMS is 123456
{
	Person details;
	int salary;
};
struct Course // Course structure as prescribed
{
	string course_name; // Select courses as CS-112,MT-101,CH-101
	string course_teacher_name;
	int enrolled_students;
	int graded_students;
	int dropped_students;
};
union Grade
{
	int marks;
};
Student rec_s[50]; // Record of upto 50 students can be stored
Teacher rec_t[50]; // Record of upto 50 teachers can be stored
Course rec_c[50];  // Record of upto 50 courses can be stored
void get_data(int i)
{
	bool rollnum_exist;
	do
	{
		cout << "Enter student roll number "<<i+1<<": ";
		cin >> rec_s[i].roll_no;
		// Check if the entered roll number already exists
		rollnum_exist = false;
		for (int j = 0; j < i; j++)
		{
			if (rec_s[i].roll_no == rec_s[j].roll_no)
			{
				cout << "Roll number already exists. Please enter a new roll number." << endl;
				rollnum_exist = true;
				break;
			}
		}
	} while (rollnum_exist);
	cout << "Enter name: ";
	cin >> rec_s[i].details.name;
	cout << "Enter age: ";
	cin >> rec_s[i].details.age;
	cout << "Enter street, city & state: ";
	cin >> rec_s[i].details.address.street;
	cin >> rec_s[i].details.address.city;
	cin >> rec_s[i].details.address.state;
	int x;
	cout << "Enter department: (1-11)";
	cin >> x;
	rec_s[i].dept = static_cast<department>(x);
	int y;
	cout << "Enter educational level: (1-3)";
	cin >> y;
	rec_s[i].level = static_cast<education_level>(y);
}
void add_student()
{
	cout << "Enter the number of students you want to enter (Upto 50): ";
	cin >> ts;
	for (int i = 0; i < ts; i++)
	{
		get_data(i);
	}
}
void remove_student()
{
	int reg;
	cout << "Enter the registration number which you want to remove: ";
	cin >> reg;
	for (int i = 0; i < ts; i++)
	{
		if (rec_s[i].roll_no == reg)
		{
			if (i != ts - 1)
			{
				for (int j = i; j < ts; j++)
				{
					rec_s[j].roll_no = rec_s[j + 1].roll_no;
				}
			}
			else
			{
				ts--;
				return;
			}
		}
	}
	ts--;
	cout << "Student has been successfully removed!" << endl;
}
void record_student()
{
	for (int i = 0; i < ts; i++)
	{
		cout << "Details of student " << i + 1 << ": " << endl;
		cout << "-------------------" << endl;
		cout << "Roll Num: " << rec_s[i].roll_no << endl;
		cout << "Name: " << rec_s[i].details.name << endl;
		cout << "Age: " << rec_s[i].details.age << endl;
		cout << "Address: " << rec_s[i].details.address.street << " " << rec_s[i].details.address.city << " " << rec_s[i].details.address.state << endl;
		cout << "Department: " << rec_s[i].dept << endl;
		cout << "Educational Level: " << rec_s[i].level << endl;
	}
}
void student_unenroll_course(int i)
{
	int total_reg = rec_s[i].num_course_registered;
	if (total_reg == 0)
	{
		cout << "You are not registered in any course." << endl;
		return;
	}
	cout << "Select the course you want to unenroll from:" << endl;
	for (int j = 0; j < total_reg; j++)
	{
		cout << j + 1 << ". " << rec_s[i].register_course[j] << endl;
	}
	int course_to_remove;
	cout << "Enter the number of the course to unenroll from: ";
	cin >> course_to_remove;
	if (course_to_remove < 1 || course_to_remove > total_reg)
	{
		cout << "Invalid input. Please enter a number between 1 and " << total_reg << "." << endl;
		return;
	}
	for (int k = course_to_remove - 1; k < total_reg - 1; k++)
	{
		rec_s[i].register_course[k] = rec_s[i].register_course[k + 1];
	}
	rec_s[i].num_course_registered--;
	cout << "You have successfully unenrolled from " << rec_s[i].register_course[total_reg - 1] << "." << endl;
}
void unenroll_student()
{
	int regnum;
	cout << "Enter your registration number: ";
	cin >> regnum;
	for (int i = 0; i < ts; i++)
	{
		if (rec_s[i].roll_no == regnum)
		{
			student_unenroll_course(i);
		}
	}
}
void get_data_teacher(int i)
{
	cout << "Enter employee " << i + 1 << " number: ";
	cin >> rec_t[i].employee_num;
	cout << "Enter name: ";
	cin >> rec_t[i].details.name;
	cout << "Enter age: ";
	cin >> rec_t[i].details.age;
	cout << "Enter address: ";
	cin >> rec_t[i].details.address.street >> rec_t[i].details.address.city >> rec_t[i].details.address.state;
	cout << "Enter salary: ";
	cin >> rec_t[i].salary;
	cout << "Enter faculty (1-5): ";
	int x;
	cin >> x;
	rec_t[i].faculty = static_cast<Department>(x);
}
void add_teacher()
{
	cout << "Enter the number of teachers you want to enter upto 50: ";
	cin >> tt;
	for (int i = 0; i < tt; i++)
	{
		get_data_teacher(i);
	}
}
void remove_teacher()
{
	string employee_num;
	cout << "Enter the employee number which you want to remove: ";
	cin >> employee_num;
	for (int i = 0; i < tt; i++)
	{
		if (rec_t[i].employee_num == employee_num)
		{
			if (i != tt - 1)
			{
				for (int j = i; j < tt; j++)
				{
					rec_t[j].employee_num = rec_t[j + 1].employee_num;
				}
			}
			else
			{
				tt--;
				return;
			}
		}
	}
	tt--;
	cout << "Teacher has been successfully removed!" << endl;
}
void update_teacher()
{
	cout << "Enter the employee number of teacher which you want to update: ";
	string employee_num;
	cin >> employee_num;
	int x;
	for (int i = 0; i < tt; i++)
	{
		if (rec_t[i].employee_num == employee_num)
		{
			cout << "For employee number -> Press 1: " << endl;
			cout << "For teacher name -> Press 2: " << endl;
			cout << "For teacher age -> Press 3: " << endl;
			cout << "For teacher address -> Press 4: " << endl;
			cout << "For teach	er salary -> Press 5: " << endl;
			cout << "For teacher faculty -> Press 6: " << endl;
			int detail;
			cout << "Which teacher detail you want to update: " << endl;
			cin >> detail;
			switch (detail)
			{
			case 1:
				cout << "Enter employee's updated number: ";
				cin >> rec_t[i].employee_num;
				break;
			case 2:
				cout << "Enter teacher's updated name: ";
				cin >> rec_t[i].details.name;
				break;
			case 3:
				cout << "Enter teacher's updated age: ";
				cin >> rec_t[i].details.age;
				break;
			case 4:
				cout << "Enter teacher's updated address (street/city/state): ";
				cin >> rec_t[i].details.address.street >> rec_t[i].details.address.city >> rec_t[i].details.address.state;
				break;
			case 5:
				cout << "Enter teacher's updated salary: ";
				cin >> rec_t[i].salary;
				break;
			case 6:
				cout << "Enter teacher's updated faculty (1-5): ";
				cin >> x;
				rec_t[i].faculty = static_cast<Department>(x);
				break;
			default:
				cout << "Enter choice b/w 1 and 6!" << endl;
			}
		}
	}
}
void record_teacher()
{
	for (int i = 0; i < tt; i++)
	{
		cout << "Details of teacher " << i + 1 << ": " << endl;
		cout << "-------------------" << endl;
		cout << "Employee Number: " << rec_t[i].employee_num << endl;
		cout << "Name: " << rec_t[i].details.name << endl;
		cout << "Age: " << rec_t[i].details.age << endl;
		cout << "Address: " << rec_t[i].details.address.street << " " << rec_t[i].details.address.city << " " << rec_t[i].details.address.state << endl;
		cout << "Salary: " << rec_t[i].salary << endl;
		cout << "Faculty: " << rec_t[i].faculty << endl;
	}
}
void add_course() // As in CS-112
{
	cout << "How many courses you want to add: ";
	cin >> tc;
	for (int i = 0; i < tc; i++)
	{
		cout << "Enter course " << i + 1 << " name: ";
		cin >> rec_c[i].course_name;
	}
	cout << "Courses succesfully added!" << endl;
}
void remove_course()
{
	string coursename;
	cout << "Enter the course code which you want to remove: ";
	cin >> coursename;
	for (int i = 0; i < tc; i++)
	{
		if (rec_c[i].course_name == coursename)
		{
			if (i != tc - 1)
			{
				for (int j = i; j < tc; j++)
				{
					rec_c[j].course_name = rec_c[j + 1].course_name;
				}
			}
			else
			{
				tc--;
				return;
			}
		}
	}
	tc--;
	cout << "Course has been successfully removed!" << endl;
}
void update_course()
{
	cout << "Enter the course name which you want to update (e.g. CS-112): ";
	string coursename;
	cin >> coursename;
	int x;
	for (int i = 0; i < tc; i++)
	{
		if (rec_c[i].course_name == coursename)
		{
			cout << "Enter new course name: ";
			cin >> rec_c[i].course_name;
		}
	}
	cout << "Course has been successfully updated!" << endl;
}
void record_course()
{
	for (int i = 0; i < tc; i++)
	{
		cout << "Course Name: " << rec_c[i].course_name << endl;
		cout << rec_c[i].course_name << " is taught by " << rec_c[i].course_teacher_name << "." << endl;
	}
}
void allocate_teacher()
{
	for (int i = 0; i < tc; i++)
	{
		cout << "Enter teacher name for course " << rec_c[i].course_name << ": ";
		cin >> rec_c[i].course_teacher_name;
	}
}
void deallocate_teacher()
{
	string courseName;
	cout << "Enter teacher's allocated coursename: ";
	cin >> courseName;
	for (int i = 0; i < tc; i++)
	{
		if (rec_c[i].course_name == courseName)
		{
			cout << rec_c[i].course_name << " is taught by: " << rec_c[i].course_teacher_name;
			cout << "Enter the new teacher name to which you want to assign the course: " << endl;
			cin >> rec_c[i].course_teacher_name;
		}
	}
}
void update_student()
{
	int regnum;
	int x, y, choice;
	cout << "Enter the registration number of student which you want to update: ";
	cin >> regnum;
	for (int i = 0; i < ts; i++)
	{
		if (rec_s[i].roll_no == regnum)
		{
			cout << "To update student's roll number -> Press 1" << endl;
			cout << "To update student's name -> Press 2" << endl;
			cout << "To update student's age -> Press 3" << endl;
			cout << "To update student's address -> Press 4" << endl;
			cout << "To update student's educational level -> Press 5" << endl;
			cout << "To update student's department -> Press 6" << endl;
			cout << "Enter your choice: " << endl;
			switch (choice)
			{
			case 1:
				cout << "Enter student's updated roll number: ";
				cin >> rec_s[i].roll_no;
				break;
			case 2:
				cout << "Enter student's updated name: ";
				cin >> rec_s[i].details.name;
				break;
			case 3:
				cout << "Enter student's updated age: ";
				cin >> rec_s[i].details.age;
				break;
			case 4:
				cout << "Enter student's updated address (street/city/state): ";
				cin >> rec_s[i].details.address.street >> rec_s[i].details.address.city >> rec_s[i].details.address.state;
				break;
			case 5:
				cout << "Enter student's updated educational level (1-3): ";
				cin >> x;
				rec_s[i].dept = static_cast<department>(x);
				break;
			case 6:
				cout << "Enter student's updated department (1-11): ";
				cin >> y;
				rec_s[i].level = static_cast<education_level>(y);
				break;
			default:
				cout << "Enter a choice b/w 1 and 6!" << endl;
			}
		}
	}
}
void student_details()
{
	int regnum;
	cout << "Enter your registration number please: ";
	cin >> regnum;
	for (int i = 0; i < ts; i++)
	{
		if (rec_s[i].roll_no == regnum)
		{
			cout << "Details of student: " << endl;
			cout << "-------------------" << endl;
			cout << "Roll Num: " << rec_s[i].roll_no << endl;
			cout << "Name: " << rec_s[i].details.name << endl;
			cout << "Age: " << rec_s[i].details.age << endl;
			cout << "Address: " << rec_s[i].details.address.street << " " << rec_s[i].details.address.city << " " << rec_s[i].details.address.state << endl;
			cout << "Department: " << rec_s[i].dept << endl;
			cout << "Educational Level: " << rec_s[i].level << endl;
		}
	}
}
void student_enroll_course(int i)
{
	int total_reg;
	cout << "Enter the total number of courses you want to register: ";
	cin >> total_reg;
	rec_s[i].num_course_registered = total_reg; // Number of courses registered by each student
	for (int j = 0; j < tc; j++)
	{
		cout << rec_c[j].course_name << endl;
	}
	cout << "Select from the following courses: " << endl;
	for (int k = 0; k < total_reg; k++)
	{
		cout << "Enter course " << k + 1 << " name: ";
		cin >> rec_s[i].register_course[k];
	}
	cout << "You have successfully enrolled in " << total_reg << " courses!" << endl;
}
void student_enroll()
{
	// To register in any course the student must be registered in system, so ask reg number first
	int regnum;
	bool found = false;
	cout << "Enter your registration number: ";
	cin >> regnum;
	for (int i = 0; i < ts; i++)
	{
		if (rec_s[i].roll_no == regnum)
		{
			student_enroll_course(i);
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << "You are not enrolled in LMS!" << endl;
	}
}
void student_grade()
{
	int regnum;
	cout << "Enter your registration number: ";
	cin >> regnum;
	for (int i = 0; i < ts; i++)
	{
		if (rec_s[i].roll_no == regnum)
		{
			for (int j = 0; j < rec_s[i].num_course_registered; j++)
			{
				cout << "Grade for " << rec_s[i].register_course[j] << " is: " << rec_s[i].grade << endl;
			}
			return;
		}
	}
	cout << "Registration number " << regnum << " not found!" << endl;
}
void student_record()
{
	int regnum;
	cout << "Enter your registration number: ";
	cin >> regnum;
	int total_reg;
	cout << "In how many courses were you registered? "; // Security Check
	cin >> total_reg;
	cout << "Your enrolled courses are: " << endl;
	cout << "---------------------------" << endl;
	for (int i = 0; i < ts; i++)
	{
		if (rec_s[i].roll_no == regnum)
		{
			for (int j = 0; j < total_reg; j++)
			{
				cout << rec_s[i].register_course[j] << endl;
			}
		}
	}
}
void display_dropped_courses(int roll_no)
{
	bool found = false;
	for (int i = 0; i < ts; i++)
	{
		if (rec_s[i].roll_no == roll_no)
		{
			found = true;
			cout << "Dropped courses for roll number " << roll_no << ":" << endl;
			for (int j = 0; j < rec_s[i].num_course_registered; j++)
			{
				string course_name = rec_s[i].register_course[j];
				for (int k = 0; k < tc; k++)
				{
					if (rec_c[k].course_name == course_name && rec_s[i].marks >= 0 && rec_s[i].marks < 33) // A course in which marks are below the passing limit is considered a dropped course
					{
						cout << k + 1 << ") " << course_name << endl;
					}
				}
			}
			break;
		}
	}
	if (!found)
	{
		cout << "No records found for roll number " << roll_no << endl;
	}
}
void dropped_course()
{
	int roll_num;
	cout << "Enter your registration number: ";
	cin >> roll_num;
	display_dropped_courses(roll_num);
}
void display_completed_courses(int roll_no)
{
	bool found = false;
	for (int i = 0; i < ts; i++)
	{
		if (rec_s[i].roll_no == roll_no)
		{
			found = true;
			cout << "Completed courses for roll number " << roll_no << ":" << endl;
			for (int j = 0; j < rec_s[i].num_course_registered; j++)
			{
				string course_name = rec_s[i].register_course[j];
				for (int k = 0; k < tc; k++)
				{
					if (rec_c[k].course_name == course_name && rec_s[i].marks >= 0 && rec_s[i].marks <= 100)
					{
						cout << course_name << " & Grade: " << rec_s[i].grade << endl;
					}
				}
			}
			break;
		}
	}
	if (!found)
	{
		cout << "No records found for roll number " << roll_no << endl;
	}
}
void completed_course()
{
	int roll_no;
	cout << "Enter your registration number: ";
	cin >> roll_no;
	display_completed_courses(roll_no);
}
void teacher_list()
{
	int regnum;
	cout << "Enter your registration number: ";
	cin >> regnum;
	int total_reg;
	cout << "Enter the total number of courses in which you were registered: "; // Security Check
	cin >> total_reg;
	cout << "Your teachers list is: " << endl;
	cout << "-----------------------" << endl;
	for (int i = 0; i < ts; i++)
	{
		if (rec_s[i].roll_no == regnum)
		{
			for (int j = 0; j < total_reg; j++)
			{
				cout << rec_c[j].course_teacher_name << " for " << rec_s[i].register_course[j] << endl;
			}
		}
	}
}
void teacher_record()
{
	string employee_num;
	cout << "Enter employee number: ";
	cin >> employee_num;
	for (int i = 0; i < tt; i++)
	{
		if (rec_t[i].employee_num == employee_num)
		{
			for (int j = 0; j < tt; j++)
			{
				cout << "Details of teacher " << j + 1 << ": " << endl;
				cout << "-------------------" << endl;
				cout << "Employee Number: " << rec_t[j].employee_num << endl;
				cout << "Name: " << rec_t[j].details.name << endl;
				cout << "Age: " << rec_t[j].details.age << endl;
				cout << "Address: " << rec_t[j].details.address.street << " " << rec_t[j].details.address.city << " " << rec_t[j].details.address.state << endl;
				cout << "Salary: " << rec_t[j].salary << endl;
				cout << "Faculty: " << rec_t[j].faculty << endl;
			}
		}
	}
}
void list_teacher_courses()
{
	string course_teacher_name;
	cout << "Enter your name please: ";
	cin >> course_teacher_name;
	cout << "You are allocated the following courses: " << endl;
	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < tc; i++)
	{
		if (rec_c[i].course_teacher_name == course_teacher_name)
		{
			cout << rec_c[i].course_name << endl;
		}
	}
}
void enrolled_students_list(string coursename)
{
	cout << "Students enrolled in " << coursename << ":" << endl;
	bool found = false;
	for (int j = 0; j < ts; j++)
	{
		for (int k = 0; k < rec_s[j].num_course_registered; k++)
		{
			if (rec_s[j].register_course[k] == coursename)
			{
				cout << "Reg Number: " << rec_s[j].roll_no << " and Name: " << rec_s[j].details.name << endl;
				found = true;
				break;
			}
		}
	}
	if (!found)
	{
		cout << "No students enrolled in " << coursename << "." << endl;
	}
}
void enrolled_students()
{
	string coursename;
	cout << "Enter the specific coursename: ";
	cin >> coursename;
	enrolled_students_list(coursename);
}
void teacher_allocate_grade() // This function allows a teacher to allocate grade to each student for his/her course only
{
	string cname;
	cout << "Enter course name: ";
	cin >> cname;
	for (int i = 0; i < tc; i++)
	{
		if (rec_c[i].course_name == cname)
		{
			for (int j = 0; j < ts; j++)
			{
				bool enrolled = false;
				for (int k = 0; k < rec_s[j].num_course_registered; k++)
				{
					if (rec_s[j].register_course[k] == cname)
					{
						enrolled = true;
						break;
					}
				}
				if (enrolled)
				{
					int marks;
					cout << "Enter marks for " << rec_s[j].roll_no << ": ";
					cin >> marks;
					rec_s[j].marks = marks;
					if (marks >= 90)
					{
						rec_s[j].grade = "A";
					}
					else if (marks >= 80)
					{
						rec_s[j].grade = "A_NEG";
					}
					else if (marks >= 70)
					{
						rec_s[j].grade = "B_POS";
					}
					else if (marks >= 60)
					{
						rec_s[j].grade = "B";
					}
					else if (marks >= 50)
					{
						rec_s[j].grade = "B_NEG";
					}
					else if (marks >= 40)
					{
						rec_s[j].grade = "C_POS";
					}
					else if (marks >= 33)
					{
						rec_s[j].grade = "C";
					}
					else
					{
						rec_s[j].grade = "F";
					}
				}
			}
			break;
		}
	}
}
void top_student()
{
	string coursename, studentname;
	int max = 0;
	bool has_students = false;
	cout << "Enter a course: ";
	cin >> coursename;
	for (int i = 0; i < tc; i++)
	{
		if (rec_c[i].course_name == coursename)
		{
			for (int j = 0; j < ts; j++)
			{
				bool enrolled = false;
				for (int k = 0; k < rec_s[j].num_course_registered; k++)
				{
					if (rec_s[j].register_course[k] == coursename)
					{
						enrolled = true;
						break;
					}
				}
				if (enrolled && max < rec_s[j].marks)
				{
					studentname = rec_s[j].details.name;
					max = rec_s[j].marks;
				}
				if (enrolled)
				{
					has_students = true;
				}
			}
			if (has_students)
			{
				cout << "The top student in " << coursename << " is: " << studentname << endl;
			}
			else
			{
				cout << "No students are enrolled in " << coursename << endl;
			}
			return;
		}
	}
	cout << "Course " << coursename << " does not exist" << endl;
}
void gradewise_division()
{
	string cname;
	cout << "Enter course name: ";
	cin >> cname;
	bool found = false;
	for (int i = 0; i < tc; i++)
	{
		if (rec_c[i].course_name == cname)
		{
			found = true;
			int total_students = 0;
			int a_count = 0, a_neg_count = 0, b_pos_count = 0, b_count = 0, b_neg_count = 0, c_pos_count = 0, c_count = 0, f_count = 0;
			for (int j = 0; j < ts; j++)
			{
				bool enrolled = false;
				for (int k = 0; k < rec_s[j].num_course_registered; k++)
				{
					if (rec_s[j].register_course[k] == cname)
					{
						enrolled = true;
						break;
					}
				}
				if (enrolled)
				{
					total_students++;
					if (rec_s[j].grade == "A")
					{
						a_count++;
					}
					else if (rec_s[j].grade == "A_NEG")
					{
						a_neg_count++;
					}
					else if (rec_s[j].grade == "B_POS")
					{
						b_pos_count++;
					}
					else if (rec_s[j].grade == "B")
					{
						b_count++;
					}
					else if (rec_s[j].grade == "B_NEG")
					{
						b_neg_count++;
					}
					else if (rec_s[j].grade == "C_POS")
					{
						c_pos_count++;
					}
					else if (rec_s[j].grade == "C")
					{
						c_count++;
					}
					else if (rec_s[j].grade == "F")
					{
						f_count++;
					}
				}
			}
			cout << "Grade-wise division of students in " << cname << " course:" << endl;
			cout << "Total students: " << total_students << endl;
			cout << "A grade: " << a_count << endl;
			cout << "A- grade: " << a_neg_count << endl;
			cout << "B+ grade: " << b_pos_count << endl;
			cout << "B grade: " << b_count << endl;
			cout << "B- grade: " << b_neg_count << endl;
			cout << "C+ grade: " << c_pos_count << endl;
			cout << "C grade: " << c_count << endl;
			cout << "F grade: " << f_count << endl;
			break;
		}
	}
	if (!found)
	{
		cout << "No course found with the name " << cname << endl;
	}
}
void function_admin()
{
	int choice;
	cout << "You have been identified as an Admin!" << endl;
	cout << "What do you want to do? " << endl;
	cout << "------------------------" << endl;
	cout << "Add Student -> Press 1: " << endl;
	cout << "Remove a student from system -> Press 2: " << endl;
	cout << "Check record of all students -> Press 3: " << endl;
	cout << "Unroll a student from a course -> Press 4: " << endl;
	cout << "Add a new teacher in system -> Press 5: " << endl;
	cout << "Remove a teacher from system -> Press 6: " << endl;
	cout << "Update teacher detail -> Press 7: " << endl;
	cout << "Check record of all teachers -> Press 8: " << endl;
	cout << "Add a course in system -> Press 9: " << endl;
	cout << "Remove course from the system -> Press 10: " << endl;
	cout << "Update course detail -> Press 11: " << endl;
	cout << "Check record of all courses -> Press 12: " << endl;
	cout << "Allocate a course to a teacher -> Press 13: " << endl;
	cout << "De-allocate a course from a teacher -> Press 14: " << endl;
	cout << "Update student detail -> Press 15: " << endl;
	cout << "To exit enter any other number :) " << endl;
	cout << "Enter your choice: " << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		add_student();
		break;
	case 2:
		remove_student();
		break;
	case 3:
		record_student();
		break;
	case 4:
		unenroll_student();
		break;
	case 5:
		add_teacher();
		break;
	case 6:
		remove_teacher();
		break;
	case 7:
		update_teacher();
		break;
	case 8:
		record_teacher();
		break;
	case 9:
		add_course();
		break;
	case 10:
		remove_course();
		break;
	case 11:
		update_course();
		break;
	case 12:
		record_course();
		break;
	case 13:
		allocate_teacher(); 
		break;
	case 14:
		deallocate_teacher();
		break;
	case 15:
		update_student();
		break;
	default:
		cout << "Enter a valid choice!" << endl;
	}
}
void function_student()
{
	int choice;
	cout << "You have been identified as a Student!" << endl;
	cout << "What do you want to do? " << endl;
	cout << "------------------------" << endl;
	cout << "Show student details -> Press 1" << endl;
	cout << "Enroll in a course -> Press 2" << endl;
	cout << "See final grade -> Press 3" << endl;
	cout << "See your teachers list -> Press 4" << endl;
	cout << "See list of enrolled courses -> Press 5" << endl;
	cout << "See list of dropped courses -> Press 6" << endl;
	cout << "See list of completed courses -> Press 7" << endl;
	cout << "To exit enter any other number :) " << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		student_details();
		break;
	case 2:
		student_enroll();
		break;
	case 3:
		student_grade();
		break;
	case 4:
		teacher_list();
		break;
	case 5:
		student_record();
		break;
	case 6:
		dropped_course();
		break;
	case 7:
		completed_course();
		break;
	default:
		cout << "Enter a valid choice!" << endl;
	}
}
void function_teacher()
{
	int choice;
	cout << "You have been identified as a teacher!" << endl;
	cout << "What do you want to do? " << endl;
	cout << "------------------------" << endl;
	cout << "Show teacher's details as entered by Admin -> Press 1" << endl;
	cout << "Show courses allocated to teacher -> Press 2" << endl;
	cout << "Show list of students enrolled in teacher's course -> Press 3" << endl;
	cout << "Assign marks and grade to each student in teacher's course -> Press 4" << endl;
	cout << "Show top student in teacher's course -> Press 5" << endl;
	cout << "Grade-wise divison of students in allocated course -> Press 6" << endl;
	cout << "To exit enter any other number :) " << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		teacher_record();
		break;
	case 2:
		list_teacher_courses();
		break;
	case 3:
		enrolled_students();
		break;
	case 4:
		teacher_allocate_grade();
		break;
	case 5:
		top_student();
		break;
	case 6:
		gradewise_division();
		break;
	default:
		cout << "Enter a valid choice!" << endl;
	}
}
int main()
{
	cout << "Welcome to LMS GIK!" << endl;
	string passkey;
	while (true)
	{
		cout << "Enter your passkey (Student,Teacher,Admin) or type exit: ";
		cin >> passkey;
		if (passkey == "123456")
		{
			function_admin();
		}
		else if (passkey == "1234")
		{
			function_student();
		}
		else if (passkey == "12345")
		{
			function_teacher();
		}
		else if (passkey == "exit")
		{
			cout << "Thanks for using LMS GIK!" << endl;
			break;
		}
		else
		{
			cout << "Invalid passkey, please try again." << endl;
			break;
		}
	}
	return 0;
}

