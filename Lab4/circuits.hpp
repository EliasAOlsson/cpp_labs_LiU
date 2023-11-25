// TODO: Complementary work needed, include header guards, all includes
// should be inside the guards.  
//
// Solution: Added header guard. For some reason, this wasn't added from the begining and was forgoten afterwards.

// TODO: Complementary work needed: The subclasses own datamembers should
// be private. 
//
// Hint: protected means that anything inheriting from the class will be able
// to access. Are any classes inherited from Battery, Restistor or Capacitor?
//
// Solution: Datamembers for Battery, Resistor and Capacitor are now private instead of protected.

// TODO: Complementary work needed: Circuit should encapsulate its data
// members.
//
// Solution: net is now private and a proper add_component function was added.

// TODO: Complementary work needed: Motivate why deallocation() should be
// public or make it private.
//
// Solution: deallocate() was made private

// Comment: The great benefit of having a Circuit class is that it can take
// ownership of an single circuit which can then be modified and simulated
// independently. To take advantage of this the Circuit should also have
// its own independent connections.
//
// Taking ownership implies responsibility for destruction. The proper c++
// way of doing this is not covered in this course so, in your case, it would
// be acceptable to write a comment in the header that
//
// void add_component(Component* const);
//
// will transfer ownership of the component to the Circuit object.
//
// If you want to learn the correct way of doing it in c++ I encourage you to
// read about std::unique_ptr ( and related rabbit holes ).

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
