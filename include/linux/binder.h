#pragma once
#include <cstdint>

#ifndef __u32
#define __u32 uint32_t
#endif

#ifndef __u64
#define __u64 uint64_t
#endif

#ifndef __u8
#define __u8 uint8_t
#endif

#ifndef __s32
#define __s32 int32_t
#endif

#ifdef BINDER_IPC_32BIT
typedef __u32 binder_size_t;
typedef __u32 binder_uintptr_t;
#else
typedef __u64 binder_size_t;
typedef __u64 binder_uintptr_t;
#endif

#define B_PACK_CHARS(c1,c2,c3,c4) ((((c1) << 24)) | (((c2) << 16)) | (((c3) << 8)) | (c4))
#define B_TYPE_LARGE 0x85

#ifndef SCHED_NORMAL
#define SCHED_NORMAL 0
#endif

#ifndef F_DUPFD_CLOEXEC
#define F_DUPFD_CLOEXEC 1030
#endif

#ifndef pid_t
#define pid_t int
#endif

#ifndef uid_t
#define uid_t int32_t
#endif

enum {
    BINDER_TYPE_BINDER = B_PACK_CHARS('s', 'b', '*', B_TYPE_LARGE),
    BINDER_TYPE_WEAK_BINDER = B_PACK_CHARS('w', 'b', '*', B_TYPE_LARGE),
    BINDER_TYPE_HANDLE = B_PACK_CHARS('s', 'h', '*', B_TYPE_LARGE),
    BINDER_TYPE_WEAK_HANDLE = B_PACK_CHARS('w', 'h', '*', B_TYPE_LARGE),
    BINDER_TYPE_FD = B_PACK_CHARS('f', 'd', '*', B_TYPE_LARGE),
    BINDER_TYPE_FDA = B_PACK_CHARS('f', 'd', 'a', B_TYPE_LARGE),
    BINDER_TYPE_PTR = B_PACK_CHARS('p', 't', '*', B_TYPE_LARGE),
};

enum flat_binder_object_shifts {
    FLAT_BINDER_FLAG_SCHED_POLICY_SHIFT = 9,
};

enum flat_binder_object_flags {
    FLAT_BINDER_FLAG_PRIORITY_MASK = 0xff,
    FLAT_BINDER_FLAG_ACCEPTS_FDS = 0x100,
    FLAT_BINDER_FLAG_SCHED_POLICY_MASK = 3U << FLAT_BINDER_FLAG_SCHED_POLICY_SHIFT,
    FLAT_BINDER_FLAG_INHERIT_RT = 0x800,
    FLAT_BINDER_FLAG_TXN_SECURITY_CTX = 0x1000,
};

enum transaction_flags {
    TF_ONE_WAY = 0x01,
    TF_ROOT_OBJECT = 0x04,
    TF_STATUS_CODE = 0x08,
    TF_ACCEPT_FDS = 0x10,
    TF_CLEAR_BUF = 0x20,
};

#ifndef _IOC_WRITE
#define _IOC_WRITE 1U
#endif

#define _IOC_NRBITS 8
#define _IOC_NRSHIFT 0
#define _IOC_TYPEBITS 8
#define _IOC_SIZEBITS 14
#define _IOC_NONE   0U

#define _IOC_TYPESHIFT (_IOC_NRSHIFT + _IOC_NRBITS)
#define _IOC_SIZESHIFT (_IOC_TYPESHIFT + _IOC_TYPEBITS)
#define _IOC_DIRSHIFT (_IOC_SIZESHIFT + _IOC_SIZEBITS)

#define _IOC(dir,type,nr,size) (((dir) << _IOC_DIRSHIFT) | ((type) << _IOC_TYPESHIFT) | ((nr) << _IOC_NRSHIFT) | ((size) << _IOC_SIZESHIFT))

#define _IOC_TYPECHECK(t) (sizeof(t))
#define _IOW(type,nr,size) _IOC(_IOC_WRITE, (type), (nr), (_IOC_TYPECHECK(size)))
#define _IO(type,nr)    _IOC(_IOC_NONE,(type),(nr),0)

struct binder_transaction_data {
    union {
        __u32 handle;
        binder_uintptr_t ptr;
    } target;
    binder_uintptr_t cookie;
    __u32 code;
    __u32 flags;
    pid_t sender_pid;
    uid_t sender_euid;
    binder_size_t data_size;
    binder_size_t offsets_size;
    union {
        struct {
            binder_uintptr_t buffer;
            binder_uintptr_t offsets;
        } ptr;
        __u8 buf[8];
    } data;
};

struct binder_ptr_cookie {
    binder_uintptr_t ptr;
    binder_uintptr_t cookie;
};

struct binder_pri_desc {
    __s32 priority;
    __u32 desc;
};

struct binder_handle_cookie {
    __u32 handle;
    binder_uintptr_t cookie;
};

struct binder_transaction_data_sg {
    struct binder_transaction_data transaction_data;
    binder_size_t buffers_size;
};

enum binder_driver_command_protocol {
    BC_TRANSACTION = _IOW('c', 0, struct binder_transaction_data),
    BC_REPLY = _IOW('c', 1, struct binder_transaction_data),
    BC_ACQUIRE_RESULT = _IOW('c', 2, __s32),
    BC_FREE_BUFFER = _IOW('c', 3, binder_uintptr_t),
    BC_INCREFS = _IOW('c', 4, __u32),
    BC_ACQUIRE = _IOW('c', 5, __u32),
    BC_RELEASE = _IOW('c', 6, __u32),
    BC_DECREFS = _IOW('c', 7, __u32),
    BC_INCREFS_DONE = _IOW('c', 8, struct binder_ptr_cookie),
    BC_ACQUIRE_DONE = _IOW('c', 9, struct binder_ptr_cookie),
    BC_ATTEMPT_ACQUIRE = _IOW('c', 10, struct binder_pri_desc),
    BC_REGISTER_LOOPER = _IO('c', 11),
    BC_ENTER_LOOPER = _IO('c', 12),
    BC_EXIT_LOOPER = _IO('c', 13),
    BC_REQUEST_DEATH_NOTIFICATION = _IOW('c', 14, struct binder_handle_cookie),
    BC_CLEAR_DEATH_NOTIFICATION = _IOW('c', 15, struct binder_handle_cookie),
    BC_DEAD_BINDER_DONE = _IOW('c', 16, binder_uintptr_t),
    BC_TRANSACTION_SG = _IOW('c', 17, struct binder_transaction_data_sg),
    BC_REPLY_SG = _IOW('c', 18, struct binder_transaction_data_sg),
};

struct binder_object_header {
    __u32 type;
};

struct flat_binder_object {
    struct binder_object_header hdr;
    __u32 flags;
    union {
        binder_uintptr_t binder;
        __u32 binder_internal_handle;
    };
    binder_uintptr_t cookie;
};

namespace porting_binder
{
    void close_binder( __u32 handle );
    __u32 fcntl_binder( __u32 handle, uint32_t to_operation, uint32_t parameters);
}
