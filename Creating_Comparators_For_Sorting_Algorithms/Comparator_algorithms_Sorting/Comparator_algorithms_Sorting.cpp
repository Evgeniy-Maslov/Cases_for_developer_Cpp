#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

//*******************/ человек /*******************//
struct Person 
{
    Person(const std::string& _lastName, const std::string& _firstName, int _age, int _job_id, int _position_id)
            : lastName(_lastName), firstName(_firstName), age(_age), job_id(_job_id), position_id(_position_id) {}
    std::string lastName;
    std::string firstName;
    int age;
    int job_id;
    int position_id;
};

//******************/ место работы /****************//
struct Job          
{
    Job(): id(0) {}
    Job(const std::string& _name, int _id) : name(_name), id(_id) {}
    Job(const Job& other) : name(other.name), id(other.id) {}
    Job& operator=(const Job& other)
    {
        name = other.name;
        id = other.id;
        return *this;
    }
    Job& operator()(const Job& other)
    {
        name = other.name;
        id = other.id;
        return *this;
    }
    std::string name ;
    int id;
};

//*****************/ должность /********************//
struct Position  
{
    Position() : id(0) {}
    Position(const std::string& _name, int _id) : name(_name), id(_id) {}
    Position(const Position& other) : name(other.name), id(other.id) {}
    Position& operator()(const Position& other)
    {
        name = other.name;
        id = other.id;
        return *this;
    }
    Position& operator=(const Position& other)
    {
        name = other.name;
        id = other.id;
        return *this;
    }
    std::string name;
    int id;
};

/*
      Класс PersonsList хранит список людей в std::vector, а места работы и должности в map - ах,
      которые индексируются по id. Класс Person ссылается на Job и Position по их id.
*/
class PersonsList
{
public:
    PersonsList(): jobMap_id(1), posMap_id(0) {}
    void addPerson(const Person& person)
    { 
        persons.push_back(person);
    }
    void addPosition(const Position& position)
    {
       positionsMap.insert(std::pair<int, Position>(posMap_id++, position));
    }
    void addJob(const Job& job)
    {
       jobsMap.insert(std::pair<int, Job>(jobMap_id++, job));
    }

    bool operator ()(const Person& person1, const Person& person2)
    {
        return name_Job(person1.job_id) < name_Job(person2.job_id);
    }

    std::string name_Job(int id)
    {
        auto nameJob = jobsMap[id];
        return nameJob.name;
        /*for (auto iter{ jobsMap.begin() }; iter != jobsMap.end(); iter++)
        {
            if (id == iter->second.id)
            {
                return iter->second.name;
            }
        }*/
    }

    std::string name_Position(int id)
    {
        auto namePosition = jobsMap[id];
        return namePosition.name;
       /* for (auto iter{ positionsMap.begin() }; iter != positionsMap.end(); iter++)
        {
            if (id == iter->second.id)
            {
                return iter->second.name;
            }
        }*/
    }

    void print_person()
    {
        for (size_t i = 0; i < persons.size(); i++)
        {
            std::cout << persons[i].firstName << " "
                << persons[i].lastName 
                << "\t - age: "<< persons[i].age 
                << " , job: " << name_Job(persons[i].job_id)
                << " , position: " << name_Position(persons[i].position_id) << std::endl;
        }
    }

    void sortByName();
    void sortByAge();
    void sortByJob();

private:
    std::vector<Person> persons;
    std::map<int, Job> jobsMap;
    int jobMap_id;
    std::map<int, Position> positionsMap;
    int posMap_id;

};

/*
    В программе реализована функция сортировки по именам с помощью статической функции сравнения и std::stable_sort.
*/
bool compareByName(const Person& person1, const Person& person2)
{
    if (person1.lastName == person2.lastName) {
        return person1.firstName < person2.firstName;
    }
    return person1.lastName < person2.lastName;
}

void PersonsList::sortByName()
{
    stable_sort(persons.begin(), persons.end(), compareByName);
}

bool compareByAge(const Person& person1, const Person& person2)
{
    return person1.age < person2.age;
}

void PersonsList::sortByAge()
{
    stable_sort(persons.begin(), persons.end(), compareByAge);
}

class compareByJob
{
public:
    compareByJob(PersonsList& _persList) : persList(&_persList) {}
    bool operator()(const Person& person1, const Person& person2)
    {
        return persList->name_Job(person1.job_id) < persList->name_Job(person2.job_id);
    }
private:
    PersonsList *persList;
};


void PersonsList::sortByJob() 
{
    std::stable_sort(persons.begin(), persons.end(), compareByJob(*this));
}


//  В main’е идет наполнение базы данных, сортировки и вывод результатов в консоль.
//  int main()
//  Тестовое задание состоит в реализации сортировки по месту работы, причем не по id, а по названию.
//  Важно, что в std::stable_sort третьим параметром передается функция, которая принимает только 2 элемента
//  для сравнения.Поскольку указатель на класс не передается, то эта функция не может быть методом класса, 
//  а только статической.Разрешается менять код в любом месте.
//  Сложность задачи состоит в передаче дополнительных данных в функцию сравнения, 
//  которая используется сортировкой из стандартной библиотеки.

//  Из википедии :
//  Функциональный объект(англ.function object), так же функтор, функционал и функционоид — распространённая 
//  в программировании конструкция, позволяющая использовать объект как функцию.Часто используется как callback,
//  делегат, либо как замена лямбда - выражениям в нефункциональных языках программирования.

int main()
{
    PersonsList person_list;
    person_list.addJob(Job("Electronics_Store", 1));
    person_list.addJob(Job("Cafeteria", 2));
    person_list.addJob(Job("Administration", 3));
    person_list.addJob(Job("Auto_Service", 4));
    person_list.addJob(Job("Service_Center", 5));

    person_list.addPosition(Position("secretary", 1));
    person_list.addPosition(Position("administrator", 2));
    person_list.addPosition(Position("manager", 3));
    person_list.addPosition(Position("auto_mechanic", 4));
    person_list.addPosition(Position("lawyer", 5));                 // юрист
    person_list.addPosition(Position("pastry_chef", 6));            // кондитер
    person_list.addPosition(Position("cook", 7));
    person_list.addPosition(Position("consultant", 8));
    person_list.addPosition(Position("programmer", 9));
    person_list.addPosition(Position("technician_repairman", 10));  // мастер по ремонту техники
    person_list.addPosition(Position("director", 11));

    person_list.addPerson(Person("Pitt", "Brad", 61, 5, 2));
    person_list.addPerson(Person("Depp", "Johnny", 61, 3, 5));
    person_list.addPerson(Person("Cage", "Nicolas", 61, 4, 10));
    person_list.addPerson(Person("Clooney", "George", 63, 1, 8));
    person_list.addPerson(Person("Pacino", "Al", 84, 2, 6));
    person_list.addPerson(Person("Douglas", "Michael", 80, 3, 2));
    person_list.addPerson(Person("Travolta", "John", 71, 2, 7));
    person_list.addPerson(Person("Costner", "Kevin", 70, 5, 4));
    person_list.addPerson(Person("Carrey", "Jim", 63, 2, 8));
    person_list.addPerson(Person("DiCaprio", "Leonardo", 50, 3, 9));
    person_list.addPerson(Person("Washington", "Denzel", 70, 4, 10));
    person_list.addPerson(Person("Cruise", "Tom", 62, 1, 5));
    person_list.addPerson(Person("Depp", "Maks", 43, 3, 4));


    std::cout << "\tbefore sorting\n" << std::endl;
    person_list.print_person();
    std::cout << std::endl;

    std::cout << "\tsortBylastName()\n " << std::endl;
    person_list.sortByName();
    person_list.print_person();
    std::cout << std::endl;

    std::cout << "\tsortByJob()\n " << std::endl;
    person_list.sortByJob();
    person_list.print_person();
    std::cout << std::endl;

    std::cout << "\tsortByAge()\n " << std::endl;
    person_list.sortByAge();
    person_list.print_person();  
    std::cout << std::endl;

    return 0;
}

