#define DRAIN_RATE 10
#define ECN_THRESH 20

int counter   = ECN_THRESH;
int last_time = 0;

struct Packet {
  int bytes;
  int time;
  int mark;
};

void func(struct Packet p) {
  // Decrement counter according to drain rate
  counter = counter - (p.time - last_time) * DRAIN_RATE;
  if (counter < 0) counter = 0;

  // Increment counter
  counter += p.bytes;

  // If we are above the ECN_THRESH, mark
  if (counter > ECN_THRESH) p.mark = 1;

  // Store last time
  last_time = p.time;
}
