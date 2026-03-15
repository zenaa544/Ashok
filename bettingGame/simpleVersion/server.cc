
/*Server Program*/

/****************************************************************************************************
DESCRIPTION: Betting Game Server Program  Accepts Cleints on TCP sockets and lets the
client pick a number.A random number is generated every 15 seconds and checkes against bets made by 
client and let the clients know if they won or not.
*****************************************************************************************************/

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

#define BEGASEP_NUM_CLIENTS 5 
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

fd_set Main_List;
int socket_Server;
int max_sdValue;
int num_ClientsConnected=0;
int Client_Bet[BEGASEP_NUM_CLIENTS];
int Win_num;

/***************************************************
getWinNum- Generate Random Number
****************************************************/
int getWinNum(int low,int high )
	{
		int num;
		static int j=0;
		if(j==0)	
		{srand(time(0));j=1;}
                num= (rand()%(high-low+1))+low;
		return num;
	}

/*********************************************************
getHeader : Adds Common Header to every BEGASEP Message
*********************************************************/

void getHeader(uint8_t protocol_Version,uint8_t msg_Length,uint8_t msg_Type,uint16_t client_Id ,Begasep_CommonHeader* msg_Header)
        {
                msg_Header->Version=protocol_Version;
                msg_Header->Length=msg_Length;

                msg_Header->Type=msg_Type;
                msg_Header->Client_id=client_Id;

        }

/***********************************************************************
HandleTimeout:Generate a winning number on timeout and tally with the
bets made by clients and sends the results to connected Clients.
***********************************************************************/ 
void HandleTimeout(fd_set* readfd_ptr)
	{
		int i;
		int Win_num;
		Begasep_CommonHeader Send_Header;
		Begasep_Result Result_Msg;
		
	        printf("\n Time Out!!\n");	
		Win_num=getWinNum(BEGASEP_NUM_MIN,BEGASEP_NUM_MAX);
		for(i=1;i<=max_sdValue;i++)
		{			
			memset(&Send_Header,'\0',sizeof(Send_Header));
			memset(&Result_Msg,'\0',sizeof(Result_Msg));
		       	if(Client_Bet[i])
		        {
				if(i==socket_Server)
				{
					printf("\nServer Timeout\n");
				}
				else
				{
                               		if(Client_Bet[i]==-1)
					{
						printf("\n invalid number sock %d\n",i);	
						close(i);
						FD_CLR(i,&Main_List);
						num_ClientsConnected--;
					}
					else
					{
						if(Client_Bet[i]==Win_num)
						{
							Result_Msg.status=1;
						}
						else
						{
							Result_Msg.status=0;
						}
				
						Result_Msg.Win_num=Win_num;
						getHeader(PROTOCOL_VERSION,sizeof(Result_Msg)+sizeof(Send_Header),BEGASEP_RESULT,i,&Send_Header);
						if(send(i,(Begasep_CommonHeader*)&Send_Header,sizeof(Send_Header),0)==-1)
                                                perror("Server:send error");
                               			if(send(i,(Begasep_Result*)&Result_Msg,sizeof(Result_Msg),0)==-1)
                                       		         perror("Server:send error");
                                       		printf("\n Server Timeout  :Sent Result Client ID=%d Winning Num =%d Status= %d\n",i,Win_num,Result_Msg.status); 
						close(i);
						FD_CLR(i,&Main_List);
						FD_CLR(i,readfd_ptr);
						Client_Bet[i]=0;	
						num_ClientsConnected--;
					}	
				}	
			}
			



		  }
	
		 for(i=0;i<=BEGASEP_NUM_CLIENTS;i++)
      		 {
               		 Client_Bet[i]=0;
       		 }

		
	}


/****************************************************************************************
ServerMessageHandler: Handles the OPEN and BET messages from connected Clients
BEGASEP_OPEN : Responded with the betting range to the Client
BEGASEp_BET : Update the Client bet data
************************************************************************************/

void ServerMessageHandler(int sock_fd)
	{
		int Client_ID;
		Begasep_CommonHeader Recv_Header;
	        Begasep_CommonHeader Send_Header;
		Begasep_Accept Accept_Msg;
		Begasep_Bet Bet_Msg;	
		memset(&Recv_Header,'\0',sizeof(Recv_Header));
		if((recv(sock_fd,&Recv_Header,sizeof(Recv_Header),0))<=0)
	        {
			perror("Server:recv error");
			fprintf(stderr,"Server: recv error");
			close(sock_fd);
			FD_CLR(sock_fd,&Main_List);
			num_ClientsConnected--;
		}				
		else
		{
			switch(Recv_Header.Type)
		        {
				case BEGASEP_OPEN:
				{
					Client_ID=sock_fd;    /*Unique Client ID= socket ID*/
					memset(&Accept_Msg,'\0',sizeof(Accept_Msg));
					memset(&Send_Header,'\0',sizeof(Send_Header));
					Accept_Msg.LowerLimit=BEGASEP_NUM_MIN;
					Accept_Msg.UpperLimit=BEGASEP_NUM_MAX;
					getHeader(PROTOCOL_VERSION,sizeof(Accept_Msg)+sizeof(Send_Header),BEGASEP_ACCEPT,Client_ID,&Send_Header);
					
					if(send(sock_fd,(Begasep_CommonHeader*)&Send_Header,sizeof(Send_Header),0)==-1)
						perror("Server:send error");
					if(send(sock_fd,(Begasep_Accept*)&Accept_Msg,sizeof(Accept_Msg),0)==-1)
						perror("Server:send error");
					printf("\n Server Sent: ClientID= %d Version =%d MessageType =%d MessageLength =%d \n",Client_ID,Send_Header.Version,Send_Header.Type,Send_Header.Length);
					
					break;
				}
				case BEGASEP_BET:
				{
					memset(&Bet_Msg,'\0',sizeof(Bet_Msg));
					if((recv(sock_fd,&Bet_Msg,sizeof(Bet_Msg),0))<=0)		
					{	perror("Server:recv error");
       		                        	fprintf(stderr,"Server: recv error");
						exit(1);
					}
					printf("\n Server: receved Bet from Client :bet=%d\n",Bet_Msg.Bet_num);	
                                        if((Bet_Msg.Bet_num<=BEGASEP_NUM_MIN)||(Bet_Msg.Bet_num>=BEGASEP_NUM_MAX))
					{
						Client_Bet[sock_fd]=-1;
					       	close(sock_fd);
						FD_CLR(sock_fd,&Main_List);
						num_ClientsConnected--;
					}
					else
					{
						Client_Bet[sock_fd]=Bet_Msg.Bet_num;
					}
					break;	

				}	
			}			
		}	
	}

/*********************************************************************************************
HandleNewConnectionReq: Called whenever a new client connection is received on server socket
accepts the connection.Terminates the onnection if MAX numer of clients has reached.
***********************************************************************************************/
void HandleNewConnectionReq()
	{
		int addrLen;
		int newSd;
		struct sockaddr_in address_newClient;
		addrLen=sizeof(address_newClient);
		memset(&address_newClient,'\0',addrLen);
		if((newSd=accept(socket_Server,(struct sockaddr*)&address_newClient,&addrLen))==-1)
                {
                	perror("Server:accept error");
                        fprintf(stderr,"Server:accept error\n");
                } 
                else
		{
                	if(num_ClientsConnected>BEGASEP_NUM_CLIENTS)
                        {
                       		printf("\n Server:Max number of Client exceeded,closing connection\n");
                                close(newSd);
                        } 
                        else
                        {
                                FD_SET(newSd,&Main_List);
                                if(newSd>max_sdValue)
                                max_sdValue=newSd;
                                num_ClientsConnected++;

				printf("\n Server: New Client Connected  socket =%d ,Address=%s\n",newSd,inet_ntoa(address_newClient.sin_addr));
                         }
                }

	}
	
/**************************************************************************
HandleClientRequest: Generic function Handle requests from all clients.
***************************************************************************/
void  HandleClientRequest(fd_set* readfd_ptr)
{
 	int newConnection;
	int addrLen;
	int i; 

        if(FD_ISSET(socket_Server,readfd_ptr))
	{
		HandleNewConnectionReq();
        }
	
	for (i=0;i<=max_sdValue;i++)
	{
		if(FD_ISSET(i,readfd_ptr))
	        {
			printf("\n sock %d is set\n",i);
			if(i==socket_Server)
			{
				/*HandleNewConnectionReq();*/
			}
			else
			{
				ServerMessageHandler(i);
			} 
		}
	
	}
}
  int main()
{
        int Event;
	int addrLen;
	int readBytes;
	int sentBytes;
	int opt=1;	
	struct sockaddr_in address_Server ;
	struct sockaddr_in address_Client ;
	
	fd_set readFds;
	
	struct timeval timeout;

	FD_ZERO(&readFds);
	FD_ZERO(&Main_List);
         
	int i;                   
        
	for(i=0;i<=BEGASEP_NUM_CLIENTS;i++)
	{
		Client_Bet[i]=0;	
	}
	
	if((socket_Server=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Server:SOCket Error");
		fprintf(stderr,"Server:socket Error\n");
		exit(1);
	}

	if(setsockopt(socket_Server,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt))==-1)
        {
                perror("Server:setsocket error");
                exit(1);
        }

	
	memset(&address_Server,'\0',sizeof(address_Server));	
	address_Server.sin_family=AF_INET;
	address_Server.sin_addr.s_addr=INADDR_ANY;
	address_Server.sin_port=htons(PORT);



	if(bind(socket_Server,(struct sockaddr*)&address_Server,sizeof(address_Server))==-1)
	{
		perror("Server:bind error");
	        fprintf(stderr,"Server:bind error\n");
		exit(1);
	}
	if(listen(socket_Server,5)==-1)
	{
		perror("Server:listen error");
		fprintf(stderr,"Server:listen error\n");
		exit(1);	
	}
	
	printf("\n Server Ready ,Waiting for Clients\n");
        max_sdValue=socket_Server; 	
	FD_SET(socket_Server,&Main_List);
	while(1)
	{
		timeout.tv_sec=15;
		timeout.tv_usec=0;
			
		readFds=Main_List;
		
	        /*Wait for any request from client or the the time out event*/ 		
		if((Event=select(max_sdValue+1,&readFds,NULL,NULL,&timeout))<0)
		{
			perror("Server:select error");
			fprintf(stderr,"Server:select error\n");
			exit(1);				
		}
		printf("\n main select Event=%d\n",Event);
		if(Event==0)/*If Event is Timeout on select*/
		{
			HandleTimeout(&readFds);
		}
		
		        HandleClientRequest(&readFds);	
	
	}		
}






















