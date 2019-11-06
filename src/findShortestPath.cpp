//
// Created by dodo on 11/5/19.
//

#include "../include/dijkstra.h"

int main() {
    std::string graph_file, start_vertex, output_file;
    std::cout << "Enter name of graph file: ";
    std::cin >> graph_file;
    auto graph = Graph(graph_file);
    do {
        std::cout << "Enter a valid vertex id for the staring vertex: ";
        std::cin >> start_vertex;
    } while (!graph.contains(start_vertex));
    auto start = std::chrono::system_clock::now();

    graph.dijkstra(start_vertex);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Total time (in seconds) to apply Dijkstra's algorithm: ";
    std::cout << elapsed.count() << std::endl;
    std::cout << "Enter name of output file: ";
    std::cin >> output_file;
    graph.print(output_file, start_vertex);
}