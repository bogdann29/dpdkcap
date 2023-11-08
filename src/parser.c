#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

void ethernet_parse(struct mac_header_s *mac_layer, struct Parser *parser)
{
    size_t start = parser->size;
    if (parser->flag == 1)
        memcpy(mac_layer->src_mac, (parser->packet_context).packet + parser->count, sizeof(mac_layer->src_mac));
    else if (parser->flag == 2)
        memset(mac_layer->src_mac, 0, sizeof(mac_layer->src_mac));
    parser->count += sizeof(mac_layer->src_mac);

    if (parser->flag == 1)
        memcpy(mac_layer->src_mac, (parser->packet_context).packet + parser->count, sizeof(mac_layer->dest_mac));
    else if (parser->flag == 2)
        memset(mac_layer->src_mac, 0, sizeof(mac_layer->dest_mac));
    
    parser->count += sizeof(mac_layer->dest_mac);

    mac_layer->ethertype = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    parser->count += sizeof(mac_layer->ethertype);

    parser->size += sizeof(struct mac_header_s);

    if (parser->flag == 2)
        memcpy(parser->new_packet + start, mac_layer, parser->size - start);
}

void vlan_parse(struct vlan_header_s *vlan_layer, struct Parser *parser)
{
    size_t start = parser->size;

    vlan_layer->tpid = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    parser->count += sizeof(vlan_layer->tpid);

    if (parser->flag)
        vlan_layer->tci = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    parser->count += sizeof(vlan_layer->tci);

    parser->size += sizeof(struct vlan_header_s);

    if (parser->flag == 2)
        memcpy(parser->new_packet + start, vlan_layer, parser->size - start);
}

void mpls_parse(struct mpls_header_s *mpls_layer, struct Parser *parser)
{
    size_t start = parser->size;

    memcpy(mpls_layer->tag, (parser->packet_context).packet + parser->count, sizeof(mpls_layer->tag));
    parser->count += sizeof(mpls_layer->tag);

    if (parser->flag)
        mpls_layer->ttl = (parser->packet_context).packet[parser->count];
    parser->count += sizeof(mpls_layer->ttl);

    parser->size += sizeof(struct mpls_header_s);

    if (parser->flag == 2)
        memcpy(parser->new_packet + start, mpls_layer, parser->size - start);
}

void ipv4_parse(struct ipv4_header_s *ipv4_layer, struct Parser *parser)
{
    size_t start = parser->size;

    if (parser->flag)
        ipv4_layer->ihl_and_version = (parser->packet_context).packet[parser->count];
    parser->count += sizeof(ipv4_layer->ihl_and_version);

    if (parser->flag == 1)
        ipv4_layer->type_of_service = (parser->packet_context).packet[parser->count];
    else if (parser->flag == 2)
        ipv4_layer->type_of_service = 0;

    parser->count += sizeof(ipv4_layer->type_of_service);

    if (parser->flag)
        ipv4_layer->total_length = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    parser->count += sizeof(ipv4_layer->total_length);

    if (parser->flag)
        ipv4_layer->identification = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    parser->count += sizeof(ipv4_layer->identification);

    if (parser->flag == 1)
        ipv4_layer->fragment_offset = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    else if (parser->flag == 2)
        ipv4_layer->fragment_offset = 0x8000 & (((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1]);
    parser->count += sizeof(ipv4_layer->fragment_offset);

    if (parser->flag == 1)
        ipv4_layer->time_to_live = (parser->packet_context).packet[parser->count];
    else if (parser->flag == 2)
        ipv4_layer->time_to_live = 0;

    parser->count += sizeof(ipv4_layer->time_to_live);

    ipv4_layer->protocol = (parser->packet_context).packet[parser->count];
    parser->count += sizeof(ipv4_layer->protocol);

    if (parser->flag == 1)
        ipv4_layer->checksum = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    else if (parser->flag == 2)
         ipv4_layer->checksum = 0;
    parser->count += sizeof(ipv4_layer->checksum);

    if (parser->flag == 1)
        memcpy(ipv4_layer->source_ip, (parser->packet_context).packet + parser->count, sizeof(ipv4_layer->source_ip));
    else if (parser->flag == 2)
        memset(ipv4_layer->source_ip, 0, sizeof(ipv4_layer->source_ip));
    parser->count += sizeof(ipv4_layer->source_ip);

    if (parser->flag == 1)
        memcpy(ipv4_layer->dest_ip, (parser->packet_context).packet + parser->count, sizeof(ipv4_layer->dest_ip));
    else if (parser->flag == 2)
        memset(ipv4_layer->dest_ip, 0, sizeof(ipv4_layer->dest_ip));

    parser->count += sizeof(ipv4_layer->dest_ip);

    uint8_t hdrlen = ipv4_layer->ihl_and_version & 0xF;
    parser->size += hdrlen * 4;

    if (parser->flag == 2)
        memcpy(parser->new_packet + start, ipv4_layer, parser->size - start);
}

void ipv6_parse(struct ipv6_header_s *ipv6_layer, struct Parser *parser)
{
    size_t start = parser->size;

    if (parser->flag)
        memcpy(ipv6_layer->version_traffic_class_flow_label, (parser->packet_context).packet + parser->count, sizeof(ipv6_layer->version_traffic_class_flow_label));
    parser->count += sizeof(ipv6_layer->version_traffic_class_flow_label);

    if (parser->flag)
        ipv6_layer->payload_length = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    parser->count += sizeof(ipv6_layer->payload_length);

    ipv6_layer->next_header = (parser->packet_context).packet[parser->count];
    parser->count += sizeof(ipv6_layer->next_header);

    if (parser->flag == 1)
        ipv6_layer->hop_limit = (parser->packet_context).packet[parser->count];
    else if (parser->flag == 2)
        ipv6_layer->hop_limit = 0;
    parser->count += sizeof(ipv6_layer->hop_limit);

    if (parser->flag)
        memcpy(ipv6_layer->source_ip, (parser->packet_context).packet + parser->count, sizeof(ipv6_layer->source_ip));
    else if (parser->flag == 2)
        memset(ipv6_layer->source_ip, 0, sizeof(ipv6_layer->source_ip));
    parser->count += sizeof(ipv6_layer->source_ip);

    if (parser->flag)
        memcpy(ipv6_layer->dest_ip, (parser->packet_context).packet + parser->count, sizeof(ipv6_layer->dest_ip));
    else if (parser->flag == 2)
        memset(ipv6_layer->dest_ip, 0, sizeof(ipv6_layer->dest_ip));

    parser->count += sizeof(ipv6_layer->dest_ip);

    parser->size += sizeof(struct ipv6_header_s);

    if (parser->flag == 2)
        memcpy(parser->new_packet + start, ipv6_layer, parser->size - start);
}

void tcp_parse(struct tcp_header_s *tcp_layer, struct Parser *parser)
{
    size_t start = parser->size;

    if (parser->flag == 1)
        tcp_layer->source_port = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    else if (parser->flag == 2)
        tcp_layer->source_port = 0;

    parser->count += sizeof(tcp_layer->source_port);

    if (parser->flag == 1)
        tcp_layer->dest_port = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    else if (parser->flag == 2)
        tcp_layer->dest_port = 0;

    parser->count += sizeof(tcp_layer->dest_port);

    if (parser->flag)
        memcpy(tcp_layer->sequence_number, (parser->packet_context).packet + parser->count, sizeof(tcp_layer->sequence_number));
    parser->count += sizeof(tcp_layer->sequence_number);

    if (parser->flag)
        memcpy(tcp_layer->ack_number, (parser->packet_context).packet + parser->count, sizeof(tcp_layer->ack_number));
    parser->count += sizeof(tcp_layer->ack_number);

    if (parser->flag)
        tcp_layer->data_offset_and_reversed = (parser->packet_context).packet[parser->count];
    parser->count += sizeof(tcp_layer->data_offset_and_reversed);

    if (parser->flag)
        tcp_layer->flags = (parser->packet_context).packet[parser->count];
    parser->count += sizeof(tcp_layer->flags);

    if (parser->flag == 1)
        tcp_layer->window_size = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    else if (parser->flag == 2)
        tcp_layer->window_size = 0;
    
    parser->count += sizeof(tcp_layer->window_size);

    if (parser->flag == 1)
        tcp_layer->checksum = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    else if (parser->flag == 2)
        tcp_layer->checksum = 0;

    parser->count += sizeof(tcp_layer->checksum);

    if (parser->flag)
        tcp_layer->urgent_pointer = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    parser->count += sizeof(tcp_layer->urgent_pointer);

    parser->size += ((tcp_layer->data_offset_and_reversed & 0xF0) >> 4) * 4;

    if (parser->flag == 2)
        memcpy(parser->new_packet + start, tcp_layer, parser->size - start);
}

void udp_parse(struct udp_header_s *udp_layer, struct Parser *parser)
{
    size_t start = parser->size;

    if (parser->flag == 1)
        udp_layer->source_port = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    else if (parser->flag == 2)
        udp_layer->source_port = 0;

    parser->count += sizeof(udp_layer->source_port);

    if (parser->flag == 1)
        udp_layer->dest_port = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    else if (parser->flag == 2)
        udp_layer->dest_port = 0;

    parser->count += sizeof(udp_layer->dest_port);

    if (parser->flag)
        udp_layer->length = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    parser->count += sizeof(udp_layer->length);

    if (parser->flag == 1)
        udp_layer->checksum = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    else if (parser->flag == 2)
        udp_layer->checksum = 0;

    parser->count += sizeof(udp_layer->checksum);

    parser->size += sizeof(struct udp_header_s);

    if (parser->flag == 2)
        memcpy(parser->new_packet + start, udp_layer, parser->size - start);
}

void icmp_parse(struct icmp_header_s *icmp_layer, struct Parser *parser)
{
    size_t start = parser->size;

    if (parser->flag)
        icmp_layer->type = (parser->packet_context).packet[parser->count];
    parser->count += sizeof(icmp_layer->type);

    if (parser->flag == 1)
        icmp_layer->code = (parser->packet_context).packet[parser->count];
    else if (parser->flag == 2)
        icmp_layer->code = 0;

    parser->count += sizeof(icmp_layer->code);

    if (parser->flag == 1)
        icmp_layer->checksum = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    else if (parser->flag == 2)
        icmp_layer->checksum = 0;

    parser->count += sizeof(icmp_layer->checksum);

    if (parser->flag)
        icmp_layer->identifier = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    parser->count += sizeof(icmp_layer->identifier);

    if (parser->flag)
        icmp_layer->sequence = ((uint16_t)(parser->packet_context).packet[parser->count] << 8) | (parser->packet_context).packet[parser->count + 1];
    parser->count += sizeof(icmp_layer->sequence);

    parser->size += sizeof(struct icmp_header_s);

    if (parser->flag == 2)
        memcpy(parser->new_packet + start, (void *)icmp_layer, parser->size - start);
}

void arp_parse(struct arp_header_s *arp_layer, struct Parser *parser) {
    size_t start = parser->size;
    memcpy(arp_layer, (parser->packet_context).packet + parser->count, sizeof(struct arp_header_s));
    parser->count += sizeof(struct arp_header_s);
    parser->size += sizeof(struct arp_header_s);

     if (parser->flag == 2)
        memcpy(parser->new_packet + start, arp_layer, parser->size - start);
}

uint32_t get_end_of_packet(struct Parser *parser)
{
    uint8_t next;
    ethernet_parse(&(parser->packet_context).mac_header, parser);
    uint16_t eth = (parser->packet_context).mac_header.ethertype;
    if (eth == ETHERTYPE_VLAN)
    {
        vlan_parse(&(parser->packet_context).first_vlan_header, parser);
        eth = (parser->packet_context).first_vlan_header.tpid;
        if (eth == ETHERTYPE_VLAN)
        {
            vlan_parse(&(parser->packet_context).second_vlan_header, parser);
            eth = (parser->packet_context).second_vlan_header.tpid;
        }
    }

    if (eth == ETHERTYPE_MPLS_MC || eth == ETHERTYPE_MPLS_UC)
    {
        mpls_parse(&(parser->packet_context).first_mpls_header, parser);
        next = (parser->packet_context).first_mpls_header.tag[2] & 1;

        if (next == 0x00)
        {
            mpls_parse(&(parser->packet_context).second_mpls_header, parser);
            next = (parser->packet_context).second_mpls_header.tag[2] & 1;

            if (next == 0x00)
            {
                mpls_parse(&(parser->packet_context).third_mpls_header, parser);
                next = (parser->packet_context).third_mpls_header.tag[2] & 1;

                if (next == 0x00)
                {
                    mpls_parse(&(parser->packet_context).fourth_mpls_header, parser);
                    next = (parser->packet_context).fourth_mpls_header.tag[2] & 1;

                    if (next == 0x00)
                    {
                        mpls_parse(&(parser->packet_context).fifth_mpls_header, parser);
                        next = (parser->packet_context).fifth_mpls_header.tag[2] & 1;
                    }
                }
            }
        }
    }
    next = ((*((parser->packet_context).packet + parser->size)) & 0xF0) >> 4;

    if (eth == ETHERTYPE_IP || next == 0x04)
    {
        ipv4_parse(&(parser->packet_context).ipv4_header, parser);
        next = (parser->packet_context).ipv4_header.protocol;
    }
    else if (eth == ETHERTYPE_IPV6 || next == 0x06)
    {
        ipv6_parse(&(parser->packet_context).ipv6_header, parser);
        next = (parser->packet_context).ipv6_header.next_header;
    }

    if (next == 0x01)
        icmp_parse(&(parser->packet_context).icmp_header, parser);
    else if (next == 0x06)
        tcp_parse(&(parser->packet_context).tcp_header, parser);
    else if (next == 0x11)
        udp_parse(&(parser->packet_context).udp_header, parser);

    return parser->size;
}
