#include <iostream>

#include "manager.h"

namespace Tenvoy {
    namespace Server {

        Manager::Manager() {
            for (int i = 0; i < 8; i++) {
                auto worker = std::make_unique<Worker>();
                workers.push_back(std::move(worker));
            }
        }

        void Manager::run() {
            std::cout << "Manager starting" << std::endl;
            for (const auto& worker : workers) {
                worker->run();
            }
        }

    }
}
