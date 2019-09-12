#include <iostream>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

struct Connection {
    int to;
    double weight;
    Connection(int to, double weight) : to(to), weight(weight) {}
};

struct Neuron {
    vector<Connection> a;
    double b;
    double current_value = 0;
};

struct NeuralNetwork {
    vector<Neuron> *neurons;
    int layers, *layerSizes;
    NeuralNetwork(int layers, int* layerSizes) : layers(layers), layerSizes(layerSizes) {
        neurons = new vector<Neuron>[layers];
        for(int i = 0; i < layers; ++ i) {
            ///neurons[i] -> layer
            for(int j = 0; j < layerSizes[i]; ++ j)
            {
                Neuron neuron;
                if(i != 0) {
                    for(int k = 0; k < layerSizes[i - 1]; ++ k) {
                        //Connection conn(k,(double)rand() / (double)(1 << 15));
                        Connection conn(k,1.0);
                        neuron.a.push_back(conn);
                    }
                }
                neurons[i].push_back(neuron);
            }
        }
    }

    double func(double a) {
        return max(a, 0.0);
    }

    void eval(double *input, double *output) {
        ///clear all the neuron values
        for(int i = 0; i < layers; ++ i) {
            for(int j = 0; j < layerSizes[i]; ++ j) {
                neurons[i][j].current_value = 0.0;
            }
        }
        ///load the input
        for(int i = 0; i < layerSizes[0]; ++ i) {
            neurons[0][i].current_value = input[i];
        }
        ///evaluate the answer

        for(int i = 1; i < layers; i ++) {
            for(int j = 0; j < layerSizes[i]; ++ j) {
                neurons[i][j].current_value = 0;
                for(int k = 0; k < neurons[i][j].a.size(); ++ k) {
                    neurons[i][j].current_value += neurons[i - 1][neurons[i][j].a[k].to].current_value * neurons[i][j].a[k].weight;
                }
                neurons[i][j].current_value += neurons[i][j].b;
            }
        }

        for(int i = 0; i < layerSizes[layers - 1]; ++ i) {
            output[i] = neurons[layers - 1][i].current_value;
        }
        return;
    }
};

int a[] = {2,1,1};
NeuralNetwork nn(3, a);
double in[] = {1,1};
double out[1];

int main() {
    srand(time(0));
    nn.eval(in, out);
    cout << out[0];
}
