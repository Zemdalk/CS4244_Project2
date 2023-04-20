#include "CNFConstructor.hpp"
#include "Converter.hpp"

// using ../test/test3.uai and ../test/test3.eivd for Bayesian network and evidence file
const string TEST_FILE = "../test/test3"; 

int main(){
    // Construct a converter to convert .uai format Bayesian 
    // network into inner data structure
    Converter cvt = Converter(TEST_FILE);
    BayesianNetwork *bn = cvt.convert();

    // Contruct the corresponding CNF formula 
    // and save as TEST_FILE.cnf in DIMACS
    std::cout << "-----------CNF-----------\n";
    CNFConstructor cst = CNFConstructor(*bn, TEST_FILE);
    cst.evidence2assignment();
    CNF cnf = cst.construct();
    std::cout << cnf.to_string() << std::endl;
    cnf.saveCnfFile();

    // Save the weight file as TEST_FILE.weight
    std::cout << "-------------------------\n";
    cnf.saveWeightFile();
    std::cout << "CNF formula and weight file have been saved!\n"
              << "Check " << TEST_FILE << ".cnf and " << TEST_FILE
              << ".weight for detail.\n";
}