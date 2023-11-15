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
  double current;

  public:
  
  Component(Node* const, Node* const, std::string const); //Done
  virtual ~Component() = default;
  void print(void) const;
  virtual void simulate(double const) = 0;
  std::string get_name() const;
};

class Circuit {

  private:

  
  public:
  Circuit();
  ~Circuit();
  
  std::vector<Component*> net;
  void simulate(uint64_t, uint64_t, double );
  void deallocate();
  //void add_component(Component* const);
};


class Resistance : public Component {

  protected:
  double resistance; 

  public:

  Resistance(Node* const, Node* const, std::string const, double const); // Done
  void simulate(double const) override;
};

class Capacitor : public Component {

  protected:
  double capacitance;
  double internal_charge;

  public:
  Capacitor(Node* const, Node* const, std::string const, double const); // Done
  void simulate(double const) override;
};

class Battery : public Component {

  protected:
  double voltage;

  public:
  Battery(Node* const, Node* const, std::string const, double const); // Done
  void simulate(double const) override;
};















