//Itay Elyashev 212356364
//Yonadav Leibowitz 207424490
#include "Server.h"

string socketIO::read() {
    char c = 0;
    string s = "";
    while (c != '\n') {
        recv(clientID, &c, sizeof(char), 0);
        s += c;
    }
    return s;
}

void socketIO::write(string text) {
    const char *buffer = text.c_str();
    //send buffer through socket:
    send(clientID, buffer, strlen(buffer), 0);
}

/*
 *     ___
                ,"   "-.      Humpty Dumpty
               / _ \/_  `.          &
              ; `''O`''   \       Alice
              | ___...---  :.____ _
              :         _."|~~~~~':'
              .\""--..-"_.";
              /,-._-..-"  / ,-.
 =====;======//:_;_"-...".`.:_;====;========
 -----|-----//-(_)--|-----`.(_)----|--------
 ----.'----/_)---,--'----.---------',---,---
     |    `|/    |       |          |   |
 ____|_.;;.||____|_______|__________|___|___
  |   (()())| |     |          |      |    |
  |  ())))))) |     |          |      |    |
 ,'-))((())))-'--,--'.-----,---'----,-'----'
 | (/()))((())   |   |     |        |
 |_//|_;`=`=".___|___|_____|________|_______
 _//  : ( | \ \       |       |       |   |
`='|  | | | | :       |       |       |   |
 --'-.; | | | |---,---'----,--'.-'`---'-,-'-
     |~.~,~,~~'   |        |   |        |
 ____|__|||_______|________|___|________|___
     SSt|||
        `'='
 */
void socketIO::write(float fl) {
    ostringstream string_stream;
    string_stream << fl;
    string s(string_stream.str());
    write(s);
}

void socketIO::read(float *f) {

}


Server::Server(int port) throw(const char *) {
    stopped = false;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        throw "socket failed";

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *) &server, sizeof(server)) < 0)
        throw "bind failure";

    if (listen(fd, 3) < 0)
        throw "listen failure";
}

void sigHandler(int sigNum) {
    cout << "sidH: " << sigNum << endl;
}

/*
 * _.---.---._
 Alice            ,'     |     `.
(01-Feb-02)     ,'       |       `.
               /         :         \
              .        ,' `.        .
              :    _,-'     `-._    :
              |  ,'___       ___`.  |
              | : ' __`-   -'__ ` : |
              | | ,',.`.   ,',.`. | |
              | | `.`'_,' `._`',' | |
              | |                 | |
              | :        )        ; |
              |  \      (_       /  |
              |   \             /   |
              |    \   ,-.-.   /    |
              |    :`.  `-'  ,':    |
              |    |,|`.___,'|.|    |
              |    | :       ; |    |
              |    |  \     /  |    |
              |    |   `---'   |    |
              :    |           |    ;
               `.  | SSt       |  ,'
                 `-'           `-'
 */
void Server::start(ClientHandler &ch) throw(const char *) {
    t = new thread([&ch, this]() {
        signal(SIGALRM, sigHandler);
        while (!stopped) {
            socklen_t clientSize = sizeof(client);
            alarm(1);
            int aClient = accept(fd, (struct sockaddr *) &client, &clientSize);
            if (aClient > 0) {
                //new thread([&aClient,this,&ch](){
                ch.handle(aClient);
                close(aClient);
                //});
            }
            alarm(1);

        }
        close(fd);
    });
}

/*
 *         .'\   /`.
         .'.-.`-'.-.`.
    ..._:   .-. .-.   :_...
  .'    '-.(o ) (o ).-'    `.
 :  _    _ _`~(_)~`_ _    _  :
:  /:   ' .-=_   _=-. `   ;\  :
:   :|-.._  '     `  _..-|:   :
 :   `:| |`:-:-.-:-:'| |:'   :
  `.   `.| | | | | | |.'   .'
    `.   `-:_| | |_:-'   .'
 jgs  `-._   ````    _.-'
          ``-------''
 */
void Server::stop() {
    stopped = true;
    t->join();
}

Server::~Server() {
}
