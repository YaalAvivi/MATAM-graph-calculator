#include <fstream>
#include <iostream>
#include "Calculator.h"



int main(int argc, char *argv[])
{

    std::string current_input;
    if(argc==1)
    {
        bool input=true;
        Calculator Calc(std::cout);
        while(Calc.isOn() &&input)
        {
            std::cout << "Gcalc> ";
            if(!std::getline(std::cin,current_input))
            {
                input=false;
            }
            else{
                if(current_input[current_input.length()-1]=='\n' || current_input[current_input.length()-1]=='\r')
                {
                    current_input.pop_back();
                }
                try{
                    Calc.reciveInput(current_input);
                }
                catch(Exception &e)
                {
                    std::cout<<e.what()<<std::endl;
                }
                catch (...)
                {
                    std::cerr << "Error: Fatal error occurred, exiting..." <<std::endl;
                    return 0;
                }
            }
        }
    }
    else if(argc==3)
    {
        std::ifstream from(argv[1]);
	    if (!from) {
		    std::cerr << "Error: cannot open file " << argv[1] << std::endl;
		    return 0;
        }
	    std::ofstream to(argv[2]);
	    if (!to) {
		    std::cerr << "Error: cannot open file " << argv[2] << std::endl;
		    return 0;
        }
        Calculator Calc(to);
        while(Calc.isOn() && from.peek()!=EOF)
        {
            std::getline(from,current_input);
            
            if(current_input!="")
            {
                if(current_input[current_input.length()-1]=='\n' || current_input[current_input.length()-1]=='\r')
                {
                    current_input.pop_back();
                }
                try{
                    Calc.reciveInput(current_input);
                }
                catch(Exception &e)
                {
                    to<<e.what()<<std::endl;
                }
                catch (...)
                {
                    std::cerr << "Error: Fatal error occurred, exiting..." <<std::endl;
                    return 0;
                }
            }
        }
    }
    else
    {
        std::cerr <<"Error: Illegal number of files"<<std::endl;
    }
    return 0;
}