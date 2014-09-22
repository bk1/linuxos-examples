
/************************************************************************
 * NAME									*
 *   pipe.c								*
 *									*
 * SYNOPSIS								*
 *   pipe [loops]							*
 *									*
 * DESCRIPTION								*
 *   Synchronisation mit Unnamed Pipes  	*
 *									*
 * AUTHOR								*
 *   Peter Schmid, Hochschule Zuerich, pschmid@hsz-t.ch			*
 *									*
 * CVS									*
 *   $Id: pipe.c,v 1.1 2007/11/21 21:19:07 pschmid Exp pschmid $	*
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

static void putstr(char *);
int loops = 1000;

int main(int argc, char **argv) {

    pid_t pid;
    int fd_p2c[2], fd_c2p[2];
    // char buffer[2]; // to be used later
    int k;

    
    if (argc == 2) {
        (void) sscanf(argv[1], "%d", &loops);
    }

    pipe(fd_p2c);
    pipe(fd_c2p);

    if ( (pid = fork()) < 0) {
	printf("fork error\n");
	exit(-1);
    }
    else if (pid == 0) {
        /* Kindprozess */
	close(fd_p2c[1]); 		// Eltern zu Kind nur lesen
	close(fd_c2p[0]); 		// Kind zu Eltern nur schreiben
	for(k=0; k<10; k++) {
	    putstr("Ausgabe vom Kindprozess\n");
	}
    } else {
	/* Elternprozess */
	close(fd_p2c[0]); 		// Eltern zu Kind nur schreiben
	close(fd_c2p[1]);		// Kind zu Eltern nur lesen
	for(k=0; k<10; k++) {
	    putstr("Ausgabe vom Elternprozess\n");
	}
    }
    exit(0);
}

static void putstr(char *str) {

    char	*ptr;
    int		c, i;
    double      f;

    setbuf(stdout, NULL); /* set unbuffered */
    for (ptr = str; (c = *ptr++) != 0; ) {
	for (i = 0; i < loops; i++) {
	    /* Verzoegerungsschlaufe */
	    f += sin((double)i);
	}
	putc(c, stdout);
    }
}
