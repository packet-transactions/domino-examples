#define ARRAY_SIZE 10000000

struct Packet {
  int drop;
  int src;
  int dst;
  int srcport;
  int dstport;
  int ftp_port;
  int array_index;
};

int ftp_data_chan[ARRAY_SIZE] = {0};

void func(struct Packet p) {
  p.array_index = p.src * 1000 + p.dst * 1000 + p.ftp_port; // row indexed 3D array
  if (p.dstport == 21) {
    ftp_data_chan[p.array_index] = 1;
  } else {
    if (p.srcport == 20) {
      p.drop = (ftp_data_chan[p.array_index] == 0);
    }
  }
}
