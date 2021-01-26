#include <bits/stdc++.h>
/*
This code simulates the workings of a router network.
We have class Router, class Package and a struct route_info.
*/

/*
Routers remember other routers they are connected to in a vector of pointers.
Each router has a name and IP address.
Each router has a routing table. Routing tables contain routing info.
Routing info consists of an IP(the route's destination), an index pointing to a neighbour of the sender, and the amount of packages sent.
*/
using namespace std;

vector<string> split_string(string input_string);
string remove_quote(string str){
	if((*str.begin())=='\"')str.erase(str.begin());
	if((*(str.end()-1))=='\"')str.erase(str.end()-1);
	return str;
}
struct route_info{
	string address;
	int connection_index;
	int packages_sent = 0;
	route_info(string address, int connection_index){
		this->address = address;
		this->connection_index = connection_index;
	}
};
bool more_packages(route_info* a, route_info* b){
	return a->packages_sent>b->packages_sent; //promenqsh ako bugi sorta
}

int in (list<route_info*> routes, string address){
	for(auto it = routes.begin();it!=routes.end();it++){
		if(not (*it)->address.compare(address))return distance(routes.begin(),it);
	}
	return -1;
}
class Package{
public:
	char* content;
	int content_length;
	string sender;
	string receiver;
	static int counter ;
	int package_number;
	int validate(){
		return strlen(content)==content_length;
	}
	Package(char* content, string sender, string receiver){
		if(strlen(content)==0)throw "Empty content";
		if(not sender.compare("0.0.0.0") or not sender.compare("127.0.0.0") or not receiver.compare("0.0.0.0") or not receiver.compare("127.0.0.0"))throw "Invalid IP";
		counter++;
		this->content = content;
		this->sender = sender;
		this->receiver = receiver;
		this->content_length = strlen(content);
		this->package_number = counter;
	}
	~Package(){
		free(content);
	}
};
int Package::counter = 0;
class Router{
public:
	string name;
	string address;
	vector<Router*> connections;
	list<route_info*> routing_table;
	static const int routes_max;
	static const int hops_max;
	int sent = 0;
    Router(string name, string address){
		this->name = name;
		this->address = address;
	}
	void add_router(Router& router){
		if(not router.address.compare("0.0.0.0") or not router.address.compare("127.0.0.0")) throw "Invalid IP";
		connections.push_back(&router);
	}
	int query_route(const string address, const int hop_count){
		if(address==this->address)return 1;
		if(hop_count==0)return 0;
		if(in(this->routing_table,address) + 1)return 1;
		for(auto it = this->connections.begin();it!=this->connections.end();it++){
			if((*it)->query_route(address, hop_count-1)){
                if(in(this->routing_table, address) + 1) return 1;

				if(this->routing_table.size()==routes_max){
					delete this->routing_table.back();
					this->routing_table.pop_back();
				}
				this->routing_table.push_back(new route_info(address,it-this->connections.begin()));
				return 1;
			}
		}
		return 0;
	}
	void send_package(const Package& package){
	
		if(not strcmp(package.content,"")) throw "No content";
		if(package.receiver == "0.0.0.0" or package.receiver == "127.0.0.0") throw "Invalid IP";
        if(not sent%10 and sent){
            printf("Sorting routing table.\n");
            this->routing_table.sort(more_packages);
            printf("Sorting successful.\n");
        }
        sent ++;
        if(package.receiver.compare(this->address)){
            if(in(this->routing_table, package.receiver)+1){
                auto it = this->routing_table.begin();
                int _in = in(this->routing_table,package.receiver);
                advance(it,_in);
                cout << "Route found in routing list. Sending package to " << this->connections.at((*it)->connection_index)->address << endl;
                //printf("Package sent successfully.\n");
                this->connections.at((*it)->connection_index)->send_package(package);
                (*it)->packages_sent++;
                return;
            }
            printf("Route not in routing list. Searching for new route.\n");
            printf("Querying route.\n");
            if(query_route(package.receiver, hops_max)){
                auto it = this->routing_table.begin();
                advance(it,in(this->routing_table,package.receiver));
                printf("Route found. Sending package to %s.\n", this->connections.at((*it)->connection_index)->address.c_str());
                printf("Package sent successfully.\n");
                this->connections.at((*it)->connection_index)->send_package(package);
                (*it)->packages_sent++;
                return;
            }
            printf("Route not found.\n");
            sent --;
            delete &package;
            return;

        }
        printf("package received successfully.\n");
        delete &package;
    }
    ~Router() {
        for(auto i = routing_table.begin(); i != routing_table.end(); i ++) {
            delete *i;
        }
    }
};
const int Router::routes_max = 10;
const int Router::hops_max = 15;
main(){
    string input;
    vector<string> split_line;
    vector<Router*> routers_all;
    ifstream in("routers.txt");
    if(in.is_open()){
        while(not in.eof()){
            getline(in,input);
            split_line = split_string(input);
            cout << split_line.at(0) << " " << split_line.at(1) << endl;
            routers_all.push_back(new Router(split_line.at(0), split_line.at(1)));
        }
    }
    in.close();
    in.open("network.txt");
    if(in.is_open()){
        while(not in.eof()){
            getline(in,input);
            split_line = split_string(input);
            Router* r1;
            Router* r2;
            for(auto it = routers_all.begin(); it!=routers_all.end();it++){
                if(not (*it)->name.compare(split_line.at(0))){
                    r1 = *it;
                }
                if(not (*it)->name.compare(split_line.at(1))){
                    r2 = *it;
                }
            }
            r1->add_router(*r2);
            r2->add_router(*r1);
        }
    }
    in.close();
    in.open("packages.txt");
    if(in.is_open()){
        while(not in.eof()){
            getline(in,input);
            split_line = split_string(input);
            split_line.at(2) = remove_quote(split_line.at(2));
            try{
                for(auto it = routers_all.begin(); it!=routers_all.end(); it++){
                    if(not (*it)->address.compare(split_line.at(0))) {
                        char* temp = (char*) malloc(split_line.at(2).length() + 1);
                        strcpy(temp, split_line.at(2).c_str());
                        (*it)->send_package(*new Package(temp,split_line.at(0),split_line.at(1)));
                    }
                }
            }
            catch(string s){
                cout << s << endl;
            }

        }
    }
    in.close();
    for(auto it = routers_all.begin();routers_all.size();){
        delete *routers_all.begin();
        routers_all.erase(routers_all.begin());
    }
    return 0;
}
vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
            return x == y and x == ' ';
            });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);
    int j = 2;
    while (pos != string::npos and j--) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, input_string.length()));

    return splits;
}
