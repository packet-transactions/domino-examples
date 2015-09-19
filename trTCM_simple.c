#define PBS 2
#define CBS 2

#define PIR 2
#define CIR 1

struct Packet {
  int size;
  int f1;
  int f2;
};

int tp = PBS;
int tc = CBS;
int last_time = 0;

void func(struct Packet pkt) {
  if (tp < pkt.size) {
    tp = tp + pkt.f2 > PBS ? PBS : tp + pkt.f2;
    tc = tc + pkt.f1 > PBS ? PBS : tc + pkt.f1;
  } else if (tc < pkt.size) {
    tp = tp - pkt.size + pkt.f2 > PBS ? PBS : tp - pkt.size + pkt.f2;
    tc = tc + pkt.f1 > PBS ? PBS : tc + pkt.f1;
  } else {
    tp = tp - pkt.size + pkt.f2 > PBS ? PBS : tp - pkt.size + pkt.f2;
    tc = tc - pkt.size + pkt.f1 > PBS ? PBS : tc - pkt.size + pkt.f1;
  }
}
