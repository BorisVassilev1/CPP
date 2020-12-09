#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
using namespace std;


class TextException : public exception {
    private:
        const char* message;
    public:
        TextException(const char* message) : message(message) {}
        virtual const char* what() const throw() {return message;}
};

class InvalidPackageException : public TextException {
    public:
        InvalidPackageException(const char* message) : TextException(message) {}
};

class InvalidRouterException : public TextException {
    public:
        InvalidRouterException(const char* message) : TextException(message) {}   
};

class Package {
    private:
        const char* content;
        const size_t length;
        const string sender_ip;
        const string receiver_ip;
        static int counter;
        const int id;
    public:
        Package(const char* content, const string sender_ip, const string receiver_ip) : length(strlen(content)), sender_ip(sender_ip), receiver_ip(receiver_ip), id(counter) {
            if(length == 0) throw InvalidPackageException("Packet: given 'content' parameter is a string of size 0.");
            this->content = content;
            if(sender_ip.compare("0.0.0.0") == 0 ||
                    sender_ip.compare("127.0.0.0") == 0 ||
                    receiver_ip.compare("0.0.0.0") == 0 ||
                    receiver_ip.compare("127.0.0.0") == 0)
                throw InvalidPackageException("Packet: one or more of the given values for 'sender_ip' and 'receiver_ip' is not a valid IP address."); 
            counter++;
        }

        ~Package() {
            delete content;
        }

        int validate() {
            return strlen(content) == length;
        }

        friend ostream& operator << (ostream& out, const Package& package) {
            out << "Package: ["; 
            out << package.content;
            out << ", " << package.sender_ip << ", " << package.receiver_ip << ", " << package.id << "]";
            return out;
        }

        const char* get_content() const {return content;}

        size_t get_length() const {return length;}

        const string get_sender_ip() const {return sender_ip;}

        const string get_receiver_ip() const {return receiver_ip;}

        static int get_counter() {return counter;}

        int get_id() const {return id;}
};

class RouteInfo {
    public:
        const string router_ip;
        const int index;
        int sent_count;

        RouteInfo(const string& router_ip,const int index) : router_ip(router_ip), index(index), sent_count(0) {}
        
        bool operator < (const RouteInfo& other) const {
            return sent_count < other.sent_count;
        }

        friend ostream& operator << (ostream& out, RouteInfo& route_info) {
            return out << "RouteInfo: [" << route_info.router_ip << ", " << route_info.index << ", " << route_info.sent_count << "]";
        }
};


class Router {
    private:
        string name;
        string ip;
        vector<Router*> routers;
        list<RouteInfo*> routing_table;
        static const int max_hop_count;
        static const int max_table_size;
        int packages_sent;

        int sort_table_if_needed() {
            if(packages_sent >= 10) {
                routing_table.sort([](const RouteInfo* one, const RouteInfo* other) {return *one < *other;});
                packages_sent = 0;
                return 1;
            }
            return 0;
        } 
    public:

        Router(string name, string ip) : name(name), ip(ip), packages_sent(0) {}


        ~Router() {
            for(auto i = routing_table.begin(); i != routing_table.end(); i ++) {
                delete *i;
            }
        }

        void add_router(const Router& router) {
            if(router.ip.compare("0.0.0.0") == 0 || router.ip.compare("127.0.0.0") == 0)
                throw InvalidRouterException("Router: tried to add a 'router' instance with an invalid IP");

            routers.push_back((Router*)&router);
        }

        int query_route(const string& address, const int hop_count) {
            if(address.compare(ip) == 0) {
                return 1;
            }
            if(hop_count == 0) return 0;
            for(auto i = routing_table.begin(); i != routing_table.end(); i ++) {
                if((*i)->router_ip.compare(address) == 0) {
                    return 1;
                }
            }
            for(int i = 0; i != (int)routers.size(); i ++) {
                Router* r = routers[i];
                int res = r->query_route(address, hop_count - 1);
                if(res) {
                    RouteInfo* info = new RouteInfo(address,i); 
                    if((int)routing_table.size() < max_table_size) {
                        routing_table.push_back(info);
                    } else {
                        delete routing_table.back();
                        routing_table.back() = info;
                    }
                    return 1;
                }
            }
            return 0;
        }

        void send_package(const Package& package) { 
            cout << endl << "Sending package: " << (Package&)package << " from router: " << name << endl;
            if(strlen(package.get_content()) == 0) {
                throw InvalidPackageException("Router: Tried sending an instance of 'Package' with empty content.");
            }
            if(package.get_sender_ip().compare("0.0.0.0") == 0 ||
                    package.get_sender_ip().compare("127.0.0.0") == 0 ||
                    package.get_receiver_ip().compare("0.0.0.0") == 0 ||
                    package.get_receiver_ip().compare("127.0.0.0") == 0)
                throw InvalidPackageException("Router: Tried sending an instance of 'Package' with invalid sender or receiver IP.");

            if(package.get_receiver_ip().compare(ip) == 0) {
                cout << "The package '" << package << "' has reached its destination." << endl;
                delete &package;
                return;
            }

            cout << "Searching in routing table for ip: " << package.get_receiver_ip() << endl;
            for(auto i = routing_table.begin(); i != routing_table.end(); i ++) {
                RouteInfo* info = *i;
                if(package.get_receiver_ip().compare(info->router_ip) == 0) {
                    cout << "Found route: " << *info << endl;
                    routers[info->index]->send_package(package);
                    info->sent_count ++;
                    packages_sent ++;
                    sort_table_if_needed();
                    return;
                }
            }
            cout << "Did not find any matches in routing table. Starting route query." << endl; 
            if(query_route(package.get_receiver_ip(), max_hop_count)) {
                cout << "query found a route. Sending again." << endl;
                this->send_package(package);
            } else {
                cout << "Query did not find a route. The package is thrown out." << endl;
                delete &package;
            }
        }

        friend ostream& operator << (ostream& out, Router& router) {
            return out << "Router: [" << router.get_name() << ", " << router.get_ip() << "]";
        }
        const string& get_name() const {return name;}
        const string& get_ip() const {return ip;}

        static int get_max_table_size() {return max_table_size;}
        static int get_max_hop_count() {return max_hop_count;}
};

int Package::counter = 0;
const int Router::max_hop_count = 2;
const int Router::max_table_size = 10;


char* to_c_str(string* str) {
    int size = str->length();
    char* res = new char[size];
    for(int i = 0; i < size; i ++) {
        res[i] = (*str)[i];
    }
    return res;
}

istream& input_router(istream& in, Router*& router) {
    if(in.eof()) return in;
    string name, ip;
    in >> name >> ip;

    if(!in) return in;

    router = new Router(name, ip);
    return in; 
}

istream& input_package(istream& in, Package*& package) {
    string ip1;
    string ip2;
    string content;
    in >> ip1 >> ip2 >> content;

    if(!in) return in;

    content.erase(0, 1);
    content.erase(content.length() - 1, 1);
    char* c_content = to_c_str(&content);
    package = new Package(c_content, ip1, ip2);
    return in;
}

auto find_router_by_name(vector<Router*>& routers, const string& name) {
    auto i = routers.begin();
    for(; i != routers.end(); ++ i) {
        if((*i)->get_name().compare(name) == 0) 
            break;
    }
    return i;
}

auto find_router_by_ip(vector<Router*>& routers, const string& ip) {
    auto i = routers.begin();
    for(;i != routers.end(); ++ i) {
        if((*i)->get_ip().compare(ip) == 0)
            break;
    }
    return i;
}

int main() {
    vector<Router*> routers;

    ifstream in("./routers.txt");
    Router* curr_r;
    while(input_router(in, curr_r)) {
        cout << *curr_r << endl; 
        routers.push_back(curr_r);
    }
    in.close();

    in.open("./network.txt");
    string name1, name2;
    while((in) >> name1 >> name2) {
        auto i1 = find_router_by_name(routers, name1);
        auto i2 = find_router_by_name(routers, name2);
        if(i1 == routers.end() || i2 == routers.end()) {
            cout << "Invalid connection" << endl;
            continue;
        }

        (*i1)->add_router(**i2);
        (*i2)->add_router(**i1); 
    }
    in.close();
    in.open("./packages.txt");
    Package* curr_p = nullptr;
    while(input_package(in, curr_p)) {
        auto i = find_router_by_ip(routers, curr_p->get_sender_ip());
        if(i == routers.end()) {
            cout << "could not find a router with that ip" << endl;
            continue;
        }
        (*i)->send_package((Package&)*curr_p);
    }
    in.close();

    for(auto i = routers.begin(); i != routers.end(); ++i) {
        delete *i;
    }
    return 0;
}
