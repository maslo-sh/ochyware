#include "server_socket.h"

static char IN_KEY[FILENAME_BUF_SIZE];

int loops = 0;
int DETECTED_VIRUSES = 0;
int SCANNED_FILES = 0;

static int call_port_scanner_func() { launch_port_scanner(); }


void handle(int socket_fd)
{
    while(1){
        bzero(IN_KEY, sizeof(IN_KEY));
        loops++;
        logger(PROMPT_CONF,
               "\nRECURSIVE SCANNING [D] / SIMPLE FILE SCANNING [F]"
               "\nUPDATE HASH DATABASE [U] / LAUNCH PORT SCANNER [S]"
               "\nQUIT [Q]");

        read(socket_fd, IN_KEY, 2);
        IN_KEY[2] = '/0';
        char opt = IN_KEY[0];        
        bzero(IN_KEY, sizeof(IN_KEY));

        switch (opt) {
        case 'F':
            logger(PROMPT_CONF, "TYPE FILENAME");
            read(socket_fd, IN_KEY, FILENAME_BUF_SIZE);
            remove_trailing_space(IN_KEY);
            process_file_unit(IN_KEY);
            logger(SUCCESS_CONF, "SCANNING FINISHED");
            logger(INFO_CONF, "VIRUSES FOUND: %d", DETECTED_VIRUSES);
            break;

        case 'D':
            logger(PROMPT_CONF, "TYPE DIRNAME");
            read(socket_fd, IN_KEY, FILENAME_BUF_SIZE);
            remove_trailing_space(IN_KEY);
            process_files(IN_KEY, 0, process_file_unit);
            logger(SUCCESS_CONF, "SCANNING FINISHED");
            logger(INFO_CONF, "SCANNED FILES: %d", SCANNED_FILES);
            logger(INFO_CONF, "VIRUSES FOUND: %d", DETECTED_VIRUSES);
            break;

        case 'U':
            deallocate_db_memory();
            logger(PROMPT_CONF, "TYPE DATABASE FILENAME");
            read(socket_fd, IN_KEY, FILENAME_BUF_SIZE);
            remove_trailing_space(IN_KEY);

            int is_dir = is_directory(IN_KEY);
            if (is_dir == 1) {
                logger(ERR_CONF, "%s IS A DIRECTORY", IN_KEY);
                logger(INFO_CONF, "READING DATABASE FROM THE ORIGIN");
                read_hash_database("database.txt");
                break;
            }

            int db_read_res = read_hash_database(IN_KEY);

            if (db_read_res == -1) {
                logger(ERR_CONF, "FAILED TO LOAD DATABASE FROM %s", IN_KEY);
                logger(INFO_CONF, "READING DATABASE FROM THE ORIGIN");
                read_hash_database("database.txt");
                break;
            }

            logger(SUCCESS_CONF, "FILE %s LOADED TO THE DATABASE", IN_KEY);
            break;

        case 'S': {
            int scanner_thread_res = spawn_thread(call_port_scanner_func);
            if (scanner_thread_res == -1) {
                logger(ERR_CONF, "FAILED TO SPAWN PORT SCANNER THREAD");
                break;
            }
            logger(SUCCESS_CONF, "SCANNING FINISHED");
            break;
        }

        case 'Q':
            deallocate_db_memory();
            logger(INFO_CONF, "CLOSING ANTIVIRUS");
            return;

        default:
            logger(INFO_CONF, "WRONG OPTION PROVIDED");
            break;
        }
    }
}
   
int main()
{
    int sock_fd, conn_fd, length;
    struct sockaddr_in serv, cli;

    srand(time(NULL)); 

    printf("%s\n\n", "<==== HELLO ANTIVIRUS ====>");
    logger(INFO_CONF, "ANTIVIRUS LAUNCHED");

    int db_read_res = read_hash_database("database.txt");

    if (db_read_res == -1) {
        logger(ERR_CONF, "FILE %s CANNOT BE OPENED", "database.txt");
        print_perror();
        deallocate_db_memory();
        return EXIT_FAILURE;
    }
   
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        logger(ERR_CONF, "SOCKET CREATION FAILED");
        exit(0);
    }
    else{
        logger(SUCCESS_CONF, "SOCKET SUCCESSFULLY CREATED");
    }
        
    bzero(&serv, sizeof(serv));
   
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(PORT);
   
    if ((bind(sock_fd, (SA*)&serv, sizeof(serv))) != 0) {
        logger(ERR_CONF, "SOCKET BIND FAILED");
        exit(0);
    }
    else
        logger(SUCCESS_CONF, "SOCKET SUCCESSFULLY BINDED");
   
    // Now server is ready to listen and verification
    if ((listen(sock_fd, 5)) != 0) {
        logger(ERR_CONF, "LISTEN FAILED");
        exit(0);
    }
    else
        logger(INFO_CONF, "SERVER IS LISTENING...\n");
    length = sizeof(cli);
   
    // Accept the data packet from client and verification
    conn_fd = accept(sock_fd, (SA*)&cli, &length);
    if (conn_fd < 0) {
        logger(ERR_CONF, "SERVER ACCEPT FAILED");
        exit(0);
    }
    else
        logger(INFO_CONF, "SERVER ACCEPTING THE CLIENT");
   
    dup2(conn_fd, STDOUT_FILENO);
    dup2(conn_fd, STDERR_FILENO);

    // function for chat
    handle(conn_fd);
   
    // close the socket
    close(sock_fd);
}