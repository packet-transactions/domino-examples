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

int array2key[ARRAY_SIZE] = {0};
int array2val[ARRAY_SIZE] = {0};

// Runs only if p.terminate is not set
void func(struct Packet p) {
 // Second stage
 p.loc = hash2(p.ckey, p.ckey);             // compute location
 if (array2key[p.loc] == p.ckey) {     // key already exists
   array2val[p.loc] = array2val[p.loc] + p.cval; // add cval
   p.terminate = 1;
 } else {
   if (array2key[p.loc] == 0) {  // empty slot
     array2key[p.loc] = p.ckey;          // init. key
     array2val[p.loc] = p.cval;          // init. value
     p.terminate = 1;
   } else {
     if (array2val[p.loc] < p.cval) { // compare
       p.tmpkey = array2key[p.loc];        // swap
       p.tmpval = array2val[p.loc];
       array2key[p.loc] = p.ckey;
       array2val[p.loc] = p.cval;
       p.ckey = p.tmpkey;
       p.cval = p.tmpval;
     }
   }
 }
}
