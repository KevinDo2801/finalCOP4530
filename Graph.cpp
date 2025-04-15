#include "Graph.hpp"

// Constants
const unsigned long INFINITY_VAL = (~0UL);

Graph::Graph() {
    // Initialize an empty graph
}

Graph::~Graph() {
    vertices.clear();
}

int Graph::findVertexIndex(const std::string& label) const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i].label == label) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void Graph::removeEdgeFromVertex(int vertexIndex, const std::string& targetLabel) {
    std::vector<Edge>& edges = vertices[vertexIndex].edges;
    for (size_t i = 0; i < edges.size(); ++i) {
        if (edges[i].to == targetLabel) {
            edges.erase(edges.begin() + i);
            break;
        }
    }
}

void Graph::addVertex(std::string label) {
    if (findVertexIndex(label) == -1) {
        Vertex newVertex;
        newVertex.label = label;
        vertices.push_back(newVertex);
    }
}

void Graph::removeVertex(std::string label) {
    int vertexIndex = findVertexIndex(label);
    if (vertexIndex != -1) {
        // Remove all edges pointing to this vertex
        for (Vertex& vertex : vertices) {
            std::vector<Edge>& edges = vertex.edges;
            for (size_t i = 0; i < edges.size(); /* no increment */) {
                if (edges[i].to == label) {
                    edges.erase(edges.begin() + i);
                } else {
                    ++i;
                }
            }
        }
        // Remove the vertex itself
        vertices.erase(vertices.begin() + vertexIndex);
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    if (label1 == label2) return; // No self-loops allowed
    
    int index1 = findVertexIndex(label1);
    int index2 = findVertexIndex(label2);
    
    if (index1 != -1 && index2 != -1) {
        // Add edge from label1 to label2
        vertices[index1].edges.push_back({label2, weight});
        // Add edge from label2 to label1 (undirected graph)
        vertices[index2].edges.push_back({label1, weight});
    }
}

void Graph::removeEdge(std::string label1, std::string label2) {
    int index1 = findVertexIndex(label1);
    int index2 = findVertexIndex(label2);
    
    if (index1 != -1 && index2 != -1) {
        removeEdgeFromVertex(index1, label2);
        removeEdgeFromVertex(index2, label1);
    }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path) {
    int startIndex = findVertexIndex(startLabel);
    int endIndex = findVertexIndex(endLabel);
    
    if (startIndex == -1 || endIndex == -1) {
        return 0;
    }

    size_t n = vertices.size();
    std::vector<unsigned long> distances(n, INFINITY_VAL);
    std::vector<int> previous(n, -1);
    std::vector<bool> visited(n, false);
    
    // Create a mapping from vertex label to index for faster lookups
    std::vector<std::string> labelToIndex(n);
    for (size_t i = 0; i < n; ++i) {
        labelToIndex[i] = vertices[i].label;
    }
    
    distances[startIndex] = 0;

    // Dijkstra's algorithm implementation
    for (size_t i = 0; i < n; ++i) {
        // Find minimum distance vertex
        int u = -1;
        unsigned long minDist = INFINITY_VAL;
        for (size_t j = 0; j < n; ++j) {
            if (!visited[j] && distances[j] < minDist) {
                u = static_cast<int>(j);
                minDist = distances[j];
            }
        }
        
        if (u == -1 || u == endIndex) break;
        
        visited[u] = true;
        
        // Update distances to neighbors
        for (const Edge& edge : vertices[u].edges) {
            // Find the neighbor's index by scanning labelToIndex
            int v = -1;
            for (size_t j = 0; j < n; ++j) {
                if (labelToIndex[j] == edge.to) {
                    v = static_cast<int>(j);
                    break;
                }
            }
            
            if (v != -1 && !visited[v]) {
                unsigned long newDist = distances[u] + edge.weight;
                if (newDist < distances[v]) {
                    distances[v] = newDist;
                    previous[v] = u;
                }
            }
        }
    }
    
    if (distances[endIndex] == INFINITY_VAL) {
        return 0;
    }
    
    // Reconstruct path
    path.clear();
    for (int current = endIndex; current != -1; current = previous[current]) {
        path.push_back(vertices[current].label);
    }
    
    // Manual reverse of path
    for (size_t i = 0; i < path.size() / 2; ++i) {
        std::string temp = path[i];
        path[i] = path[path.size() - 1 - i];
        path[path.size() - 1 - i] = temp;
    }
    
    return distances[endIndex];
} 