// TODO: Complementary work needed: Use '{...}' to initalize members
//
// Solution: all members in all constructors are intialized with {} instead
// of ().
//
// TODO 1: All initializations should be done with {...} and not '=' or '()'
//
// I was perhaps unclear on this so if you fix it you can still have
// your bonus. Make this a habit in c++ (including lab5) and it will save
// you time and headaches.
//
// "Solution": Every initialization is now done with {...}. Sorry for the confusion (and thanks for maintaining the bonus).

// Comment: If get_voltage() doesn't return the absolute value you could use 
// the sign of the returned voltage to simplify other functions.
//
// "Solution": Get voltage returns a signed value, useful for knowing which terminal is the one with highest_potential.
//
// Comment 1: Resistance::simulate() could also get rid of the if-statement.

#include "circuits.hpp"
#include <iomanip>

Component::Component(Node* const a, Node* const b, std::string const name):

  terminal_a{a},
  terminal_b{b},
  name{name}
{}

Resistance::Resistance(Node* const a, Node* const b, std::string const name, double const r):
  Component::Component{a, b, name},
  resistance{r}
{}

Capacitor::Capacitor(Node* const a, Node* const b, std::string const name, double const c):
  Component::Component{a, b, name},
  capacitance{c},
  internal_charge{0.0}
{}


Battery::Battery(Node* const a, Node* const b, std::string const name, double const v):
  Component::Component{a, b, name},
  voltage{v}
{}

Circuit::Circuit():
  net{}
{}

Circuit::~Circuit()
{
  deallocate();
}

void Circuit::add_component(Component* component){

  net.push_back(component);
}

std::string Component::get_name() const {
  return name;
}

double Component::get_voltage() const {
  return terminal_a->voltage - terminal_b->voltage;
}

void Capacitor::simulate(double const step) {
  
  double voltage_diff {get_voltage()};
  Node* highest_potential {nullptr};
  Node* lowest_potential {nullptr};
  
  //Get voltage returns t_a-t_b. If the value is negative, t_b is greater than t_a

  if(voltage_diff > 0){
    
    highest_potential = terminal_a;
    lowest_potential = terminal_b;
  } else {

    highest_potential = terminal_b;
    lowest_potential = terminal_a;
  }

  double charge_to_move {capacitance * (fabs(voltage_diff)- internal_charge) * step};

  highest_potential->voltage = highest_potential->voltage - charge_to_move;
  lowest_potential->voltage = lowest_potential->voltage + charge_to_move;
  internal_charge = internal_charge + charge_to_move;
}

double Capacitor::get_current() const {

  return capacitance * (get_voltage()- internal_charge);
}

void Resistance::simulate(double const step) {
  
  double voltage_diff {get_voltage()};
  Node* highest_potential {nullptr};
  Node* lowest_potential {nullptr};

  if(voltage_diff > 0){
    
    highest_potential = terminal_a;
    lowest_potential = terminal_b;
  } else {

    highest_potential = terminal_b;
    lowest_potential = terminal_a;
  }
  
  double charge_to_move {(fabs(voltage_diff)/resistance) * step};

  highest_potential->voltage = highest_potential->voltage - charge_to_move;
  lowest_potential->voltage = lowest_potential->voltage + charge_to_move;
}

double Resistance::get_current() const {

  return get_voltage()/resistance;
}

void Battery::simulate(double const) {

  terminal_a->voltage = voltage;  
  terminal_b->voltage = 0;
}

double Battery::get_current() const {

  return 0;
}

void Component::print(void) const {


  std::cout << std::setw(5) << std::fixed << std::right << std::setprecision(2) << get_voltage();
  
  std::cout << std::setw(5) << std::fixed << std::right << std::setprecision(2) << get_current() << " ";
}

void Circuit::simulate(uint64_t simulations, uint64_t lines_to_print, double step){

  int n_components {0};

  for(Component* component: net) {

    std::cout << std::setw(10) << std::right << component->get_name() << " ";
    ++n_components;
  }
  std::cout << std::endl;

  for(int i {0}; i < n_components; ++i) {

    std::cout << std::setw(5) << std::right << "Volt" << std::setw(5) << std::right << "Curr" << " ";
  }
  std::cout << std::endl;

  for(uint64_t i {0}; i < simulations; ++i) {
    for(Component* component : net) {

      component->simulate(step);

      
      if((i+1) % (simulations/lines_to_print) == 0) {
          component->print();
      }

    }

    if((i+1) % (simulations/lines_to_print) == 0) {
      std::cout << std::endl;
    }
  }
}

void Circuit::deallocate() {

  for(Component* component : net) {
  
    delete component;
  }
}
