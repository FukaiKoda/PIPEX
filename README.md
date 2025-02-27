# pipex - Inter-Process Communication (IPC)

## 📌 Overview
pipex is a project that explores **inter-process communication (IPC)** through UNIX **pipes**, mimicking the behavior of the shell when executing chained commands. This concept, first introduced in **1973**, allows data to flow between processes using a **buffer in kernel space**. The project strengthens the understanding of system calls, process management, and file handling.

## 🛠️ How It Works
pipex simulates the shell behavior when executing:
```sh
< infile cmd1 | cmd2 > outfile
```
The execution flow:
1. The program **creates a pipe**, establishing a unidirectional communication channel.
2. **Forks a child process** to execute `cmd1`, redirecting its output to the **write end** of the pipe.
3. Another **child process reads** from the **read end** of the pipe and executes `cmd2`, sending output to `outfile`.
4. Each process **closes its file descriptor** to ensure proper resource management and prevent descriptor leaks.

## 🔄 Buffer and Kernel-Space Communication
- A pipe consists of a **buffer created in kernel space**, allowing one process to write data that another process can read.
- The buffer temporarily holds data between the processes, avoiding direct file interaction.
- Proper **closing of file descriptors** ensures that resources are freed, preventing **inode table** saturation.

## 🚀 Usage
Compile the program:
```sh
make
```
Run pipex with an input file, two commands, and an output file:
```sh
./pipex infile "cmd1" "cmd2" outfile
```
Example:
```sh
./pipex input.txt "grep hello" "wc -l" output.txt
```
This is equivalent to running:
```sh
cat input.txt | grep hello | wc -l > output.txt
```

## 🎯 Key Takeaways
- Deepened understanding of **process creation (fork)** and **pipes**.
- Explored **kernel-space buffer usage** for efficient communication.
- Learned the importance of **closing file descriptors** to free inodes.
- Mimicked real shell behavior using **dup2** for redirection.

## 📜 License
This project is open-source and available under the MIT License.

---
pipex is a crucial step toward mastering process management in UNIX-based systems! 🚀

