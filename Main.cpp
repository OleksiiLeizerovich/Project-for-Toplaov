#include <iostream>
#include <string>
#include <vector>

using namespace std;

class University;
class Faculty;
class Department;
class Teacher;
class Human;
class Student;
class Course;

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
        cout << "Кількість факультетів: " << numberOfFaculties << endl;
        cout << "============================" << endl;
    };
    vector<Faculty *> getFaculties() { return faculties; }
    void addFaculty(Faculty *faculty);
    void removeFaculty(Faculty *faculty);
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

    // University
    University* univ = new University();
    univ->setName("Київський національний університет");
    univ->setLocation("Київ");
    univ->setEstablishmentYear(1834);
    univ->setNumberOfFaculties(13);
    univ->getDetails();

    // Faculty
    Faculty* fac = new Faculty();
    fac->setName("Факультет інформаційних технологій");
    fac->setDean("Проф. Іваненко І.І.");
    fac->getDetails();

    // Department
    Department* dept = new Department();
    dept->setID(101);
    dept->setName("Кафедра програмної інженерії");
    dept->setHeadOfDepartment("Доц. Петренко П.П.");
    dept->getDetails();

    // Student
    Student* stud = new Student();
    stud->setName("Сидоренко Олена");
    stud->setID("ST001");
    stud->setYear(2);
    stud->setCourse(3);
    stud->setStateFunded(true);
    stud->getDetails();

    // Teacher
    Teacher* teach = new Teacher();
    teach->setName("Коваленко Михайло");
    teach->setID("TC001");
    teach->setPosition("Доцент");
    teach->setExperience(10);
    teach->setClassroom(305);
    teach->getDetails();

    // Human (використовуємо через Student, оскільки Human є абстрактним)
    Human* human = new Student();
    human->setName("Мельник Ірина");
    human->setID("ST002");
    human->setYear(1);
    human->getDetails();
    return 0;
}