#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <pthread.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>

#include "worker.h"

namespace Tenvoy {
    namespace Server {

        void* worker_pthread_routine_wrapper(void* arg) {
            Worker* worker = static_cast<Worker*>(arg);
            worker->thread_routine();
            return nullptr;
        }

        void read_cb(struct bufferevent* bev, void* arg) {
            printf("read_cb\n");
            char buf[256];
            memset((void*)buf, 0, sizeof(buf));
            bufferevent_read(bev, (void*)buf, sizeof(buf));
            for (int i = 0; i < 256; i++) {
                if (buf[i] == '\n') {
                    break;
                }
                buf[i] = buf[i]+1;
            }
            bufferevent_write(bev, (const void*)buf, sizeof(buf));
        }

        void write_cb(struct bufferevent* bev, void* arg) {
            printf("write_cb\n");
        }

        void event_cb(struct bufferevent* bev, short events, void* arg) {
            printf("event_cb\n");
        }

        void worker_listener_callback(struct evconnlistener* listener, evutil_socket_t client_sock, struct sockaddr* remote_addr, int len, void* arg) {
            Worker* worker = static_cast<Worker*>(arg);
            printf("worker_listener_callback worker %d\n", worker->id);
            struct bufferevent* bev = bufferevent_socket_new(worker->event_base, client_sock, BEV_OPT_CLOSE_ON_FREE);
            if (bev == nullptr) {
                perror("bufferevent_socket_new");
                exit(1);
            }
            bufferevent_setcb(bev, read_cb, write_cb, event_cb, (void*)worker);
            bufferevent_enable(bev, EV_WRITE);
            bufferevent_enable(bev, EV_READ);
        }

        Worker::Worker(int id, int listen_fd) {
            this->event_base = event_base_new();
            if (event_base == nullptr) {
                perror("event_base_new");
                exit(1);
            }
            this->id = id;
            this->listen_fd = listen_fd;
        }

        void Worker::run() {
            pthread_create(&(this->thread_handle), nullptr, worker_pthread_routine_wrapper, this);
        }

        void Worker::wait() {
            pthread_join(this->thread_handle, nullptr);
        }

        void Worker::thread_routine() {
            printf("hello from worker %d\n", this->id);

            struct event* event;
            struct timeval ten_sec = {60, 0};

            evconnlistener_new(this->event_base, worker_listener_callback, this, 0/*flags*/, -1/*backlog*/, this->listen_fd);

            event = event_new(this->event_base, 0, EV_TIMEOUT|EV_PERSIST, [](evutil_socket_t fd, short what, void* arg) -> void {
                Worker* worker = static_cast<Worker*>(arg);
                printf("timer event triggered on worker %d on fd %d, ev %x\n", worker->id, fd, what);
            }, this);
            event_add(event, &ten_sec);

            event_base_dispatch(this->event_base);

            printf("bye from worker %d\n", id);
        }

    }
}
