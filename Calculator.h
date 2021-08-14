#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "Exceptions.h"
#include "Graph.h"
#include <map>
#include <string>
#include <vector>
#include <algorithm>

class Calculator
{
    //graphs: map of names (keys) and graphs (values)
    std::map<std::string,Graph> graphs;
    //function_reserved_names: all the names that are reserved for functions
    std::vector<std::string> function_reserved_names={"print","delete","who","reset","quit","save","load"};
    //os: where to write into
    std::ostream& output;
    //on: if the Calculator is on
    bool on;



    //clearSpaces: recives string and returns new string without the spaces in the beginning and end
    static std::string clearSpaces(const std::string& str);

    //removeFromStart: recives string and returns new string without the spaces in the beginning
    static std::string removeFromStart(const std::string& str);

    //removeFromEnd: recives string and returns new string without the spaces in the end
    static std::string removeFromEnd(const std::string& str);

    //firstOccourenceNonNameChar: returns the location of char in string that is not a letter or a number
    static int firstOccourenceNonNameChar(const std::string& str);

    //checkIfLegalFileName: checks if a given string has no comma (,) and no opening bracket or closing bracket
    static void checkIfLegalFileName(const std::string& file_name);

    //checkLegalInput: checks if the input is valid parentheses wise
    static void checkLegalParentheses(const std::string& reciveInput);

    //findOpenParentheses: finds the first open parentheses that are not related to load()
    static int findOpenParentheses(const std::string& str);

    //findCloseParentheses: finds the closing parentheses that closes the parentheses of the given index
    static int findCloseParentheses(const std::string& str,const int openParenthesesLocation);

    //isNotLoadParentheses: checks if given opening parentheses in index is related to load() or not
    static bool isNotLoadParentheses(const std::string& str,const int index);

    //parenthesesExist: checks if there are still parentheses that are not related to load()
    static bool parenthesesExist(const std::string& str);
    
    //getNameFromString: returns input as name
    static std::string getNameFromString(const std::string& input);

    //replaceString: returns original_str, after to_replace has been inserted from firstIndex to lastIndex
    static std::string replaceString(std::string original_str,const int firstIndex,const int lastIndex,const std::string& to_replace);

    //countNumOfExclamationAndEarse: returns the number of Exclamation marks in the beginning of a given string and earses them (ignores spaces and also earse them)
    static int countNumOfExclamationAndEarse(std::string& str);



    //operateOnGraph: operates on graph_to_operate with given operation and given graph
    static void operateOnGraph(Graph& graph_to_operate,const Graph& graph,const char operation);



    //commandOption: checks if the input is a command option
    static bool commandOption(const std::string& input);
    


    //convertToNoParenthesesAndCalculate: converts the given string to a new string without Parentheses and also calculates that graph that is in input
    std::string convertToNoParenthesesAndCalculate(std::string input);

    //convertToNoParentheses: converts the given string to a new string without Parentheses
    std::string convertToNoParentheses(std::string input);


    //CalculateGraphFromString: recives graphs name and input and returns graph according to input
    Graph CalculateGraphFromString(const std::string name,std::string input);

    //updateGraphFromString: recives graph,graphs name ,input,opeartion and updates graph according to input
    void updateGraphFromString(std::string& input,const std::string name,Graph& graph,char& operation);

    //updateGraphFromCurrentGraphsOrLoad: updates given graph according to input from exsiting graphs in Calculator or loading a new graph
    void updateGraphFromCurrentGraphsOrLoad(std::string& input,const std::string name,Graph& graph,char& operation);

    //loadAndUpdateGraph: loads graph from input and update graph if a graph was loaded succesfully
    void loadAndUpdateGraph(std::string& input,const std::string name,Graph& graph,char& operation);

    //UpdateGraphWithNotSymbol: updates given graph accordin to input, with not symbol operated on the graph
    void UpdateGraphWithNotSymbol(std::string& input,const std::string name,Graph& graph,char& operation);

    

    //checkIfCommand: Checks if given input starts with command and a Parentheses (such as print())
    static bool checkIfCommand(const std::string& input,const std::string& command);

    //tryPrint: Checkes if current input is a print request
    void tryPrint(const std::string& input);

    //tryDelete: Checkes if current input is a delete request
    void tryDelete(const std::string& input);

    //tryWho: Checkes if current input is a who request
    void tryWho(const std::string& input) const;

    //tryReset: Checkes if current input is a reset request
    void tryReset(const std::string& input);

    //trySave: Checkes if current input is a save request
    void trySave(const std::string& input);

    //tryQuit: Checkes if current input is a quit request
    void tryQuit(const std::string& input);



    //print: prints according to the input
    void print(std::string input);

    //deleteGraph: deletes graph by name from current graphs
    void deleteGraph(const std::string& name);

    //who: prints all current graphs
    void who() const;

    //reset: deletes all current graphs
    void reset();

    //quit: quits from calculator by turning 'on' off
    void quit();

    //save: save the given graph (by string) to file 'file_name;
    void save(std::string graph, const std::string& file_name);

    //load: load agraph from file 'file_name;
    Graph load(const std::string& file_name);


    //addGraph: add graph 'name' to Calculator
    void addGraph(const std::string& name,const Graph& graph);

    //reciveInputWithoutEqual: function that cares of input when there is no equal sign
    void reciveInputWithoutEqual(std::string& input);

    public:
    Calculator(std::ostream& os);
    //reciveInput: recives input to Calculator
    void reciveInput(std::string& input);
    //isOn: returns if the Calculator is on
    bool isOn() const;
    ~Calculator()= default;

};

#endif