#include "hashes.h"
#define ARRAY_SIZE 1000000

struct Packet {
  int loc;    // location in array
  int tmpkey; // temporary variable for holding key
  int tmpval; // temporary variable for holding value
  int ckey;   // current key
  int cval;   // current val
  int terminate; // don't run second and subsequent stages
};

// Assume
// For keys that don't exist: key and value are both 0,
// For keys that do exist: key and value are both non-zero
int array2key[ARRAY_SIZE] = {0};
int array2val[ARRAY_SIZE] = {0};

// Runs only if p.terminate is not set
void func(struct Packet p) {
 // Second stage
 p.loc = hash2(p.ckey, p.ckey);             // compute location
 if (array2key[p.loc] == p.ckey) {     // key already exists
   array2val[p.loc] = array2val[p.loc] + p.cval; // add cval
   p.terminate = 1;
 } else if (array2val[p.loc] < p.cval) { // Assume array2val[p.loc] == 0 => key doesn't exist
   p.tmpkey = array2key[p.loc];        // swap
   p.tmpval = array2val[p.loc];
   array2key[p.loc] = p.ckey;
   array2val[p.loc] = p.cval;
   p.ckey = p.tmpkey; // these assignments are spurious if terminate is set
   p.cval = p.tmpval;
   p.terminate = (array2val[p.loc] == 0);
 }
}
