// This runs on the ingress pipeline, with the link util (p.link_util)
// lazily synced up to the ingress pipeline.

// Constants
#define NUM_TORS 1000
#define KEEP_ALIVE_THRESH 20

// Data is load balanced using congestion-aware flowlet load balancing
// These are only the fields in the HULA probe packets.
struct Packet {
  int path_util; // path utilization carried by HULA probe
  int link_util; // current link utilization; has to be in packet in Domino
  int dst_tor;   // original probe destination ToR
  int cur_time;  // current time; again has to be in packet in Domino
  int cur_time_sub; // sub KEEP_ALIVE_THRESH from cur_time
  int in_port;   // port on which HULA probe arrived
  int update;    // should update or not?
};

int min_path_util[NUM_TORS] = {0};// min. path util. for each dst TOR from this node
int update_time[NUM_TORS] = {0}; // last time the min_path_util was updated
int best_hop[NUM_TORS] = {0}; // best next hop for each dst TOR

// This is triggered by the arrival of probe packets
void func(struct Packet p) {
  // TODO: Fix compiler
  p.dst_tor = p.dst_tor;

  // Set path utilization to minimum of current path utilization and link util
  if (p.path_util < p.link_util) {
    p.path_util = p.link_util;
  }

  // If path util is less than min_path_util for the dst TOR
  // (or) it's been a while since you updated the min_path_util
  // , then update min_path_util and update_time
  p.cur_time_sub = p.cur_time - KEEP_ALIVE_THRESH;
  if (min_path_util[p.dst_tor] > p.path_util) {
    min_path_util[p.dst_tor] = p.path_util;
    update_time[p.dst_tor] = p.cur_time_sub + KEEP_ALIVE_THRESH;
    p.update = 1;
  } else if (update_time[p.dst_tor] < p.cur_time_sub) {
    min_path_util[p.dst_tor] = p.path_util;
    update_time[p.dst_tor] = p.cur_time_sub + KEEP_ALIVE_THRESH;
    p.update = 1;
  }


  if (p.update) {
    best_hop[p.dst_tor] = p.in_port;
  }

  // set path utilization to whatever is in min_path_util
  // Required to multicast the packet onward.
  p.path_util = min_path_util[p.dst_tor];
}
