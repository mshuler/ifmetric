#ifndef foonlrequesthfoo
#define foonlrequesthfoo

#include <sys/socket.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <linux/if.h>

/* Issue a netlink message and wait for a response, calling 'callback' for every response message */
int netlink_request(int s, struct nlmsghdr *n, int (*callback) (struct nlmsghdr *n, void*u), void *u);

int addattr32(struct nlmsghdr *n, int maxlen, int type, int data);
int addattr_l(struct nlmsghdr *n, int maxlen, int type, void *data, int alen);

int netlink_open(void);
    

#endif
    
