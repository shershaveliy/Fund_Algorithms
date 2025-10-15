#include <stddef.h>

#if defined(_WIN32) || defined(_WIN64)
    static const char *error_messages[] = {
        "Success",                                  // 0
        "Operation not permitted",                  // 1 EPERM
        "No such file or directory",                // 2 ENOENT
        "No such process",                          // 3 ESRCH
        "Interrupted function",                     // 4 EINTR
        "Input/output error",                       // 5 EIO
        "No such device or address",                // 6 ENXIO
        "Argument list too long",                   // 7 E2BIG
        "Exec format error",                        // 8 ENOEXEC
        "Bad file number",                          // 9 EBADF
        "No spawned processes",                     // 10 ECHILD
        "No more processes or not enough memory",   // 11 EAGAIN
        "Not enough memory",                        // 12 ENOMEM
        "Permission denied",                        // 13 EACCES
        "Bad address",                              // 14 EFAULT
        "Unknown error",                            // 15
        "Device or resource busy",                  // 16 EBUSY
        "File exists",                              // 17 EEXIST
        "Cross-device link",                        // 18 EXDEV
        "No such device",                           // 19 ENODEV
        "Not a directory",                          // 20 ENOTDIR
        "Is a directory",                           // 21 EISDIR
        "Invalid argument",                         // 22 EINVAL
        "Too many files open in system",            // 23 ENFILE
        "Too many open files",                      // 24 EMFILE
        "Inappropriate I/O control operation",      // 25 ENOTTY
        "Text file busy",                           // 26 ETXTBSY
        "File too large",                           // 27 EFBIG
        "No space left on device",                  // 28 ENOSPC
        "Invalid seek",                             // 29 ESPIPE
        "Read-only file system",                    // 30 EROFS
        "Too many links",                           // 31 EMLINK
        "Broken pipe",                              // 32 EPIPE
        "Math argument",                            // 33 EDOM
        "Result too large",                         // 34 ERANGE
        "Resource deadlock would occur",            // 35 EDEADLOCK
        "Resource deadlock would occur",            // 36 EDEADLK
        "Unknown error",                            // 37
        "Filename too long",                        // 38 ENAMETOOLONG
        "No locks available",                       // 39 ENOLCK
        "Function not supported",                   // 40 ENOSYS
        "Directory not empty",                      // 41 ENOTEMPTY
        "Illegal sequence of bytes",                // 42 EILSEQ
        "No message of desired type",               // 43 ENOMSG
        "Identifier removed",                       // 44 EIDRM
        "Channel number out of range",              // 45 ECHRNG
        "Level 2 not synchronized",                 // 46 EL2NSYNC
        "Level 3 halted",                           // 47 EL3HLT
        "Level 3 reset",                            // 48 EL3RST
        "Link number out of range",                 // 49 ELNRNG
        "Protocol driver not attached",             // 50 EUNATCH
        "No CSI structure available",               // 51 ENOCSI
        "Level 2 halted",                           // 52 EL2HLT
        "Invalid exchange",                         // 53 EBADE
        "Invalid request descriptor",               // 54 EBADR
        "Exchange full",                            // 55 EXFULL
        "No anode",                                 // 56 ENOANO
        "Invalid request code",                     // 57 EBADRQC
        "Invalid slot",                             // 58 EBADSLT
        "Bad font file format",                     // 59 EBFONT
        "Device not a stream",                      // 60 ENOSTR
        "No data available",                        // 61 ENODATA
        "Timer expired",                            // 62 ETIME
        "Out of streams resources",                 // 63 ENOSR
        "Machine is not on the network",            // 64 ENONET
        "Package not installed",                    // 65 ENOPKG
        "Object is remote",                         // 66 EREMOTE
        "Link has been severed",                    // 67 ENOLINK
        "Advertise error",                          // 68 EADV
        "Srmount error",                            // 69 ESRMNT
        "Communication error on send",              // 70 ECOMM
        "Protocol error",                           // 71 EPROTO
        "Multihop attempted",                       // 72 EMULTIHOP
        "RFS specific error",                       // 73 EDOTDOT
        "Bad message",                              // 74 EBADMSG
        "Value too large for defined data type",    // 75 EOVERFLOW
        "Name not unique on network",               // 76 ENOTUNIQ
        "File descriptor in bad state",             // 77 EBADFD
        "Remote address changed",                   // 78 EREMCHG
        "Can not access a needed shared library",   // 79 ELIBACC
        "String copy resulted in truncation",       // 80 STRUNCATE
        "Accessing a corrupted shared library",     // 81 ELIBBAD
        ".lib section in a.out corrupted",          // 82 ELIBSCN
        "Attempting to link in too many shared libraries", // 83 ELIBMAX
        "Cannot exec a shared library directly",    // 84 ELIBEXEC
        "Invalid or incomplete multibyte or wide character", // 85 EILSEQ
        "Interrupted system call should be restarted", // 86 ERESTART
        "Streams pipe error",                       // 87 ESTRPIPE
        "Too many users",                           // 88 EUSERS
        "Socket operation on non-socket",           // 89 ENOTSOCK
        "Destination address required",             // 90 EDESTADDRREQ
        "Message too long",                         // 91 EMSGSIZE
        "Protocol wrong type for socket",           // 92 EPROTOTYPE
        "Protocol not available",                   // 93 ENOPROTOOPT
        "Protocol not supported",                   // 94 EPROTONOSUPPORT
        "Socket type not supported",                // 95 ESOCKTNOSUPPORT
        "Operation not supported",                  // 96 ENOTSUP
        "Protocol family not supported",            // 97 EPFNOSUPPORT
        "Address family not supported by protocol", // 98 EAFNOSUPPORT
        "Address already in use",                   // 99 EADDRINUSE
        "Address in use",                           // 100 EADDRINUSE
        "Address not available",                    // 101 EADDRNOTAVAIL
        "Address family not supported",             // 102 EAFNOSUPPORT
        "Connection already in progress",           // 103 EALREADY
        "Bad message",                              // 104 EBADMSG
        "Operation canceled",                       // 105 ECANCELED
        "Connection aborted",                       // 106 ECONNABORTED
        "Connection refused",                       // 107 ECONNREFUSED
        "Connection reset",                         // 108 ECONNRESET
        "Destination address required",             // 109 EDESTADDRREQ
        "Host unreachable",                         // 110 EHOSTUNREACH
        "Identifier removed",                       // 111 EIDRM
        "Operation in progress",                    // 112 EINPROGRESS
        "Already connected",                        // 113 EISCONN
        "Too many symbolic link levels",            // 114 ELOOP
        "Message size",                             // 115 EMSGSIZE
        "Network down",                             // 116 ENETDOWN
        "Network reset",                            // 117 ENETRESET
        "Network unreachable",                      // 118 ENETUNREACH
        "No buffer space",                          // 119 ENOBUFS
        "No message available",                     // 120 ENODATA
        "No link",                                  // 121 ENOLINK
        "No message",                               // 122 ENOMSG
        "No protocol option",                       // 123 ENOPROTOOPT
        "No stream resources",                      // 124 ENOSR
        "Not a stream",                             // 125 ENOSTR
        "Not connected",                            // 126 ENOTCONN
        "State not recoverable",                    // 127 ENOTRECOVERABLE
        "Not a socket",                             // 128 ENOTSOCK
        "Not supported",                            // 129 ENOTSUP
        "Operation not supported",                  // 130 EOPNOTSUPP
        "Other",                                    // 131 EOTHER
        "Value too large",                          // 132 EOVERFLOW
        "Owner dead",                               // 133 EOWNERDEAD
        "Protocol error",                           // 134 EPROTO
        "Protocol not supported",                   // 135 EPROTONOSUPPORT
        "Wrong protocol type",                      // 136 EPROTOTYPE
        "Stream timeout",                           // 137 ETIME
        "Timed out",                                // 138 ETIMEDOUT
        "Text file busy",                           // 139 ETXTBSY
        "Operation would block",                    // 140 EWOULDBLOCK
};

#elif defined(__linux__)
    static const char *error_messages[] = {
        "Success",                                  // 0
        "Operation not permitted",                  // 1 EPERM
        "No such file or directory",                // 2 ENOENT
        "No such process",                          // 3 ESRCH
        "Interrupted system call",                  // 4 EINTR
        "Input/output error",                       // 5 EIO
        "No such device or address",                // 6 ENXIO
        "Argument list too long",                   // 7 E2BIG
        "Exec format error",                        // 8 ENOEXEC
        "Bad file descriptor",                      // 9 EBADF
        "No child processes",                       // 10 ECHILD
        "Resource temporarily unavailable",         // 11 EAGAIN
        "Cannot allocate memory",                   // 12 ENOMEM
        "Permission denied",                        // 13 EACCES
        "Bad address",                              // 14 EFAULT
        "Block device required",                    // 15 ENOTBLK
        "Device or resource busy",                  // 16 EBUSY
        "File exists",                              // 17 EEXIST
        "Invalid cross-device link",                // 18 EXDEV
        "No such device",                           // 19 ENODEV
        "Not a directory",                          // 20 ENOTDIR
        "Is a directory",                           // 21 EISDIR
        "Invalid argument",                         // 22 EINVAL
        "Too many open files in system",            // 23 ENFILE
        "Too many open files",                      // 24 EMFILE
        "Inappropriate I/O control operation",      // 25 ENOTTY
        "Text file busy",                           // 26 ETXTBSY
        "File too large",                           // 27 EFBIG
        "No space left on device",                  // 28 ENOSPC
        "Illegal seek",                             // 29 ESPIPE
        "Read-only file system",                    // 30 EROFS
        "Too many links",                           // 31 EMLINK
        "Broken pipe",                              // 32 EPIPE
        "Numerical argument out of domain",         // 33 EDOM
        "Numerical result out of range",            // 34 ERANGE
        "Resource deadlock avoided",                // 35 EDEADLK
        "File name too long",                       // 36 ENAMETOOLONG
        "No locks available",                       // 37 ENOLCK
        "Function not implemented",                 // 38 ENOSYS
        "Directory not empty",                      // 39 ENOTEMPTY
        "Too many levels of symbolic links",        // 40 ELOOP
        "No message of desired type",               // 42 ENOMSG
        "Identifier removed",                       // 43 EIDRM
        "Channel number out of range",              // 44 ECHRNG
        "Level 2 not synchronized",                 // 45 EL2NSYNC
        "Level 3 halted",                           // 46 EL3HLT
        "Level 3 reset",                            // 47 EL3RST
        "Link number out of range",                 // 48 ELNRNG
        "Protocol driver not attached",             // 49 EUNATCH
        "No CSI structure available",               // 50 ENOCSI
        "Level 2 halted",                           // 51 EL2HLT
        "Invalid exchange",                         // 52 EBADE
        "Invalid request descriptor",               // 53 EBADR
        "Exchange full",                            // 54 EXFULL
        "No anode",                                 // 55 ENOANO
        "Invalid request code",                     // 56 EBADRQC
        "Invalid slot",                             // 57 EBADSLT
        "Bad font file format",                     // 59 EBFONT
        "Device not a stream",                      // 60 ENOSTR
        "No data available",                        // 61 ENODATA
        "Timer expired",                            // 62 ETIME
        "Out of streams resources",                 // 63 ENOSR
        "Machine is not on the network",            // 64 ENONET
        "Package not installed",                    // 65 ENOPKG
        "Object is remote",                         // 66 EREMOTE
        "Link has been severed",                    // 67 ENOLINK
        "Advertise error",                          // 68 EADV
        "Srmount error",                            // 69 ESRMNT
        "Communication error on send",              // 70 ECOMM
        "Protocol error",                           // 71 EPROTO
        "Multihop attempted",                       // 72 EMULTIHOP
        "RFS specific error",                       // 73 EDOTDOT
        "Bad message",                              // 74 EBADMSG
        "Value too large for defined data type",    // 75 EOVERFLOW
        "Name not unique on network",               // 76 ENOTUNIQ
        "File descriptor in bad state",             // 77 EBADFD
        "Remote address changed",                   // 78 EREMCHG
        "Can not access a needed shared library",   // 79 ELIBACC
        "Accessing a corrupted shared library",     // 80 ELIBBAD
        ".lib section in a.out corrupted",          // 81 ELIBSCN
        "Attempting to link in too many shared libraries", // 82 ELIBMAX
        "Cannot exec a shared library directly",    // 83 ELIBEXEC
        "Invalid or incomplete multibyte or wide character", // 84 EILSEQ
        "Interrupted system call should be restarted", // 85 ERESTART
        "Streams pipe error",                       // 86 ESTRPIPE
        "Too many users",                           // 87 EUSERS
        "Socket operation on non-socket",           // 88 ENOTSOCK
        "Destination address required",             // 89 EDESTADDRREQ
        "Message too long",                         // 90 EMSGSIZE
        "Protocol wrong type for socket",           // 91 EPROTOTYPE
        "Protocol not available",                   // 92 ENOPROTOOPT
        "Protocol not supported",                   // 93 EPROTONOSUPPORT
        "Socket type not supported",                // 94 ESOCKTNOSUPPORT
        "Operation not supported",                  // 95 ENOTSUP
        "Protocol family not supported",            // 96 EPFNOSUPPORT
        "Address family not supported by protocol", // 97 EAFNOSUPPORT
        "Address already in use",                   // 98 EADDRINUSE
        "Cannot assign requested address",          // 99 EADDRNOTAVAIL
        "Network is down",                          // 100 ENETDOWN
        "Network is unreachable",                   // 101 ENETUNREACH
        "Network dropped connection on reset",      // 102 ENETRESET
        "Software caused connection abort",         // 103 ECONNABORTED
        "Connection reset by peer",                 // 104 ECONNRESET
        "No buffer space available",                // 105 ENOBUFS
        "Transport endpoint is already connected",  // 106 EISCONN
        "Transport endpoint is not connected",      // 107 ENOTCONN
        "Cannot send after transport endpoint shutdown", // 108 ESHUTDOWN
        "Too many references: cannot splice",       // 109 ETOOMANYREFS
        "Connection timed out",                     // 110 ETIMEDOUT
        "Connection refused",                       // 111 ECONNREFUSED
        "Host is down",                             // 112 EHOSTDOWN
        "No route to host",                         // 113 EHOSTUNREACH
        "Operation already in progress",            // 114 EALREADY
        "Operation now in progress",                // 115 EINPROGRESS
        "Stale file handle",                        // 116 ESTALE
        "Structure needs cleaning",                 // 117 EUCLEAN
        "Not a XENIX named type file",              // 118 ENOTNAM
        "No XENIX semaphores available",            // 119 ENAVAIL
        "Is a named type file",                     // 120 EISNAM
        "Remote I/O error",                         // 121 EREMOTEIO
        "Disk quota exceeded",                      // 122 EDQUOT
        "No medium found",                          // 123 ENOMEDIUM
        "Wrong medium type",                        // 124 EMEDIUMTYPE
        "Operation canceled",                       // 125 ECANCELED
        "Required key not available",               // 126 ENOKEY
        "Key has expired",                          // 127 EKEYEXPIRED
        "Key has been revoked",                     // 128 EKEYREVOKED
        "Key was rejected by service",              // 129 EKEYREJECTED
        "Owner died",                               // 130 EOWNERDEAD
        "State not recoverable",                    // 131 ENOTRECOVERABLE
        "Operation not possible due to RF-kill",    // 132 ERFKILL
        "Memory page has hardware error",           // 133 EHWPOISON
        "Unknown error",                            // 134
        "Unknown error",                            // 135
        "Unknown error",                            // 136
        "Unknown error",                            // 137
        "Unknown error",                            // 138
        "Unknown error",                            // 139
        "Unknown error",                            // 140
    };
#endif