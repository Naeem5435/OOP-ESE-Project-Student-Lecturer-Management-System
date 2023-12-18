#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

// global variable for array sizes
int count[3];

// Base People class for students and lecturers
class People
{
private:
	// People properties which are same for Student and Lecturer
	string number;
	string name;
	string surname;
	string department;
	string email;
	string phone;

public:
	// get and set functions for Number, Name, Surname, Department, Email, Phone properties
	string getNumber()
	{
		return this->number;
	};
	void setNumber(string _number)
	{
		this->number = _number;
	};
	string getName()
	{
		return this->name;
	};
	void setName(string _name)
	{
		this->name = _name;
	};
	string getSurname()
	{
		return this->surname;
	};
	void setSurname(string _surname)
	{
		this->surname = _surname;
	};
	string getDepartment()
	{
		return this->department;
	};
	void setDepartment(string _department)
	{
		this->department = _department;
	};
	string getEmail()
	{
		return this->email;
	};
	void setEmail(string _email)
	{
		this->email = _email;
	};
	string getPhone()
	{
		return this->phone;
	};
	void setPhone(string _phone)
	{
		this->phone = _phone;
	};
};

// inherit Student class from People class
class Student : public People
{
private:
	// Student properties
	string year;

public:
	// constructor
	Student(){};
	Student(string *_temp, int size);
	// get and set functions for Year property
	string getYear()
	{
		return this->year;
	};
	void setYear(string _year)
	{
		this->year = _year;
	};
	// display students
	void display()
	{
		cout << getNumber() << " - ";
		cout << getName() << " - ";
		cout << getSurname() << " - ";
		cout << getDepartment() << " - ";
		cout << getYear() << " - ";
		cout << getEmail() << " - ";
		cout << getPhone() << endl;
	};
};

Student ::Student(string _temp[], int size)
{
	// construct Student object using the line in the given file
	setNumber(_temp[0]);
	setName(_temp[1]);
	setSurname(_temp[2]);
	setDepartment(_temp[3]);
	setYear(_temp[4]);
	setEmail(_temp[5]);
	setPhone(_temp[6]);
}

// inherit Lecturer class from People class
class Lecturer : public People
{
private:
	// Lecturer properties
	string chair;

public:
	// constructor
	Lecturer(){};
	Lecturer(string *_temp);
	// get and set functions for Chair property
	string getChair()
	{
		return this->chair;
	};
	void setChair(string _chair)
	{
		this->chair = _chair;
	};
	// display lecturers
	void display()
	{
		cout << " " << getNumber() << "   ";
		cout << getName() << " ";
		cout << getSurname() << "     ";
		cout << getDepartment() << "      ";
		cout << getEmail() << "    ";
		cout << getPhone() << "     ";
		cout << getChair() << endl;
	};
};

Lecturer ::Lecturer(string *_temp)
{
	// construct Lecturer object using the line in the given file
	setNumber(_temp[0]);
	setName(_temp[1]);
	setSurname(_temp[2]);
	setDepartment(_temp[3]);
	setEmail(_temp[4]);
	setPhone(_temp[5]);
	setChair(_temp[6]);
}

// composite Appointment class from Student and Lecturer classes
class Appointment
{
private:
	// appointment properties
	string date;
	string start;
	string end;

public:
	// composition
	Lecturer L;
	Student S;
	// constructor
	Appointment(){};
	Appointment(string *_temp);
	// get and set functions for Date, Start and End
	string getDate()
	{
		return this->date;
	};
	void setDate(string _date)
	{
		this->date = _date;
	};
	string getStart()
	{
		return this->start;
	}
	void setStart(string _start)
	{
		this->start = _start;
	}
	string getEnd()
	{
		return this->end;
	}
	void setEnd(string _end)
	{
		this->end = _end;
	};
	// display appointments
	void display()
	{
		cout << "   " << S.getNumber() << "   ";
		cout << "   " << L.getNumber() << "   ";
		cout << "     " << getDate() << "   ";
		cout << "   " << getStart() << "   ";
		cout << getEnd() << endl;
	};
};

Appointment ::Appointment(string *_temp)
{
	S.setNumber(_temp[0]);
	L.setNumber(_temp[1]);
	setDate(_temp[2]);
	setStart(_temp[3]);
	setEnd(_temp[4]);
}

// set count array variables as the entries of the files, student-lecturer-appointment numbers respectively
void countFile(string filename, int filenum)
{

	string temp;
	ifstream readFile;
	readFile.open(filename);
	while (getline(readFile, temp))
	{
		count[filenum]++;
	}
	readFile.close();
}

// read relevant information from the files
void readFromFile(Student _s[], Lecturer _l[], Appointment _a[], string f1, string f2, string f3)
{

	string temp[10];
	int i = 0, num = 0, j = 0;
	// Student.csv reading
	ifstream readFile(f1);
	string line;
	while (getline(readFile, line))
	{
		stringstream ss(line);
		i = 0;
		// Read each line from the CSV file
		while (getline(ss, temp[i], ','))
		{
			i++;

			// Check if we have read all elements in a line
			if (i == 7)
			{
				// Create a Student object using the relevant information from the temp array
				Student s(temp, 7);

				// Store the Student object in the array _s
				_s[num] = s;

				// Increment the counter for the number of students
				num++;

				// Reset the counter for the temp array
				i = 0;
			}
		}
	}

	// Close the file
	readFile.close();
	// read from Lecturer.csv
	i = 0;
	num = 0;
	ifstream readFile2(f2);
	string line2;
	while (getline(readFile2, line2))
	{
		stringstream ll(line2);
		i = 0;
		// Read each line from the CSV file
		while (getline(ll, temp[i], ','))
		{
			i++;

			// control with 7, since each line contains 7 elements
			if (i == 7)
			{
				// line is read, now create a Lecturer object using the relevant information of this line
				Lecturer l(temp);
				_l[num] = l;
				num++;
				i = 0;
			}
		}
	}
	readFile.close();

	// read from appointments.csv file
	bool control;
	i = 0;
	num = 0;
	ifstream readFile3(f3);
	string line3;
	while (getline(readFile3, line3))
	{
		stringstream mm(line3);
		i = 0;
		// Read each line from the CSV file
		while (getline(mm, temp[i], ','))
		{
			i++;

			// control with 5, since each line contains 5 elements
			if (i == 5)
			{
				// line is read, now create a Appointment object using the relevant information of this line
				// if this is the first appointment, add it directly
				if (num == 0)
				{
					Appointment a(temp);
					_a[num] = a;
					num++;
					i = 0;
				}
				// if this is not the first appointment, control if any overlaps with the previous appointments
				else
				{
					for (j = 0; j < num; j++)
					{
						// if overlap occurs, display an error message
						if (_a[j].L.getNumber() == temp[1] && _a[j].getDate() == temp[2] && (_a[j].getStart() == temp[3]))
						{
							cout << "Error. " << temp[0] << " between " << temp[1] << " appointment cannot be scheduled." << endl;
							cout << "This time period is full. " << endl
								 << endl;
							control = false;
							break;
							
						}
						// if not, keep going
						else
							control = true;
					}
					if (control)
					{
						Appointment a(temp);
						_a[num] = a;
						num++;
					}
					i = 0;
				}
			}
		}
	}
	readFile.close();
}

int main()
{

	// init global array variables as zero
	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	// get command line arguments for file names
	string file1 = "Student.csv";
	string file2 = "Lecturer.csv";
	string file3 = "Appointments.csv";
	// calculate array sizes
	countFile(file1, 0);
	countFile(file2, 1);
	countFile(file3, 2);
	// x is student size, y is lecturer size, z is appoinment size
	int x = count[0];
	int y = count[1];
	int z = count[2];
	// initiate arrays of objects
	Student _S[100];
	Lecturer _L[100];
	Appointment _A[100];
	// read information of students, lecturers and appointments from the given files (named ogrenci.txt, akademisyen.txt, randevu.txt respectively)
	readFromFile(_S, _L, _A, file1, file2, file3);

	// menu variables
	int menuLoop = 0;
	int menu = 0;
	int i;

	while (menuLoop != 5)
	{
		// display main menu
		cout << endl
			 << "Student - Lecturer Appointment System" << endl
			 << endl;
		cout << "Menu:" << endl;
		cout << "1 - Student Menu" << endl;
		cout << "2 - Lecturer Menu" << endl;
		cout << "3 - Appointment Menu" << endl;
		cout << "4 - Get Final Lists" << endl;
		cout << "5 - Exit" << endl;
		cin >> menuLoop;

		// display detailed menu
		if (menuLoop == 1)
		{
			// student menu is chosen
			cout << "1 - Add Student" << endl;
			cout << "2 - List Students" << endl;
			cout << "3 - Remove Student" << endl;
			cout << "4 - Update Student" << endl;
			cin >> menu;

			if (menu == 1)
			{
				// student addition is chosen
				string temp_;
				Student newS;
				cout << "Student No.(6 digits):" << endl;
				cin >> temp_;
				newS.setNumber(temp_);
				cout << "Student Name:" << endl;
				cin >> temp_;
				newS.setName(temp_);
				cout << "Student Last Name:" << endl;
				cin >> temp_;
				newS.setSurname(temp_);
				cout << "Student Department:" << endl;
				cin >> temp_;
				newS.setDepartment(temp_);
				cout << "Student Starting Year:" << endl;
				cin >> temp_;
				newS.setYear(temp_);
				cout << "Student E-Mail:" << endl;
				cin >> temp_;
				newS.setEmail(temp_);
				cout << "Student Phone Number:" << endl;
				cin >> temp_;
				newS.setPhone(temp_);

				_S[x] = newS;
				x++;
			}
			else if (menu == 2)
			{
				cout << "****__________________STUDENT MENU_________________*****" << endl;
				// student display is chosen
				cout << endl;
				for (i = 0; i < x; i++)
				{
					_S[i].display();
				}
			}
			else if (menu == 3)
			{
				// student deletion is chosen
				string temp_;
				int deleted;
				cout << "Enter the Student No(6 digits) to remove:" << endl;
				cin >> temp_;
				i = 0;
				while (i < x)
				{
					if (_S[i].getNumber() == temp_)
						deleted = i;
					i++;
				}
				for (i = deleted; i < x; i++)
				{
					_S[i] = _S[i + 1];
				}
				x--;
			}
			else if (menu == 4)
			{
				// student update is chosen
				string temp_;
				int updated;
				cout << "Enter the Student No.(6 digits) to update:" << endl;
				cin >> temp_;
				i = 0;
				while (i < x)
				{
					if (_S[i].getNumber() == temp_)
						updated = i;
					i++;
				}
				cout << "Updated Student Name:" << endl;
				cin >> temp_;
				_S[updated].setName(temp_);
				cout << "Updated Student Last Name:" << endl;
				cin >> temp_;
				_S[updated].setSurname(temp_);
				cout << "Updated Student Department:" << endl;
				cin >> temp_;
				_S[updated].setDepartment(temp_);
				cout << "Updated Student Starting Year:" << endl;
				cin >> temp_;
				_S[updated].setYear(temp_);
				cout << "Updated Student E-Mail:" << endl;
				cin >> temp_;
				_S[updated].setEmail(temp_);
				cout << "Updated Student Phone Number:" << endl;
				cin >> temp_;
				_S[updated].setPhone(temp_);
			}
			else
			{
				cout << "Error." << endl;
			}
		}
		else if (menuLoop == 2)
		{
			// lecturer menu is chosen
			cout << "1 - Add Lecturer" << endl;
			cout << "2 - List Lecturers" << endl;
			cout << "3 - Remove Lecturer" << endl;
			cout << "4 - Update Lecturer" << endl;
			cin >> menu;

			if (menu == 1)
			{
				// lecturer addition is chosen
				string temp_;
				Lecturer newL;
				cout << "Lecturer No.(4 digits):" << endl;
				cin >> temp_;
				newL.setNumber(temp_);
				cout << "Lecturer Name:" << endl;
				cin >> temp_;
				newL.setName(temp_);
				cout << "Lecturer Last Name:" << endl;
				cin >> temp_;
				newL.setSurname(temp_);
				cout << "Lecturer Department:" << endl;
				cin >> temp_;
				newL.setDepartment(temp_);
				cout << "Lecturer E-Mail:" << endl;
				cin >> temp_;
				newL.setEmail(temp_);
				cout << "Lecturer Phone Number:" << endl;
				cin >> temp_;
				newL.setPhone(temp_);
				cout << "Lecturer Title:" << endl;
				cin >> temp_;
				newL.setChair(temp_);

				_L[y] = newL;
				y++;
			}
			else if (menu == 2)
			{
				cout << "****__________________LECTURERS MENU_________________*****" << endl;
				// lecturer display is chosen
				cout << endl;

				for (i = 0; i < y; i++)
				{
					_L[i].display();
				}
			}
			else if (menu == 3)
			{
				// lecturer deletion is chosen
				string temp_;
				int deleted;
				cout << "Enter the Lecturer No.(4 digits) to remove:" << endl;
				cin >> temp_;
				i = 0;
				while (i < y)
				{
					if (_L[i].getNumber() == temp_)
						deleted = i;
					i++;
				}
				for (i = deleted; i < y; i++)
				{
					_L[i] = _L[i + 1];
				}
				y--;
			}
			else if (menu == 4)
			{
				// lecturer update is chosen
				string temp_;
				int updated;
				cout << "Enter the Lecturer No.(4 digits) to update:" << endl;
				cin >> temp_;
				i = 0;
				while (i < y)
				{
					if (_L[i].getNumber() == temp_)
						updated = i;
					i++;
				}
				cout << "Updated Lecturer Name:" << endl;
				cin >> temp_;
				_L[updated].setName(temp_);
				cout << "Updated Lecturer Last Name:" << endl;
				cin >> temp_;
				_L[updated].setSurname(temp_);
				cout << "Updated Lecturer Department:" << endl;
				cin >> temp_;
				_L[updated].setDepartment(temp_);
				cout << "Updated Lecturer E-Mail:" << endl;
				cin >> temp_;
				_L[updated].setEmail(temp_);
				cout << "Updated Lecturer Phone Number:" << endl;
				cin >> temp_;
				_L[updated].setPhone(temp_);
				cout << "Updated Lecturer title:" << endl;
				cin >> temp_;
				_L[updated].setChair(temp_);
			}
			else
			{
				cout << "Error." << endl;
			}
		}
		else if (menuLoop == 3)
		{
			// appointment menu is chosen
			cout << "1 - Add Appointment" << endl;
			cout << "2 - List Appointments" << endl;
			cout << "3 - Remove Appointment" << endl;
			cout << "4 - Update Appointment" << endl;
			cin >> menu;

			if (menu == 1)
			{
				// appointment addition is chosen
				string temp_;
				Appointment newA;
				cout << "Student No(6 digits):" << endl;
				string temp0;
				cin >> temp0;
				newA.S.setNumber(temp0);
				cout << "Lecturer No(4 digits):" << endl;
				string temp1;
				cin >> temp1;
				newA.L.setNumber(temp1);
				cout << "Appointment Date:" << endl;
				string temp2;
				cin >> temp2;
				newA.setDate(temp2);
				cout << "Starting Hour:" << endl;
				string temp3;
				cin >> temp3;
				newA.setStart(temp3);
				cout << "Ending Hour:" << endl;
				cin >> temp_;
				newA.setEnd(temp_);
				bool control;
				int j = 0;
				for (j = 0; j < z; j++)
				{
					if (_A[j].L.getNumber() == temp1 && _A[j].getDate() == temp2 && (_A[j].getStart() == temp3))
					{
						cout << "Error. " << temp0 << " between " << temp1 << " appointment cannot be scheduled." << endl;
						cout << "This time period is full. " << endl
							 << endl;
						control = false;
						break;
					}
					// if not, keep going
					else
						control = true;
				}
				if (control)
				{
					_A[z] = newA;
					z++;
				}
			}
			else if (menu == 2)
			{
				// appointment display is chosen
				cout << "**--------------------------Appointment Menu----------------------**" << endl;
				cout << "**--------------------------  ***Welcome*** ----------------------**" << endl;
				cout << endl;

				for (i = 0; i < z; i++)
				{
					_A[i].display();
				}
			}
			else if (menu == 3)
			{
				// appointment deletion is chosen
				string temp_, temp_2;
				int deleted;
				cout << "Enter the  Student No.(6 digits) to remove:" << endl;
				cin >> temp_;
				cout << "Enter the Lecturer No.(4 digits) to remove:" << endl;
				cin >> temp_2;
				i = 0;
				while (i < z)
				{
					if (_A[i].S.getNumber() == temp_ && _A[i].L.getNumber() == temp_2)
						deleted = i;
					i++;
				}
				for (i = deleted; i < z; i++)
				{
					_A[i] = _A[i + 1];
				}
				z--; // to remoove the line deleted;
			}
			else if (menu == 4)
			{
				// appointment update is chosen
				string temp_, temp_2;
				int updated;
				cout << "Enter the Student No.(6 digits) to update:" << endl;
				cin >> temp_;
				cout << "Enter the Lecturer No.(4 digits) to update:" << endl;
				cin >> temp_2;
				i = 0;
				while (i < z)
				{
					if (_A[i].S.getNumber() == temp_ && _A[i].L.getNumber() == temp_2)
						updated = i;
					i++;
				}
				cout << "Updated Appointment Date:" << endl;
				cin >> temp_;
				_A[updated].setDate(temp_);
				cout << "Updated Starting Hour:" << endl;
				cin >> temp_;
				_A[updated].setStart(temp_);
				cout << "Updated Ending Hour:" << endl;
				cin >> temp_;
				_A[updated].setEnd(temp_);
			}
			else
			{
				cout << "Error." << endl;
			}
		}
		else if (menuLoop == 4)
		{
			// write to file is chosen
			ofstream writeToFile;

			// updated student file is writing
			writeToFile.open("Student.csv");
			for (i = 0; i < x; i++)
			{
				writeToFile << _S[i].getNumber() << "," << _S[i].getName() << ","
							<< _S[i].getSurname() << ","
							<< _S[i].getDepartment() << ","
							<< _S[i].getYear() << ","
							<< _S[i].getEmail() << ","
							<< _S[i].getPhone() << endl;
			}
			writeToFile.close();

			// updated lecturer file is writing
			writeToFile.open("Lecturer.csv");
			for (i = 0; i < y; i++)
			{
				writeToFile << _L[i].getNumber() << ","
							<< _L[i].getName() << ","
							<< _L[i].getSurname() << ","
							<< _L[i].getDepartment() << ","
							<< _L[i].getEmail() << ","
							<< _L[i].getPhone() << ","
							<< _L[i].getChair() << endl;
			}
			writeToFile.close();

			// updated appointment file is writing
			writeToFile.open("Appointments.csv");
			for (i = 0; i < z; i++)
			{
				writeToFile << _A[i].S.getNumber() << ","
							<< _A[i].L.getNumber() << ","
							<< _A[i].getDate() << ","
							<< _A[i].getStart() << ","
							<< _A[i].getEnd() << endl;
			}
			writeToFile.close();
		}
		else if (menuLoop == 5)
		{
			cout << "Program terminated." << endl;
			return 0;
		}
		else
		{
			cout << "Error." << endl;
		}
	}

	return 0;
}
