#include "pcap-test.h"

void usage() {
    printf("syntax: pcap-test <interface>\n");
    printf("sample: pcap-test wlan0\n");
}

typedef struct {
    char* dev_;
} Param;

Param param = {
    .dev_ = NULL
};

bool parse(Param* param, int argc, char* argv[]) {
    if (argc != 2) {
        usage();
        return false;
    }
    param->dev_ = argv[1];
    return true;
}

int main(int argc, char *argv[]){
    if (!parse(&param, argc, argv))
        return -1;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* pcap = pcap_open_live(param.dev_, BUFSIZ, 1, 1000, errbuf);

    if (pcap == NULL) {
        fprintf(stderr, "pcap_open_live(%s) return null - %s\n", param.dev_, errbuf);
        return -1;
    }

    while(true){
        struct pcap_pkthdr* header;
        const u_char* packet;

        pcap_next_ex(pcap,&header,&packet);

        struct libnet_ethernet_hdr* eth_hdr = (struct libnet_ethernet_hdr *)packet;
        struct libnet_ipv4_hdr* ip_hdr = (struct libnet_ipv4_hdr *)(packet + LIBNET_ETH_H);
        struct libnet_tcp_hdr* tcp_hdr = (struct libnet_tcp_hdr *)(packet + (ip_hdr->ip_hl * 4) + LIBNET_ETH_H);

        uint16_t tcph_size = tcp_hdr->th_off * 4;
        uint16_t iph_size = ip_hdr->ip_hl * 4;
        printf("%d, %d, %d",htons(ip_hdr->ip_len),tcph_size, iph_size);

        if(eth_hdr->ether_type == 0x0800 && ip_hdr->ip_p == 0x06)
            continue;
        printf("Src Mac : %s\n", ether_ntoa((const struct ether_addr *)&eth_hdr->ether_shost));
        printf("Dst Mac: %s\n", ether_ntoa((const struct ether_addr *)&eth_hdr->ether_dhost));
        printf("Src Ip: %s\n", inet_ntoa(ip_hdr->ip_src));
        printf("Dst Ip: %s\n", inet_ntoa(ip_hdr->ip_dst));
        printf("Src Port: %d\n", ntohs(tcp_hdr->th_sport));
        printf("Dst Port: %d\n", ntohs(tcp_hdr->th_dport));

        unsigned char * data = (unsigned char *)(packet + LIBNET_ETH_H  + LIBNET_IPV4_H + LIBNET_TCP_H);

        uint8_t data_size = htons(ip_hdr->ip_len) - tcph_size - iph_size;

        printf("Data : ");

        if( data_size < 20)
            data_size = data_size;
        else
            data_size = 20;

        for(int i = 0 ; i < data_size; i++){
            printf("%02X ", data[i]);
        }
        printf("\n----------------------------------------\n");
    }
    pcap_close(pcap);
}
