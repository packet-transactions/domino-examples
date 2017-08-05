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
};

int array1key[ARRAY_SIZE] = {0};
int array2key[ARRAY_SIZE] = {0};
int array1val[ARRAY_SIZE] = {0};
int array2val[ARRAY_SIZE] = {0};

void func(struct Packet p) {
 // First stage
 p.loc = hash2(p.ikey, p.ikey); // Compute location using hash
 if (array1key[p.loc] == p.ikey) { // if key already exists
   p.key_exists = 1;
 } else if (array1key[p.loc] == 0) { // if it doesn't
   p.key_exists = 0;
   array1key[p.loc] = p.ikey;          // initialize key
 } else {                              // if something else exists
   p.key_exists = 2;
   p.ckey = array1key[p.loc];         // swap
   array1key[p.loc] = p.ikey;
 }

 if (p.key_exists == 1) {
   array1val[p.loc] = array1val[p.loc] + 1; // increment
 } else if (p.key_exists == 0) {
   array1val[p.loc] = 1;              // initialize value
 } else {
   p.cval = array1val[p.loc];
   array1val[p.loc] = 1;              // initialize value
 }

// // Second stage
// p.loc = hash2(p.ckey, p.ckey);             // compute location
// if (array2key[p.loc] == p.ckey) {     // key already exists
//   array2val[p.loc] = array2val[p.loc] + p.cval; // add cval
// } else if (array2key[p.loc] == 0) {  // empty slot
//   array2key[p.loc] = p.ckey;          // init. key
//   array2val[p.loc] = p.cval;          // init. value
// } else if (array2val[p.loc] < p.cval) { // compare
//   p.tmpkey = array2key[p.loc];        // swap
//   p.tmpval = array2val[p.loc];
//   array2key[p.loc] = p.ckey;
//   array2val[p.loc] = p.cval;
//   p.ckey = p.tmpkey;
//   p.cval = p.tmpval;
// }
}
