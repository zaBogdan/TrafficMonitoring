#include "Message.h"

Message *Message::instance = 0;

Message::Message()
{

}

Message* Message::GetInstance()
{
    if(!instance)
        instance = new Message;
    return instance;
}

std::string Message::Format(std::string msg)
{
    std::string formatedMessage = BTRShared::Commands::Evaluate(msg);
    if(formatedMessage == "")
    {
        return "";
    }
    //adding the formatter (here I should get the internal state of the app too - for login)
    formatedMessage = MESSAGE_SEPARATOR + formatedMessage;
    
    //prefixing the message with it's length
    std::string messageLength = std::to_string(formatedMessage.length());
    messageLength.insert(0, 4-messageLength.length(),'0');
    formatedMessage = messageLength+formatedMessage;

    //returning the message
    return formatedMessage;
}

char* Message::Parse(const char* msg)
{
    char* data = new char[10];
    Logger::Debug(msg);
    return (char*)data;
}
// https://www.youtube.com/watch?v=Y6pFtgRdUts
// std::string Message::GetSocketMessage(int clientSocket)
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

// bool Message::SendMessage(int clientSocket)
// {
//     return true;
// }   