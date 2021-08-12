#include <iostream>
#include <vector>
#include <map>
#include <string>
///2GB ram, 3s

///DOVARSHI TOQ BOKLUK BE, BEBIL!!!!

std::vector<std::vector<int> > graph;
std::map<std::string, int> myMap;

std::string calculateCodes(int start)
{
    if(graph[start].size() == 0) {
        std::string a = "[]";
        myMap[a] += 1;
        return a;
    }
    std::string toReturn = "[";
    for(int i = 0; i < graph[start].size(); i ++){
        toReturn += calculateCodes(graph[start][i]);
    }
    toReturn += "]";
    myMap[toReturn] += 1;
    return toReturn;
}

int main(){
    int n;
    std::cin >> n;
    graph.resize(n);
    for(int i = 1; i < n;i  ++) {
        int u, v;
        std:: cin >> u >> v;
        graph[u].push_back(v);
    }
    calculateCodes(1)
    for(auto map
}
/*
11
1 2
1 3
2 4
2 5
3 6
3 7
4 8
4 9
7 10
7 11
*/

