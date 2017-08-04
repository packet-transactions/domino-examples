#define FREEZE_TIME 10
#define DELTA1 1
#define DELTA2 2
#define QMAX 5

struct Packet {
  int loss;
  int qlen;
  int now;
  int link_idle;
}

int last_update;
int p_mark;

void func(struct Packet p) {
  if (p.qlen > QMAX) {
    if (p.now - last_update > FREEZE_TIME) {
      p_mark = p_mark + DELTA1;
      last_update = p.now;
    }
  } else if (p.loss) {
    if (p.now - last_update > FREEZE_TIME) {
      p_mark = p_mark + DELTA1;
      last_update = p.now;
    }
  }

  if (p.link_idle) {
    if (p.now - last_update > FREEZE_TIME) {
      p_mark = p_mark + DELTA2;
      last_update = p.now;
    }
  }
}
