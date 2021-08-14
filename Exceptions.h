#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>

class Exception : public std::exception
{
};

class FilesException : public Exception{
    std::string error_string;
    
public:
    FilesException(const std::string &error_type);
    const char *what() const noexcept;
    virtual ~FilesException();
};

class InputException : public Exception{
    std::string error_string;
    
public:
    InputException(const std::string &error_type);
    const char *what() const noexcept;
    virtual ~InputException();
};

class GraphException : public Exception
{
    std::string error_string;

public:
    GraphException(const std::string &error_type);
    const char *what() const noexcept;
    virtual ~GraphException();
};

class vertexAlreadyExists : public GraphException
{
public:
    vertexAlreadyExists(const std::string &vertex);
};

class beginVertexDoesNotExists : public GraphException
{
public:
    beginVertexDoesNotExists(const std::string &source, const std::string &dest);
};

class endVertexDoesNotExists : public GraphException
{
public:
    endVertexDoesNotExists(const std::string &source, const std::string &dest);
};

class LoopEdge : public GraphException
{
public:
    LoopEdge(const std::string &vertex);
};

class EdgeAlreadyExists : public GraphException
{
public:
    EdgeAlreadyExists(const std::string& source, const std::string& dest);
};


class IllegalEmptyVertexName : public GraphException
{
public:
    IllegalEmptyVertexName();
};

class IllegalVertexName : public GraphException
{
public:
    IllegalVertexName(const std::string& vertex_name);
};

class IllegalGraphName : public GraphException
{
    public:
    IllegalGraphName(const std::string& graph_name);
};

class IllegalSyntax : public InputException
{
    public:
    IllegalSyntax();
};


class UndefinedVariable : public InputException
{
    public:
    UndefinedVariable(const std::string& name);
};

class UnrecognizedCommand : public InputException
{
    public:
    UnrecognizedCommand(const std::string& input);
};


class NullPointer : public InputException
{
    public:
    NullPointer();
};

class IllegalFile : public FilesException
{
    public:
    IllegalFile (const std::string& file_name);
};

#endif