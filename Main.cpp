#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    vector<Student *> getStudents() const { return students; }
    void addStudent(Student *student) { students.push_back(student); }
    void removeStudent(Student *student)
    {
        students.erase(remove(students.begin(), students.end(), student), students.end());
    }
    vector<Teacher *> getTeachers() const { return teachers; }
    void addTeacher(Teacher *teacher) { teachers.push_back(teacher); }
    void removeTeacher(Teacher *teacher)
    {
        teachers.erase(remove(teachers.begin(), teachers.end(), teacher), teachers.end());
    }
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
    void removeFaculty(Faculty *faculty)
    {
        for (auto it = faculties.begin(); it != faculties.end(); ++it)
        {
            if (*it == faculty)
            {
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
    string address;

public:
    Human() : year(0) {}
    virtual ~Human() {}
    void setName(const string &n) { name = n; }
    void setID(const string &i) { id = i; }
    void setYear(int y) { year = y; }

    virtual void getDetails() const
    {
        cout << "\n--- Загальні дані ---" << endl;
        cout << "Ім'я: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Рік народження: " << year << endl;
        cout << "Адреса: " << address << endl;
    }
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
};

class Teacher : public Human
{
private:
    string position;
    int experience;

public:
    void setPosition(const string &pos) { position = pos; }
    void setExperience(int exp) { experience = exp; }
    Teacher() : experience(0) {}
    void getDetails() const override
    {
        Human::getDetails();
        cout << "--- Інформація про викладача ---" << endl;
        cout << "Посада: " << position << endl;
        cout << "Досвід: " << experience << " років" << endl;
        cout << "--------------------------------" << endl;
    };
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

        int numStudents, numTeachers;
        cout << "Кількість студентів на факультеті: ";
        cin >> numStudents;
        cin.ignore();
        for (int j = 0; j < numStudents; j++)
        {
            Student *student = new Student();
            string studentName;
            int course;
            bool stateFunded;

            cout << "Ім'я студента " << j + 1 << ": ";
            getline(cin, studentName);
            student->setName(studentName);

            cout << "Курс студента: ";
            cin >> course;
            student->setCourse(course);

            cout << "Фінансування (1 - так, 0 - ні): ";
            cin >> stateFunded;
            cin.ignore();
            student->setStateFunded(stateFunded);

            faculty->addStudent(student);
        }

        cout << "Кількість викладачів на факультеті: ";
        cin >> numTeachers;
        cin.ignore();
        for (int j = 0; j < numTeachers; j++)
        {
            Teacher *teacher = new Teacher();
            string teacherName, position;
            int experience;

            cout << "Ім'я викладача " << j + 1 << ": ";
            getline(cin, teacherName);
            teacher->setName(teacherName);

            cout << "Посада викладача: ";
            getline(cin, position);
            teacher->setPosition(position);

            cout << "Досвід викладача (роки): ";
            cin >> experience;
            cin.ignore();
            teacher->setExperience(experience);

            faculty->addTeacher(teacher);
        }

        univ->addFaculty(faculty);
    }

    cout << "\nВся інформація про університет та факультети:" << endl;
    univ->FullDetails();

    // Cleanup
    vector<Faculty *> faculties = univ->getFaculties();
    for (Faculty *faculty : faculties)
    {
        vector<Student *> students = faculty->getStudents();
        for (Student *student : students)
            delete student;

        vector<Teacher *> teachers = faculty->getTeachers();
        for (Teacher *teacher : teachers)
            delete teacher;

        delete faculty;
    }
    delete univ;

    return 0;
}