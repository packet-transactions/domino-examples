// TODO: This needs to run on the egress pipeline,
// not the ingress because that's where the link utilization is available.
// Flowlet switching runs on the ingress pipeline, so we need a mechanism
// to occasionally sync up the ingress and egress pipelines. 

// Constants
#define NUM_TORS 1000
#define KEEP_ALIVE_THRESH 20

// Data is load balanced using congestion-aware flowlet load balancing
// These are only the fields in the HULA probe packets.
struct Packet {
  int path_util; // path utilization carried by HULA probe
  int link_util; // current link utilization; has to be in packet in Domino
  int dst_tor;   // original probe destination ToR
  int dst_tor1;  // 3 copies of probe's destination 
  int dst_tor2;  // copy 2
  int dst_tor3;  // copy 3
  int cur_time;  // current time; again has to be in packet in Domino
  int in_port;   // port on which HULA probe arrived
};

int min_path_util[NUM_TORS] = {0};// min. path util. for each dst TOR from this node
int update_time[NUM_TORS] = {0}; // last time the min_path_util was updated
int best_hop[NUM_TORS] = {0}; // best next hop for each dst TOR

void func(struct Packet p) {
  p.dst_tor1 = p.dst_tor;
  p.dst_tor2 = p.dst_tor;
  p.dst_tor3 = p.dst_tor;

  // Set path utilization to minimum of current path utilization and link util
  if (p.path_util < p.link_util) {
    p.path_util = p.link_util;
  }

  // If path util is less than min_path_util for the dst TOR
  // (or) it's been a while since you updated the min_path_util
  // , then update min_path_util and update_time
  // Ask Naga if all the dst_tor ares from the probe header 
  if (p.path_util < min_path_util[p.dst_tor1]) {
    min_path_util[p.dst_tor1] = p.path_util;
    best_hop[p.dst_tor3] = p.in_port;
    update_time[p.dst_tor2] = p.cur_time;
  } else if (p.cur_time - update_time[p.dst_tor2] > KEEP_ALIVE_THRESH) {
    min_path_util[p.dst_tor1] = p.path_util;
    best_hop[p.dst_tor3] = p.in_port;
    update_time[p.dst_tor2] = p.cur_time;
  }

  // set path utilization to whatever is in min_path_util
  // this seems redundant, ask Naga why this is there?
  p.path_util = min_path_util[p.dst_tor1];
}
