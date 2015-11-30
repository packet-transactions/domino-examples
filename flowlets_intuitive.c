#include "hashes.h"

#define NUM_FLOWLETS 8000
#define THRESHOLD    5
#define NUM_HOPS     10

struct Packet {
  int sport;
  int dport;
  int new_hop;
  int arrival;
  int next_hop;
  int id; // array index
};

int last_time [NUM_FLOWLETS] = {0};
int saved_hop [NUM_FLOWLETS] = {0};

void flowlet(struct Packet pkt) {
  // Compute packet id
  pkt.id  = hash2(pkt.sport,
                  pkt.dport)
            % NUM_FLOWLETS;

  if (pkt.arrival -
      last_time[pkt.id] >
      THRESHOLD) {
    // Load balance if we exceeded IPG
    pkt.next_hop = hash3(pkt.sport,
                        pkt.dport,
                        pkt.arrival)
                   % NUM_HOPS;
    // Save load balancing decision
    saved_hop[pkt.id] = pkt.next_hop;
  } else {
    // otherwise, leave it as before
    pkt.next_hop = saved_hop[pkt.id];
  }

  // Update last_time always
  last_time[pkt.id] = pkt.arrival;
}
