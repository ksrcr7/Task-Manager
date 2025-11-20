# Task-Manager

A small, clean C++17 console app to manage tasks from the command line  
(`add / list / done / remove`) with **file persistence**.

This project is a follow-up to my Fraction Calculator and is focused on:

- Practicing **STL containers** and basic algorithms  
- Working with **file I/O** and a simple custom text format  
- **OOP design**, separation of concerns, and error handling  
- Designing a small but **testable and maintainable CLI tool**

---

## Features

- ✅ Add tasks with a textual title  
- ✅ List all tasks with stable numeric IDs  
- ✅ Mark tasks as done / not done  
- ✅ Remove tasks by ID  
- ✅ Persistent storage on disk (load/save between runs)  
- ✅ Input validation and basic error handling  
- ✅ Simple, explicit CLI interface (no hidden magic)

Tasks are stored in a plain text file so they survive between program runs.

---

## CLI Usage

The executable is called `TaskManager_CLI` (or `TaskManager_CLI.exe` on Windows).

General form:

```bash
TaskManager_CLI <command> [arguments...]


Commands
help
Show available commands and a short description.
TaskManager_CLI help


add <title>
Add a new task with the given title.
TaskManager_CLI add "Buy milk"
TaskManager_CLI add "Fix bug; urgent"
TaskManager_CLI add "Multi-line\\nnote"

list
List all current tasks:
TaskManager_CLI list

Example output:
(no tasks)
[ ] #1 : Buy milk
[x] #2 : Fix bug; urgent

[ ] → not done
[x] → done

done <id>
TaskManager_CLI done 1

Validation:
If id is missing → ID required.
If id is not a valid number → Invalid ID.
If no task with that ID exists → Not found.

remove <id>
Remove a task by ID:
TaskManager_CLI remove 2

Persistence & File Format
Tasks are stored in a text file, e.g.:
data/tasks.txt

escaping rules
To keep the format simple and robust, the title is escaped before writing:
\ → \\
; → \;
newline ('\n') → \n
carriage return ('\r') → \r
On load, the reverse transformation is applied (unescape), so the original title is restored exactly.
The next ID is computed as max(existing_ids) + 1, so IDs remain stable and unique over time.
-----------------------------------------------------------------------------------------------------
Build
Requirements
C++17-compatible compiler (g++, Clang, MSVC, …)
CMake 3.15+
Build with CMake (CLI):
git clone https://github.com/<your-username>/Task-Manager.git
cd Task-Manager

mkdir build
cd build

cmake ..
cmake --build .
-------------------------------------------------------------------------------------------------------

Project Structure:
Task-Manager/
├─ CMakeLists.txt
├─ include/
│  ├─ Task.h
│  ├─ TaskManager.h
│  └─ CLI.h
├─ src/
│  ├─ Task.cpp
│  ├─ TaskManager.cpp
│  ├─ CLI.cpp
│  └─ main.cpp
└─ data/
   └─ tasks.txt        (created at runtime)

--------------------------------------------------------------------------------------------------------
 Roadmap

 Basic CLI (add, list, done, remove)

 Load/Save from file with custom escaping

 Input validation & error handling

 Simple tests (assert or a lightweight test framework)

 Colored / nicer CLI output

 Interactive mode (REPL-style instead of single-command runs)

 Configurable storage path (via env var or CLI flag)
--------------------------------------------------------------------------------------------------------
Notes

This is a small learning project, focused on:

Writing clean, modular C++

Understanding string handling and file I/O

Designing a simple but realistic CLI tool

Feedback, ideas for improvement, or PRs are always welcome.






