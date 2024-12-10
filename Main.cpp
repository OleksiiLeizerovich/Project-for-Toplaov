#include <iostream>
#include <string>
#include <vector>

using namespace std;

class University;
class Department;
class Teacher;
class Human;
class Student;
class Course;

class Faculty
{
private:
    string name;
    string dean;
    vector<Student *> students;
    vector<Teacher *> teachers;

public:
    void setName(const string &n) { name = n; }
    void setDean(const string &d) { dean = d; }
    void getDetails() const
    {
        cout << "\n=== Деталі про факультет ===" << endl;
        cout << "Назва: " << name << endl;
        cout << "Декан: " << dean << endl;
        cout << "Кількість студентів: " << students.size() << endl;
        cout << "Кількість викладачів: " << teachers.size() << endl;
        cout << "============================" << endl;
    }
    vector<Student *> getStudents() const;
    void addStudent(Student *student);
    void removeStudent(Student *student);
    vector<Teacher *> getTeachers() const;
    void addTeacher(Teacher *teacher);
    void removeTeacher(Teacher *teacher);
};

class University
{
private:
    string name;
    string location;
    int establishmentYear;
    int numberOfFaculties;
    vector<Faculty *> faculties;

public:
    University() : establishmentYear(0), numberOfFaculties(0) {}
    void setName(const string &n) { name = n; }
    void setLocation(const string &l) { location = l; }
    void setEstablishmentYear(int year) { establishmentYear = year; }
    void setNumberOfFaculties(int num) { numberOfFaculties = num; }
    void getDetails()
    {
        cout << "\n=== Деталі про університет ===" << endl;
        cout << "Ім'я: " << name << endl;
        cout << "Локація: " << location << endl;
        cout << "Заснування: " << establishmentYear << endl;
        cout << "Кількість факультетів: " << faculties.size() << endl;
        cout << "============================" << endl;
    };
    void FullDetails()
    {
        getDetails();

        cout << "\n=== Детальна інформація про всі факультети ===" << endl;
        if (faculties.empty())
        {
            cout << "Факультети відсутні" << endl;
        }
        else
        {
            for (Faculty *faculty : faculties)
            {
                faculty->getDetails();
            }
        }
        cout << "===========================================" << endl;
    }
    vector<Faculty *> getFaculties() { return faculties; }
    void addFaculty(Faculty *faculty)
    {
        faculties.push_back(faculty);
    }
    void removeFaculty(Faculty *faculty) {
        for(auto it = faculties.begin(); it != faculties.end(); ++it) {
            if(*it == faculty) {
                faculties.erase(it);
                break;
            }
        }
    }
};

class Department
{
private:
    int ID;
    string headOfDepartment;
    string name;

public:
    void setID(int id) { ID = id; }
    void setName(const string &n) { name = n; }
    void setHeadOfDepartment(const string &head) { headOfDepartment = head; }
    void getDetails() const
    {
        cout << "\n=== Деталі про департамент ===" << endl;
        cout << "ID: " << ID << endl;
        cout << "Ім'я: " << name << endl;
        cout << "Голова департаменту: " << headOfDepartment << endl;
        cout << "============================" << endl;
    }
};

class Human
{
private:
    string name;
    string id;
    int year;
    Faculty *faculty;
    string address;

public:
    void setName(const string &n) { name = n; }
    void setID(const string &i) { id = i; }
    void setYear(int y) { year = y; }
    Human() : year(0), faculty(nullptr) {}
    virtual void getDetails() const;
};

class Student : public Human
{
private:
    int course;
    bool stateFunded;

public:
    void setCourse(int c) { course = c; }
    void setStateFunded(bool state) { stateFunded = state; }
    Student() : course(0), stateFunded(false) {}
    void getDetails() const override
    {
        Human::getDetails();
        cout << "\n--- Деталі про студента ---" << endl;
        cout << "Курс: " << course << endl;
        cout << "Фінансується держвою: " << (stateFunded ? "Так" : "Ні") << endl;
        cout << "--------------------------------" << endl;
    };
    Faculty *getFaculty() const;
    bool getStateFunded() const { return stateFunded; }
    void changeFaculty(Faculty *newFaculty);
};

class Teacher : public Human
{
private:
    string position;
    Faculty *faculty;
    int experience;
    int classroom;

public:
    void setPosition(const string &pos) { position = pos; }
    void setExperience(int exp) { experience = exp; }
    void setClassroom(int room) { classroom = room; }
    Teacher() : faculty(nullptr), experience(0), classroom(0) {}
    void getDetails() const override
    {
        cout << "--- Інформація про викладача ---" << endl;
        cout << "Посада: " << position << endl;
        cout << "Досвід: " << experience << " years" << endl;
        cout << "Клас: " << classroom << endl;
        cout << "--------------------------------" << endl;
    };
    int getExperience() const { return experience; }
    int getClassroom() const { return classroom; }
    string getPosition() const { return position; }
};

class Course
{
private:
    string courseID;
    vector<string> students;
    vector<string> teachers;
    Teacher *professor;

public:
    Course() : professor(nullptr) {}
    void addStudent(Student *student);
    void removeStudent(Student *student);
    void setProfessor(Teacher *prof) { professor = prof; }
    Teacher *getProfessor() { return professor; }
};

int main()
{
    setlocale(LC_ALL, "uk-UA.UTF-8");

    University *univ = new University();

    string name, location;
    int year;

    cout << "=== Введіть інформацію про університет ===" << endl;
    cout << "Назва університету: ";
    getline(cin, name);
    univ->setName(name);

    cout << "Місце розташування: ";
    getline(cin, location);
    univ->setLocation(location);

    cout << "Рік заснування: ";
    cin >> year;
    cin.ignore();
    univ->setEstablishmentYear(year);

    int numFaculties;
    cout << "Введіть кількість факультетів: ";
    cin >> numFaculties;
    cin.ignore();

    for (int i = 0; i < numFaculties; i++)
    {
        Faculty *faculty = new Faculty();
        string facultyName, deanName;

        cout << "\n=== Факультет " << i + 1 << " ===" << endl;
        cout << "Назва факультету: ";
        getline(cin, facultyName);
        faculty->setName(facultyName);

        cout << "Декан факультету: ";
        getline(cin, deanName);
        faculty->setDean(deanName);

        univ->addFaculty(faculty);
    }

    cout << "\nВся інформація про університет та факультети:" << endl;
    univ->FullDetails();

    vector<Faculty *> faculties = univ->getFaculties();
    for (Faculty *faculty : faculties)
    {
        delete faculty;
    }
    delete univ;

    return 0;
}