#define PBS 2
#define CBS 2

#define PIR 2
#define CIR 1

struct Packet {
  int size;
  int time;
};

int tc = CBS;

void func(struct Packet pkt) {
  if (tc < pkt.size) {
  } else {
    tc = tc - pkt.size;
  }

  tc = tc + CIR * (pkt.time);
  if (tc > CBS) tc = CBS;
}
