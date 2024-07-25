#include "pcap-test.h"

int main(int argc, char *argv[]){
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t * pcap = pcap_open_live(argv[1],BUFSIZ,1,1000,errbuf);

    while(true){
        struct pcap_pkthdr* header;
        const u_char* packet;
        struct libnet_ethernet_hdr* eth_hdr;
        struct libnet_ipv4_hdr* ip_hdr;
        struct libnet_tcp_hdr* tcp_hdr;


        pcap_next_ex(pcap,&header,&packet);
        eth_hdr = (struct libnet_ethernet_hdr *)packet;
        ip_hdr = (struct libnet_ipv4_hdr *)(packet + LIBNET_ETH_H);
        tcp_hdr = (struct libnet_tcp_hdr *)(packet + LIBNET_IPV4_H + LIBNET_ETH_H);
        char pkt_data[20] = {' ',};
        printf("Source MAC: %s\n", ether_ntoa((const struct ether_addr *)&eth_hdr->ether_shost));
        printf("Destination MAC: %s\n", ether_ntoa((const struct ether_addr *)&eth_hdr->ether_dhost));
        printf("Source IP: %s\n", inet_ntoa(ip_hdr->ip_src));
        printf("Destination IP: %s\n", inet_ntoa(ip_hdr->ip_dst));
        printf("Source Port: %d\n", ntohs(tcp_hdr->th_sport));
        printf("Destination Port: %d\n", ntohs(tcp_hdr->th_dport));

        unsigned char * data = (unsigned char *)(packet + LIBNET_ETH_H  + LIBNET_IPV4_H + LIBNET_TCP_H);
        printf("Data : ");
        for(int i = 0; i< 20; i++){
            printf("%02X ", data[i]);
        }
        printf("\n----------------------------------------\n");
    }
    pcap_close(pcap);
}
