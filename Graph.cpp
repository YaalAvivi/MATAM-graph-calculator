#include "Graph.h"

Graph::Graph(const std::string& name,std::string graph_info)
{
    verifyGraphName(name);
    if (graph_info != "")
    {
        validateInfoAndFix(graph_info);
        int delim_index=graph_info.find('|');
        std::string info = graph_info.substr(1, delim_index - 1);
        if(info.length()>=1){
            insertVertexes(info);
        }
        info = graph_info.substr(delim_index, graph_info.length() - (info.length() + 2));
        if(info.length()>1){
            insertEdges(info);
        }
    }
}

void Graph::insertVertexes(std::string &info)
{
    std::string curr_name;
    std::stringstream vertexes_list(info);
    while (getline(vertexes_list, curr_name, ','))
    {
        addVertex(clearSpaces(curr_name));
    }
}

void Graph::insertEdges(std::string &info)
{
    std::string curr_pair, curr_source, curr_dest;
    std::stringstream edges_list(info);
    while (getline(edges_list, curr_pair, '>'))
    {
        curr_pair = curr_pair.substr(2);
        curr_source = curr_pair.substr(0, curr_pair.find(','));
        curr_dest = curr_pair.substr(curr_pair.find(',') + 1, curr_pair.length() - (curr_source.length() + 1));
        curr_source=clearSpaces(curr_source);
        curr_dest=clearSpaces(curr_dest);
        addNewEdge(curr_source,curr_dest);
    }
}

void Graph::verifyGraphName(const std::string& name)
{
    if(name.length()==0 || !isalpha(name[0]))
    {
        throw IllegalGraphName(name);
    }
    for(const char& current:name)
    {
        if(!isalnum(current))
        {
            throw IllegalGraphName(name);
        }
    }
}


void Graph::validateInfoAndFix(std::string &info){
    size_t index_of_special_char=info.find('|');
    if(index_of_special_char== std::string::npos) /*add | in currect place*/
    {
        index_of_special_char=info.find('<');
        if(index_of_special_char== std::string::npos)
        {
            info.insert(info.length()-1,"|");
        }
        else
        {
            info.insert(1,"|");
        }
    }
    std::string vertex_names = info.substr(1, info.find('|') - 1);
    validateNamesOfVertexes(clearSpaces(vertex_names));
    std::string edges_info = info.substr(info.find('|')+1, info.length() - (vertex_names.length() + 3));
    validateNamesOfEdges(edges_info);
    removeSpaces(info);
}

void Graph::validateNamesOfVertexes(std::string names)
{
    std::string curr_name;
    std::stringstream vertexes_list(names);
    if(names[names.length()-1]==',')
    {
        throw IllegalEmptyVertexName();
    }
    while (getline(vertexes_list, curr_name, ','))
    {
        verifyVertexName(clearSpaces(curr_name));
    }
}

void Graph::validateNamesOfEdges(std::string& info)
{
    bool in_bracket=false,end_of_bracket=false;
    int open_bracket=0,closing_bracket=0,coma_between=0,length=info.length();
    for(int i=0;i<length;i++)
    {
        if(in_bracket)
        {
            if(info[i]=='<')
            {
                throw IllegalSyntax();
            }
            else if(info[i]=='>')
            {
                closing_bracket=i;
                end_of_bracket=true;
                in_bracket=false;
            }
        }
        else
        {
            switch(info[i]){
            case '<':
                in_bracket=true;
                open_bracket=i;
                coma_between=0;
                break;
            case ' ':
                break;
            case ',':
                    coma_between++;
                    if(coma_between>1)
                    {
                        throw IllegalSyntax();
                    }
                    break;
            default:
                throw IllegalSyntax();
                }
        }
        if(end_of_bracket)
        {
            std::string curr_pair=info.substr(open_bracket+1,closing_bracket-open_bracket-1);
            size_t coma_index=curr_pair.find(',');
            if(coma_index== std::string::npos)
            {
                throw IllegalSyntax();
            }
            std::string curr_name=curr_pair.substr(0,coma_index);
            verifyVertexName(clearSpaces(curr_name));
            curr_name=curr_pair.substr(coma_index+1,curr_pair.length()-coma_index-1);
            verifyVertexName(clearSpaces(curr_name));
            end_of_bracket=false;
            if(info.substr(closing_bracket).find('<')!=std::string::npos 
                        &&info.substr(closing_bracket,info.substr(closing_bracket).find('<')).find(',')==std::string::npos)
                {
                    throw IllegalSyntax();
                }
        }   
    }
    if(in_bracket || coma_between>0)
    {
        throw IllegalSyntax();
    }
}


void Graph::removeSpaces(std::string& str)  
{ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
} 

void Graph::verifyVertexName(const std::string& name)
{
    std::string name_copy=name;
    if(name_copy.length()==0)
    {
        throw IllegalEmptyVertexName();
    }
    int bracket_counter=0,length=name_copy.length();
    for(int i=0;i<length;i++)
    {
        if(!isalnum(name_copy[i]))
        {
            switch(name_copy[i]){
                case '[':
                    bracket_counter++;
                    break;
                case ']':
                    bracket_counter--;
                    if(bracket_counter<0)
                    {
                        throw IllegalVertexName(name);
                    }
                    break;
                case ';':
                    if(bracket_counter<=0)
                    {
                        throw IllegalVertexName(name);
                    }
                break;
                default:
                    throw IllegalVertexName(name);
            }
        }
    }
        if(bracket_counter!=0)
        {
            throw IllegalVertexName(name);
        } 
    }


Graph& Graph::operator=(const Graph& other)
{
    if(this==&other)
    {
        return *this;
    }
    vertexs_and_edges=other.vertexs_and_edges;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Graph &graph)
{
    for (auto const& pair: graph.vertexs_and_edges) {
		os <<  pair.first << std::endl;
	}
    os <<  "$" << std::endl;
    for (auto const& pair: graph.vertexs_and_edges) {
		for(std::string dest:pair.second ){
		    os << pair.first << " "<< dest<<std::endl;;
		}
	}
    return os;
}

Graph operator+(const Graph& graph1,const Graph& graph2)
{
    Graph uni_graph(graph1);
    for (auto const& pair: graph2.vertexs_and_edges) {//add all vertexes of graph2 that isn't in graph1
        if (uni_graph.vertexs_and_edges.count(pair.first) == 0)
        {
            uni_graph.addVertex(pair.first);
        }
    }
    for (auto const& pair: graph2.vertexs_and_edges) {//add all edges from graph2
        for(std::string dest:pair.second )
        {
            uni_graph.vertexs_and_edges[pair.first].insert(dest);
        }
    }
    return uni_graph;
}


Graph operator^(const Graph& graph1,const Graph& graph2)
{
    Graph inter_graph;
    for (auto const& pair: graph2.vertexs_and_edges) {//add all vertexes that are both in graph1 and graph2
        if (graph1.vertexs_and_edges.count(pair.first) != 0)
        {
            inter_graph.addVertex(pair.first);
        }
    }
    for (auto const& pair: inter_graph.vertexs_and_edges)//add all edges that are both in graph1 and graph2
    {
        for(std::string dest: graph1.vertexs_and_edges.at(pair.first))
        {
            if(graph2.vertexs_and_edges.at(pair.first).count(dest)>0)
            {
                inter_graph.vertexs_and_edges[pair.first].insert(dest);
            }
        }
    }
    return inter_graph;
}

Graph operator-(const Graph& graph1,const Graph& graph2)
{
    Graph diff_graph;
    for (auto const& pair: graph1.vertexs_and_edges) {//add all vertexes that are not in graph2
        if (graph2.vertexs_and_edges.count(pair.first) == 0)
        {
            diff_graph.addVertex(pair.first);
        }
    }
    for (auto const& pair: graph1.vertexs_and_edges) {//add all edges that still exsist and are not in graph2
        if(diff_graph.vertexs_and_edges.count(pair.first)>0)
        {
            for(std::string dest:pair.second )
            {
                if(diff_graph.vertexs_and_edges.count(dest)!=0)
                {
                    diff_graph.addNewEdge(pair.first,dest);
                }
            }
        }
    }
    return diff_graph;
    }

Graph operator!(const Graph& graph)
{
    Graph comp_graph;
    for (auto const& pair: graph.vertexs_and_edges) {//add all vertexes
        comp_graph.addVertex(pair.first);
    }
    for (auto const& source: comp_graph.vertexs_and_edges)//add all edges that are not in graph
    {
        for(auto const& dest: comp_graph.vertexs_and_edges)
        {
            if(source.first!=dest.first && graph.vertexs_and_edges.at(source.first).count(dest.first)==0)
            {
                comp_graph.addNewEdge(source.first,dest.first);
            }
        }
    }
    return comp_graph;
}


Graph operator*(const Graph& graph1,const Graph& graph2)
{
    Graph prod_graph;
    for (auto const& pair1: graph1.vertexs_and_edges) {//add all vertexes in the form [v1;u1]
        for (auto const& pair2: graph2.vertexs_and_edges)
        {
            prod_graph.addVertex("["+pair1.first+";"+pair2.first+"]");
        }
    }
    for (auto const& pair1: graph1.vertexs_and_edges) {//add all existing edges
        for(std::string dest1:pair1.second )
        {
            for (auto const& pair2: graph2.vertexs_and_edges)
            {
                for(std::string dest2:pair2.second )
                {
                    prod_graph.addNewEdge("["+pair1.first+";"+pair2.first+"]","["+dest1+";"+dest2+"]");
                }
            }
        }
    }
    return prod_graph;
}


void Graph::writeGraphToFile(const std::string& filename) const
{
    std::ofstream outfile(filename, std::ios_base::binary);
    if(!outfile)
    {
        throw IllegalFile(filename);
    }
    unsigned int num_of_vertexes=vertexs_and_edges.size(),num_of_edges=countEdges();    
    outfile.write((const char*)&num_of_vertexes, sizeof(num_of_vertexes));
    outfile.write((const char*)&num_of_edges, sizeof(num_of_edges));
    for(auto const& pair: vertexs_and_edges)//inserting vertexes
    {
        unsigned int length_of_current_vertex=pair.first.length();
        outfile.write((const char*)&length_of_current_vertex, sizeof(length_of_current_vertex));
        for(unsigned int j=0;j<length_of_current_vertex;j++)
        {
            outfile.write((const char*)&pair.first[j], sizeof(char));
        }
    }
    for(auto const& pair: vertexs_and_edges)//inserting edges
    {
        unsigned int length_of_current_vertex=pair.first.length();
        for(std::string dest:pair.second )
        {
            outfile.write((const char*)&length_of_current_vertex, sizeof(length_of_current_vertex));
            for(unsigned int j=0;j<length_of_current_vertex;j++)
            {
                outfile.write((const char*)&pair.first[j], sizeof(char));
            }
            unsigned int length_of_current_dest=dest.length();
            outfile.write((const char*)&length_of_current_dest, sizeof(length_of_current_dest));
            for(unsigned int j=0;j<length_of_current_dest;j++)
            {
                outfile.write((const char*)&dest[j], sizeof(char));
            }
        }
    }
}

Graph loadGraphFromFile(const std::string& filename)
{
    Graph graph;
    std::ifstream infile(filename, std::ios_base::binary);
    if(!infile)
    {
        throw IllegalFile(filename);
    }
    unsigned int num_of_vertexes=0,num_of_edges=0;
    if(infile.peek() == EOF)
    {
        throw IllegalFile(filename);
    }
    infile.read((char*)&num_of_vertexes, sizeof(num_of_vertexes));
    if(infile.peek() == EOF )
    {
        throw IllegalFile(filename);
    }
    infile.read((char*)&num_of_edges, sizeof(num_of_edges));

    for(unsigned int i=0;i<num_of_vertexes;i++)//insert all vertexes
    {
        unsigned int current_length=0;
        if(infile.peek() == EOF )
        {
            throw IllegalFile(filename);
        }
        infile.read((char*)&current_length, sizeof(current_length));
        std::string current_name="";
        char c;
        for(unsigned int j=0;j<current_length;j++)
        {
            if(infile.peek() == EOF)
            {
                throw IllegalFile(filename);
            }
            infile.read((char*)&c, sizeof(c));
            current_name+=c;
        }
        graph.addVertex(current_name);
    }

    for(unsigned int i=0;i<num_of_edges;i++)//insert all edges
    {
        unsigned int current_length_of_source=0;
        if(infile.peek() == EOF )
        {
            throw IllegalFile(filename);
        }
        infile.read((char*)&current_length_of_source, sizeof(current_length_of_source));
        std::string current_name_of_source="";
        char c;
        for(unsigned int j=0;j<current_length_of_source;j++)
        {
            if(infile.peek() == EOF)
            {
                throw IllegalFile(filename);
            }
            infile.read((char*)&c, sizeof(c));
            current_name_of_source+=c;
        }
        unsigned int current_length_of_dest=0;
        if(infile.peek() == EOF )
        {
            throw IllegalFile(filename);
        }
        infile.read((char*)&current_length_of_dest, sizeof(current_length_of_dest));
        std::string current_name_of_dest="";
        for(unsigned int j=0;j<current_length_of_dest;j++)
        {
            if(infile.peek() == EOF)
            {
                throw IllegalFile(filename);
            }
            infile.read((char*)&c, sizeof(c));
            current_name_of_dest+=c;
        }
        graph.addNewEdge(current_name_of_source,current_name_of_dest);
    }
    if(infile.peek() != EOF)
    {
        throw IllegalFile(filename);
    }
    return graph;
}

void Graph::addVertex(const std::string& vertex)
{
    verifyVertexName(vertex);
    if(vertexs_and_edges.count(vertex)>0)
    {
        throw vertexAlreadyExists(vertex);
    }
    std::set<std::string> new_set;
    vertexs_and_edges.insert(make_pair(vertex, new_set));
}

void Graph::addNewEdge(const std::string& source,const std::string& dest)
{
    std::string source_name=clearSpaces(source),dest_name=clearSpaces(dest);
    verifyVertexName(source_name);
    verifyVertexName(dest_name);
    if(vertexs_and_edges.count(source_name)==0)
    {
        throw beginVertexDoesNotExists(source_name,dest_name);
    }
    if(vertexs_and_edges.count(dest_name)==0)
    {
        throw endVertexDoesNotExists(source_name,dest_name);
    }
    if(vertexs_and_edges[source_name].count(dest_name)>0)
    {
        throw EdgeAlreadyExists(source_name,dest_name);
    }
    if(source_name==dest_name)
    {
        throw LoopEdge(source_name);
    }
    vertexs_and_edges.at(source_name).insert(dest_name);
}

int Graph::countEdges() const
{
    int counter=0;
    for(auto const& pair: vertexs_and_edges)
    {
        counter+=pair.second.size();
    }
    return counter;
}

std::string Graph::clearSpaces(const std::string& str)
{
    return removeFromEnd(removeFromStart(str));
}

std::string Graph::removeFromStart(const std::string& str)
{
	size_t start = str.find_first_not_of(' ');
	return (start == std::string::npos) ? "" : str.substr(start);
}

std::string Graph::removeFromEnd(const std::string& str)
{
	size_t end = str.find_last_not_of(' ');
	return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

std::string Graph::graphToString()
{
    bool vertexes=false,edges_exsist=false;
    std::string str="{";
    for(auto const& pair: vertexs_and_edges)
    {
        vertexes=true;
        str+=pair.first+",";
    }
    if(vertexes)
    {
        str.pop_back();
    }
    str+="|";
    for(auto const& pair: vertexs_and_edges)
    {
        for(std::string dest: pair.second)
        {
            edges_exsist=true;
            str+="<"+pair.first+","+dest+">,";
        }
    }
    if(edges_exsist)
    {
        str.pop_back();
    }
    str+="}";
    return str;
}