#include <iostream>
using namespace std;

const int MAX_N = 10000;
int n;
int m;
int graph[MAX_N + 1][MAX_N + 1][2];
int start , end;
int vertexData[MAX_N + 1][3];
/*
    ne raboti!
*/
int main()
{
    cin >> n;
    cin >> m;
    for(int i = 0; i < m; i ++)
    {
        int id1, id2, length, type;
        cin >> id1>> id2>> length>> type;
        graph[id1][id2][0] = length;
        graph[id1][id2][1] = type;
        graph[id2][id1][0] = length;
        graph[id2][id1][1] = type;
        vertexData[id1][0] = -1;
        vertexData[id1][1] = -1;
        vertexData[id2][0] = -1;
        vertexData[id2][1] = -1;
        vertexData[id1][2] = 0;
        vertexData[id2][2] = 0;
    }
    cin >> start >> end;

    vertexData[start][1] = 0;
    vertexData[start][2] = 1;
    bool shouldContinue = true;
    for(int iteration = 1;shouldContinue; iteration ++)
    {
        shouldContinue = false;
        for(int i = 1; i <= n; i ++)
        {
            if(vertexData[i][1] != -1 && vertexData[i][2] == iteration)
            {
                for(int j = 1; j <= n; j ++)
                {
                    if(graph[i][j][0] != 0 && (vertexData[j][1] == -1 || vertexData[j][1] > vertexData[i][1] + graph[i][j][0]))
                    {
                        vertexData[j][1] = vertexData[i][1] + graph[i][j][0] * 2;
                        vertexData[j][2] = iteration + 1;

                        shouldContinue = true;
                    }
                }
            }
        }
    }

    for(int i = 0; i < n; i ++)
    {
        vertexData[i][2] = 0;
    }
    vertexData[start][2] = 1;
    vertexData[start][0] = 0;

    shouldContinue = true;
    for(int iteration = 1;shouldContinue; iteration ++)
    {
        shouldContinue = false;
        for(int i = 1; i <= n; i ++)
        {
            if(vertexData[i][0] != -1 && vertexData[i][2] == iteration)
            {
                for(int j = 1; j <= n; j ++)
                {
                    if(graph[i][j][1] != 2 && graph[i][j][0] != 0 && (vertexData[j][0] == -1 || vertexData[j][0] > vertexData[i][0] + graph[i][j][0]))
                    {
                        vertexData[j][0] = vertexData[i][0] + graph[i][j][0];
                        vertexData[j][2] = iteration + 1;

                        shouldContinue = true;
                    }
                }
            }
        }
    }
    if(vertexData[end][1] > vertexData[end][0])
    {
        cout<<"Rabbit" << endl << vertexData[end][0] << endl;
    }
    else
    {
        cout<<"Tortoise" << endl << vertexData[end][1] << endl;
    }

    int meetingsCount = 0;
    int cellId = end;
    while(cellId != start)
    {
        shouldContinue = true;
        for(int i = 1; i <= n && shouldContinue; i ++)
        {
            if(vertexData[cellId][0] = vertexData[i][0] + graph[i][cellId][0])
            {
                if(vertexData[i][0] == vertexData[i][1])
                {
                    ++meetingsCount;
                }
                cellId = i;
                shouldContinue = false;
            }
        }
    }
    cout << meetingsCount;

    return 0;
}
