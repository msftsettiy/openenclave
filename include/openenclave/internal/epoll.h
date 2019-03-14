
/* Copyright (c) Microsoft Corporation. All rights reserved. */
/* Licensed under the MIT License. */

#ifndef _OE_EPOLL_H
#define _OE_EPOLL_H

#include <openenclave/internal/device.h>

OE_EXTERNC_BEGIN

enum OE_EPOLL_EVENTS
{
    OE_EPOLLIN = 0x001,
    OE_EPOLLPRI = 0x002,
    OE_EPOLLOUT = 0x004,
    OE_EPOLLRDNORM = 0x040,
    OE_EPOLLRDBAND = 0x080,
    OE_EPOLLWRNORM = 0x100,
    OE_EPOLLWRBAND = 0x200,
    OE_EPOLLMSG = 0x400,
    OE_EPOLLERR = 0x008,
    OE_EPOLLHUP = 0x010,
    OE_EPOLLRDHUP = 0x2000,
    OE_EPOLLEXCLUSIVE = 1u << 28,
    OE_EPOLLWAKEUP = 1u << 29,
    OE_EPOLLONESHOT = 1u << 30,
    OE_EPOLLET = 1u << 31
};

oe_device_t* oe_epoll_get_epoll(void);

int oe_register_epoll_device(void);

OE_PACK_BEGIN
typedef struct _oe_device_notifications
{
    uint32_t event_mask; // oe_epoll_event.event
    union {
        uint64_t data;
        struct
        {
            uint32_t epoll_fd; // Enclave fd for the
            uint32_t
                list_idx; // On the host side we set this into the event data
        };
    };
} oe_device_notifications_t;
OE_PACK_END

struct oe_device_notification_args
{
    uint64_t num_notifications;
    // struct oe_device_notifications events[];
};

oe_result_t _handle_oe_device_notification(uint64_t args);

/* internal signalling */
void oe_signal_device_notification(oe_device_t* pdevice, uint32_t event_mask);

void oe_broadcast_device_notification(void);
int oe_wait_device_notification(int timeout);
void oe_clear_device_notification(void);

#define OE_EPOLL_CTL_ADD 1 /* Add a file descriptor to the interface. */
#define OE_EPOLL_CTL_DEL 2 /* Remove a file descriptor from the interface. */
#define OE_EPOLL_CTL_MOD \
    3 /* Change file descriptor oe_epoll_event structure. */

typedef union oe_epoll_data {
    void* ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
} oe_epoll_data_t;

typedef union _oe_ev_data {
    struct
    {
        uint32_t epoll_enclave_fd;
        uint32_t event_list_idx;
    };
    uint64_t data;
} oe_ev_data_t;

OE_PACK_BEGIN
struct oe_epoll_event
{
    uint32_t events;      /* Epoll events */
    oe_epoll_data_t data; /* User data variable */
};
OE_PACK_END

int oe_epoll_create(int size);
int oe_epoll_create1(int flags);
int oe_epoll_ctl(int epfd, int op, int fd, struct oe_epoll_event* event);
int oe_epoll_wait(
    int epfd,
    struct oe_epoll_event* events,
    int maxevents,
    int timeout);

// int oe_epoll_pwait (int epfd, struct epoll_event *events, int maxevents,
// int timeout, const sigset_t *ss);

void oe_handle_hostepoll_ocall(void* args_);

OE_EXTERNC_END

#endif /* _OE_EPOLL_H */