struct Packet {
  int tcpseq;
};

int count = 0;
int maxseq = 0;

void func(struct Packet p) {
  if (p.tcpseq < maxseq) {
    count = count + 1;
  } else {
    maxseq = p.tcpseq;
  }
}
