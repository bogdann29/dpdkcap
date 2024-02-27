#ifndef NET_HEADERS_H
#define NET_HEADERS_H

#include <stdint.h>

#if !defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__) && defined(__BYTE_ORDER)

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define __LITTLE_ENDIAN__
#elif __BYTE_ORDER == __BIG_ENDIAN
#define __BIG_ENDIAN__
#endif

#endif

#define ETHERTYPE_VLAN 0x8100 /**< IEEE 802.1Q VLAN tagging */
#define ETHERTYPE_IP 0x0800   /**< IP */
#define ETHERTYPE_IPV6 0x86dd /**< IP protocol version 6 */

#define ETHERTYPE_MPLS_UC 0x8847
#define ETHERTYPE_MPLS_MC 0x8848

#define IPv6_HEADER_PROTOCOL_HOP_BY_HOP 0
#define IP_HEADER_PROTOCOL_ICMP 1
#define IP_HEADER_PROTOCOL_TCP 6
#define IP_HEADER_PROTOCOL_UDP 17
#define IPv6_HEADER_PROTOCOL_ICMP 58

/**
 * @file net_headers.h
 * @brief Definition of network protocol header structures
 *
 */

/**
 * @brief MAC Header Structure
 */
struct mac_header_s
{
    uint8_t dest_mac[6]; /**< Destination MAC Address */
    uint8_t src_mac[6];  /**< Source MAC Address */
    uint16_t ethertype;  /**< Ethertype FieldD */
} __attribute__((packed));

/**
 * @brief VLAN Header Structure
 */
struct vlan_header_s
{
    uint16_t tpid; /**< Tag Protocol Identifier (TPID) - 0x8100 for VLAN tagging */
    uint16_t tci;  /**< Tag Control Information (TCI) - Contains VLAN ID and priority */
} __attribute__((packed));

/**
 * @brief MPLS Header Structure
 */
struct mpls_header_s
{
    uint8_t tag[3]; ///< Label Value, Experimental Bits, Bottom of Stack Bit
    uint8_t ttl;    ///< Time-to-Live (TTL)

    // #if defined(__LITTLE_ENDIAN__)
    //     uint32_t label : 20, ///< Label Value
    //         exp : 3,         ///< Experimental Bits
    //         bos : 1,         ///< Bottom of Stack Bit
    //         ttl : 8;         ///< Time-to-Live (TTL)
    // #elif defined(__BIG_ENDIAN__)
    //     uint32_t ttl : 8, ///< Time-to-Live (TTL)
    //         bos : 1,      ///< Bottom of Stack Bit
    //         exp : 3,      ///< Experimental Bits
    //         label : 20;   ///< Label Value
    // #endif
} __attribute__((packed));

/**
 * @brief ARP Header Structure
 */
struct arp_header_s
{
    uint16_t hardware_type;          /**< Hardware Type (e.g., Ethernet)*/
    uint16_t protocol_type;          /**< Protocol Type (e.g., IPv4)*/
    uint8_t hardware_length;         /**< Length of Hardware Address (Ethernet MAC: 6 bytes)*/
    uint8_t protocol_length;         /**< Length of Protocol Address (IPv4: 4 bytes)*/
    uint16_t operation;              /**< ARP Operation (Request or Reply)*/
    uint8_t sender_hardware_addr[6]; /**< Sender's Hardware (MAC) Address*/
    uint8_t sender_protocol_addr[4]; /**< Sender's Protocol (IP) Address*/
    uint8_t target_hardware_addr[6]; /**< Target's Hardware (MAC) Address*/
    uint8_t target_protocol_addr[4]; /**< Target's Protocol (IP) Address*/
} __attribute__((packed));

/**
 * @brief IPv4 Header Structure
 */
struct ipv4_header_s
{
    uint8_t ihl_and_version; ////< Header Length (in 32-bit words) && IP Version (IPv4)

    // #if defined(__LITTLE_ENDIAN__)
    //     uint8_t
    //         header_length : 4, ///< Header Length (in 32-bit words)
    //         version : 4;       ///< IP Version (IPv4)
    // #elif defined(__BIG_ENDIAN__)
    //     uint8_t
    //         version : 4,       ///< IP Version (IPv4)
    //         header_length : 4; ///< Header Length (in 32-bit words)
    // #endif

    uint8_t type_of_service;  /**< Type of Service */
    uint16_t total_length;    /**< Total Length (including header and data) */
    uint16_t identification;  /**< Identification */
    uint16_t fragment_offset; /**< Fragment Offset and Flags */
    uint8_t time_to_live;     /**< Time to Live */
    uint8_t protocol;         /**< Protocol (e.g., TCP, UDP) */
    uint16_t checksum;        /**< Header Checksum */
    uint8_t source_ip[4];     /**< Source IP Address */
    uint8_t dest_ip[4];       /**< Destination IP Address */
} __attribute__((packed));

/**
 * @brief IPv6 Header Structure
 */
struct ipv6_header_s
{
    uint8_t version_traffic_class_flow_label[4]; /**< Version, Traffic Class, and Flow Label */
    uint16_t payload_length;                     /**< Payload Length */
    uint8_t next_header;                         /**< Next Header */
    uint8_t hop_limit;                           /**< Hop Limit */
    uint8_t source_ip[16];                       /**< Source IPv6 Address */
    uint8_t dest_ip[16];                         /**< Destination IPv6 Address */
} __attribute__((packed));

/**
 * @brief ICMP Header Structure
 */
struct icmp_header_s
{
    uint8_t type;        /**< ICMP Message Type */
    uint8_t code;        /**< ICMP Message Code */
    uint16_t checksum;   /**< Checksum for Integrity Verification */
    uint16_t identifier; /**< Identifier (used in some ICMP messages) */
    uint16_t sequence;   /**< Sequence Number (used in some ICMP messages) */
} __attribute__((packed));

/**
 * @brief TCP Header Structure
 */
struct tcp_header_s
{
    uint16_t source_port;       /**< Source Port Number */
    uint16_t dest_port;         /**< Destination Port Number */
    uint8_t sequence_number[4]; /**< Sequence Number */
    uint8_t ack_number[4];      /**< Acknowledgment Number */

    uint8_t data_offset_and_reversed; /**< Reversed and Data offset */
    uint8_t flags;                    /**< TCP flags */

    // #if defined(__LITTLE_ENDIAN__)

    //     uint16_t
    //         FIN : 1,         ///< FIN (Finish Flag): Indicates the termination of the connection.
    //         SYN : 1,         ///< SYN (Synchronize Flag): Initiates a new connection.
    //         RST : 1,         ///< RST (Reset Flag): Indicates the reset of the connection.
    //         PSH : 1,         ///< PSH (Push Flag): Indicates a request for immediate data push to the application.
    //         ACK : 1,         ///< ACK (Acknowledgment Flag): Indicates that the Acknowledgment field is significant.
    //         URG : 1,         ///< URG (Urgent Flag): Indicates that the Urgent pointer field is significant.
    //         ECE : 1,         ///< ECE (Explicit Congestion Notification Echo): Indicates support for ECN (Explicit Congestion Notification).
    //         CWR : 1,         ///< CWR (Congestion Window Reduced): Indicates that the sender has reduced its congestion window.
    //         reversed : 4,    ///< Reserved bits for future use. Must be set to zero.
    //         data_offset : 4; ///< Specifies the length of the TCP header in 32-bit words.

    // #elif defined(__BIG_ENDIAN__)

    //     uint16_t
    //         data_offset : 4, ///< Specifies the length of the TCP header in 32-bit words.
    //         reversed : 4,    ///< Reserved bits for future use. Must be set to zero.
    //         CWR : 1,         ///< CWR (Congestion Window Reduced): Indicates that the sender has reduced its congestion window.
    //         ECE : 1,         ///< ECE (Explicit Congestion Notification Echo): Indicates support for ECN (Explicit Congestion Notification).
    //         URG : 1,         ///< URG (Urgent Flag): Indicates that the Urgent pointer field is significant.
    //         ACK : 1,         ///< ACK (Acknowledgment Flag): Indicates that the Acknowledgment field is significant.
    //         PSH : 1,         ///< PSH (Push Flag): Indicates a request for immediate data push to the application.
    //         RST : 1,         ///< RST (Reset Flag): Indicates the reset of the connection.
    //         SYN : 1,         ///< SYN (Synchronize Flag): Initiates a new connection.
    //         FIN : 1;         ///< FIN (Finish Flag): Indicates the termination of the connection.
    // #endif

    uint16_t window_size;    /**< Window Size */
    uint16_t checksum;       /**< Checksum */
    uint16_t urgent_pointer; /**< Urgent Pointer */
} __attribute__((packed));

/**
 * @brief UDP Header Structure
 */
struct udp_header_s
{
    uint16_t source_port; /**< Source Port Number */
    uint16_t dest_port;   /**< Destination Port Number */
    uint16_t length;      /**< Length of UDP Header + Data */
    uint16_t checksum;    /**< Checksum for Integrity Verification */
} __attribute__((packed));

#endif /* NET_HEADERS_H */