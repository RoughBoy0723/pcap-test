# pcap-test
pcap-test homework 
7/26 Pcap lib, Libnet lib의 숙달 및 OSI 7Layer 각종 프로토콜에 대해 알아가는 수업이었습니다.

수업 내용으로 ppt를 만들었으며 내용은 OSI7 Layer와 각 layer에서 사용되는 프로토콜 및 기기들을 정리했습니다.

![gilgil's_OSI7Layer](https://github.com/user-attachments/assets/5e489b09-64cd-488c-b800-e5a726b4ed53)

과제 코드 작성에 앞서 필요한 사전지식은 수업에서 배운 pcap 사용법과 패킷의 헤더에서 필요한 정보만 빼오는 능력들입니다.

Libnet labrary의 libnet-headers.h를 찾아본 결과 각 헤더의 길이와 구조체들은 아래의 사진과 같습니다.

ETH의 헤더 길이와 구조체

![LIBNET_ETH_H](https://github.com/user-attachments/assets/1248117a-ec89-461d-af9e-2f012a964d20)
![libnet_ethernet_hdr](https://github.com/user-attachments/assets/f7088a14-9c65-4c26-acb0-6ef144c553ff)

TCP 헤더 길이와 구조체

![LIBNET_TCP_H](https://github.com/user-attachments/assets/bdd6a11b-6a3b-4a1d-9444-498d58bedb5c)
![libnet_tcp_hdr](https://github.com/user-attachments/assets/b199e978-a3be-4a63-90f1-a5ad3a52cc14)

IPv4 헤더 길이와 구조체

![LIBNET_IPV4_H](https://github.com/user-attachments/assets/71b5c7ee-5297-4333-932d-3ace5441c0a8)
![libnet_ipv4_hdr](https://github.com/user-attachments/assets/698422f1-c00b-4c64-be54-4ae48ece7ba8)

위의 지식만 알고있으면 pcap_open_live()를 이용하여 현재 패킷을 불러오고 pacp_next_ex() 혹은 pcap_loop()를 사용하여 capture하는 패킷의 정보를 계속해서 가져옵니다. 그 다음 패킷의 헤더를 parsing하여 원하는 정보를 가져와서 출력하면 됩니다. 그후 예외처리를 통해 실행 파일의 안정성 및 안전성을 챙기면 과제는 완료됩니다.


참고 사이트 : 
http://packetfactory.openwall.net/projects/libnet/
https://tmdgus.tistory.com/134
