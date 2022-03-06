#include "Call.h"
#include <ostream>    

namespace Complete
{
std::vector<double> Call::C_t0() const{
    int N = get_N();
    int M = get_M();
    // AP_m = -(u_{m+1}+u_{m}) + BP_{m+1} forall m in {0,1,...,M-1}

    // P va contenir toutes les valeurs à l'instant initial pour tout s. 
    std::vector<double> P(N-1);
    // La matrice P est initialisée à partir des conditions terminales
    //(P connu à l'instant T)
    for(int i=0; i< N-1; i++){
        P.at(i) = C_T((i+1)*get_L()/N);
    }
    // u code directement pour (-u_{m+1}-u_{m})
    std::vector<double> u(N-1,0);
    u.at(N-2) = -(get_r()*(N-1) + pow(get_sigma()*(N-1),2))*(get_K() + C_L((M-1)*delta_T()))/4;
    for(int i=M-2; i>=0; i--){
        // P_{m-1} est la solution d'un système linéaire
        P = solve(get_A(), u + get_B()*P);
        // Update de (-u_{m} - u_{m-1}) pour l'étape suivante
        u.at(N-2) = -(get_r()*(N-1) + pow(get_sigma()*(N-1),2))*(C_L((i+1)*delta_T()) + C_L(i*delta_T()))/4;
    }
    return P;
}
} // namespace Complete


namespace Reduced
{
std::vector<double> Call::C_t0() const{
    int N = get_N();
    int M = get_M();
    // CP_{m+1} = -u_{m+1} + P_{m} forall m in {0,1,...,M-1}

    // P_tmp va contenir toutes les valeurs C_tilde(s_tilde, T). 
    std::vector<double> P_tmp(N-1,0);
    // La matrice P_tmp est initialisée à partir des conditions initiale
    //(P_tmp connu à l'instant 0)
    for(int i=0; i< N-1; i++){
        P_tmp.at(i) = C_ttilde0(stilde((double)(i+1)*get_L()/N, get_T()));
    }
    // Initialisation du vecteur u
    std::vector<double> u(N-1,0);
    u.at(N-2) = (pow(get_sigma(),2)*delta_T())/(2*pow(delta_stilde(),2))*get_K()*exp(2*get_r()*delta_T());
    for(int m=1; m < M; m++) {
        P_tmp = solve(get_C(), P_tmp + u);
        // Update de u_{m+1}  pour l'étape suivante
        u.at(N-2) = (pow(get_sigma(),2)*delta_T())/(2*pow(delta_stilde(),2))*get_K()*exp(2*get_r()*delta_T()*(m+1));
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
