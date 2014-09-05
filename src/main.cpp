#include "main.h"

using Gemino::Core::Socket;
using Gemino::Core::Http;
using std::vector;

typedef struct {
    unsigned char version;
    unsigned char type;
    unsigned char requestIdB1;
    unsigned char requestIdB0;
    unsigned char contentLength;
    unsigned char contentLengthB1;
    unsigned char contentLengthB0;
    unsigned char paddingLength;
    unsigned char reserved;
    unsigned char contentData[65535];
    unsigned char paddingData[255];
} FCGI_Record;

void processClient(Socket *&Client) {
    FCGI_Record *data = (FCGI_Record*)Client->Read(1000);
    printf("%d\n", data->type);

    Client->Write("CGI/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n");
}

void clearZombies(std::vector<pid_t> &pids) {
    vector<pid_t>::iterator pidIterator = pids.begin();
    int status;
    pid_t wpid;
    while (pidIterator != pids.end()) {
        wpid = waitpid(*pidIterator, &status, WNOHANG);
        if (wpid == *pidIterator && WIFEXITED(status)) {
            pidIterator = pids.erase(pidIterator);
            continue;
        }
        ++pidIterator;
    }
}

int main(void) {
    try {
        Http *Server = new Http();

        Socket *Client;

        vector<pid_t> pids;
        pid_t pid, wpid;
        int status;
        while (1) {
            do {
                clearZombies(pids);
            } while (pids.size() >= MAX_NUM_PROC);

            Client = Server->Accept();

            pid = fork();
            if (pid == 0) {
                delete Server;
                Server = NULL;

                processClient(Client);
                delete Client;
                Client = NULL;

                _exit(0);
            } else if (pid > 0) {
                Client = NULL;

                wpid = waitpid(pid, &status, WNOHANG);
                if ((wpid == pid && !WIFEXITED(status)) || wpid == 0) {
                    pids.push_back(pid);
                }
            }
        }
    } catch (int e) {
        // TODO
    }

    return 0;
}
