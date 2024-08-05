#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "threadPool.h"
#include "time.h"

typedef struct
{
    char *file;
    char *parameter;
} Node;

int work(void *arg)
{
    Node *node = (Node *)arg;
    char *buffer = malloc(sizeof(char) * 1024 * 1024);
    if (node->parameter)
    {
        snprintf(buffer, 1024 * 1024, "sh %s %s", node->file, node->parameter);
    }
    else
    {
        snprintf(buffer, 1024 * 1024, "sh %s", node->file);
    }
    char *time = NULL;
    time = getTime(2);
    printf("%s -> Doing: \"%s\".\n", time, buffer);
    free(time);
    int flag = system(buffer);
    time = getTime(2);
    printf("%s -> Done: \"%s\" (%d).\n", time, buffer, flag);
    free(time);
    fflush(stdout);
    free(buffer);
    return flag;
}

char *createShell(char *commands)
{
    char *file = getTime(1);
    FILE *openFile = fopen(file, "w");
    assert(openFile);
    fputs(commands, openFile);
    fclose(openFile);
    return file;
}

int runCommands(int nThreads, char *file, char **parameters, int nParameters)
{
    ThreadPool *threadPool = threadPoolCreate(nThreads);
    assert(threadPool);
    if (nParameters)
    {
        for (int i = 0; i < nParameters; i++)
        {
            Node *node = malloc(sizeof(Node));
            node->file = file;
            node->parameter = parameters[i];
            assert(!threadPoolPut(threadPool, work, node));
        }
    }
    else
    {
        Node *node = malloc(sizeof(Node));
        node->file = file;
        node->parameter = NULL;
        assert(!threadPoolPut(threadPool, work, node));
    }
    assert(!threadPoolFree(threadPool));
    return 0;
}

int printHelp(char *self)
{
    puts("\nRun some commands in parallel (https://github.com/liu-congcong/parallel)");
    puts("Usage:");
    printf("    %s [--threads <int>] [--parameters <str>] --input <str>.\n", self);
    puts("Options:");
    puts("    -t/--threads: number of threads [default: 1].");
    puts("    -p/--parameters: list of parameters.");
    puts("    -i/--input: commands or shell file.\n");
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1 || !strncasecmp("-help", argv[1], 2) || !strncasecmp("--help", argv[1], 3))
    {
        printHelp(argv[0]);
    }
    else
    {
        int nThreads = 1;
        int nParameters = 0;
        char **parameters = malloc(sizeof(char *) * argc);
        assert(parameters);
        char *input = NULL;
        int flag = 0;

        for (int i = 0; i < argc; i++)
        {
            if (!strncasecmp("-threads", argv[i], 2) || !strncasecmp("--threads", argv[i], 3))
            {
                flag = 0;
                nThreads = atoi(argv[i + 1]);
            }
            else if (!strncasecmp("-parameters", argv[i], 2) || !strncasecmp("--parameters", argv[i], 3))
            {
                flag = 1;
            }
            else if (!strncasecmp("-input", argv[i], 2) || !strncasecmp("--input", argv[i], 3))
            {
                flag = 0;
                input = argv[i + 1];
            }
            else if (flag == 1)
            {
                parameters[nParameters] = argv[i];
                nParameters++;
            }
        }

        if (!input)
        {
            printHelp(argv[0]);
        }

        if (access(input, R_OK))
        {
            input = createShell(input);
            flag = 1;
        }
        else
        {
            flag = 0;
        }

        runCommands(nThreads, input, parameters, nParameters);

        if (flag)
        {
            remove(input);
            free(input);
        }
        free(parameters);
    }
    return 0;
}
