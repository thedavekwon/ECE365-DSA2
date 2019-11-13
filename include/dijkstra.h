//
// Created by Do Hyung Kwon on 11/5/19.
//

#ifndef SPELLCHECK_DIJKSTRA_H
#define SPELLCHECK_DIJKSTRA_H

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <utility>

#include "../include/hash.h"
#include "../include/functions.h"
#include "../include/heap.h"

class Graph {
private:
    class Vertex {
    public:
        std::list<std::pair<Vertex *, int>> *adj;
        Vertex *prev;
        std::string name;
        int dist;
        bool known;

        Vertex(std::string _name);
    };

    hashTable *vertexMap;
    std::vector<Vertex *> vertices;

    Vertex *getOrCreateVertex(const std::string name);

public:
    Graph(const std::string &graph_file);

    void dijkstra(const std::string start_vertex);

    bool contains(const std::string &start_vertex);

    void print(const std::string &output_file, const std::string &start_vertex);
};


#endif //SPELLCHECK_DIJKSTRA_H
