#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <glob.h>
#include <stdbool.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024

int last_exit_status = 0;

int get_last_exit_status()
{
    return last_exit_status;
}

void set_last_exit_status(int status)
{
    last_exit_status = status;
}
void executeCommand(char *tokens[])
{
    if (tokens[0] != NULL && strcmp(tokens[0], "exit") == 0)
    {
        printf("Exiting...\n");
        exit(0);
    }
    if (tokens[0] == NULL)
    {

        return;
    }

    if (strcmp(tokens[0], "cd") == 0)
    {
        if (tokens[1] != NULL)
        {
            if (chdir(tokens[1]) != 0)
            {
                perror("cd");
            }
        }
        else
        {
            fprintf(stderr, "cd: missing argument\n");
        }
        return;
    }
    else if (strcmp(tokens[0], "pwd") == 0)
    {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
        }
        else
        {
            perror("getcwd");
        }
        return;
    }
    else if (strcmp(tokens[0], "which") == 0)
    {
        if (tokens[1] != NULL)
        {
            printf("%s\n", tokens[1]);
        }
        else
        {
            fprintf(stderr, "which: missing argument\n");
        }
        return;
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
    }
    else if (pid == 0)
    {

        int input_redirection_index = -1;
        for (int i = 0; tokens[i] != NULL; ++i)
        {
            if (strcmp(tokens[i], "<") == 0)
            {
                input_redirection_index = i;
                break;
            }
        }

        if (input_redirection_index != -1)
        {
            if (tokens[input_redirection_index + 1] != NULL)
            {
                int input_fd = open(tokens[input_redirection_index + 1], O_RDONLY);
                if (input_fd == -1)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            else
            {
                fprintf(stderr, "Missing input file after <\n");
                exit(EXIT_FAILURE);
            }

            // Remove redirection tokens and filenames
            for (int i = input_redirection_index; tokens[i] != NULL; ++i)
            {
                tokens[i] = NULL;
            }
        }

        // Handle output redirection
        int output_redirection_index = -1;
        for (int i = 0; tokens[i] != NULL; ++i)
        {
            if (strcmp(tokens[i], ">") == 0)
            {
                output_redirection_index = i;
                break;
            }
        }

        if (output_redirection_index != -1)
        {
            if (tokens[output_redirection_index + 1] != NULL)
            {
                int output_fd = open(tokens[output_redirection_index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0640);
                if (output_fd == -1)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }
            else
            {
                fprintf(stderr, "Missing output file after >\n");
                exit(EXIT_FAILURE);
            }

            // Remove redirection tokens and filenames
            for (int i = output_redirection_index; tokens[i] != NULL; ++i)
            {
                tokens[i] = NULL;
            }
        }

        int wildcard_count = 0;
        int i;
        for (i = 1; tokens[i] != NULL; ++i)
        {
            if (strchr(tokens[i], '*') != NULL)
            {
                ++wildcard_count;
            }
        }

        if (wildcard_count > 0)
        {
            glob_t glob_result;
            glob_result.gl_offs = i;

            int glob_status = glob(tokens[1], GLOB_NOCHECK | GLOB_ERR, NULL, &glob_result);

            if (glob_status != 0)
            {
                fprintf(stderr, "Error in wildcard expansion: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            tokens[i - 1] = NULL;

            for (size_t j = 0; j < glob_result.gl_pathc; ++j)
            {
                tokens[i + j] = strdup(glob_result.gl_pathv[j]);
            }

            tokens[i + glob_result.gl_pathc] = NULL;
            globfree(&glob_result);
        }

        for (int i = 0; tokens[i] != NULL; ++i)
        {
            if (strcmp(tokens[i], "|") == 0)
            {

                tokens[i] = NULL;
                char *cmd2[MAX_INPUT_SIZE];
                for (int j = 0; tokens[i + 1 + j] != NULL; ++j)
                {
                    cmd2[j] = tokens[i + 1 + j];
                }
                cmd2[0] = NULL;
                executeCommand(tokens);
                executeCommand(cmd2);
                exit(EXIT_SUCCESS);
            }
        }

        bool execute_command = true;
        if (strcmp(tokens[0], "then") == 0)
        {

            execute_command = (WIFEXITED(get_last_exit_status()) && WEXITSTATUS(get_last_exit_status()) == 0);
        }
        else if (strcmp(tokens[0], "else") == 0)
        {

            execute_command = !(WIFEXITED(get_last_exit_status()) && WEXITSTATUS(get_last_exit_status()) == 0);
        }
        else if (strcmp(tokens[0], "exit") == 0)
        {
            exit(0);
        }

        if (execute_command)
        {

            execvp(tokens[0], tokens);

            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else
        {

            exit(EXIT_SUCCESS);
        }
    }
    else
    {

        int status;

        bool is_background = false;
        for (int i = 1; tokens[i] != NULL; ++i)
        {
            if (strcmp(tokens[i], "&") == 0)
            {
                is_background = true;
                tokens[i] = NULL;
                break;
            }
        }

        if (!is_background)
        {

            waitpid(pid, &status, 0);
            set_last_exit_status(status);
        }
        else
        {

            printf("Background command started: %s\n", tokens[0]);
        }
    }
}

void interactiveMode()
{
    printf("Welcome to my shell!\n");

    while (1)
    {

        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("mysh:%s> ", cwd);
        }
        else
        {
            perror("getcwd");
            printf("mysh> ");
        }

        char input[MAX_INPUT_SIZE];
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        char *tokens[MAX_INPUT_SIZE];
        char *token = strtok(input, " \t\n");
        int i = 0;
        while (token != NULL)
        {
            tokens[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        tokens[i] = NULL;

        executeCommand(tokens);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {

        interactiveMode();
    }
    else if (argc == 2)
    {

        FILE *batchFile = fopen(argv[1], "r");
        if (batchFile == NULL)
        {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        char line[MAX_INPUT_SIZE];
        while (fgets(line, sizeof(line), batchFile) != NULL)
        {

            char *tokens[MAX_INPUT_SIZE];
            char *token = strtok(line, " \t\n");
            int i = 0;
            while (token != NULL)
            {
                tokens[i++] = token;
                token = strtok(NULL, " \t\n");
            }
            tokens[i] = NULL;

            executeCommand(tokens);
        }

        fclose(batchFile);
    }
    else
    {
        fprintf(stderr, "Usage: %s [batchfile]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
