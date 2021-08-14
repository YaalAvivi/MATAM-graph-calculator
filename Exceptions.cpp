#include "Exceptions.h"

FilesException::FilesException(const std::string &error_type) : error_string("Error: " + error_type)
{
}
const char *FilesException::what() const noexcept
{
    return error_string.c_str();
}
FilesException::~FilesException() {}

GraphException::GraphException(const std::string &error_type) : error_string("Error: " + error_type)
{
}
const char *GraphException::what() const noexcept
{
    return error_string.c_str();
}
GraphException::~GraphException() {}

InputException::InputException(const std::string& error_type) : error_string("Error: " + error_type)
{
}
const char* InputException::what() const noexcept
{
    return error_string.c_str();
}
InputException::~InputException() {}


vertexAlreadyExists::vertexAlreadyExists(const std::string &vertex) : GraphException("Cannot add vertex " + vertex + " because it's already exists.") {}
beginVertexDoesNotExists::beginVertexDoesNotExists(const std::string &source, const std::string &dest) : GraphException("Cannot add edge <" + source + "," + dest + "> due to missing beginingpoint.") {}
endVertexDoesNotExists::endVertexDoesNotExists(const std::string &source, const std::string &dest) : GraphException("Cannot add edge <" + source + "," + dest + "> due to missing endpoint.") {}
LoopEdge::LoopEdge(const std::string &vertex) : GraphException("Cannot add edge <" + vertex + ", " + vertex + "> due to self loop.") {}
EdgeAlreadyExists::EdgeAlreadyExists(const std::string& source, const std::string& dest) : GraphException("Cannot add edge <" + source + ", " + dest + "> because it's already exists.") {}
IllegalEmptyVertexName::IllegalEmptyVertexName() : GraphException("Empty vertex name is illegal") {}
IllegalVertexName::IllegalVertexName(const std::string& vertex_name) : GraphException("Vertex name '"+vertex_name+"' is illegal") {}
IllegalGraphName::IllegalGraphName(const std::string& graph_name) : GraphException("Graph name '"+graph_name+"' is illegal") {}


IllegalSyntax::IllegalSyntax() : InputException("Unrecognized command"){}
UndefinedVariable::UndefinedVariable(const std::string& name) : InputException("Undefined variable '"+name+"'"){}
UnrecognizedCommand::UnrecognizedCommand(const std::string& input) : InputException("Unrecognized command '"+input+"'"){}
NullPointer::NullPointer() : InputException("Illegal pointer"){}

IllegalFile::IllegalFile(const std::string& file_name) : FilesException("File '"+file_name+"' is invalid"){}