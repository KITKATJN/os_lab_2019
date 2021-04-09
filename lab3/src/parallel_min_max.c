
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv) {
  int seed = -1;
  int array_size = -1;
  int pnum = -1;
  bool with_files = false;

  while (true) {
    //int current_optind = optind ? optind : 1;

    static struct option options[] = {{"seed", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"by_files", no_argument, 0, 'f'},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            seed = atoi(optarg);
            if (seed <= 0)
            {
              printf("Error with seed\n");
              return (1);
            }
            // your code here
            // error handling
            break;
          case 1:
            array_size = atoi(optarg);
            if (array_size <= 0)
            {
              printf("Error with array_size\n");
              return (1);
            }
            // your code here
            // error handling
            break;
          case 2:
            pnum = atoi(optarg);
            if (pnum <= 0)
            {
              printf("Error with pnum\n");
              return (1);
            }
            // your code here
            // error handling
            break;
          case 3:
            with_files = true;
            break;

          default:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case 'f':
        with_files = true;
        break;

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  // if (optind < argc) {
  //   printf("Has at least one no option argument\n");
  //   return 1;
  // }

  if (seed == -1 || array_size == -1 || pnum == -1) {
    printf("Usage: %s --seed \"num\" --array_size \"num\" --pnum \"num\" \n",
           argv[0]);
    return 1;
  }

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);
  int active_child_processes = 0;

  struct timeval start_time;
  gettimeofday(&start_time, NULL);

    int pipefd[2];
    pipe(pipefd);

  for (int i = 0; i < pnum; i++) {
    pid_t child_pid = fork();
    if (child_pid >= 0) {
      // successful fork
      active_child_processes += 1;
      if (child_pid == 0) {
        // child process
        struct MinMax min_max1;
        min_max1 = GetMinMax(array, 0, array_size - 1);
        // parallel somehow

        if (with_files) {
          FILE *fp;
          fp = fopen("text.txt", "a+");//a+ - open for reading and writing (append if file exists)
          if (!fp)
          {
            printf("Error with file\n");
            return (1);
          }
          else
          {
            fwrite(&min_max1, sizeof(struct MinMax), 1, fp);
          }
          fclose(fp);
          // use files here
        } else {
          write(pipefd[1], &min_max1, sizeof(min_max1));
          // use pipe here
        }
        return 0;
      }

    } else {
      printf("Fork failed!\n");
      return 1;
    }
  }

  while (active_child_processes > 0) {
    // your code here
    close(pipefd[1]);
    wait(0);
    active_child_processes -= 1;
  }

  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  for (int i = 0; i < pnum; i++) {
    int min = INT_MAX;
    int max = INT_MIN;
    struct MinMax Min_Max_file;

    if (with_files) {
      FILE *fp;
      fp = fopen("text.txt", "rb+");//b в двоичном режиме
      if (fp==0)
      {
            printf( "Could not open file\n" );
            return 1;
      } else
      {
            fseek(fp, i*sizeof(struct MinMax), SEEK_SET);
            fread(&Min_Max_file, sizeof(struct MinMax), 1, fp);
      }
      fclose(fp);
      // read from files
    } else {
        read(pipefd[0], &Min_Max_file, sizeof(struct MinMax));
      // read from pipes
    }
    max = Min_Max_file.max;
    min = Min_Max_file.min;
    if (min < min_max.min) min_max.min = min;
    if (max > min_max.max) min_max.max = max;
  }

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  free(array);

  printf("Min: %d\n", min_max.min);
  printf("Max: %d\n", min_max.max);
  printf("Elapsed time: %fms\n", elapsed_time);
  fflush(NULL);
  return 0;
}
