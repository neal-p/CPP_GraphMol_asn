#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <memory>
#include <queue>

#include "attribute.h"


enum Colors { White, Gray, Black };

class GraphBase{


public:
    // Tie an attribute name to an attribute for
    // vertices
    // edges
    std::unordered_map<std::string, std::vector<Attribute*>> v_attr_;

    // Keep track of vertices
    int n_vertices_;
    
    // keep track of edges with adjacency list
    bool directed_;
    int n_edges_;

    GraphBase(int n_vertices, std::vector<std::pair<int, int>> edges, bool directed=false) : 
        n_vertices_(n_vertices), 
        n_edges_(edges.size()),
        directed_(directed){}


    virtual std::vector<int> getNeighbors(int v) = 0;


    template <typename T>
    void addVertexAttributes(const std::string& name, std::vector<T> values){

        if (values.size() != n_vertices_){
            throw std::runtime_error("number of provided attribute values must match number of vertices");
        }

        std::vector<Attribute*> attrs;
        v_attr_[name] = attrs;

        for (auto val : values){
            v_attr_[name].push_back(new AttributeValue<T>(val));
        }
    }

    template <typename T>
    void setVertexAttribute(const std::string& name, int v, T value){

        auto it = v_attr_.find(name);
        if (it == v_attr_.end()){
            throw std::runtime_error("Attribute not found!");
        }

        dynamic_cast<AttributeValue<T>*>(it->second.at(v))->value = value;
    }


    template <typename T>
    T getVertexAttribute(const std::string& name, int v) const {

        auto it = v_attr_.find(name);
        if (it == v_attr_.end()){
            throw std::runtime_error("Attribute not found!");
        }

        // This got a bit complicated, basically here we are
        //    1. it->second  getting the value from the attribute found in v_attr_
        //    2. it->.at(v) that value is a vector, so retrieving the vth value
        //    3. converting that from an Attribute pointer to an AttributeValue<T> pointer with dynamic cast
        //    4. returning the value stored in the AttributeValue
        return dynamic_cast<AttributeValue<T>*>(it->second.at(v))->value;
    }

    template <typename T>
    std::vector<T> getVertexAttributes(const std::string& name) const {

        auto it = v_attr_.find(name);
        if (it == v_attr_.end()){
            throw std::runtime_error("Attribute not found!");
        }

        // This got a bit complicated, basically here we are
        //    1. it->second  getting the value from the attribute found in v_attr_
        //    2. it->.at(v) that value is a vector, so retrieving the vth value
        //    3. converting that from an Attribute pointer to an AttributeValue<T> pointer with dynamic cast
        //    4. returning the value stored in the AttributeValue

        std::vector<T> attrs;
        for (auto a : it->second){
            attrs.push_back(dynamic_cast<AttributeValue<T>*>(a)->value);
        }
        return attrs;
    }


    void printVertices() const {
        for (int v=0; v < n_vertices_; v++){
            std::cout << "Vertex: " << v << std::endl;
        }
    }

    void printVertices(const std::string& attr) const {

        auto it = v_attr_.find(attr);
        if (it == v_attr_.end()){
            throw std::runtime_error("Attribute does not exist!");
        }

        for (int v=0; v < n_vertices_; v++){
            std::cout << "Vertex: " << v << " " << attr << ": ";
            it->second[v]->print();
            std::cout << std::endl;
        }
    }

    void printVertices(const std::vector<std::string> attrs) const {

        for (int v=0; v < n_vertices_; v++){
            std::cout << "Vertex: " << v << " ";

            for (auto attr : attrs){
                auto it = v_attr_.find(attr);
                if (it == v_attr_.end()){
                    throw std::runtime_error("Attribute does not exist!");
                }

                std::cout << attr << ": ";
                it->second[v]->print();
                std::cout << " ";
            }

            std::cout << std::endl;
       }
    }

    std::vector<int> BFS(int x){
        // Set initial properties
        std::vector<Colors> colors(n_vertices_, Colors::White);
        std::vector<int> distances(n_vertices_, n_vertices_+1);
        std::vector<int> pis(n_vertices_, -1);
        addVertexAttributes("_color", colors);
        addVertexAttributes("_distance", distances);
        addVertexAttributes("_pi", pis);

        setVertexAttribute("_color", x, Gray);
        setVertexAttribute("_distance", x, 0);
        setVertexAttribute("_pi", x, -1);

        // Enqueue our start position
        std::queue<int> Q;
        Q.push(x);

        // Start traversal
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (auto v : getNeighbors(u)){
                Colors curr_color = getVertexAttribute<Colors>("_color", v);
                if (curr_color == White){
                    setVertexAttribute("_color", v, Gray);
                    setVertexAttribute("_distance", v, getVertexAttribute<int>("_distance", u) + 1);
                    setVertexAttribute("_pi", v, u);
                    Q.push(v);
                }
            }
            setVertexAttribute("_color", u, Black);
        }

        std::vector<int> accessible_vertices;
        for (int v=0; v < n_vertices_; v++){
            Colors curr_color = getVertexAttribute<Colors>("_color", v);
            if (curr_color == Black){
                accessible_vertices.push_back(v);
            }
        }
        return accessible_vertices;
    }

    std::vector<std::vector<int>> getDistanceMatrix(){
        // Initalize distance matrix
        // and for each vertex, calcuate distances
        // to each other vertex
        std::vector<std::vector<int>> distmat;
        for (int v=0; v < n_vertices_; v++){
            BFS(v);  // sets the distance to the query vertex in the "distance" vertex attribute
            distmat.push_back(getVertexAttributes<int>("_distance"));
        }
        return distmat;
    }
};


