//
// Created by dingrui on 2024/7/18.
//

#ifndef SQL_STUDIO__MYSQL_MACROS_H_
#define SQL_STUDIO__MYSQL_MACROS_H_

// Capabilities Flags
// Use the improved version of Old Password Authentication. More...
#define    CLIENT_LONG_PASSWORD   1
// Send found rows instead of affected rows in EOF_Packet. More...
#define    CLIENT_FOUND_ROWS   2
// Get all column flags. More...
#define    CLIENT_LONG_FLAG   4
// Database (schema) name can be specified on connect in Handshake Response Packet. More...
#define    CLIENT_CONNECT_WITH_DB   8
// DEPRECATED: Don't allow database.table.column. More...
#define    CLIENT_NO_SCHEMA    16
// Compression protocol supported. More...
#define    CLIENT_COMPRESS   32
// Special handling of ODBC behavior. More...
#define    CLIENT_ODBC   64
// Can use LOAD DATA LOCAL. More...
#define    CLIENT_LOCAL_FILES   128
// Ignore spaces before '('. More...
#define    CLIENT_IGNORE_SPACE   256
// New 4.1 protocol. More...
#define    CLIENT_PROTOCOL_41   512
// This is an interactive client. More...
#define    CLIENT_INTERACTIVE   1024
// Use SSL encryption for the session. More...
#define    CLIENT_SSL   2048
// Client only flag. More...
#define    CLIENT_IGNORE_SIGPIPE   4096
// Client knows about transactions. More...
#define    CLIENT_TRANSACTIONS   8192
// DEPRECATED: Old flag for 4.1 protocol
#define    CLIENT_RESERVED   16384
// DEPRECATED: Old flag for 4.1 authentication \ CLIENT_SECURE_CONNECTION. More...
#define    CLIENT_RESERVED2    32768
// Enable/disable multi-stmt support. More...
#define    CLIENT_MULTI_STATEMENTS   (1UL << 16)
// Enable/disable multi-results. More...
#define    CLIENT_MULTI_RESULTS   (1UL << 17)
// Multi-results and OUT parameters in PS-protocol.
#define    CLIENT_PS_MULTI_RESULTS   (1UL << 18)
// Client supports plugin authentication.
#define    CLIENT_PLUGIN_AUTH   (1UL << 19)
// Client supports connection attributes. More...
#define    CLIENT_CONNECT_ATTRS   (1UL << 20)
// Enable authentication response packet to be larger than 255 bytes. More...
#define    CLIENT_PLUGIN_AUTH_LENENC_CLIENT_DATA   (1UL << 21)
// Don't close the connection for a user account with expired password. More...
#define    CLIENT_CAN_HANDLE_EXPIRED_PASSWORDS   (1UL << 22)
// Capable of handling server state change information. More...
#define    CLIENT_SESSION_TRACK   (1UL << 23)
// Client no longer needs EOF_Packet and will use OK_Packet instead. More...
#define    CLIENT_DEPRECATE_EOF   (1UL << 24)
// The client can handle optional metadata information in the resultset. More...
#define    CLIENT_OPTIONAL_RESULTSET_METADATA   (1UL << 25)
// Compression protocol extended to support zstd compression method. More...
#define    CLIENT_ZSTD_COMPRESSION_ALGORITHM   (1UL << 26)
// Support optional extension for query parameters into the COM_QUERY and COM_STMT_EXECUTE packets. More...
#define    CLIENT_QUERY_ATTRIBUTES   (1UL << 27)
// Support Multi factor authentication. More...
#define    MULTI_FACTOR_AUTHENTICATION   (1UL << 28)
// This flag will be reserved to extend the 32bit capabilities structure to 64bits. More...
#define    CLIENT_CAPABILITY_EXTENSION   (1UL << 29)
// Verify server certificate. More...
#define    CLIENT_SSL_VERIFY_SERVER_CERT   (1UL << 30)
// Don't reset the options after an unsuccessful connect. More...
#define    CLIENT_REMEMBER_OPTIONS   (1UL << 31)

#endif //SQL_STUDIO__MYSQL_MACROS_H_
