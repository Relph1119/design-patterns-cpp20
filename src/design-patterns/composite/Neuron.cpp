//
// Created by HRF on 2023/3/2.
// P95-100
// 神经网络
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Neuron;

template <typename Self>
struct SomeNeurons {
    template<typename T> void connect_to(T &other) {
        for (Neuron & from: *static_cast<Self*>(this)) {
            for (Neuron & to: other) {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }

    virtual Neuron* begin() = 0;
    virtual Neuron* end() = 0;

};

struct Neuron : SomeNeurons<Neuron>{
    vector<Neuron*> in, out;
    unsigned int id;

    Neuron() {
        static int id = 1;
        this->id = id++;
    }

    Neuron * begin() override {
        return this;
    }

    Neuron * end() override {
        return this + 1;
    }
};

struct NeuronLayer : vector<Neuron> {
    NeuronLayer() {
        NeuronLayer(1);
    }

    NeuronLayer(int count) {
        while (count-- > 0) {
            emplace_back(Neuron{});
        }
    }
};

// TODO: 本代码不完整，运行还有问题
int main() {
    Neuron neuron, neuron2;
    NeuronLayer layer, layer2;
    neuron.connect_to(neuron2);
    neuron2.connect_to(layer);
    layer.begin()->connect_to(neuron);
    layer.end()->connect_to(layer2);
    return 0;
}
