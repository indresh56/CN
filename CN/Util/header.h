#include<bits/stdc++.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/un.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<pthread.h>
#include<poll.h>
#include<sys/msg.h>
#include<netinet/ip_icmp.h>
#include<netinet/if_ether.h>
#include<netinet/ether.h>
#include<netinet/tcp.h>
#include<netinet/udp.h>
#include<time.h>
using namespace std;
typedef sockaddr * sa;
void PrintData (const u_char * data , int Size)
{
   //u_char *ptr=(u_char *)data;
 //  const char* S1 = reinterpret_cast<const char*>(data);
  // fprintf(stdout,"%s\n",S1);
    int i , j;
    for(i=0 ; i < Size ; i++)
    {
        if( i!=0 && i%16==0)   //if one line of hex printing is complete...
        {
            fprintf(stdout , "         ");
            for(j=i-16 ; j<i ; j++)
            {
                if(data[j]>=32 && data[j]<=128)
                    fprintf(stdout , "%c",(unsigned char)data[j]); //if its a number or alphabet
                 
                else fprintf(stdout , "."); //otherwise print a dot
            }
            fprintf(stdout , "\n");
        } 
         
        if(i%16==0) fprintf(stdout , "   ");
            fprintf(stdout , " %02X",(unsigned int)data[i]);
                 
        if( i==Size-1)  //print the last spaces
        {
            for(j=0;j<15-i%16;j++) 
            {
              fprintf(stdout , "   "); //extra spaces
            }
             
            fprintf(stdout , "         ");
             
            for(j=i-i%16 ; j<=i ; j++)
            {
                if(data[j]>=32 && data[j]<=128) 
                {
                  fprintf(stdout , "%c",(unsigned char)data[j]);
                }
                else
                {
                  fprintf(stdout , ".");
                }
            }
             
            fprintf(stdout ,  "\n" );
        }
    }
}
void print_ethernet_header(const u_char *Buffer, int Size)
{
    struct ethhdr *eth = (struct ethhdr *)Buffer;
     
    fprintf(stdout , "\n");
    fprintf(stdout , "Ethernet Header\n");
    fprintf(stdout, "   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0] , eth->h_dest[1] , eth->h_dest[2] , eth->h_dest[3] , eth->h_dest[4] , eth->h_dest[5] );
    fprintf(stdout , "   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5] );
    fprintf(stdout, "   |-Protocol            : %u \n",(unsigned short)eth->h_proto);
}
void print_ip_header(const u_char * Buffer, int Size)
{
    print_ethernet_header(Buffer , Size);
   
    unsigned short iphdrlen;

    sockaddr_in source,dest;     
    struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );
    iphdrlen =iph->ihl*4;
     
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
     
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
     
    fprintf(stdout , "\n");
    fprintf(stdout , "IP Header\n");
    fprintf(stdout , "   |-IP Version        : %d\n",(unsigned int)iph->version);
    fprintf(stdout , "   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
    fprintf(stdout , "   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
    fprintf(stdout , "   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
    fprintf(stdout , "   |-Identification    : %d\n",ntohs(iph->id));
    fprintf(stdout , "   |-TTL      : %d\n",(unsigned int)iph->ttl);
    fprintf(stdout , "   |-Protocol : %d\n",(unsigned int)iph->protocol);
    fprintf(stdout , "   |-Checksum : %d\n",ntohs(iph->check));
    fprintf(stdout , "   |-Source IP        : %s\n" , inet_ntoa(source.sin_addr) );
    fprintf(stdout , "   |-Destination IP   : %s\n" , inet_ntoa(dest.sin_addr) );
}
void print_tcp_packet(const u_char * Buffer, int Size)
{
    unsigned short iphdrlen;
     
    struct iphdr *iph = (struct iphdr *)( Buffer  + sizeof(struct ethhdr) );
    iphdrlen = iph->ihl*4;
     
    struct tcphdr *tcph=(struct tcphdr*)(Buffer + iphdrlen + sizeof(struct ethhdr));
             
    int header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff*4;
     
    fprintf(stdout , "\n\n***********************TCP Packet*************************\n");  
         
    print_ip_header(Buffer,Size);
         
    fprintf(stdout , "\n");
    fprintf(stdout , "TCP Header\n");
    fprintf(stdout , "   |-Source Port      : %u\n",ntohs(tcph->source));
    fprintf(stdout , "   |-Destination Port : %u\n",ntohs(tcph->dest));
    fprintf(stdout , "   |-Sequence Number    : %u\n",ntohl(tcph->seq));
    fprintf(stdout , "   |-Acknowledge Number : %u\n",ntohl(tcph->ack_seq));
    fprintf(stdout , "   |-Header Length      : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
    fprintf(stdout , "   |-Urgent Flag          : %d\n",(unsigned int)tcph->urg);
    fprintf(stdout , "   |-Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
    fprintf(stdout , "   |-Push Flag            : %d\n",(unsigned int)tcph->psh);
    fprintf(stdout , "   |-Reset Flag           : %d\n",(unsigned int)tcph->rst);
    fprintf(stdout , "   |-Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
    fprintf(stdout , "   |-Finish Flag          : %d\n",(unsigned int)tcph->fin);
    fprintf(stdout , "   |-Window         : %d\n",ntohs(tcph->window));
    fprintf(stdout , "   |-Checksum       : %d\n",ntohs(tcph->check));
    fprintf(stdout , "   |-Urgent Pointer : %d\n",tcph->urg_ptr);
    fprintf(stdout , "\n");
    fprintf(stdout , "                        DATA Dump                         ");
    fprintf(stdout , "\n");
         
    fprintf(stdout , "IP Header\n");
    PrintData(Buffer,iphdrlen);
         
    fprintf(stdout , "TCP Header\n");
    PrintData(Buffer+iphdrlen,tcph->doff*4);
         
    fprintf(stdout , "Data Payload\n");    
    PrintData(Buffer + header_size , Size - header_size );
                         
    fprintf(stdout , "\n###########################################################");
}
 
void print_udp_packet(const u_char *Buffer , int Size)
{
     
    unsigned short iphdrlen;
     
    struct iphdr *iph = (struct iphdr *)(Buffer +  sizeof(struct ethhdr));
    iphdrlen = iph->ihl*4;
     
    struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen  + sizeof(struct ethhdr));
     
    int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
     
    fprintf(stdout , "\n\n***********************UDP Packet*************************\n");
     
    print_ip_header(Buffer,Size);           
     
    fprintf(stdout , "\nUDP Header\n");
    fprintf(stdout , "   |-Source Port      : %d\n" , ntohs(udph->source));
    fprintf(stdout , "   |-Destination Port : %d\n" , ntohs(udph->dest));
    fprintf(stdout , "   |-UDP Length       : %d\n" , ntohs(udph->len));
    fprintf(stdout , "   |-UDP Checksum     : %d\n" , ntohs(udph->check));
     
    fprintf(stdout , "\n");
    fprintf(stdout , "IP Header\n");
    PrintData(Buffer , iphdrlen);
         
    fprintf(stdout , "UDP Header\n");
    PrintData(Buffer+iphdrlen , sizeof udph);
         
    fprintf(stdout , "Data Payload\n");    
     
    //Move the pointer ahead and reduce the size of string
    PrintData(Buffer + header_size , Size - header_size);
     
    fprintf(stdout , "\n###########################################################");
}
unsigned short csum(unsigned short *ptr,int nbytes) 
{
	register long sum;
	unsigned short oddbyte;
	register short answer;

	sum=0;
	while(nbytes>1) {
		sum+=*ptr++;
		nbytes-=2;
	}
	if(nbytes==1) {
		oddbyte=0;
		*((u_char*)&oddbyte)=*(u_char*)ptr;
		sum+=oddbyte;
	}

	sum = (sum>>16)+(sum & 0xffff);
	sum = sum + (sum>>16);
	answer=(short)~sum;
	
	return(answer);
}
void setAddress(struct sockaddr_in &Addr, int portno)
{
    Addr.sin_addr.s_addr=INADDR_ANY;
    Addr.sin_port=htons(portno);
    Addr.sin_family=AF_INET;
}
int createTCPSocket(int port, int nolisten)
{
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in saddr;
    setAddress(saddr,port);
    int opt=1;
    setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(int));
    int p=bind(sfd,(sa) &saddr,sizeof(saddr));
    if(p<0)
    perror("Error in binding to port \n");
    listen(sfd,nolisten);
    return sfd;
}
int createUDPSocket(int port)
{
    int sfd=socket(AF_INET,SOCK_DGRAM,0);
    sockaddr_in saddr;
    setAddress(saddr,port);
    int opt=1;
    setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(int));
    int p=bind(sfd,(sa) &saddr,sizeof(saddr));
    if(p<0)
    perror("Error in binding to port \n");
    return sfd;
}
int createUXSocket(string path,int nolisten)
{
    int usfd=socket(AF_LOCAL,SOCK_STREAM,0);
    sockaddr_un uaddr;
    uaddr.sun_family=AF_LOCAL;
    strcpy(uaddr.sun_path,path.c_str());
    unlink(path.c_str());
    int p=bind(usfd,(sa) &uaddr,sizeof(uaddr));
    if(p<0)
    perror("Unix socket bind error\n");
    listen(usfd,nolisten);
    return usfd;
}
int createUXSocket(string path)
{
    int usfd=socket(AF_LOCAL,SOCK_STREAM,0);
    sockaddr_un uaddr;
    uaddr.sun_family=AF_LOCAL;
    strcpy(uaddr.sun_path,path.c_str());
    unlink(path.c_str());
    int p=bind(usfd,(sa) &uaddr,sizeof(uaddr));
    if(p<0)
    perror("Unix socket bind error\n");
    return usfd;
}
void setAddress(sockaddr_un &usaddr, string path)
{
    usaddr.sun_family=AF_LOCAL;
    strcpy(usaddr.sun_path,path.c_str());
}
ssize_t sock_fd_write(int sock, void *buf, ssize_t buflen, int fd)
{
    ssize_t     size;
    struct msghdr   msg;
    struct iovec    iov;
    union {
        struct cmsghdr  cmsghdr;
        char        control[CMSG_SPACE(sizeof (int))];
    } cmsgu;
    struct cmsghdr  *cmsg;

    iov.iov_base = buf;
    iov.iov_len = buflen;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    if (fd != -1) {
        msg.msg_control = cmsgu.control;
        msg.msg_controllen = sizeof(cmsgu.control);

        cmsg = CMSG_FIRSTHDR(&msg);
        cmsg->cmsg_len = CMSG_LEN(sizeof (int));
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;

        printf ("passing fd %d\n", fd);
        *((int *) CMSG_DATA(cmsg)) = fd;
    } else {
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
        printf ("not passing fd\n");
    }

    size = sendmsg(sock, &msg, 0);

    if (size < 0)
        perror ("sendmsg");
    return size;
}
ssize_t sock_fd_read(int sock, void *buf, ssize_t bufsize, int *fd)
{
    ssize_t     size;

    if (fd) {
        struct msghdr   msg;
        struct iovec    iov;
        union {
            struct cmsghdr  cmsghdr;
            char        control[CMSG_SPACE(sizeof (int))];
        } cmsgu;
        struct cmsghdr  *cmsg;

        iov.iov_base = buf;
        iov.iov_len = bufsize;

        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = cmsgu.control;
        msg.msg_controllen = sizeof(cmsgu.control);
        size = recvmsg(sock,&msg,0);
        if (size < 0) {
            perror ("recvmsg");
            exit(1);
        }
        cmsg = CMSG_FIRSTHDR(&msg);
        if (cmsg && cmsg->cmsg_len == CMSG_LEN(sizeof(int))) {
            if (cmsg->cmsg_level != SOL_SOCKET) {
                fprintf (stderr, "invalid cmsg_level %d\n",
                     cmsg->cmsg_level);
                exit(1);
            }
            if (cmsg->cmsg_type != SCM_RIGHTS) {
                fprintf (stderr, "invalid cmsg_type %d\n",
                     cmsg->cmsg_type);
                exit(1);
            }

            *fd = *((int *) CMSG_DATA(cmsg));
            printf ("received fd %d\n", *fd);
        } else
            *fd = -1;
    } else {
        size = read (sock, buf, bufsize);
        if (size < 0) {
            perror("read");
            exit(1);
        }
    }
    return size;
}
