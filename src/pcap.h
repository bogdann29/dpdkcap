#ifndef DPDKCAP_PCAP_H
#define DPDKCAP_PCAP_H

#include <stdint.h>

#define PCAP_SNAPLEN_DEFAULT 65535

/**
 * @file pcap.h
 * @brief Definition of pcap file format structures and functions
 */

/**
 * @struct pcap_header
 * @brief Structure representing the header of a pcap file
 */
struct __attribute__((__packed__)) pcap_header
{
	uint32_t magic_number;	/**< Magic number */
	uint16_t version_major; /**< Major version number */
	uint16_t version_minor; /**< Minor version number */
	int32_t thiszone;		/**< GMT to local correction */
	uint32_t sigfigs;		/**< Accuracy of timestamps */
	uint32_t snaplen;		/**< Max length of captured packets, in octets */
	uint32_t network;		/**< Data link type */
};

/**
 * @struct pcap_packet_header
 * @brief Structure representing the header of a pcap packet
 */
struct pcap_packet_header
{
	uint32_t timestamp;			 /**< Timestamp of the packet */
	uint32_t microseconds;		 /**< Microseconds portion of the timestamp */
	uint32_t packet_length;		 /**< Length of the packet */
	uint32_t packet_length_wire; /**< Length of the packet on the wire */
};

/**
 * @brief Initialize the pcap header with the provided snap length
 *
 * @param header Pointer to the pcap_header structure to be initialized
 * @param snaplen Snap length value to be set in the header
 */
void pcap_header_init(struct pcap_header *header, unsigned int snaplen);

#endif
