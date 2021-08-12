#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

///vtf tva ima shortove v bulev masiv

int n;
int vol;
int generation = 1;

struct obekt {
    int pari = 0;
    int obem = 0;
    obekt(int pari, int obem) : pari(pari), obem(obem) {}
    obekt() {}
};

obekt obekti[10000];

struct jivotno {
    bool genes[10000];
    int fitness = 0;
    jivotno() {}
    jivotno(const jivotno &other) {
        fitness = other.fitness;
        for(int i = 0; i < n; i ++) {
            //if(other.genes[i] != 1 && other.genes[i] != 0) cout << "pederas";
            genes[i] = other.genes[i];
        }
    }
    bool operator < (const jivotno a)const {
        return this->fitness > a.fitness;
    }
    jivotno mutation(int rate) {
        jivotno novo(*this);
        //for(int i = 0; i < n; i ++) cout << novo.genes[i];
        if(rate == 0) rate = 1;
        for(int i = 0; i < rate; ++ i) {
            int a = rand() % n;
            novo.genes[a] = !(genes[a]);
            //if(novo.genes[i] != 1 && novo.genes[i] != 0) cout << "pederas";
        }
        return novo;
    }
    int calcFitness() {
        int fitnes = 0;
        /*int remainingVolume = vol;
        for(int i = 0; i < n && remainingVolume >= obekti[i].obem ;i ++) {
            if(genes[i]) {
                fitnes += obekti[i].pari;
                remainingVolume -= obekti[i].obem;
            }
        }*/
        int curr_vol = 0;
        for(int i = 0; i < n; i ++) {
            if(genes[i] == true) {
                fitnes += obekti[i].pari;
                curr_vol += obekti[i].obem;
            }
            if(curr_vol > vol) {
                    fitnes -= obekti[i].pari; break;}
        }
        //cout << fitnes << " ";
        fitness = fitnes;
        return fitnes;
    }
};

const int GENERATIONS_COUNT = 10000;
const int THINGS_PER_GENERATION = 100;

jivotno jivotni[THINGS_PER_GENERATION];

void firstGeneration() {
    for(int i = 0; i < THINGS_PER_GENERATION; ++ i) {
        for(int j = 0; j < n; j ++) {
            jivotni[i].genes[j] = rand() % 2;
        }
    }
}

void sortByFitness() {
    sort(jivotni, jivotni + THINGS_PER_GENERATION);
}

void calcFitness() {
    for(int i = 0; i < THINGS_PER_GENERATION; ++ i) {
        jivotni[i].calcFitness();
    }
}


void nextGeneration() {
    for(int i = 0; i < THINGS_PER_GENERATION ; i ++) {
        if(i < THINGS_PER_GENERATION / 4) {
            jivotni[i * 2 + THINGS_PER_GENERATION / 4] = jivotni[i].mutation(n / generation / 2);
            jivotni[i * 2 + 1 + THINGS_PER_GENERATION / 4] = jivotni[i].mutation(n / generation / 2);
        }
        else if(i > THINGS_PER_GENERATION / 4 * 3) {
            for(int j = 0; j < n; j ++) {
                jivotni[i].genes[j] = rand() % 2;
            }
        }
    }
    generation ++;
}

int main() {
    srand(42);
    ifstream in("genetichni_knapsack_tests.txt");
    in >> n;
    //cout << n << endl;
    for(int i = 0; i < n; i ++) {
        in >> obekti[i].pari >> obekti[i].obem;
        //cout << obekti[i].pari << obekti[i].obem << endl;
        //cout << obekti[i].pari << obekti[i].obem;
    }
    in >> vol;
    //cout << vol;
    firstGeneration();
    for(int i = 0; i < GENERATIONS_COUNT; i ++) {
        calcFitness();
        sortByFitness();
        //cout << i << ": " << jivotni[0].fitness << endl;
        nextGeneration();
    }
    //calcFitness();
    //sortByFitness();
    cout << endl;
    /*for(int i = 0; i < THINGS_PER_GENERATION; i ++) {
        for(int j = 0; j < n; j ++) {
            cout << jivotni[i].genes[j] << " ";
        }
        //jivotni[i].calcFitness();
        cout << jivotni[i].fitness << endl;
    }*/

    cout << jivotni[0].fitness;
}

/*
5 7

5 1
10 7
3 1
3 3
4 1
*/
