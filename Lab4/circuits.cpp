#include "circuits.hpp"
#include <iomanip>
#include <ios>

Component::Component(Node* const a, Node* const b, std::string const name):

  terminal_a(a),
  terminal_b(b),
  name(name),
  current(0.0)
{}

Resistance::Resistance(Node* const a, Node* const b, std::string const name, double const r):
  Component::Component(a, b, name),
  resistance(r)
{}

Capacitor::Capacitor(Node* const a, Node* const b, std::string const name, double const c):
  Component::Component(a, b, name),
  capacitance(c),
  internal_charge(0.0)
{}


Battery::Battery(Node* const a, Node* const b, std::string const name, double const v):
  Component::Component(a, b, name),
  voltage(v)
{}

Circuit::Circuit():
  net ()
{}

Circuit::~Circuit()
{
  deallocate();
}

std::string Component::get_name() const {
  return name;
}

void Capacitor::simulate(double const step) {

  double potential_diff = fabs(terminal_a->voltage - terminal_b->voltage);
  Node* highest_potential = nullptr;
  Node* lowest_potential = nullptr;

  if(terminal_a->voltage >= terminal_b->voltage){
    
    highest_potential = terminal_a;
    lowest_potential = terminal_b;
  } else {

    highest_potential = terminal_b;
    lowest_potential = terminal_a;
  }

  double charge_to_move = capacitance * (potential_diff - internal_charge) * step;
  current = capacitance * (potential_diff - internal_charge);

  highest_potential->voltage = highest_potential->voltage - charge_to_move;
  lowest_potential->voltage = lowest_potential->voltage + charge_to_move;
  internal_charge = internal_charge + charge_to_move;
}

void Resistance::simulate(double const step) {

  double potential_diff = fabs(terminal_a->voltage - terminal_b->voltage);
  Node* highest_potential = nullptr;
  Node* lowest_potential = nullptr;

  if(terminal_a->voltage >= terminal_b->voltage){
    
    highest_potential = terminal_a;
    lowest_potential = terminal_b;
  } else {

    highest_potential = terminal_b;
    lowest_potential = terminal_a;
  }
  
  double charge_to_move = (potential_diff/resistance) * step;
  current = potential_diff/resistance;

  highest_potential->voltage = highest_potential->voltage - charge_to_move;
  lowest_potential->voltage = lowest_potential->voltage + charge_to_move;
}

void Battery::simulate(double const) {

  terminal_a->voltage = voltage;  
  terminal_b->voltage = 0;
}

void Component::print(void) const {


  std::cout << std::setw(5) << std::fixed << std::right << std::setprecision(2) << terminal_a->voltage - terminal_b->voltage << std::setw(5) << std::fixed << std::right << std::setprecision(2) << current << " ";
}

void Circuit::simulate(uint64_t simulations, uint64_t lines_to_print, double step){

  int n_components = 0;

  for(Component* component: net) {

    std::cout << std::setw(10) << std::right << component->get_name() << " ";
    ++n_components;
  }
  std::cout << std::endl;

  //for(int i=0; i < n_components; ++i) {
  for(Component* component : net) {

    std::cout << std::setw(5) << std::right << "Volt" << std::setw(5) << std::right << "Curr" << " ";
  }
  std::cout << std::endl;

  for(uint64_t i = 0; i < simulations; ++i) {
    for(Component* component : net) {

      component->simulate(step);

      if(i >= simulations - lines_to_print) {
        component->print();
      }
    }

    if(i >= simulations - lines_to_print) {
      std::cout << std::endl;
    }
  }
}

void Circuit::deallocate() {

  for(Component* component : net) {
  
    delete component;
  }
}








