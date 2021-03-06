#include<stdlib.h>
#include<stdio.h>
#include"logger.h"
#include"event_loop.h"
#include"macro.h"
#include"epoll.h"

event_loop* event_loop_create()
{
    event_loop* loop = (event_loop*)duo_malloc(sizeof(event_loop));
    if (loop == NULL) {
        debug_ret("create event loop failed, file : %s, line : %d", __FILE__, __LINE__);
        return NULL;
    }
    loop->epoll_fd = epoller_create();
    if (loop->epoll_fd == -1) {
        debug("epoller_create failed, file: %s, line : %d", __FILE__, __LINE__);
        duo_free(loop);
        return NULL;
    }
    return loop;
}

void event_loop_run(event_loop* e) 
{
    int timeout = -1;
    while(1) 
    {
        epoller_dispatch(e->epoll_fd, timeout);
    }
}