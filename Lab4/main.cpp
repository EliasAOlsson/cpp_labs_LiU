#include "circuits.hpp"
#include <vector>
#include <string>
#include <iostream>

int main (int argc, char* argv[]){

  // Command for calling program, Number of simulations, prints, step, voltage of battery

  
  std::vector<std::string> args {argv, argv + argc};
  try {
    if(argc < 5) {

      throw 1;
    }
  } catch (int error){

    std::cout << "Missing arguments." << std::endl;
    return 1;
  }

  int64_t simulations;
  int64_t prints;
  double step;
  double battery; 

  try {

    simulations = std::stoi(args[1]);

    if(simulations < 0) {

      throw 1; 
    }
  } catch (int error) {

    std::cout << "Simulations should be positive." << std::endl;
    return 1;
  } catch (std::invalid_argument) {

    std::cout << "Invalid argument for simulations." << std::endl;
    return 1;
  }
  
  try {

    prints = std::stoi(args[2]);

    if(prints < 0) {

      throw 1; 
    }

    if(prints > simulations) {

      throw 'e';
    }
  } catch (int error) {

    std::cout << "Prints should be positive." << std::endl;
    return 1;
  } catch (std::invalid_argument) {

    std::cout << "Invalid argument for prints." << std::endl;
    return 1;
  } catch (char error) {

    std::cout << "Prints should be less than simulations." << std::endl;
    return 1;
  }

  try {

    step = std::stod(args[3]);

    if(step < 0) {

      throw 1; 
    }
  } catch (int error) {

    std::cout << "Steps should be positive." << std::endl;
    return 1;
  } catch (std::invalid_argument) {

    std::cout << "Invalid argument for steps." << std::endl;
    return 1;
  }

  try {

    battery = std::stod(args[4]);

    if(battery < 0) {

      throw 1; 
    }
  } catch (int error) {

    std::cout << "Battery should be positive." << std::endl;
    return 1;
  } catch (std::invalid_argument) {

    std::cout << "Invalid argument for battery." << std::endl;
    return 1;
  }
  

  {
  Node p, n, z;
  Circuit circuit;

  (circuit.net).push_back(new Resistance(&p, &n, "R1", 50.0));
  (circuit.net).push_back(new Battery(&p, &z, "Bat", battery));
  (circuit.net).push_back(new Resistance(&n, &z, "R2", 50.0));

  circuit.simulate(simulations, prints, step);
  }

  {
  Node p, n;
  Circuit circuit;

  (circuit.net).push_back(new Capacitor(&p, &n, "C1", 0.05));
  (circuit.net).push_back(new Battery(&p, &n, "Bat", battery));
  (circuit.net).push_back(new Resistance(&p, &n, "R2", 50.0));

  circuit.simulate(simulations, prints, step);
  }


  return 0;
}
