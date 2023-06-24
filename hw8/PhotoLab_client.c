#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/* Displays an error message to the command line */
void FatalError(const char *Program, const char *ErrorMsg);

/* Sends a request to the specified socket */
int SendRequest(const int SocketFD, const char *ReqMsg);

/* Prints out the available command flags */
void PrintUsage();

int main(int argc, char *argv[])
{
  int x = 1;
  char *server_ip;
  int port = -1;
  int sock;
  struct sockaddr_in server;
  int print_flag = 0;
  int autotest_flag = 0;

  while (x < argc) {
	/* the server ip address option */
	if (strcmp(argv[x], "-ip") == 0) {
	  if (x < argc - 1) {
		server_ip = argv[x+1];
	  } else {
		printf("Missing argument for server IP address!\n");
		return 5;
	  }
	  x += 2;
	  continue;
	}

    /* the server port number option */
	if (strcmp(argv[x], "-p") == 0) {
	  if (x < argc - 1) {
	    if (sscanf(argv[x+1], "%d", &port) != 1 || port <= 2000) {
	      printf("Invalid argument for server port number!\n");
	      return 6;
	    }
	  } else {
	    printf("Missing argument for server port number!\n");
	    return 7;
	  }
	  x += 2;
	  continue;
	}

	/* the help option */
	if (strcmp(argv[x], "-h") == 0) {
	  PrintUsage();
	  return 0;
	}

    /* the print option */
    if (strcmp(argv[x], "-print") == 0) {
      print_flag = 1;
    }

    /* the autotest option */
    if (strcmp(argv[x], "-autotest") == 0) {
      autotest_flag = 1;
    }

	x++;
  }

  /* Validation for mandatory fields */
  if(server_ip == NULL || port == -1) {
    printf("Mandatory fields missing!\n");
    PrintUsage();
    return 8;
  }

  /* Set up sockets and begin connecting to the server here... */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    FatalError("PhotoLab_client", "Failed to create socket");
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  if (inet_aton(server_ip, &server.sin_addr) == 0) {
    FatalError("PhotoLab_client", "Invalid server IP address");
  }

  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    FatalError("PhotoLab_client", "Failed to connect to the server");
  }

  /* After a successful connection, send commands to the server here... */
  if(print_flag) {
    if (SendRequest(sock, "PRINT") < 0) {
      FatalError("PhotoLab_client", "Failed to send PRINT request");
    }
  }

  if(autotest_flag) {
    if (SendRequest(sock, "AUTOTEST") < 0) {
       FatalError("PhotoLab_client", "Failed to send AUTOTEST request");
    }
  }

  close(sock);

  return 0;
}

/*Functions for Error Handling, Send Request and PrintUsage*/

void FatalError(const char *Program, const char *ErrorMsg) {
  fprintf(stderr, "%s: %s\n", Program, ErrorMsg);
  exit(1);
}

int SendRequest(const int SocketFD, const char *ReqMsg) {
  int len = strlen(ReqMsg);
  if (write(SocketFD, ReqMsg, len) != len) {
    return -1;
  }
  return 0;
}

void PrintUsage() {
  printf("Usage: ./PhotoLab_client -ip <server-ip> -p <port> [-print] [-autotest] [-h]\n");
  printf("Options:\n");
  printf("    -ip <server-ip>    : Server IP address\n");
  printf("    -p <port>          : Server port number (Should be > 2000)\n");
  printf("    -print             : Print server response\n");
  printf("    -autotest          : Auto test server\n");
  printf("    -h                 : Print this usage information\n");
}
    
