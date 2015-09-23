// Sample every 30th packet in a flow
#define N 30

struct Packet {
  int sample;
};

int count = 0;

void func(struct Packet pkt) {
  if (count == N - 1) {
    pkt.sample = 1;
    count = 0;
  } else {
    pkt.sample = 0;
    count = count + 1;
  }
}
