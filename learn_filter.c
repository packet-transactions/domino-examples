#include "hashes.h"

struct Packet {
  int sport;
  int dport;
  int member;
  int filter_idx;
};

#define NUM_ENTRIES 256

int filter[NUM_ENTRIES] = {0};

void func(struct Packet pkt) {
  pkt.filter_idx = hash2(pkt.sport, pkt.dport) % NUM_ENTRIES;
  pkt.member = (filter[pkt.filter_idx]);

  filter[pkt.filter_idx] = 1;
}
