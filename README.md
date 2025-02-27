# AlgoSched: CPU Scheduling Algorithms Simulator

AlgoSched is a C++ simulator that implements and compares various CPU scheduling algorithms. The project supports both non-preemptive and preemptive algorithms and computes important metrics like turnaround time and waiting time for each simulation.

## Features

- **FCFS (First-Come, First-Served):** Non-preemptive scheduling based on arrival order.
- **SJF (Shortest Job First):** Non-preemptive scheduling that selects the process with the smallest burst time.
- **SRTF (Shortest Remaining Time First):** Preemptive version of SJF that selects the process with the smallest remaining time.
- **Priority Scheduling:** Preemptive scheduling based on process priority (with FCFS as a tie-breaker).
- **Round Robin:** Preemptive scheduling that gives each process a fixed time quantum.

## Project Structure

The project is organized into multiple files for better modularity:

AlgoSched/ ├── .vscode/ │ ├── tasks.json # Build task configuration for VS Code │ └── launch.json # Debug configuration for VS Code (optional) ├── fcfs.cpp # Implementation of FCFS algorithm ├── sjf.cpp # Implementation of SJF algorithm ├── srtf.cpp # Implementation of SRTF algorithm ├── priority.cpp # Implementation of Priority Scheduling ├── roundrobin.cpp # Implementation of Round Robin algorithm ├── utils.cpp # Utility functions for calculating averages (optional) ├── scheduling.h # Header file with common declarations and prototypes └── main.cpp # Main driver file for the simulator

mathematica
Copy
Edit

## Installation and Setup

### Prerequisites

- **C++ Compiler:**  
  - **Windows:** [MinGW](http://www.mingw.org/) or MSVC (Visual Studio Build Tools)  
  - **Linux/macOS:** GCC or Clang
- **Visual Studio Code:** [Download VS Code](https://code.visualstudio.com/)
- **C/C++ Extension for VS Code:** Install the "C/C++" extension by Microsoft from the VS Code Marketplace

### Setting Up in VS Code

1. **Clone or Download the Project:**
   - Clone the repository or download the source files into a folder (e.g., `AlgoSched`).

2. **Open the Folder in VS Code:**
   - Open VS Code and select **File > Open Folder...** to open your project folder.

3. **Configure Build Tasks:**
   - Inside the `AlgoSched` folder, create a folder named `.vscode` if it doesn't already exist.
   - Create a file named `tasks.json` inside `.vscode` with the following sample content:

     ```json
     {
         "version": "2.0.0",
         "tasks": [
             {
                 "label": "build AlgoSched",
                 "type": "shell",
                 "command": "g++",
                 "args": [
                     "-g",
                     "main.cpp",
                     "fcfs.cpp",
                     "sjf.cpp",
                     "srtf.cpp",
                     "priority.cpp",
                     "roundrobin.cpp",
                     "utils.cpp",  // Remove this line if not using utils.cpp
                     "-o",
                     "AlgoSched"
                 ],
                 "group": {
                     "kind": "build",
                     "isDefault": true
                 },
                 "problemMatcher": [
                     "$gcc"
                 ]
             }
         ]
     }
     ```

4. **(Optional) Configure Debugging:**
   - Create a `launch.json` file inside the `.vscode` folder with a configuration for your debugger. For example:

     ```json
     {
         "version": "0.2.0",
         "configurations": [
             {
                 "name": "Launch AlgoSched",
                 "type": "cppdbg",
                 "request": "launch",
                 "program": "${workspaceFolder}/AlgoSched",
                 "args": [],
                 "stopAtEntry": false,
                 "cwd": "${workspaceFolder}",
                 "environment": [],
                 "externalConsole": false,
                 "MIMode": "gdb",
                 "miDebuggerPath": "/usr/bin/gdb",  // Adjust this path as necessary
                 "setupCommands": [
                     {
                         "description": "Enable pretty-printing for gdb",
                         "text": "-enable-pretty-printing",
                         "ignoreFailures": true
                     }
                 ]
             }
         ]
     }
     ```

## Building and Running

### Using VS Code

1. **Build:**
   - Press `Ctrl+Shift+B` to build the project using the configured task.
2. **Run:**
   - Open the integrated terminal (`Ctrl+``) and execute the generated binary:
     - On Linux/macOS: `./AlgoSched`
     - On Windows: `AlgoSched.exe`

### Using Command Line

Open your terminal, navigate to the project folder, and run:

```bash
g++ -g main.cpp fcfs.cpp sjf.cpp srtf.cpp priority.cpp roundrobin.cpp utils.cpp -o AlgoSched
./AlgoSched   # On Windows, run AlgoSched.exe instead
Usage
When you run the simulator, it will prompt you for:

The number of processes.
Arrival time, burst time, and priority for each process.
The time quantum for Round Robin scheduling.
After providing the inputs, the simulator will execute each scheduling algorithm and display the average turnaround time and average waiting time for each.

Contributing
Contributions are welcome! Feel free to fork the repository, make improvements, and submit pull requests.

License
This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgments
This project was inspired by classical CPU scheduling algorithms and aims to provide an educational tool for understanding their behavior.
