#include "hashes.h"
#define ARRAY_SIZE 1000000

struct Packet {
  int loc;    // location in array
  int ikey;   // initial key of incoming packet
  int tmpkey; // temporary variable for holding key
  int tmpval; // temporary variable for holding value
  int ckey;   // current key
  int cval;   // current val
  int key_exists; // variable to track if key exists to give the compiler a leg up
  int terminate; // don't run second and subsequent stages
};

int array1key[ARRAY_SIZE] = {0};
int array1val[ARRAY_SIZE] = {0};

void func(struct Packet p) {
 // First stage
 p.loc = hash2(p.ikey, p.ikey); // Compute location using hash
 if (array1key[p.loc] == p.ikey) { // if key already exists
   p.key_exists = 1;
   p.terminate = 1;
 } else if (array1key[p.loc] == 0) { // if it doesn't
   p.key_exists = 0;
   array1key[p.loc] = p.ikey;          // initialize key
   p.terminate = 1;
 } else {                              // if something else exists
   p.key_exists = 2;
   p.ckey = array1key[p.loc];         // swap
   array1key[p.loc] = p.ikey;
 }

 if (p.key_exists == 1) {
   array1val[p.loc] = array1val[p.loc] + 1; // increment
 } else {
   p.cval = array1val[p.loc];         // Technically this should be set iff
                                      // key_exists == 2, while here we
                                      // do so for both key_exists == 0 and key_exists == 2
                                      // It's OK, because terminate = 1/0 distinguishes the 2
                                      // in downstream stages
   array1val[p.loc] = 1;              // initialize value
 }
}
