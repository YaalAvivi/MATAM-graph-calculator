#include "Calculator.h"

Calculator::Calculator(std::ostream& os): output(os), on(true)
{}



bool Calculator::isOn() const
{
    return on;
}


void Calculator::reciveInput(std::string& input)
{
    checkLegalParentheses(input);
    if(commandOption(input))
    {
        reciveInputWithoutEqual(input);
    }
    else
    {
        size_t equal_sign=input.find('=');
        std::string first_part=input.substr(0,equal_sign),second_part=input.substr(equal_sign+1);
        std::string name=getNameFromString(first_part);
        Graph graph(name);
        try{
            second_part=convertToNoParentheses(second_part);
            graph=CalculateGraphFromString(name,second_part);
        }
        catch(IllegalSyntax& e)
        {
            throw UnrecognizedCommand(input);
        }
        addGraph(name,graph);
    }
}

bool Calculator::commandOption(const std::string& input)
{
    size_t equal_sign=input.find('=');
    if(equal_sign==std::string::npos)
    {
        return true;
    }
    else if(checkIfCommand(input,"save")||checkIfCommand(input,"print")||checkIfCommand(input,"delete"))
    {
        return true;
    }
    else{
        return false;
    }
}
bool Calculator::checkIfCommand(const std::string& input,const std::string& command)
{
    std::string input_to_check=clearSpaces(input);
    int command_length=command.length(),input_length=input_to_check.length();
    if(input_length<command_length)
    {
        return false;
    }
    for(int i=0;i<command_length;i++)
    {
        if(input_to_check[i]!=command[i])
        {
            return false;
        }
    }
    std::string copy= input;
    copy=clearSpaces(copy.substr(command_length));
    if(copy.length()!=0 && copy[0]=='(')
    {
        return true;
    }
    return false;
}

std::string Calculator::convertToNoParentheses(std::string input)
{
    while(parenthesesExist(input))
    {
        int openParentheses=findOpenParentheses(input),closeParentheses=findCloseParentheses(input,openParentheses);
        std::string replaceInsideParentheses=convertToNoParenthesesAndCalculate(input.substr(openParentheses+1,closeParentheses-openParentheses-1));
        input=replaceString(input,openParentheses,closeParentheses,replaceInsideParentheses);
    }
    return input;
}

std::string Calculator::convertToNoParenthesesAndCalculate(std::string input)
{
    while(parenthesesExist(input))
    {
        int openParentheses=findOpenParentheses(input),closeParentheses=findCloseParentheses(input,openParentheses);
        std::string replaceInsideParentheses=convertToNoParenthesesAndCalculate(input.substr(openParentheses+1,closeParentheses-openParentheses-1));
        input=replaceString(input,openParentheses,closeParentheses,replaceInsideParentheses);
    }
    return CalculateGraphFromString("g",input).graphToString();
}

bool Calculator::parenthesesExist(const std::string& str)
{
    int length=str.length();
    for(int i=0;i<length;i++)
    {
        if(str[i]=='(')
        {
            if(isNotLoadParentheses(str,i))
            {
                return true;
            }
        }
    }
    return false;
}

bool Calculator::isNotLoadParentheses(const std::string& str,const int index)
{
    if(index==0)
    {
        return true;
    }
    std::string str_to_check=clearSpaces(str.substr(0,index));
    return !(str_to_check.length()>=4 && str_to_check[str_to_check.length()-1]=='d' && 
            str_to_check[str_to_check.length()-2]=='a' && str_to_check[str_to_check.length()-3]=='o' && 
            str_to_check[str_to_check.length()-4]=='l');
}

int Calculator::findOpenParentheses(const std::string& str)
{
    int length=str.length();
    for(int i=0;i<length;i++)
    {
        if(str[i]=='(')
        {
            if(isNotLoadParentheses(str,i))
            {
                return i;
            }
        }
    }
    return -1;
}

int Calculator::findCloseParentheses(const std::string& str,const int openParenthesesLocation)
{
    int length=str.length(),counter=0;
    for(int i=openParenthesesLocation;i<length;i++)
    {
        if(str[i]=='(')
        {
            counter++;
        }
        else if(str[i]==')')
        {
            counter--;
        }
        if(counter==0)
        {
            return i;
        }
    }
    return -1;
}


std::string Calculator::replaceString(std::string original_str,const int firstIndex,const int lastIndex,const std::string& to_replace)
{
    std::string new_str="";
    int original_length=original_str.length(),replace_length=to_replace.length();
    for(int i=0;i<firstIndex;i++)
    {
        new_str+=original_str[i];
    }
    for(int i=0;i<replace_length;i++)
    {
        new_str+=to_replace[i];
    }
    for(int i=lastIndex+1;i<original_length;i++)
    {
        new_str+=original_str[i];
    }
    return new_str;
}




void Calculator::reciveInputWithoutEqual(std::string& input)
{
    std::string new_input=clearSpaces(input);
    if(new_input.length()!=0)
    {
        switch(new_input[0]){
            case ' ':
                break;
            case 'p':
                try{
                    tryPrint(new_input);
                }
                catch(IllegalSyntax& e)
                {
                    throw UnrecognizedCommand(input);
                }
                return;
                break;
            case 'd':
                try{
                    tryDelete(new_input);
                }
                catch(IllegalSyntax& e)
                {
                    throw UnrecognizedCommand(input);
                }
                return;
                break;
            case 'w':
                try{
                    tryWho(new_input);
                }
                catch(IllegalSyntax& e)
                {
                    throw UnrecognizedCommand(input);
                }
                return;
                break;
            case 'r':
                try{
                    tryReset(new_input);
                }
                catch(IllegalSyntax& e)
                {
                    throw UnrecognizedCommand(input);
                }
                return;
                break;
            case 'q':
                try{
                    tryQuit(new_input);
                }
                catch(IllegalSyntax& e)
                {
                    throw UnrecognizedCommand(input);
                }
                return;
                break;
            case 's':
                try{
                    trySave(new_input);
                }
                catch(IllegalSyntax& e)
                {
                    throw UnrecognizedCommand(input);
                }
                return;
                break;
            default:
                throw UnrecognizedCommand(input);
                break;
        }
    }
}

void Calculator::tryPrint(const std::string& input)
{
    if(input.length()<5 || (input[0]!='p' ||input[1]!='r' || input[2]!='i' || input[3]!='n'|| input[4]!='t'))
    {
        throw IllegalSyntax();
    }
    std::string input_to_check=clearSpaces(input.substr(5));
    if(input_to_check.length()==0 || input_to_check[0]!='('||input_to_check[input_to_check.length()-1]!=')')
    {
        throw IllegalSyntax();
    }
    std::string graph_input=input_to_check.substr(1,input_to_check.length()-2);
    graph_input=clearSpaces(graph_input);
    print(graph_input);
}

void Calculator::tryDelete(const std::string& input)
{
    if(input.length()<6 || (input[0]!='d' ||input[1]!='e' || input[2]!='l' || input[3]!='e'|| input[4]!='t'|| input[5]!='e'))
    {
        throw IllegalSyntax();
    }
    std::string input_to_check=clearSpaces(input.substr(6));
    if(input_to_check.length()==0 || input_to_check[0]!='('||input_to_check[input_to_check.length()-1]!=')')
    {
        throw IllegalSyntax();
    }
    std::string name=input_to_check.substr(1,input_to_check.length()-2);
    name=clearSpaces(name);
    deleteGraph(name);
}

void Calculator::tryWho(const std::string& input) const
{
    if(input.length()<3 || (input[0]!='w'||input[1]!='h' || input[2]!='o'))
    {
        throw IllegalSyntax();
    }
    std::string input_to_check=input.substr(3);
    if(input_to_check.find_first_not_of(' ')!=std::string::npos)
    {
        throw IllegalSyntax();
    }
    who();
}

void Calculator::tryReset(const std::string& input)
{
    if(input.length()<5 || (input[0]!='r'||input[1]!='e' || input[2]!='s'|| input[3]!='e'|| input[4]!='t'))
    {
        throw IllegalSyntax();
    }
    std::string input_to_check=input.substr(5);
    if(input_to_check.find_first_not_of(' ')!=std::string::npos)
    {
        throw IllegalSyntax();
    }
    reset();
}

void Calculator::trySave(const std::string& input)
{
    if(input.length()<4 || (input[0]!='s'||input[1]!='a' || input[2]!='v'|| input[3]!='e'))
    {
        throw IllegalSyntax();
    }
    std::string input_to_check=clearSpaces(input.substr(4));
    if(input_to_check.length()==0|| input_to_check[0]!='('||input_to_check[input_to_check.length()-1]!=')')
    {
        throw IllegalSyntax();
    }
    input_to_check=input_to_check.substr(1,input_to_check.length()-2);
    size_t comma_index=input_to_check.find_last_of(',');
    if(comma_index==std::string::npos)
    {
        throw IllegalSyntax();
    }
    save(input_to_check.substr(0,comma_index),clearSpaces(input_to_check.substr(comma_index+1)));
}

void Calculator::tryQuit(const std::string& input)
{
    if(input.length()<4 || (input[0]!='q'||input[1]!='u' || input[2]!='i'|| input[3]!='t'))
    {
        throw IllegalSyntax();
    }
    std::string input_to_check=input.substr(4);
    if(input_to_check.find_first_not_of(' ')!=std::string::npos)
    {
        throw IllegalSyntax();
    }
    quit();
}

void Calculator::quit()
{
    on=false;
}


void Calculator::save(std::string graph, const std::string& file_name)
{
    checkIfLegalFileName(file_name);
    graph=convertToNoParentheses(graph);
    Graph G= CalculateGraphFromString("g",graph);
    G.writeGraphToFile(file_name);
}

std::string Calculator::clearSpaces(const std::string& str)
{
    return removeFromEnd(removeFromStart(str));
}

std::string Calculator::removeFromStart(const std::string& str)
{
	size_t start = str.find_first_not_of(' ');
	return (start == std::string::npos) ? "" : str.substr(start);
}

std::string Calculator::removeFromEnd(const std::string& str)
{
	size_t end = str.find_last_not_of(' ');
	return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

void Calculator::print(std::string input)
{
    input=convertToNoParentheses(input);
    output << CalculateGraphFromString("g",input);
}

void Calculator::deleteGraph(const std::string& name)
{
    if(graphs.count(name)==0)
    {
        throw UndefinedVariable(name);
    }
    else
    {
        graphs.erase(name);
    }
}

void Calculator::who() const
{
    for(auto const& pair: graphs) {
        output << pair.first << std::endl;
    }
}

void Calculator::reset()
{
    graphs.clear();
}

Graph Calculator::load(const std::string& file_name)
{
    checkIfLegalFileName(file_name);
    return loadGraphFromFile(file_name);
}

std::string Calculator::getNameFromString(const std::string& input)
{
    return clearSpaces(input);
}

Graph Calculator::CalculateGraphFromString(const std::string name,std::string input)
{
    input=clearSpaces(input);
    Graph graph(name);
    char current_op='s';
    if(input.length()==0)
    {
        throw IllegalSyntax();
    }
    else{
        while(input.length()>0)
        {
            input=clearSpaces(input);
            if(input[0]=='{')
            {
                updateGraphFromString(input,name,graph,current_op);
            }
            else if( input[0]=='+' || input[0] == '^' || input[0]== '-' || input[0]== '*')
            {
                if(current_op=='+' || current_op=='^' || current_op== '-' || current_op == '*' || current_op=='s')
                {
                    throw IllegalSyntax();
                }
                current_op=input[0];
                input=input.substr(1);
            }
            else if(input[0]=='!')
            {
                UpdateGraphWithNotSymbol(input,name,graph,current_op);
            }
            else
            {
                updateGraphFromCurrentGraphsOrLoad(input,name,graph,current_op);
            }  
        }
    }
    if(current_op!='f')
    {
        throw IllegalSyntax();
    }
    else{
        return graph;
    }
}

void Calculator::UpdateGraphWithNotSymbol(std::string& input,const std::string name,Graph& graph,char& operation)
{
    if(countNumOfExclamationAndEarse(input)%2==0)
    {
        return;
    }
    clearSpaces(input);
    if(input.length()==0||input[0]=='+' || input[0]=='^' || input[0]== '-' || input[0] == '*')
    {
        throw IllegalSyntax();
    }
    Graph new_graph;
    char temp_operation='s';
    if(input[0]=='{')
    {
        updateGraphFromString(input,name,new_graph,temp_operation);
    }
    else
    {
        updateGraphFromCurrentGraphsOrLoad(input,name,new_graph,temp_operation);
    }
    new_graph=!new_graph;
    operateOnGraph(graph,new_graph,operation);
    operation='f';
}


void Calculator::loadAndUpdateGraph(std::string& input,const std::string name,Graph& graph,char& operation)
{
    if(input.length()<4 || (input[1]!='o' || input[2]!='a'|| input[3]!='d'))
    {
        throw IllegalSyntax();
    }
    std::string new_input=clearSpaces(input.substr(4));
    size_t close_bracket_index=new_input.find(')');
    if(new_input.length()==0|| new_input[0]!='('||close_bracket_index==std::string::npos)
    {
        throw IllegalSyntax();
    }
    new_input=clearSpaces(new_input.substr(1,close_bracket_index-1));
    Graph new_graph=load(new_input);
    operateOnGraph(graph,new_graph,operation);
    operation='f';
    input=input.substr(input.find(')')+1);
}


void Calculator::updateGraphFromString(std::string& input,const std::string name,Graph& graph,char& operation)
{
    size_t close_bracket_index=input.find('}');
    if(close_bracket_index==std::string::npos)
    {
        throw IllegalSyntax();
    }
    Graph new_graph=Graph(name,input.substr(0,close_bracket_index+1));
    operateOnGraph(graph,new_graph,operation);
    operation='f';
    input=input.substr(close_bracket_index+1);
}

void Calculator::updateGraphFromCurrentGraphsOrLoad(std::string& input,const std::string name,Graph& graph,char& operation){
    if(checkIfCommand(input,"load"))
    {
        loadAndUpdateGraph(input,name,graph,operation);
    }
    else{
        std::string graph_name=input.substr(0,firstOccourenceNonNameChar(input));
        if(graphs.count(graph_name)==0)
        {
            throw UndefinedVariable(graph_name);
        }
        else
        {
            Graph new_graph=graphs[graph_name];
            operateOnGraph(graph,new_graph,operation);
            operation='f';
            input=input.substr(firstOccourenceNonNameChar(input));
        }
    }
}

void Calculator::checkIfLegalFileName(const std::string& file_name)
{
    clearSpaces(file_name);
    if(file_name.find(',')!=std::string::npos || file_name.find('(')!=std::string::npos|| file_name.find(')')!=std::string::npos )
    {
        throw IllegalFile(file_name);
    }
}

int Calculator::firstOccourenceNonNameChar(const std::string& str){
    int length=str.length();
    for(int i=0;i<length;i++)
    {
        if(!isalnum(str[i]))
            return i;
    }
    return length;
}

int Calculator::countNumOfExclamationAndEarse(std::string& str)
{
    int counter=0;
    while(str.length()>0)
    {
        str=clearSpaces(str);
        if(str[0]=='!')
        {
            counter++;
        }
        else{
            return counter;
        }
        str=str.substr(1);
    }
    return counter;
}


void Calculator::addGraph(const std::string& name,const Graph& graph)
{
    if(std::find(function_reserved_names.begin(), function_reserved_names.end(), name) != function_reserved_names.end())
    {
        throw IllegalGraphName(name);
    }
    graphs[name]=graph;
}

/*
bool Calculator::checkIfLoad(std::string& input)
{
    if(input.length()<4 || input[0]!='l' || input[1]!='o' || input[2]!='a'|| input[3]!='d')
    {
        return false;
    }
    std::string copy= input;
    copy=clearSpaces(copy.substr(4));
    if(copy.length()!=0 && copy[0]=='(')
    {
        return true;
    }
    return false;
}*/

void Calculator::operateOnGraph(Graph& graph_to_operate,const Graph& graph,const char operation)
{
    switch(operation)
    {
        case 's':
            graph_to_operate=graph;
            break;
        case '+':
            graph_to_operate=graph_to_operate+graph;
            break;
        case '-':
            graph_to_operate=graph_to_operate-graph;
            break;
        case '^':
            graph_to_operate=graph_to_operate^graph;
            break;
        case '*':
            graph_to_operate=graph_to_operate*graph;
            break;
        default:
            throw IllegalSyntax();
    }
}

void Calculator::checkLegalParentheses(const std::string& reciveInput)
{
    int length=reciveInput.length(),counter=0;
    for(int i=0;i<length;i++)
    {
        if(reciveInput[i]=='(')
        {
            counter++;
        }
        else if(reciveInput[i]==')')
        {
            counter--;
        }
        if(counter<0)
        {
            throw UnrecognizedCommand(reciveInput);
        }
    }
    if(counter!=0)
    {
        throw UnrecognizedCommand(reciveInput);
    }
}