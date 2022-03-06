#include "Matrix.h"
#include "Payoff.h"
#include "Call.h"
#include "Put.h"
#include <iostream>
#include <fstream>
#include<thread>
#include<chrono>

// Global variables
int N=1000;
int M=1000;

void todo()
{
    //**************************************************************************************
    //               SOLUTION OF BLACK-SCOLES EQUATION (COMPLETE FORM)
    //**************************************************************************************
    
    {
    // A call option with the default values given in the subject, expect N and M that 
    // vary to test the effectiveness of std::thread
    Complete::Call call_c(100, 0.1, 0.1, 1, 300, N, M);

    // A put option with the default values given in the subject, expect N and M that 
    // vary to test the effectiveness of std::thread
    Complete::Put put_c(100, 0.1, 0.1, 1, 300, N, M);

    //**************************************************************************************
    //              Create a txt file to store the results of regular asset price s
    //**************************************************************************************

    /*  std::cout << "---------Regular discretization of the s interval:---------" << std::endl;
    std::vector<double> s_regulars = call_c.s_regular_values();
    std::ofstream s1_out("../Vectors_results/s_regular_values.txt");
    for(int i=0; i< N-1; i++)
        {
            // std::cout << s_regulars.at(i) << std::endl;
            s1_out << s_regulars.at(i) << std::endl;
        }
    s1_out.close(); */

    //**************************************************************************************
    //              Create txt files to store the results of complete call and put
    //**************************************************************************************
    
     try 
    {
        // Complete call
        std::cout << "---------Complete put content:---------" << std::endl;
        std::vector<double> put_result = put_c.C_t0();
        std::ofstream put_out("../Vectors_results/put_complete.txt");
        for(int i=0; i<N-1; i++)
        {
            std::cout << put_result.at(i) << std::endl;
            //put_out << put_result.at(i) << std::endl;
        }
        put_out.close(); 

        // Complete put
        /* std::cout << "---------Complete call content:---------" << std::endl;
        std::vector<double> call_result = call_c.C_t0();
        std::ofstream call_out("../Vectors_results/call_complete.txt");
        for(int i=0; i<N-1; i++)
        {
            std::cout << call_result.at(i) << std::endl;
            call_out << call_result.at(i) << std::endl;
        }
        call_out.close(); */
    }
    catch(const char* s)
    {
        std::cout<< s << std::endl;
    }
    }

    //**************************************************************************************
    //               SOLUTION OF BLACK-SCOLES EQUATION (REDUCED FORM)
    //**************************************************************************************
    
    {
    // A call option with the default values given in the subject, expect N and M that 
    // vary to test the effectiveness of std::thread
    Reduced::Call call_r(100, 0.1, 0.1, 1, 300, N, M);

    // A put option with the default values given in the subject, expect N and M that 
    // vary to test the effectiveness of std::thread
    Reduced::Put put_r(100, 0.1, 0.1, 1, 300, N, M);

    //**************************************************************************************
    //              Create a txt file to store the results of non-regular asset price s
    //**************************************************************************************

    /* std::cout << "---------Non-regular discretization of the s interval:---------" << std::endl;
    std::vector<double> s_not_regulars = call_r.s_not_regular_values();
    std::ofstream s2_out("../Vectors_results/s_not_regular_values.txt");
    for(int i=0; i< N-1; i++)
        {
            // std::cout << s_not_regulars.at(i) << std::endl;
            s2_out << s_not_regulars.at(i) << std::endl;
        }
    s2_out.close(); */

    //**************************************************************************************
    //              Create txt files to store the results of reduced call and put
    //**************************************************************************************

    /* try 
    {
        // Reduced Put
        std::cout << "---------Reduced put content:---------" << std::endl;
        std::vector<double> put_result = put_r.C_t0();
        std::ofstream put_out("../Vectors_results/put_reduced.txt");
        for(int i=0; i<N-1; i++)
        {
           std::cout << put_result.at(i) << std::endl;
            put_out << put_result.at(i) << std::endl;
        }
        put_out.close(); 
        
    }
    catch(const char* s)
    {
        std::cout<< s << std::endl;
    } */

    //**************************************************************************************
    //              Create txt files to store the results of the errors complete/reduced
    //**************************************************************************************

    /* try{
        // Errors values for put options
        std::cout << "---------Absolute errors values for puts option: ---------" << std::endl;
        std::vector<double> put_result_r = put_r.C_t0();
        std::vector<double> put_result_c = put_c.C_t0();
        std::ofstream errors_out("../Vectors_results/put_errors.txt");
        for(int i=0; i<N-1; i++)
        {
            std::cout <<  abs(put_result_r.at(i) - put_result_c.at(i)) << std::endl;
            errors_out << abs(put_result_r.at(i) - put_result_c.at(i)) << std::endl;
        }
        errors_out.close();
    }
    catch(const char* s){
        std::cout<< s << std::endl;
    } */
    } 
}

int main(){

    // -------------------------------- WITHOUT STD::THREAD --------------------------------
    auto start = std::chrono::high_resolution_clock::now();
    todo();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << "-----------------------------------\n";
    std::cout << "Duration of the calculations without a thread: " << duration.count() << "s" << std::endl;   


    // -------------------------------- WITH STD::THREAD --------------------------------
/*     auto start_thread = std::chrono::high_resolution_clock::now();
    std::thread th(todo);
    // Wait for the thread to finish
    th.join();
    auto end_thread = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration_thread = end_thread - start_thread;
    std::cout << "-----------------------------------\n";
    std::cout << "Duration of the calculations with a thread: " << duration_thread.count() << "s" << std::endl;  */   
    
    return 0;
}

