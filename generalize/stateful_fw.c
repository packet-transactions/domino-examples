#define ARRAY_SIZE 1000000
#define VALID_IP 10234

struct Packet {
  int drop;
  int src;
  int dst;
  int array_index;
};

int established[ARRAY_SIZE] = {0};

void func(struct Packet p) {
  p.array_index = p.src * 1000 + p.dst; // row indexed 2D array
  if (p.src == VALID_IP) {
    established[p.array_index] = 1;
  } else {
    if (p.dst == VALID_IP) {
      p.drop = (established[p.array_index] == 0);
    }
  }
}
