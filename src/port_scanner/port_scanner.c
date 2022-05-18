#include "port_scanner.h"

int launch_port_scanner() {
    struct hostent *host;
    int err, i, sock;
    int open_ports_numb = 0;
    int start = 1, end = 65535;
    int start_input[15], end_input[15];
    char hostname[] = "192.168.67.129";
    struct sockaddr_in sa;

    // logger(PROMPT_CONF, "ENTER START PORT NUMBER:");
    // scanf("%d", &start);
    // fgets(start, 15, stdin);

    // logger(PROMPT_CONF, "ENTER END PORT NUMBER:");
    // scanf("%d", &end);
    // fgets(end, 15, stdin);

    logger(INFO_CONF, "SCANNING PORTS FROM %d to %d", start, end);

    strncpy((char *)&sa, "", sizeof sa);
    sa.sin_family = AF_INET;

    // direct ip address, use it
    if (isdigit(hostname[0])) {
        logger(INFO_CONF, "CALLING inet_addr()...");
        sa.sin_addr.s_addr = inet_addr(hostname);
    }
    // Resolve hostname to ip address
    else if ((host = gethostbyname(hostname)) != 0) {
        logger(INFO_CONF, "CALLING gethostbyname()...");
        strncpy((char *)&sa.sin_addr, (char *)host->h_addr, sizeof sa.sin_addr);
    } else {
        logger(ERR_CONF, "WRONG HOSTNAME PROVIDED");
        return -1;
    }

    // Start the port scan loop
    logger(INFO_CONF, "STARTING SCAN LOOP");
    for (i = start; i <= end; i++) {
        // Fill in the port number
        sa.sin_port = htons(i);
        // Create a socket of type internet
        sock = socket(AF_INET, SOCK_STREAM, 0);

        // Check whether socket created fine or not
        if (sock < 0) {
            print_perror();
            return -1;
        }
        // Connect using that socket and sockaddr structure
        err = connect(sock, (struct sockaddr *)&sa, sizeof sa);

        // not connected
        if (err < 0) {
            // printf("%s %-5d %s\r" , hostname , i, strerror(errno));
            fflush(stdout);
        }
        // connected
        else {
            open_ports_numb++;
            logger(SUCCESS_CONF, "FOUND OPEN PORT: %-5d", i);
        }
        close(sock);
    }
    logger(INFO_CONF, "FOUND %d OPEN PORTS ON LOCAL MACHINE", open_ports_numb);
    fflush(stdout);
    return 0;
}