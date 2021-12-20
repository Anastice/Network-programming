#include "net_util.h"

using namespace std;

int main(int argc,char* argv[])
{
//  Declare variables
    SOCKET openedSocket;
    struct sockaddr_in scanAddr;

//  Init variables
    WSADATA wsd;
    if(WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
    {
        printf("Can't startup WSA Library");
    }
    memset(&scanAddr, 0, sizeof(sockaddr_in));
    openedSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    scanAddr.sin_family = AF_INET;
    scanAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    printf("|\tPort\t|\tStatus\t\t|\tWSAErrorCode\t\t|\n");
    for(short port = 5149; port < 6000; ++port)
    {
        scanAddr.sin_port = htons(port);
        short res = connect(openedSocket, (struct sockaddr *)&scanAddr, sizeof(scanAddr));
        if(res < 0)
        {
//            printf("Port %d is in use. %d \n %d\n", ip, res, WSAGetLastError());
            printf("|\t%d\t|\t%s\t|\t%d\t|\n", port, "Can't connect", WSAGetLastError());
        }
        else
        {
//            printf("Port %d is free. %d \n %d\n", ip, res, WSAGetLastError());
            printf("|\t%d\t|\t%s\t|\t%d\t|\n", port, "Connected", WSAGetLastError());
        }
    }
    char c;
    cin >> c;
    WSACleanup();
    closesocket(openedSocket);
    return 0;
}
