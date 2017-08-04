#define ARRAY_SIZE 1000000
#define THRESHOLD 1000

// Note that flipping domains and IPs still allows this
// example to work (SNAP-Policy 2)

// Suppose an attacker tries to avoid blocking ac-
// cess to his malicious IP through a specific DNS domain
// by frequently changing the domain name that relates to
// that IP [6]. Detection of this behavior is implemented
// below.

int domain_ip_pair[ARRAY_SIZE] = {0};
int num_of_domains[ARRAY_SIZE] = {0};
int mal_ip_list[ARRAY_SIZE]    = {0};

struct Packet {
  int rdata;
  int qname;
  int dip_index;
};

// Triggered only when srcport = 53 (match guard)
void func(struct Packet dns) {
  // TODO: Compiler bug, need to fix this
  dns.rdata = dns.rdata;

  // row-indexed 2D array implemented as a 1 D array
  dns.dip_index = dns.rdata * 1000 + dns.qname;
  // If this domain name (qname) + IP pair (rdata) has not been seen before
  if (domain_ip_pair[dns.dip_index] == 0) {
    // Increase number of the domains for this IP address (rdata)
    num_of_domains[dns.rdata] = num_of_domains[dns.rdata] + 1;

    // Say that it has been seen now
    domain_ip_pair[dns.dip_index] = 1; 

    // Flag if the number of domains for this rdata has hit a threshold
    if (num_of_domains[dns.rdata] == THRESHOLD) {
      mal_ip_list[dns.rdata] = 1;
    }
  }
}
