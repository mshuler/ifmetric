#include <string.h>
#include <stdio.h>

#include "getifn.h"
#include "nlrequest.h"

struct getifn_info {
    char ifname[IFNAMSIZ+1];
    int idx;
};

int getifn_callback(struct nlmsghdr *n, void *u) {
    struct rtattr *a = NULL;
    int l;
    struct getifn_info *gi = (struct getifn_info*) u;
    struct ifinfomsg *i;

    if (n->nlmsg_type != RTM_NEWLINK) {
        fprintf(stderr, "NETLINK: Got response for wrong request.\n");
        return -1;
    }

    i = NLMSG_DATA(n);
    l = NLMSG_PAYLOAD(n, sizeof(struct ifinfomsg));
    a = IFLA_RTA(i);
    
    while(RTA_OK(a, l)) {
        
        switch(a->rta_type) {
            case IFLA_IFNAME:
                if (strncmp(RTA_DATA(a), gi->ifname, IFNAMSIZ) == 0)  {
                    gi->idx = i->ifi_index;
                    return 0;
                }
        }
        a = RTA_NEXT(a, l);
    }
    
    return 0;
}

int getifn(int s, char *iface) {
    struct getifn_info gi;
    
    struct {
        struct nlmsghdr n;
        struct ifinfomsg i;
        char a[1024];
    } req;
    
    memset(&req, 0, sizeof(req));
    req.n.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
    req.n.nlmsg_flags = NLM_F_REQUEST|NLM_F_MATCH;
    req.n.nlmsg_type = RTM_GETLINK;
    
    req.i.ifi_family = AF_UNSPEC;
    req.i.ifi_change = -1;

    memset(&gi, 0, sizeof(gi));
    strncpy(gi.ifname, iface, IFNAMSIZ);
    gi.idx = -1;

    if (addattr_l(&req.n, sizeof(req), IFLA_IFNAME, gi.ifname, IFNAMSIZ+1) < 0) {
        fprintf(stderr, "Failed to add attribute to netlink message\n");
        return -1;
    }
    
    if (netlink_request(s, (struct nlmsghdr*) &req, getifn_callback, &gi) < 0)
        return -1;

    if (gi.idx < 0) {
        fprintf(stderr, "Interface '%s' not existent.\n", iface);
        return -1;
    }
    
    return gi.idx;
}
