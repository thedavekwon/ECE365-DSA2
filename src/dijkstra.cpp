//
// Created by Do Hyung Kwon on 11/5/19.
//

#include "../include/dijkstra.h"

Graph::Graph(const std::string &graph_file) {
    vertexMap = new hashTable(hashTable::primes[0]);
    std::ifstream input(graph_file);
    if (input.is_open()) {
        std::string line;
        while (std::getline(input, line)) {
            auto parsed = split(line);
            Vertex *from, *to;
            from = getOrCreateVertex(parsed[0]);
            to = getOrCreateVertex(parsed[1]);
            from->adj->push_back({to, stoi(parsed[2])});
        }
    }
}

Graph::Vertex *Graph::getOrCreateVertex(const std::string name) {
    Vertex *v;
    if (vertexMap->contains(name)) {
        v = static_cast<Vertex *>(vertexMap->getPointer(name, nullptr));
    } else {
        v = new Graph::Vertex(name);
        vertexMap->insert(name, v);
        vertices.push_back(v);
    }
    return v;
}

void Graph::dijkstra(const std::string start_vertex) {
    auto* s = static_cast<Vertex *>(vertexMap->getPointer(start_vertex));
    for (auto v : vertices) {
        v->known = false;
        v->dist = std::numeric_limits<int>::max();
    }
    s->dist = 0;
    heap unknown_vertices(vertices.size());
    for (auto v : vertices) {

        unknown_vertices.insert(v->name, v->dist, v);
    }

    while (!unknown_vertices.isempty()) {
        Vertex* v;
        unknown_vertices.deleteMin(nullptr, nullptr, &v);
        v-> known = true;
        for (auto it = v->adj->begin(); it != v->adj->end(); it++) {
            if (it->first->known) continue;
            int cost = it->second;
            if (DEBUG) std::cout << "from: " << it->first->dist << " to: " << v->dist + cost << std::endl;
            if (v->dist + cost < it->first->dist) {
                if (unknown_vertices.setKey(it->first->name, v->dist + cost) != 0) {
                    std::cout << it->first->name << " " << v->dist + cost << "failed" << std::endl;
                }
                it->first->dist = v->dist + cost;
                it->first->prev = v;
            }
        }
    }
}

bool Graph::contains(const std::string &start_vertex) {
    return vertexMap->contains(start_vertex);
}

void Graph::print(const std::string &output_file, const std::string &start_vertex) {
    std::ofstream output(output_file);
    for (auto v : vertices) {
        int dist = v->dist;
        output << v->name << ": ";
        std::vector<std::string> path;
        path.push_back(v->name);
        while (v->prev != nullptr) {
            path.push_back(v->prev->name);
            v = v->prev;
        }
        if (v->name == start_vertex) {
            output << dist << " [";
            for (int i = path.size() - 1; i >= 0; i--) {
                output << path[i];
                if (i) output << ", ";
            }
            output << "]" << std::endl;
        } else {
            output << "NO PATH" << std::endl;
        }
    }
}

Graph::Vertex::Vertex(std::string _name): name(_name) {
    adj = new std::list<std::pair<Vertex*, int>>();
    known = false;
    prev = nullptr;
    dist = 0;
}
