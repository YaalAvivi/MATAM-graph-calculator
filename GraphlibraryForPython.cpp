#include "GraphlibraryForPython.h"


Graph* create()
{
    return new Graph("g");
}

void destroy(Graph* graph)
{
    try{
        if(graph!=nullptr)
        {
            delete graph;
        }
    }
    catch(Exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Error: Unknown error has occurred"<<std::endl;
    }
}

Graph* addVertex(Graph* graph,char* vertex)
{
    try{
        if(graph!=nullptr)
        {
            graph->addVertex(vertex);
            return graph;
        }
        else
        {
            throw NullPointer();
        }   
    }
    catch(Exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Error: Unknown error has occurred"<<std::endl;
    }
    return nullptr;
}

Graph* addEdge(Graph* graph,char* source,char* dest)
{
    try{
        if(graph!=nullptr)
        {
            graph->addNewEdge(source,dest);
            return graph;
        }
        else
        {
            throw NullPointer();
        }
    }
    catch(Exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Error: Unknown error has occurred"<<std::endl;
    }
    return nullptr;
}

void disp(Graph* graph)
{
    try{
        if(graph!=nullptr)
        {
            std::cout << *graph ;
        }
        else
        {
            throw NullPointer();
        }
    }
    catch(Exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Error: Unknown error has occurred"<<std::endl;
    }
}

Graph* graphUnion(Graph* graph_in1,Graph* graph_in2,Graph* graph_out)
{
    try{
        if(graph_in1!=nullptr && graph_in2!=nullptr && graph_out!=nullptr)
        {
            *graph_out=(*graph_in1)+(*graph_in2);
            return graph_out;
        }
        else
        {
            throw NullPointer();
        }
    }
    catch(Exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Error: Unknown error has occurred"<<std::endl;
    }
    return nullptr;
}

Graph* graphIntersection(Graph* graph_in1,Graph* graph_in2,Graph* graph_out)
{
    try{
        if(graph_in1!=nullptr && graph_in2!=nullptr && graph_out!=nullptr)
        {
            *graph_out=(*graph_in1)^(*graph_in2);
            return graph_out;
        }
        else
        {
            throw NullPointer();
        }        
    }
    catch(Exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Error: Unknown error has occurred"<<std::endl;
    }
    return nullptr;
}

Graph* graphDifference(Graph* graph_in1,Graph* graph_in2,Graph* graph_out)
{
    try{
        if(graph_in1!=nullptr && graph_in2!=nullptr && graph_out!=nullptr)
        {
            *graph_out=(*graph_in1)-(*graph_in2);
            return graph_out;
        }
        else
        {
            throw NullPointer();
        }        
    }
    catch(Exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Error: Unknown error has occurred"<<std::endl;
    }
    return nullptr;
}

Graph* graphProduct(Graph* graph_in1,Graph* graph_in2,Graph* graph_out)
{
    try{
        if(graph_in1!=nullptr && graph_in2!=nullptr && graph_out!=nullptr)
        {
            *graph_out=(*graph_in1) * (*graph_in2);
            return graph_out;
        }
        else
        {
            throw NullPointer();
        }        
    }
    catch(Exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Error: Unknown error has occurred"<<std::endl;
    }
    return nullptr;
}

Graph* graphComplement(Graph* graph_in,Graph*  graph_out)
{
    try{
        if(graph_in!=nullptr && graph_out!=nullptr)
        {
            *graph_out=!(*graph_in);
            return graph_out;
        }
        else
        {
            throw NullPointer();
        }        
    }
    catch(Exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Error: Unknown error has occurred"<<std::endl;
    }
    return nullptr;
}
