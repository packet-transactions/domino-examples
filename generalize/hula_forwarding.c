// This runs on the ingress pipeline,
// with the link util (p.link_util)
// lazily synced up to the ingress pipeline.

// Constants
#define NUM_TORS     1000
#define NUM_FLOWLETS 1000
#define FLOWLET_TOUT 1000

// Data is load balanced using congestion-aware flowlet load balancing
struct Packet {
  int meta_data_dst_tor;   // destination ToR for this packet
  int meta_data_nxt_hop;   // next hop for this packet
  int cur_time;  // current time; again has to be in packet in Domino
  int flow_hash;    // should update or not?
  int new_flowlet;  // detected a new flowlet
  int tmp;          // temporary variable for holding best_hop (AGAIN our compiler doesn't work)
};

int best_hop[NUM_TORS] = {0}; // best next hop for each dst TOR
int flowlet_time[NUM_FLOWLETS] = {0}; // last time for each flowlet
int flowlet_hop[NUM_FLOWLETS] = {0}; // next hop for each flowlet, update on new flowlet

// This is triggered by the arrival of data packets
void func(struct Packet p) {
  // TODO: compiler bug
  p.flow_hash = p.flow_hash;
  p.meta_data_dst_tor = p.meta_data_dst_tor;

  if (p.cur_time - flowlet_time[p.flow_hash] > FLOWLET_TOUT) {
    p.tmp = best_hop[p.meta_data_dst_tor];
    flowlet_hop[p.flow_hash] = p.tmp;
  }

  p.meta_data_nxt_hop = flowlet_hop[p.flow_hash];
  flowlet_time[p.flow_hash] = p.cur_time;
}
