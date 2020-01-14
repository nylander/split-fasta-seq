/*    File: splitfast.c                        */
/*      By: Johan Nylander                     */
/* Version: Tue 14 Jan 2020                    */
/* Compile: gcc -Wall -o splitfast splitfast.c */
/*     Run: ./splitfast -m 30 -w 10 fasta.fas  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLENGTH 100000 // max length of seq 100000
#define WRAPLENGTH 80    // line wrap for fasta seq 80
#define STR_MAX_SIZE 200 // max length for fasta header

int main (int argc, char **argv) {

    FILE *fp;
    char str[STR_MAX_SIZE];
    char sstr[STR_MAX_SIZE];
    long int seqlen;
    int inheader;
    int foundspace;
    int ngts;     // Number of greater-than-signs.
    char r;       // r is the character currently read
    int k, h;     // k is position on line,
                  // h is the header counter.
    int ihc;      // Header line-position counter

    extern char *optarg;
    extern int optind;
    int c, err = 0;
    int mflag = 0;
    int sflag = 0;
    int wflag = 0;
    char *mopt = NULL;
    char *wopt = NULL;
    char *endptr;
    long int maxlength = MAXLENGTH;
    long int wraplength = WRAPLENGTH;

    static char usage[] = "\nSplit long fasta sequences.\n\nUsage:\n\n %s [-h] [-s] [-m <maxlength>] [-w <wraplength>] infile(s).\n\n  -h  help\n  -s  use short output header\n  -m  max sequence length (default 100,000)\n  -w  line width (default 80)\n\n  infile should be in fasta format.\n\n";

    if (argc == 1) {
        fprintf(stderr, usage, argv[0]);
        exit(EXIT_FAILURE);
    }

    while ((c = getopt(argc, argv, "hsm:w:")) != -1) {
        switch (c) {
            case 'h':
                fprintf(stderr, usage, argv[0]);
                exit(1);
                break;
            case 's':
                sflag = 1;
                break;
            case 'm':
                mflag = 1;
                mopt= optarg;
                break;
            case 'w':
                wflag = 1;
                wopt = optarg;
                break;
            case '?':
                err = 1;
                break;
        }
    }

    if (err) {
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }

    if (wflag) {
        wraplength = strtol(wopt, &endptr, 10);
    }

    if (mflag) {
        maxlength = strtol(mopt, &endptr, 10);
    }

    if (optind < argc) {
        for (; optind < argc; optind++) {
            fp = fopen(argv[optind], "r");

            if (fp == NULL) {
                perror("Error: failed in opening file");
                exit(EXIT_FAILURE);
            }

            inheader = 0;
            foundspace = 0;
            ihc = 0;
            ngts = 0;
            seqlen = 0;
            k = 0;
            h = 1;

            while ((r = getc(fp)) != EOF) {
                if (inheader == 1) {
                    if (r == '\n') {
                        inheader = 0;
                        foundspace = 0;
                        str[ihc] = '\0';
                        sstr[ihc] = '\0';
                        if (! sflag) {
                            printf("_0");
                        }
                        putchar(r);
                    }
                    else if (r == ' ') {
                        if (sflag) {
                            if (! foundspace) {
                                printf("_0");
                                foundspace = 1;
                                sstr[ihc] = '\0';
                            }
                        }
                        else {
                            str[ihc] = r;
                            putchar(r);
                        }
                    }
                    else {
                        str[ihc] = r;
                        sstr[ihc] = r;
                        if (! sflag || ! foundspace) {
                            putchar(r);
                        }
                    }
                    ++ihc;
                }
                else if (r == '>') {
                    ++ngts;
                    if (ngts > 1) {
                        putchar('\n');
                        ngts = 1;
                    }
                    putchar(r);
                    inheader = 1;
                    ihc = 0;
                    seqlen = 0;
                    h = 1;
                    k = 0;
                }
                else {
                    if (r != '\n') {
                        ++seqlen;
                        ++k;
                        putchar(r);
                        if (k > 0) {
                            if (k % wraplength == 0) {
                                printf("\n");
                                k = 0;
                            }
                        }
                        if (seqlen == maxlength) {
                            if (k > 0) {
                                if (sflag) {
                                    printf("\n>%s_%d",sstr, h);
                                }
                                else {
                                    printf("\n>%s_%d",str, h);
                                }
                            }
                            else {
                                if (sflag) {
                                    printf(">%s_%d",sstr, h);
                                }
                                else {
                                    printf(">%s_%d",str, h);
                                }
                            }
                            putchar('\n');
                            seqlen = 0;
                            k = 0;
                            ++h;
                        }
                    }
                }
            }
            putchar('\n');
            fclose(fp);
        }
    }
    else {
        printf("Error: Need input fasta file(s) to process.\n");
        fprintf(stderr, usage, argv[0]);
        exit(EXIT_FAILURE);
    }
    exit(0);
}

