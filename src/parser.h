#ifndef PARSER_H
#define PARSER_H

// #include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "NetHeaders.h"

/**
 * @brief Packet context structure.
 *
 */
struct packet_context_s
{
    const uint8_t *packet;
    int counter;

    struct mac_header_s mac_header;
    struct vlan_header_s first_vlan_header;
    struct vlan_header_s second_vlan_header;

    struct mpls_header_s first_mpls_header;
    struct mpls_header_s second_mpls_header;
    struct mpls_header_s third_mpls_header;
    struct mpls_header_s fourth_mpls_header;
    struct mpls_header_s fifth_mpls_header;

    struct arp_header_s arp_header;

    struct ipv4_header_s ipv4_header;
    struct ipv6_header_s ipv6_header;

    struct tcp_header_s tcp_header;
    struct udp_header_s udp_header;
    struct icmp_header_s icmp_header;
};

struct Parser{
    struct packet_context_s packet_context;
    int flag;      ///< flag indicates whether header fields need to be parsed
    uint32_t count; ///< number of parsed headers
    uint32_t size;
    uint8_t *new_packet;
};

uint32_t get_end_of_packet(struct Parser *parser);

void ethernet_parse(struct mac_header_s *mac_layer, struct Parser *parser);

void vlan_parse(struct vlan_header_s *vlan_layer, struct Parser *parser);

void mpls_parse(struct mpls_header_s *mpls_layer, struct Parser *parser);

void ipv4_parse(struct ipv4_header_s *ipv4_layer, struct Parser *parser);

void ipv6_parse(struct ipv6_header_s *ipv6_layer, struct Parser *parser);

void tcp_parse(struct tcp_header_s *tcp_layer, struct Parser *parser);

void udp_parse(struct udp_header_s *udp_layer, struct Parser *parser);

void icmp_parse(struct icmp_header_s *icmp_layer, struct Parser *parser);

#endif /* PARSER_H */