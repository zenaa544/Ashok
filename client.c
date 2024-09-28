
/*Client Program*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2222

/*Message Types*/

#define BEGASEP_OPEN     0x1
#define BEGASEP_ACCEPT   0x2
#define BEGASEP_BET      0x3
#define BEGASEP_RESULT   0x4

#define BEGASEP_NUM_CLIENTS 40
#define BEGASEP_NUM_MIN  100 // 0xE0FFFF00
#define BEGASEP_NUM_MAX  900 // 0xE0FFFFAA

#define PROTOCOL_VERSION  0x1

typedef struct Begasep_CommonHeader
	{
		uint8_t   Version:3;/*Protocol Version*/
		uint8_t   Length:5;
		uint8_t   Type;
		uint16_t  Client_id;
	}Begasep_CommonHeader;
typedef struct Begasep_AcceptMsg
	{
		int LowerLimit;
		int UpperLimit;
	}Begasep_Accept;
typedef struct Begasep_BetMsg
	{
		int Bet_num;

	}Begasep_Bet;
typedef struct Begasep_ResultMsg 
	{
		uint8_t status;
		int Win_num;
	}Begasep_Result;

void getHeader(uint8_t protocol_Version,uint8_t msg_Length,uint8_t msg_Type,uint16_t client_Id ,Begasep_CommonHeader* msg_Header) 
	{
		msg_Header->Version=protocol_Version;
        	msg_Header->Length=msg_Length;
              	msg_Header->Type=msg_Type;
		msg_Header->Client_id=client_Id;

	}

int main(int argc , char* argv[])
{
	int client_socket;
	int readBytes;
	int connectionStatus;
      	int Result_Received;
 
	Begasep_Accept Accept_Msg;
	Begasep_Bet  Bet_Msg;
        Begasep_Result Result_Msg;
        int ResultReceived=0;
	struct sockaddr_in address_Server;

	Begasep_CommonHeader Send_Header;
	Begasep_CommonHeader Recv_Header;
        
	if(argc!=2)
	{
		fprintf(stderr,"\nusage :client srever IP\n");
		exit(1);
	}
	
	if((client_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Client:socket error");
		fprintf(stderr,"Client:socket failure\n");
		exit(1);
	}
        
	memset(&address_Server,'\0',sizeof(address_Server));
        address_Server.sin_family=AF_INET;
	address_Server.sin_port=htons(PORT);
	address_Server.sin_addr.s_addr=inet_addr(argv[1]);
	
	connectionStatus=connect(client_socket,(struct sockaddr*)&address_Server,sizeof(address_Server));
	
	if(connectionStatus==-1)
	{
	        perror("Client:Conecction error");
		fprintf(stderr,"Client : connet failure server Ip %s\n",argv[1]);
	        exit(1);		
	}
	
	memset(&Send_Header,'\0',sizeof(Send_Header));
	getHeader(PROTOCOL_VERSION,sizeof(Send_Header),BEGASEP_OPEN,0,&Send_Header);
        
	if(send(client_socket,(Begasep_CommonHeader*)&Send_Header,sizeof(Send_Header),0)==-1)
	{
	        perror("Client:Send Error\n");
                fprintf(stderr,"client :Send Error\n");
        }
		 
	Result_Received=0;	
	while(1)
	{
                memset(&Recv_Header,'\0',sizeof(Recv_Header));
		if((recv(client_socket,&Recv_Header,sizeof(Recv_Header),0))==-1)
		{
			perror("Client:recv Error");
		        fprintf(stderr,"Client: Recv Errori\n");
		}
	
		printf("\n Client Recieved: Version=%d MessageType =%d Packet Length=%d ClientId=%d\n",Recv_Header.Version,Recv_Header.Type,Recv_Header.Type,Recv_Header.Client_id);	
		switch(Recv_Header.Type)
        	{ 

       			 case BEGASEP_ACCEPT:
	          
      		        	memset(&Accept_Msg,'\0',sizeof(Accept_Msg));	
	       			if((recv(client_socket,&Accept_Msg,sizeof(Accept_Msg),0))==-1) 
    	       		        {
					perror("Client :recv Error");		 		 
                    			fprintf(stderr,"Client :recv error\n"); 
                                }
				printf("\n lower limit %d upperi limit %d ",Accept_Msg.LowerLimit,Accept_Msg.UpperLimit);
			        
                                memset(&Bet_Msg,'\0',sizeof(Bet_Msg));
				printf("\n Enter your Bet between %d and %d :: \n",Accept_Msg.LowerLimit,Accept_Msg.UpperLimit);
				scanf("%d",&(Bet_Msg.Bet_num));
			        printf("\n Debug: bet number :%d \n",Bet_Msg.Bet_num); 	
				getHeader(PROTOCOL_VERSION,sizeof(Send_Header)+sizeof(Bet_Msg),BEGASEP_BET,Recv_Header.Client_id,&Send_Header);

				if(send(client_socket,(Begasep_CommonHeader*)&Send_Header,sizeof(Send_Header),0)==-1)
                                                perror("Client:send error");
                                if(send(client_socket,(Begasep_Bet*)&Bet_Msg,sizeof(Bet_Msg),0)==-1)
                                                perror("Client:send error");
				printf("\n Client Sent: Version=%d MessageType =%d Packet Length=%d ClientId=%d\n",Send_Header.Version,Send_Header.Type,Send_Header.Type,Send_Header.Client_id);
                                 
				
				break;

		          case BEGASEP_RESULT:			
                          	
				memset(&Result_Msg,'\0',sizeof(Accept_Msg));	
				if((recv(client_socket,&Result_Msg,sizeof(Result_Msg),0))==-1)
                                {
                                        perror("Client :recv Error");
                                        fprintf(stderr,"Client :recv error\n");
                                }
				
				printf("\n Received Result : result status :%d winning Number:%d \n",Result_Msg.status,Result_Msg.Win_num);
				
				if(Result_Msg.status==1)
				printf("\n Congratulations You Won!!\n");
				else
				printf("\n You lost the bet!!\n"); 
                                
				Result_Received=1;
				break;	
                 }/*switch*/
			
		if(Result_Received==1)
		break;
	}/*while*/

	close(client_socket);

}/*main*/
			
