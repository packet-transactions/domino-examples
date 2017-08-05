#include "hashes.h"
#define ARRAY_SIZE 1000000

struct Packet {
  int loc;    // location in array
  int ikey;   // initial key of incoming packet
  int tmpkey; // temporary variable for holding key
  int tmpval; // temporary variable for holding value
  int ckey;   // current key
  int cval;   // current val
  int terminate; // don't run second and subsequent stages
};

// Assume
// For keys that don't exist: key and value are both 0,
// For keys that do exist: key and value are both non-zero
int array1key[ARRAY_SIZE] = {0};
int array1val[ARRAY_SIZE] = {0};

// p.terminate determines if the downstream stages run
void func(struct Packet p) {
 // First stage
 p.loc = hash2(p.ikey, p.ikey); // Compute location using hash
 if (array1key[p.loc] == p.ikey) { // if this key already exists
   array1val[p.loc] = array1val[p.loc] + 1; // increment
   p.terminate = 1;
 } else { // if it doesn't
   array1key[p.loc] = p.ikey;         // initialize key
   array1val[p.loc] = 1;              // initialize value
   p.ckey = array1key[p.loc];         // swap (spurious swap if terminate is set)
   p.cval = array1val[p.loc];
   p.terminate = (array1key[p.loc] == 0); // terminate if the location was empty
 }
}
