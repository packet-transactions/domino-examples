#ifndef SUCCESS_H
#define SUCCESS_H

#include <cstring>

#include "vops.h"

namespace ANONYMOUS{
  class StateResult;
}
namespace ANONYMOUS{
class StateResult; 
class StateResult{
  public:
  int  result_state_1;
  int  result_state_2;
  StateResult(){}
  static StateResult* create(  int  result_state_1_,   int  result_state_2_);
  ~StateResult(){
  }
  void operator delete(void* p){ free(p); }
};
extern void main__Wrapper(int state_1, int state_2, int pkt_1, int pkt_2, int pkt_3, int pkt_4, int pkt_5);
extern void main__WrapperNospec(int state_1, int state_2, int pkt_1, int pkt_2, int pkt_3, int pkt_4, int pkt_5);
extern void _main(int state_1, int state_2, int pkt_1, int pkt_2, int pkt_3, int pkt_4, int pkt_5);
extern void codelet(int state_1_0, int state_2, int pkt_1, int pkt_2, int pkt_3, int pkt_4, int pkt_5, StateResult*& _out);
extern void atom_template(int state_1_0, int state_2, int pkt_1, int pkt_2, int pkt_3, int pkt_4, int pkt_5, StateResult*& _out);
extern void rel_op(int pkt_1, int constant, int opcode, bool& _out);
}

#endif
