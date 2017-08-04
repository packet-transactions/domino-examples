#define THRESH 1000
#define ARRAY_SIZE 1000000

struct Packet {
  int smtp_mta;
};

int mail_counter[ARRAY_SIZE] = {0};
int mta_dir[ARRAY_SIZE] = {1};

// Policy 6 from SNAP paper
void func(struct Packet p) {
  // TODO: Compiler bug
  p.smtp_mta = p.smtp_mta;

  // Check unknown (1)
  if (mta_dir[p.smtp_mta] == 1) {
    // Set tracked (2)
    mta_dir[p.smtp_mta] = 2;
    mail_counter[p.smtp_mta] = 0;
  }

  // Check tracked (2)
  if (mta_dir[p.smtp_mta] == 2) {
    mail_counter[p.smtp_mta] = mail_counter[p.smtp_mta] + 1;
    if (mail_counter[p.smtp_mta] == THRESH) {
      // Set spammer (3)
      // TODO: The SNAP paper says mta_directory here. I think that's a typo.
      mta_dir[p.smtp_mta] = 3;
    } 
  }

}
