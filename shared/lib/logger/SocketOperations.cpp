#include "../includes/SocketOperations.h"

SocketOperations *SocketOperations::instance = 0;

SocketOperations::SocketOperations()
{

}

SocketOperations* SocketOperations::GetInstance()
{
    if(!instance)
        instance = new SocketOperations;
    return instance;
}

std::string SocketOperations::GetMessage(int workingSocket)
{
    char* initialBuffer = (char*)malloc(5*sizeof(char));
    initialBuffer = "1234";
    std::cout << initialBuffer;
    return "";
}

bool SocketOperations::SendMessage(int workingSocket, std::string msg)
{
    return true;
}
// std::string SocketOperations::GetSocketMessage(int clientSocket)
// {
//     bzero (msg, 100);
//     printf ("[server]Asteptam mesajul...\n");
//     fflush (stdout);
      
//     /* citirea mesajului */
//     if (read (client, msg, 100) <= 0)
// 	{
// 	  perror ("[server]Eroare la read() de la client.\n");
// 	  close (client);	/* inchidem conexiunea cu clientul */
// 	  continue;		/* continuam sa ascultam */
// 	}
	
//     printf ("[server]Mesajul a fost receptionat...%s\n", msg);
      
//     return "";
// }

// bool SocketOperations::SendMessage(int clientSocket)
// {
//     return true;
// }   