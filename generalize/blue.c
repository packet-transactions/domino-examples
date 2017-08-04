#define FREEZE_TIME 10
#define DELTA1 1
#define DELTA2 2
#define QMAX 5

struct Packet {
  int loss;
  int qlen;
  int now;
  int link_idle;
  int cond1;
  int now_plus_free;
};

int last_update;
int p_mark;

void func(struct Packet p) {
  p.now_plus_free = p.now - FREEZE_TIME;
// cond1 and link_idle can be checked for in the match part of the programmable match-action table
//  p.cond1 = (p.qlen > QMAX) || (p.loss);
// Separate transaction when q exceeds QMAX or on packet loss (higher priority?)
//  if (p.cond1) {
  if (p.now_plus_free > last_update) {
     p_mark = p_mark + DELTA1;
     last_update = p.now;
  }

// Separate transaction when link goes idle (lower priority?)
//  if (p.link_idle) {
//    if (p.now - last_update > FREEZE_TIME) {
//      p_mark = p_mark - DELTA2;
//      last_update = p.now;
//    }
//  }
}
