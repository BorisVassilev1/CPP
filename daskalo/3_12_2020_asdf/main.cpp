#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Human {
protected:
    string* name;
    int position_code = -1;

public:
    Human() {
        name = new string();
    }
    Human(string* name, int position_code) {
        this -> name = name;
        this -> position_code = position_code; 
    }
    
    ~Human() {
        delete name;
    }

    int eval_payment();
    
    string& get_name() {
        return *name;
    }
    
    void set_name(string* name) {
        this -> name = name;
    }
    
    int& get_position_code() {
        return position_code;
    }
    
    void set_position_code(int position_code) {
        this -> position_code;
    }
};

class Manager : public Human {
    protected:
        int salary = -1;
    public:
        Manager() {}
        Manager(string* name, int salary) : Human(name, 0){
           this -> salary = salary;
        }

        int get_salary() {
            return salary;
        }

        void set_salary(int salary) {
            this -> salary = salary;
        }

        int eval_payment() {
            return salary;
        }

        friend ostream& operator << (ostream& out, Manager& manager) {
            out << "Manager:    [ name: " << *(manager.name);
            for(int i = 0; i < 32 - manager.name->length(); i ++)
                out << " ";
            out << ", payment: " << manager.eval_payment() << " ]";
            return out;
        }
};

class Project {
    private:
        int per_hour;
        int hours;
    public:
        Project() {}
        Project(int per_hour, int hours) {
            this -> per_hour = per_hour;
            this -> hours = hours;
        }

        int get_per_hour() {
            return per_hour;
        }

        void set_per_hour(int per_hour) {
            this -> per_hour = per_hour;
        }

        int get_hours() {
            return hours;
        }
        
        void set_hours(int hours) {
            this -> hours = hours;
        }
        friend istream& operator >> (istream& in, Project& project) {
            in >> project.per_hour;
            in >> project.hours;
            return in;
        }

        int eval_price() {
            return per_hour * hours;
        }
};

class Programmer : public Human {
    protected:
        vector<Project*>* projects;
    public:
        Programmer(string* name, Project* project) : Human(name, 1) {
            projects = new vector<Project*>();
            projects->push_back(project);
        }
    
        ~Programmer() {
            for(int i = 0; i < projects->size(); i ++) {
                delete ((*projects)[i]);
            }
            delete projects;
        }
        
        int eval_payment() {
            int pay = 0;
            for(int i = 0;i < projects->size(); i ++) {
                pay += (*projects)[i]->eval_price();
            }
            return pay;
        }

        friend ostream& operator << (ostream& out, Programmer& programmer) {
            out << "Programmer: [ name: " << *(programmer.name);
            for(int i = 0; i < 32 - programmer.name->length(); i ++) {
                out << " ";
            }
            out << ", payment: " << programmer.eval_payment() << " ]";
            return out;
        }

        void add_project(Project* project) {
            projects->push_back(project);
        }

        Project* get_project() {
            return ((*projects).back());
        }

        void pop_project() {
            projects->pop_back();
        }
};

istream& input(istream& in, Human** human) {
    string* name = new string();
    in >> *name;
    int position_code;
    in >> position_code;

    if(position_code) {
        Project* project = new Project();
        in >> *project;
        *human = new Programmer(name, project);

    } else {
        int salary;
        in >> salary;
        *human = new Manager(name, salary);
    }
    return cin;
}


int main() {
    vector <Human*> v;
    Human* curr_human;
    while(input(cin, &curr_human)) {
        auto i = v.begin();
        while(i != v.end()) {
            if((*i)->get_name().compare(curr_human->get_name()) == 0) {
                break;
            }
            ++ i;
        }

        if(i != v.end() && curr_human->get_position_code()) {
            Programmer* programmer = (Programmer*)curr_human;
            Programmer* programmer_v = (Programmer*)(*i);
            programmer_v->add_project(programmer->get_project());
            programmer->pop_project();
            delete curr_human;
        }
        else {
            v.push_back(curr_human);
        }
    }

    for(int i = 0; i < v.size(); i ++) {
        Human* human = v[i];
        if(human->get_position_code()) {
            Programmer* programmer = (Programmer*) human;
            cout << *programmer << endl;
        } else {
            Manager* manager = (Manager*) human;
            cout << *manager << endl;
        }
    }

}
