CS 214 Spring 2024
Project I: My Shell<br>
`David Menendez`

Team Members:
- Zeel Patel (NetID: zap19)
- Shreya Vyas (NetID: sv693)

#mysh.c implementation

## Overview

This README provides an overview of a simple shell implementation in C. The shell supports basic commands, input/output redirection, pipes, wildcard expansion, and conditional execution based on the success or failure of previous commands.

## Code Structure

The shell code is organized into several functions, each responsible for specific functionalities:

- `executeCommand`: Executes commands entered by the user, handles built-in commands (`cd`, `pwd`, `which`), input/output redirection, wildcard expansion, pipes, and conditional execution.
- `interactiveMode`: Implements the interactive mode where the user can enter commands directly into the shell.
- `main`: The entry point of the program, determining whether to run in interactive mode or batch mode based on the command line arguments.

## Usage

### Interactive Mode

Run the program without any command line arguments to enter interactive mode:

```bash
./myshell
```

### Batch Mode

Run the program with a batch file as a command line argument:

```bash
./myshell batchfile.txt
```

## Test Plan

### Scenarios to Test

1. **Basic Command Execution**: Test the execution of basic commands (e.g., `ls`, `echo`).
2. **Built-in Commands**: Test built-in commands (`cd`, `pwd`, `which`).
3. **Input/Output Redirection**: Test input/output redirection using `<` and `>` operators.
4. **Pipes**: Test command pipelines using the `|` operator.
5. **Wildcard Expansion**: Test wildcard expansion using `*` in file paths.
6. **Conditional Execution**: Test conditional execution using `then`, `else`, and `exit` commands.
7. **Background Execution**: Test running commands in the background using `&`.

### Test Cases

1. **Basic Command Execution**
   ```bash
   ls
   echo "Hello, World!"
   ```

2. **Built-in Commands**
   ```bash
   cd /path/to/directory
   pwd
   which ls
   ```

3. **Input/Output Redirection**
   ```bash
   echo "Redirected input" > input.txt
   cat < input.txt
   ```

4. **Pipes**
   ```bash
   echo "Test" > out.txt
   cat < out.txt | grep "Test"
   ```

5. **Wildcard Expansion**
   ```bash
   echo *.*
   ```

6. **Conditional Execution**
   ```bash
   ls then echo "Directory listed successfully"
   ls else echo "Error listing directory"
   ```

7. **Background Execution**
   ```bash
   sleep 5 &
   ```

### Testing Strategy

1. **Manual Testing**: Manually execute each test case in the interactive mode and observe the results.
2. **Batch File Testing**: Create a batch file with test cases and run the shell in batch mode to ensure correct execution.
3. **Edge Cases**: Test with edge cases, such as empty input, missing arguments, and invalid commands.
4. **Concurrency Testing**: Test background execution with multiple commands running concurrently.

### How to Run Tests

1. Compile the shell program:
   ```bash
   gcc -o myshell myshell.c
   ```

2. Run individual test cases in interactive mode:
   ```bash
   ./myshell
   ```

3. Run batch tests using a batch file:
   ```bash
   ./myshell test_batch.txt
   ```

4. Observe output and check for any error messages.

## Conclusion

This simple shell implementation provides basic shell functionalities and supports various command-line scenarios. Extensive testing ensures the reliability and correctness of the shell in different usage scenarios.
