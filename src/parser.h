#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>
#include "net_headers.h"
#include "hash_map.h"

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

struct Parser
{
    struct packet_context_s packet_context;
    int flag;               /**< flag indicates whether header fields need to be parsed */
    uint32_t count;         /**< number of parsed bytes */
    uint32_t size;          /**< total header size */
    uint32_t *ip_idx;       /**< new ip4 addr for replace */
    __uint128_t *ip_idx128; /**< new ip6 addr for replace */
    struct hash_map *map;
    struct hash_map128 *map128;
    uint8_t *new_packet; /**< new package with zeroed fields that could have been changed */
};

/**
 * @brief getting the length of the packet headers (levels 2-4)
 *
 * @param parser pointer to the structure of the parser (parsed package)
 * @return uint32_t
 */
uint32_t get_end_of_packet(struct Parser *parser);

/**
 * @brief etherner header parser with filling fields
 *
 * @param mac_layer link layer header structure pointer
 * @param parser parser structure pointer
 */
void ethernet_parse(struct mac_header_s *mac_layer, struct Parser *parser);

/**
 * @brief vlan header parser with filling fields
 *
 * @param mac_layer vlan header structure pointer
 * @param parser parser structure pointer
 */
void vlan_parse(struct vlan_header_s *vlan_layer, struct Parser *parser);

/**
 * @brief mpls header parser with filling fields
 *
 * @param mac_layer mpls header structure pointer
 * @param parser parser structure pointer
 */
void mpls_parse(struct mpls_header_s *mpls_layer, struct Parser *parser);

/**
 * @brief ipv4 header parser with filling fields
 *
 * @param mac_layer ipv4 header structure pointer
 * @param parser parser structure pointer
 */
void ipv4_parse(struct ipv4_header_s *ipv4_layer, struct Parser *parser);

/**
 * @brief ipv6 header parser with filling fields
 *
 * @param mac_layer ipv6 header structure pointer
 * @param parser parser structure pointer
 */
void ipv6_parse(struct ipv6_header_s *ipv6_layer, struct Parser *parser);

/**
 * @brief tcp header parser with filling fields
 *
 * @param mac_layer tcp header structure pointer
 * @param parser parser structure pointer
 */
void tcp_parse(struct tcp_header_s *tcp_layer, struct Parser *parser);

/**
 * @brief udp header parser with filling fields
 *
 * @param mac_layer udp header structure pointer
 * @param parser parser structure pointer
 */
void udp_parse(struct udp_header_s *udp_layer, struct Parser *parser);

/**
 * @brief icmp header parser with filling fields
 *
 * @param mac_layer icmp header structure pointer
 * @param parser parser structure pointer
 */
void icmp_parse(struct icmp_header_s *icmp_layer, struct Parser *parser);

/**
 * @brief arp header parser with filling fields
 *
 * @param mac_layer arp header structure pointer
 * @param parser parser structure pointer
 */
void arp_parse(struct arp_header_s *arp_layer, struct Parser *parser);

#endif /* PARSER_H */