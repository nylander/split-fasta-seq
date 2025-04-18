#include "splitfast.h"

void print_wrapped_sequence(const char *sequence, size_t length, long int wraplength) {
    for (size_t i = 0; i < length; i++) {
        putchar(sequence[i]);
        if ((i + 1) % wraplength == 0 || i == length - 1) {
            putchar('\n');
        }
    }
}

void extract_first_string(char *header) {
    char *space = strchr(header, ' ');
    if (space) {
        *space = '\0';
    }
}

int main(int argc, char **argv) {
    FILE *fp;
    char header[STR_MAX_SIZE];
    char *sequence_chunk = NULL;
    long int maxlength = 100000;
    long int wraplength = 80;
    char *endptr;
    int c, sflag = 0;

    static char usage[] = "\nSplit long fasta sequences.\n\n"
                          "Usage:\n\n %s [-h] [-v] [-s] [-m <maxlength>] [-w <wraplength>] infile(s).\n\n"
                          "  -h  help\n"
                          "  -v  print version\n"
                          "  -s  output only the first string of the header line\n"
                          "  -m  max sequence length (default 100,000)\n"
                          "  -w  line width (default 80)\n\n"
                          "  infile should be in fasta format.\n\n";

    if (argc == 1) {
        fprintf(stderr, usage, argv[0]);
        exit(EXIT_FAILURE);
    }

    while ((c = getopt(argc, argv, "hvsm:w:")) != -1) {
        switch (c) {
        case 'h':
            fprintf(stderr, usage, argv[0]);
            exit(EXIT_SUCCESS);
        case 'v':
            printf("splitfast version %s\n", VERSION);
            exit(EXIT_SUCCESS);
        case 's':
            sflag = 1;
            break;
        case 'm':
            maxlength = strtol(optarg, &endptr, 10);
            if (*endptr != '\0' || maxlength <= 0) {
                fprintf(stderr, "Invalid maxlength value.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'w':
            wraplength = strtol(optarg, &endptr, 10);
            if (*endptr != '\0' || wraplength <= 0) {
                fprintf(stderr, "Invalid wraplength value.\n");
                exit(EXIT_FAILURE);
            }
            break;
        case '?':
            fprintf(stderr, usage, argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Error: Need input fasta file(s) to process.\n");
        fprintf(stderr, usage, argv[0]);
        exit(EXIT_FAILURE);
    }

    sequence_chunk = (char *)malloc(maxlength * sizeof(char));
    if (sequence_chunk == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for sequence chunk.\n");
        exit(EXIT_FAILURE);
    }

    for (; optind < argc; optind++) {
        fp = fopen(argv[optind], "r");
        if (fp == NULL) {
            perror("Error: failed in opening file");
            free(sequence_chunk);
            exit(EXIT_FAILURE);
        }

        int in_sequence = 0;
        size_t seq_len = 0;
        int part_num = 0;
        char current_char;

        while ((current_char = fgetc(fp)) != EOF) {
            if (current_char == '>') {
                if (in_sequence) {
                    if (seq_len > 0) {
                        if (sflag) {
                            printf(">%s__%d\n", header, part_num++);
                        }
                        else {
                            printf(">%s__%d\n", header, part_num++);
                        }
                        print_wrapped_sequence(sequence_chunk, seq_len, wraplength);
                    }
                }

                if (fgets(header, sizeof(header), fp) != NULL) {
                    header[strcspn(header, "\n")] = '\0';
                    if (sflag) {
                        extract_first_string(header);
                    }
                }
                else {
                    fprintf(stderr, "Error: Failed to read header line.\n");
                    fclose(fp);
                    free(sequence_chunk);
                    exit(EXIT_FAILURE);
                }

                seq_len = 0;
                part_num = 0;
                in_sequence = 1;
            }
            else if (current_char != '\n') {
                sequence_chunk[seq_len++] = current_char;

                if (seq_len == maxlength) {
                    if (sflag) {
                        printf(">%s__%d\n", header, part_num++);
                    }
                    else {
                        printf(">%s__%d\n", header, part_num++);
                    }
                    print_wrapped_sequence(sequence_chunk, seq_len, wraplength);
                    seq_len = 0;
                }
            }
        }

        if (in_sequence && seq_len > 0) {
            if (sflag) {
                printf(">%s__%d\n", header, part_num++);
            }
            else {
                printf(">%s__%d\n", header, part_num++);
            }
            print_wrapped_sequence(sequence_chunk, seq_len, wraplength);
        }

        fclose(fp);
    }

    free(sequence_chunk);

    return 0;
}
