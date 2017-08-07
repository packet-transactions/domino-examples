#define PBS 2
#define CBS 2

#define PIR 2
#define CIR 1

struct Packet {
  int size;
  int color;
  int time;
};

int tp = PBS;
int tc = CBS;
int last_time = 0;

void func(struct Packet pkt) {
  if (tp < pkt.size) {
    // exceeds peak rate (PIR) (red)
    pkt.color = 1;
  } else if (tc < pkt.size) {
    // exceeds commitited, but not peak (orange)
    pkt.color = 2;
    tp = tp - pkt.size;
  } else {
    // within both peak and committed rates (green)
    pkt.color = 3;
    tp = tp - pkt.size;
    tc = tc - pkt.size;
  }

  // Refill logic
  tp = tp + PIR * (pkt.time - last_time);
  if (tp > PBS) tp = PBS;

  tc = tc + CIR * (pkt.time - last_time);
  if (tc > CBS) tc = CBS;

  last_time = pkt.time;

}
