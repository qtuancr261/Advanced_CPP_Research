#include "player.h"

struct Erdos
{
  Erdos(){ whoAmIReally();}
  void testVoice() const{whoAmIReally();}
  virtual void whoAmIReally() const {cout << "I really am Erdos" << endl;}
};
struct Fermat: public Erdos
{
    Fermat() = default;
    virtual void whoAmIReally() const override {cout << "I Really am Fermat" << endl;}
};
int main(int argc, char *argv[])
{
    for (int i{}; i < argc; i++) cout << argv[i] << endl;
    cout << "Let see how the default constructor works: " << endl;
    Erdos erdos;
    Fermat fermat;
    cout << "After then:" << endl;
    erdos.testVoice();
    fermat.testVoice();
    cout << "Be advised: NERVER call virtual functions in a constructor" << endl;
    return 0;
}
