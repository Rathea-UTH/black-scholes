#include "Put.h"
#include <ostream>  

namespace Complete
{
std::vector<double> Put::C_t0() const{
    int N = get_N();
    int M = get_M();
    // AP_m = -u_{m} - u_{m+1} + BP_{m+1} forall m in {0,1,...,M-1}
    // Goal: Get P_0
    std::vector<double> P(N-1);
    // P to initialize with the terminal conditions
    for(int i=0; i< N-1; i++){
        P.at(i) = C_T((i+1)*get_L()/N);
    }
    // u directly codes for (-u_{m+1}-u_{m}), t_n = n*delta(T)
    std::vector<double> u(N-1,0);
    u.at(0) = -(pow(get_sigma(),2) - get_r())*C_s0((M-1)*delta_T())/4 - (pow(get_sigma(),2) - get_r())*get_K()/4;
    for(int i=M-2; i>=0; i--){
        // P_{n-1} is the solution of a linear system
        P = solve(get_A(), u + get_B()*P);
        // Update to compute -u_{n-1} - u_{n}
        u.at(0) = -(pow(get_sigma(),2) - get_r())*C_s0((i+1)*delta_T())/4 -(pow(get_sigma(),2) - get_r())*C_s0(i*delta_T())/4;
    }
    return P;
}
} // namespace Complete


namespace Reduced
{
std::vector<double> Put::C_t0() const{
    int N = get_N();
    int M = get_M();
    // CP_{m+1} = P_{m} - u_{m+1} forall m in {0,1,...,M-1}

    // P_tmp va contenir toutes les valeurs C_tilde(s_tilde, T). 
    std::vector<double> P_tmp(N-1,0);
    // La matrice P_tmp est initialisée à partir des conditions initiale
    //(P_tmp connu à l'instant 0)
    for(int i=0; i< N-1; i++){
        P_tmp.at(i) = C_ttilde0(stilde((double)(i+1)*get_L()/N, get_T()));
    }
    // Initialisation du vecteur u
    std::vector<double> u(N-1,0);
    u.at(0) = (pow(get_sigma(),2)*delta_T())/(2*pow(delta_stilde(),2))*get_K();
    for(int m=1; m < M; m++) {
        P_tmp = solve(get_C(), u + P_tmp);
        // Update de u_{m+1} pour l'étape suivante
        u.at(0) = (pow(get_sigma(),2)*delta_T())/(2*pow(delta_stilde(),2))*get_K();
    }

    // On retourne à C (avec t et s) via la relation entre C et Ctilde
    // Mise en évidence du retour à C au détriment de la performance du code
    std::vector<double> P(N-1,0);
    for(int i=0; i< N-1; i++){
        P.at(i) = exp(-get_r()*ttilde(M))*P_tmp.at(i);
    }
    return P;
}
} // namespace Reduced

