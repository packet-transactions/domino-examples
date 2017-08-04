int count = 0;
struct Packet {
  int new;
};

// Detect first packet of a new flow
// Trigger: whatever is the definition of a flow
void func(struct Packet p) {
  if (count == 0) {
    count = 1;
    p.new = 1;
  }
}
