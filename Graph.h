#ifndef GRAPH_H
#define GRAPH_H
#include "Exceptions.h"
#include <set>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

class Graph
{
    //vertexs_and_edges: a map of vertexes (keys) and all of its edges (value, a set of vertexes)
    std::map<std::string, std::set<std::string>> vertexs_and_edges;



    //RemoveSpaces:Removes all spaces from string
    static void removeSpaces(std::string& str);

    //clearSpaces: recives string and returns new string without the spaces in the beginning and end
    static std::string clearSpaces(const std::string& str);

    //removeFromStart: recives string and returns new string without the spaces in the beginning
    static std::string removeFromStart(const std::string& str);

    //removeFromEnd: recives string and returns new string without the spaces in the end
    static std::string removeFromEnd(const std::string& str);


    //verifGraphName: checks if the graph name is legal
    static void verifyGraphName(const std::string& name);

    //verifyVertexName:Checkes if a name is a valid vertex name
    static void verifyVertexName(const std::string& name);

    //validateInfoAndFix:Checks if info in {} is validate (names and syntax) and deletes all spaces afterwards
    static void validateInfoAndFix(std::string &info);

    //validateNamesOfVertexes:Checkes if the names in a list of vertexes is valid
    static void validateNamesOfVertexes(std::string names);

    //validateNamesOfEdges:Checkes if the names in a list of edges is valid
    static void validateNamesOfEdges(std::string& info);


    //countEdges: return how many edges there are in the graph
    int countEdges() const;
    
    //insertVertexes:Inserts all the vertexes from a list
    void insertVertexes(std::string &info);

    //insertEdges:Inserts all the edges from a list
    void insertEdges(std::string &info);

public:
    Graph()=default;
    Graph(const std::string& name, std::string graph_info="");
    Graph(const Graph &other_graph)=default;
    ~Graph()=default;

    void addVertex(const std::string& vertex);
    void addNewEdge(const std::string& source,const std::string& dest);
    
    Graph& operator=(const Graph& other);
    friend Graph operator+(const Graph& graph1,const Graph& graph2);
    friend Graph operator^(const Graph& graph1,const Graph& graph2);
    friend Graph operator-(const Graph& graph1,const Graph& graph2);
    friend Graph operator!(const Graph& graph);
    friend Graph operator*(const Graph& graph1,const Graph& graph2);
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

    void writeGraphToFile(const std::string& filename) const;
    friend Graph loadGraphFromFile(const std::string& filename);

    std::string graphToString();
    
};

Graph loadGraphFromFile(const std::string& filename);

#endif