#include "circuits.hpp"
#include <vector>
#include <string>
#include <iostream>

int main (int argc, char* argv[]){

  // Command for calling program, Number of simulations, prints, step, voltage of battery

  
  std::vector<std::string> args {argv, argv + argc};

  if(argc < 5) {
    std::cout << "Missing arguments." << std::endl;
    return 1;
  }

  if(argc > 5) {
    std::cout << "Too many arguments." << std::endl;
    return 1;
  }

  int64_t simulations;
  int64_t prints;
  double step;
  double battery; 

  try {

    simulations = std::stoi(args[1]);

  } catch (std::invalid_argument const & e) {

    std::cout << "Invalid argument for simulations." << std::endl;
    return 1;
  }

  if(simulations < 0) {
    std::cout << "Simulations should be positive." << std::endl;
    return 1; 
  }

  
  try {

    prints = std::stoi(args[2]);
  } catch (std::invalid_argument const & e) {

    std::cout << "Invalid argument for prints." << std::endl;
    return 1;
  }

  if(prints < 0) {

    std::cout << "Prints should be positive." << std::endl;
    return 1; 
  }

  if(prints > simulations) {

    std::cout << "Prints should be less than simulations." << std::endl;
    return 1;
  }


  try {

    step = std::stod(args[3]);

  } catch (std::invalid_argument const & e) {

    std::cout << "Invalid argument for steps." << std::endl;
    return 1;
  }

  if(step < 0) {

    std::cout << "Steps should be positive." << std::endl;
    return 1;
  }

  try {

    battery = std::stod(args[4]);

  } catch (std::invalid_argument const & e) {

    std::cout << "Invalid argument for battery." << std::endl;
    return 1;
  }

  if(battery <= 0) {

    std::cout << "Battery should be positive." << std::endl;
    return 1; 
  }
  

  {
    //Example circuit 1
    Node a,b,c,d;
    Circuit circuit;
    circuit.add_component(new Battery(&a, &d, "Bat", battery));
    circuit.add_component(new Resistance(&a, &b, "R1", 6));
    circuit.add_component(new Resistance(&b, &c, "R2", 4));
    circuit.add_component(new Resistance(&c, &d, "R3", 8));
    circuit.add_component(new Resistance(&b, &d, "R4", 12));

    circuit.simulate(simulations, prints, step);
  }
  {
    //Example circuit 2
    Node p,l,r,n;
    Circuit circuit;
    
    circuit.add_component(new Battery(&p, &n, "Bat", battery));
    circuit.add_component(new Resistance(&p, &l, "R1", 150));
    circuit.add_component(new Resistance(&p, &r, "R2", 50));
    circuit.add_component(new Resistance(&r, &l, "R3", 100));
    circuit.add_component(new Resistance(&l, &n, "R4", 300));
    circuit.add_component(new Resistance(&r, &n, "R5", 250));

    circuit.simulate(simulations, prints, step);
  }

  {
    //Example circuit 3
    Node p,l,r,n;
    Circuit circuit;

    circuit.add_component(new Battery(&p, &n, "Bat", battery));
    circuit.add_component(new Resistance(&p, &l, "R1", 150));
    circuit.add_component(new Resistance(&p, &r, "R2", 50));
    circuit.add_component(new Capacitor(&r, &l, "C3", 1));
    circuit.add_component(new Resistance(&l, &n, "R4", 300));
    circuit.add_component(new Capacitor(&r, &n, "C5", 0.75));

    circuit.simulate(simulations, prints, step);
  }

  return 0;
}
