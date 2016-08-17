#include "hashes.h"

#define NUM_FLOWS 8000
#define TIME_MIN 1

struct Packet {
  int sport;
  int dport;
  int id;
  int start;
  int length;
  int virtual_time;
};

int last_finish [NUM_FLOWS] = {TIME_MIN};

void stfq(struct Packet pkt) {
  pkt.id  = hash2(pkt.sport,
                  pkt.dport)
            % NUM_FLOWS;

  if ((last_finish[pkt.id] > TIME_MIN) && (pkt.virtual_time < last_finish[pkt.id])) {
    pkt.start = last_finish[pkt.id];
    last_finish[pkt.id] += pkt.length;
  } else {
    pkt.start = pkt.virtual_time;
    last_finish[pkt.id] = pkt.virtual_time + pkt.length;
  }
}
