#ifndef CIRCUITS_H
#define CIRCUITS_H

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>

struct Node {
  double voltage;
};

class Component {

  protected:

  Node* const terminal_a;
  Node* const terminal_b;
  std::string const name;

  public:
  virtual ~Component() = default;
  virtual void simulate(double const) = 0;
  virtual double get_current() const = 0;  //Get current and get voltage added as functions 
  
  double get_voltage() const;
  Component(Node* const, Node* const, std::string const); //Done
  void print(void) const;
  std::string get_name() const;
};

class Circuit {

  private:
  void deallocate();
  std::vector<Component*> net; //Now private

  public:
  Circuit();
  ~Circuit();
  
  void simulate(uint64_t, uint64_t, double );
  void add_component(Component*); // Now there is a proper add_component function, as net is now private.
};


class Resistance : public Component {

  private:
  double resistance; 

  public:

  Resistance(Node* const, Node* const, std::string const, double const); // Done
  void simulate(double const) override;
  double get_current() const override;

};

class Capacitor : public Component {

  private:
  double capacitance;
  double internal_charge;

  public:
  Capacitor(Node* const, Node* const, std::string const, double const); // Done
  void simulate(double const) override;
  double get_current() const override;

};

class Battery : public Component {

  private:
  double voltage;

  public:
  Battery(Node* const, Node* const, std::string const, double const); // Done
  void simulate(double const) override;
  double get_current() const override;

};

#endif
