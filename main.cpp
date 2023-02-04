#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
private:
    string email;
public:
    string first_name;
    string last_name;
    int age;
public:
    void setEmail(string value) { email = value; }
    string getEmail() { return email; }

};

class Job_Person : public Person
{
public:
    string position;   
};

class Department {
public:
    string name;
    Job_Person manager;
    vector<Job_Person> employees;
    vector<Department> sub_departments;

};



int GetRandomNumber(int min, int max)
{
    // Получить случайное число

    int num = min + rand() % (max - min + 1);

    return num;
}

std::string first_names[] = { "John", "Jane", "Bob", "Alexey", "Mike", "Emma", "David", "Olivia", "Daniel"};
std::string last_names[] = { "Smith", "Johnson", "Brown", "Petrov", "Miller", "Wilson", "Moore", "Taylor", "Anderson", };

Job_Person generateJobPerson(string position) {
    // генерация работника

    Job_Person job_person;
    job_person.first_name = first_names[GetRandomNumber(0, 7)];;
    job_person.last_name = last_names[GetRandomNumber(0, 7)];
    job_person.age = GetRandomNumber(20, 60);
    job_person.position = position;
    job_person.setEmail(job_person.first_name + "@example.com");

    return job_person;
}

vector<Department> generateDepartments(int levels, int num_departments, int num_employees, int num_sub_departments) {
    // отвечает за генерацию отделов

    vector<Department> departments;

    // если уровень вложенности равен 0, то прерываем функцию, сделано во избежание бесконечной рекурсии
    if (levels <= 0) {
        return departments;
    }


    for (int i = 0; i < num_departments; i++) {
        Department department;
        department.name = std::to_string(i + 1);
        department.manager = generateJobPerson("manager");


        for (int j = 0; j < num_employees; j++) {
            department.employees.push_back(generateJobPerson("engineer"));
        }
        // если количество под-отделов не равно нулю, то создаем под-отделы
        if (num_sub_departments > 0) {
            department.sub_departments = generateDepartments(levels - 1, num_departments, num_employees, num_sub_departments);
        }
        departments.push_back(department);
    }

    return departments;
}



void print_department(const Department& department, int indent_level = 0) {
    // Отвечает за вывод структуры организаций в виде лесенки

    // отступ
    string indent = string(indent_level, ' ');

    // если отдел основной, то пишется его название
    if (indent_level == 0) {
        cout << indent << "department name: " << department.name << endl;

    }
    cout << indent << "|__ Manager: " << department.manager.first_name << " " << department.manager.last_name << endl;

    indent = string(indent_level + 2, ' ');

    cout << indent << "|" << endl;
    cout << indent << "| Employees:" << endl;

    for (const auto& employee : department.employees) {

        cout<< indent << "|" << employee.first_name << " " << employee.last_name << endl;
    }

    if (indent_level == 0) {
        cout << indent << "|__Sub-dep" << endl;

    }


    // т.к в под-отделах могут содержаться ещё подтодтелы, вызывается рекурсиваная функция
    // при отсутствий под-отделов она заканчиватся
    for (const auto& sub_department : department.sub_departments) {
        print_department(sub_department, indent_level + 5);

    }

    indent = string(indent_level, ' ');

    // создание лестницы
    string stairs = string(2, '_');

    //cout << indent_level << endl;
    cout << indent << stairs << "|" << endl;

}

int main()
{
    // указывание возможной "вложенности структуры" (сколько под-отделов может быть в под-отделах и основных отделах) при указываний единицы под-отделов не будет
    int num_levels = GetRandomNumber(1, 1);

    // количество возможных основных отделов
    int num_departments = GetRandomNumber(3, 3);

    // количество возможных работников в каждом отделе и под-отделе
    int num_employees = GetRandomNumber(2, 5);

    // количество возможных под-отделов
    int num_sub_departments = GetRandomNumber(0, 1);

    std::vector<Department> departments = generateDepartments(num_levels, num_departments, num_employees, num_sub_departments);

    // вывод каждого департамента в консоль
    for (int i = 0; i < departments.size(); i++) {
        print_department(departments[i]);
    }


    return 0;
}

