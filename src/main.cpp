#include "main.h"

using Gemino::Socket;
using std::vector;

void processClient(Socket *Client) {
    char* request = Client->Read(10);
    printf("%s\n", request);

    Client->Write("Lorem ipsum dolor sit amet");
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
        Socket *Server = new Socket(AF_INET, SOCK_STREAM, 0);

        Socket *Client;

        Server->Bind(5005);
        Server->Listen();

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
