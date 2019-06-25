#include <iostream>

#include <event2/event.h>
#include <event2/listener.h>

#include "manager.h"

namespace Tenvoy {
    namespace Server {

        Manager::Manager() {

            int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
            if (listen_fd < 0) {
                perror("socket");
                exit(1);
            }
            struct sockaddr_in serv_addr;
            memset(&serv_addr, 0, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_addr.s_addr = 0;
            serv_addr.sin_port = htons(7009);
            if (bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
                perror("bind");
                exit(1);
            }
            evutil_make_socket_nonblocking(listen_fd);

            event_base = event_base_new();
            if (event_base == nullptr) {
                perror("event_base_new");
                exit(1);
            }
            for (int i = 0; i < 3; i++) {
                auto worker = std::make_unique<Worker>(i, listen_fd);
                workers.push_back(std::move(worker));
            }
        }

        void Manager::run() {
            std::cout << "Manager starting" << std::endl;
            for (const auto& worker : workers) {
                worker->run();
            }
            for (const auto& worker : workers) {
                worker->wait();
            }
            std::cout << "Manager exiting" << std::endl;
        }

    }
}
