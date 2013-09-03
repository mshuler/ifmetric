#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "nlrequest.h"

int netlink_open(void) {
    struct sockaddr_nl addr;
    int s;
    
    if ((s = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE)) < 0) {
        fprintf(stderr, "socket(PF_NETLINK): %s\n", strerror(errno));
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = 0;
    addr.nl_pid = getpid();

    if (bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        fprintf(stderr, "bind(): %s\n", strerror(errno));
        return -1;
    }

    return s;
}


int netlink_request(int s, struct nlmsghdr *n, int (*callback) (struct nlmsghdr *n, void *u), void *u) {
    static int seq = 0;
    pid_t pid = getpid();
    assert(s >= 0 && n);

    n->nlmsg_seq = seq++;
    n->nlmsg_flags |= NLM_F_ACK;
    
    if (send(s, n, n->nlmsg_len, 0) < 0) {
        fprintf(stderr, "NETLINK: send(): %s\n", strerror(errno));
        return -1;
    }

    for (;;) {
        int bytes;
        char replybuf[2048];
        struct nlmsghdr *p = (struct nlmsghdr *) replybuf;
        
        if ((bytes = recv(s, &replybuf, sizeof(replybuf), 0)) < 0) {
            fprintf(stderr, "recv(): %s\n", strerror(errno));
            return -1;
        }

        for (; bytes > 0; p = NLMSG_NEXT(p, bytes)) {
            int ret;
            
            if (!NLMSG_OK(p, bytes) || bytes < sizeof(struct nlmsghdr) || bytes < p->nlmsg_len) {
                fprintf(stderr, "NETLINK: Packet too small or truncated! %u!=%u!=%u\n", bytes, sizeof(struct nlmsghdr), p->nlmsg_len);
                return -1;
            }

            if (p->nlmsg_type == NLMSG_DONE)
                return 0;

            if (p->nlmsg_type == NLMSG_ERROR) {
                struct nlmsgerr *e = (struct nlmsgerr *) NLMSG_DATA (p);

                if (e->error) {
                    fprintf(stderr, "NETLINK: Error: %s\n", strerror(-e->error));
                    return -1;
                } else
                    return 0;
            }

            if (p->nlmsg_pid != pid)
                continue;

            if (p->nlmsg_seq != n->nlmsg_seq) {
                fprintf(stderr, "NETLINK: Received message with bogus sequence number!\n");
                continue;
            }

            if (callback)
                if ((ret = callback(p, u)) < 0)
                    return ret;
        }
    }
        
    return 0;
}

/*
 * Utility function comes from iproute2.
 * Author: Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

int addattr_l(struct nlmsghdr *n, int maxlen, int type, void *data, int alen) {
    int len;
    struct rtattr *rta; 
    
    len = RTA_LENGTH(alen);
    
    if (NLMSG_ALIGN(n->nlmsg_len) + len > maxlen)
        return -1;
    
    rta = (struct rtattr*) (((char*)n) + NLMSG_ALIGN (n->nlmsg_len));
    rta->rta_type = type;
    rta->rta_len = len;
    memcpy (RTA_DATA(rta), data, alen);
    n->nlmsg_len = NLMSG_ALIGN (n->nlmsg_len) + len;
    
    return 0;
}

/*
 * Utility function originated from iproute2.
 * Author: Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

int addattr32(struct nlmsghdr *n, int maxlen, int type, int data) {
    int len;
    struct rtattr *rta;
    
    len = RTA_LENGTH(4);
    
    if (NLMSG_ALIGN (n->nlmsg_len) + len > maxlen)
        return -1;
    
    rta = (struct rtattr*) (((char*)n) + NLMSG_ALIGN (n->nlmsg_len));
    rta->rta_type = type;
    rta->rta_len = len;
    memcpy (RTA_DATA(rta), &data, 4);
    n->nlmsg_len = NLMSG_ALIGN (n->nlmsg_len) + len;
    
    return 0;
}

