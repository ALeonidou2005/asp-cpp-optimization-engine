# Army Scheduler Project (ASP) - C++ Optimization Engine

A C++ optimization engine that generates optimal duty schedules for military personnel using a two-phase approach: **optimized brute-force** to find valid solutions, followed by **simulated annealing** with geometric cooling to optimize for fairness and preferences.

![Output Example](output-screenshots/ASP%20C++%20Optimization%20Engine%20Output%201.png)

## Overview

This project solves the complex problem of scheduling military duty assignments across multiple days while satisfying **23 different constraints** related to availability, preferences, fairness, and operational requirements. The algorithm efficiently finds high-quality schedules that balance hard requirements with soft optimization goals.

**Key Features:**
- Handles 30+ personnel across a month-long scheduling period
- Enforces 15 fixed (mandatory) constraints
- Optimizes 8 additional constraints using simulated annealing
- Two-phase approach: validity search → quality optimization
- Weighted penalty system for comparing solution quality
- Cross-platform support (macOS, Linux, Windows)
- Designed as a shared library for integration with Unity frontend

**Part of a Larger System:**
This optimization engine serves as the backend for a Unity desktop application with a complete user interface. The Unity app allows users to configure constraints, input personnel data, and visualize and export the generated schedules. This repository focuses only on the backend core algorithmic component of the project.

## Algorithm Architecture

### Two-Phase Approach

**Phase 1: Finding Valid Solutions (Optimized Brute Force)**
- Builds schedules day-by-day using strategic backtracking
- When constraints become unsatisfiable, backtracks and tries alternative assignments
- Maximum iterations: 1,000,000 (configurable)
- Ensures the algorithm starts within the valid solution space before the optimization begins

**Phase 2: Optimization (Simulated Annealing)**
- Starts from a valid schedule found in Phase 1
- Iteratively explores neighboring valid schedules
- Optimizes the 8 soft constraints using weighted penalties
- Uses geometric cooling schedule with configurable parameters
- Maximum neighbor-finding attempts: 2,000,000 (configurable)

### Simulated Annealing Details

**Core Concept:**
Simulated annealing is inspired by the metallurgical process of annealing, where materials are heated and slowly cooled to reach their lowest-energy state. The algorithm balances exploration (trying diverse solutions at high temperature) with exploitation (refining solutions at low temperature).

**Acceptance Probability:**
```
P(accept worse solution) = e^(-ΔE/T)
```
where:
- `ΔE` = Energy increase (penalty increase)
- `T` = Current temperature

**Cooling Schedule (Geometric):**
```
T(k) = T₀ × α^k
```
where:
- `T₀` = Initial temperature
- `α` = Cooling rate (0.9-0.99 range)
- `k` = Iteration number

**Why Geometric Cooling:**
- Most commonly used and effective for most problems
- Faster than logarithmic, more controlled than linear
- Balances convergence speed with solution quality

**Temperature Phases:**
1. **High Temperature (Exploration):** Accepts many worse solutions to explore the solution space and escape local optima
2. **Low Temperature (Exploitation):** Becomes increasingly selective, refining the current solution toward a local optimum

**Neighbor Generation:**
The algorithm uses optimized brute-force to generate neighboring schedules by making small changes (e.g., swapping duty assignments) while maintaining validity of all 15 fixed constraints. This ensures every explored solution is still valid (in the valid solution space).

**Convergence:**
The algorithm terminates when:
- Maximum iterations reached, OR
- It's unable to find any more neighbour schedules that can potentially optimize the solution

## Constraints System

The scheduler handles **23 total constraints** divided into two categories:

### Fixed Constraints (15) - Must Be Satisfied

These are hard requirements that every valid schedule must meet:

1. **Duties per day**: Exact number of people required on duty each day
2. **No consecutive days**: Personnel cannot have duty on consecutive days
3. **Thursday-PSK rule**: If on duty Thursday, cannot have PSK (Fri-Sat-Sun) duty
4. **RED availability (Code 0)**: Guarantee no duty on that day
5. **GREEN availability (Code 2)**: Guarantee duty on that day
6. **Max duties per person**: Monthly limit on total duty days per person
7. **Max PSK duties per person**: Monthly limit on weekend (Fri-Sat-Sun) duties
8. **Max Monday duties**: Monthly limit per person
9. **Max Tuesday duties**: Monthly limit per person
10. **Max Wednesday duties**: Monthly limit per person
11. **Max Thursday duties**: Monthly limit per person
12. **Max Friday duties**: Monthly limit per person
13. **Max Saturday duties**: Monthly limit per person
14. **Max Sunday duties**: Monthly limit per person
15. **Min people per company**: Aim for a minimum staffing from each company (subunit) every day

### Optimized Constraints (8) - Soft Goals

These are optimized using simulated annealing with weighted penalties:

1. **Balance total duties**: Distribute total duty count evenly across all personnel
2. **Balance PSK duties**: Distribute (Friday-Saturday-Sunday) duties evenly across all personnel
3. **Min total duties per person**: Ensure each person gets at least a minimum number of duties
4. **Min PSK duties per person**: Ensure fair minimum distribution of weekend duties
5. **ORANGE preference (Code 4)**: Try to avoid assigning duty on that day
6. **LIGHT GREEN preference (Code 3)**: Try to assign duty on that day
7. **Spread out duties**: Spread out the duties of each person throughout the month
8. **Balance PSK (Friday-Saturday-Sunday) totals**: Ensure fair distribution of each (Friday-Saturday-Sunday) day type

Each optimized constraint has a configurable weight function, allowing fine-tuning of priorities. The total penalty is the weighted sum of individual penalties across all soft constraints.

## Project Structure

```
ASP-Optimization-Engine/
├── src/
│   ├── scheduler.cpp       # Core optimization engine (~1700 lines)
│   └── tester.cpp          # Test harness and library loader
├── tests/
│   └── input*.txt          # 19 test cases with various scenarios
├── output-screenshots/     # Sample terminal outputs showing schedule matrices
├── build.sh                # Compilation script
├── run.sh                  # Test execution script
├── .gitignore              # Git ignore rules
├── LICENSE                 # MIT License
└── README.md               # This file
```

## Requirements

- **Compiler**: g++ with C++17 support
- **Operating System**: macOS or Linux (Windows requires MinGW or WSL)
- **Dependencies**: None (uses only C++ STL)

## Building

1. **Clone the repository:**
```bash
git clone https://github.com/ALeonidou2005/asp-optimization-engine.git
cd asp-optimization-engine
```

2. **Build the project:**
```bash
bash build.sh
```

This compiles:
- `scheduler.dylib` - The optimization engine shared library
- `tester` - Test executable that loads and runs the library

## Usage

Run the test program with a specific test case:

```bash
bash run.sh [test_number]
```

**Examples:**
```bash
bash run.sh 1      # Run test case input1.txt (30 people, 30 days)
bash run.sh 18     # Run test case input18.txt
bash run.sh        # Defaults to test case 1
```

The test harness simulates the Unity frontend by initializing the scheduler with hardcoded constraint parameters before execution.

### Input Format

Test input files (`tests/inputN.txt`) contain:

**Line 1:** `[people] [days] [first_day_type]`
- `people`: Number of personnel (e.g., 30)
- `days`: Number of days in scheduling period (e.g., 30)
- `first_day_type`: Day of week the period starts (1=Monday, ..., 7=Sunday)

**Lines 2 to (people+1):** Availability/Preference Matrix
- `people × days` matrix of integers (0-4)
- Each row represents one person's preferences for each day

**Lines (people+2) to (2×people+1):** Historical Duty Totals
- `people × 7` matrix showing past duty counts
- Columns represent: Mon, Tue, Wed, Thu, Fri, Sat, Sun totals for each person
- Used to balance long-term fairness

**Line (2×people+2):** Company Assignments
- Array of size `people` with values 0,1, or 2
- Indicates which company (subunit) each person belongs to

**Availability/Preference Matrix Codes:**
- `0` = **RED** - Unavailable (guaranteed no duty)
- `1` = **WHITE** - No preference
- `2` = **GREEN** - Required (guaranteed duty)
- `3` = **LIGHT GREEN** - Prefer to have duty (optimized)
- `4` = **ORANGE** - Prefer not to have duty (optimized)

### Console Output

The test program produces comprehensive colored terminal output:

**Input Display:**
- Color-coded availability/preference matrix showing all personnel and days
- Historical duty totals for each person
- Company assignments

**Process Messages:**
- Real-time status updates during schedule generation
- Color-coded warnings (yellow) when the algorithm encounters difficulties
- Color-coded errors (red) when constraints cannot be satisfied or invalid states are reached

**Output Display:**
- Color-coded schedule matrix (see screenshot above)
- Rows represent personnel, columns represent days
- Visual indication of duty assignments

### DLL Output Format

When called from Unity (or the test harness), the library returns:

**Schedule Data:**
- Formatted C-array containing the complete schedule matrix
- Each element indicates duty status for person × day

**Metadata:**
- Final penalty score (weighted sum of soft constraint violations)
- Execution time breakdown:
  - Time to find initial valid schedule (Phase 1)
  - Time spent optimizing (Phase 2)
  - Total runtime
- Iteration counts and convergence statistics
- Success/failure status

This structured output allows the Unity frontend to display results, visualize statistics, and provide detailed feedback to users.

### Schedule Matrix Format

The core output is a schedule matrix where:
- Rows represent personnel (0-indexed)
- Columns represent days (0-indexed)
- Values indicate duty status:
  - `0` = Not on duty
  - `1` = On duty

Example output:
```
0: 0 1 0 0 0 0 1 0 0 0 1 0 0 0 0 ...
1: 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 ...
2: 1 0 0 0 0 1 0 0 0 0 0 1 0 0 0 ...
...
```

## Performance

Runtime depends on constraint tightness and input complexity:

**Typical Performance:**
- **Normal constraints**: ~1.5 seconds (30 people × 30 days)
- **Tight constraints**: ~3-5 seconds
- **Very tight or impossible constraints**: Up to 10 seconds before timeout

**Iteration Limits (configurable):**
- Initial valid schedule search: 1,000,000 max attempts
- Neighbor-finding during SA: 2,000,000 max attempts
- These limits translate to ~10 seconds worst-case on typical hardware

**Success Rate:**
Under realistic constraints, at least one valid schedule is almost always found. The algorithm will notify the user if no valid schedule exists (i.e., constraints are impossible to satisfy).

**Optimality:**
The simulated annealing phase explores the solution space to find high-quality schedules. While not guaranteed to find the global optimum (NP-hard problem), the algorithm consistently produces near-optimal solutions that are usually indistinguishable from optimal in real-world usage.

## Integration with Unity

This engine was designed as a backend library for a Unity desktop application:

**Architecture:**
1. **Compilation**: Built as a shared library (.dylib for macOS, .dll for Windows)
2. **Interface**: Exposes C-style functions callable from Unity via P/Invoke
3. **Configuration**: Unity UI sends constraint parameters via array to the DLL
4. **Data Transfer**: Results returned through callback functions to Unity
5. **Visualization**: Unity renders the schedule matrix with interactive UI

**Why Separate C++ Engine:**
- Performance: C++ is significantly faster for intensive optimization
- Portability: Same algorithm works across platforms
- Maintainability: Clean separation of concerns (algorithm vs. UI)

See the main Army Scheduler Project (ASP) repository for the complete Unity application with user interface.

## Technical Highlights

- **~1,700 lines of optimized C++17**
- Custom simulated annealing implementation from scratch
- Efficient constraint checking with early termination
- Optimized neighbor generation avoiding invalid states
- Weighted penalty system for soft constraint prioritization
- Memory-efficient data structures
- Cross-platform shared library (.dylib/.dll)
- Clean C-style API for external integration
- Comprehensive test suite with 19 diverse scenarios

## Development Context

Originally developed for the military of the Greek Cypriot National Guard to automate duty scheduling for corporals and reduce manual planning overhead. While military adoption was limited and still pending, this project demonstrates:

- **Algorithm Design**: Implementation of advanced optimization techniques
- **Problem Solving**: Real-world constraint satisfaction problem
- **Systems Programming**: Cross-platform C++ library development  
- **Software Architecture**: Clean separation of backend logic and frontend UI
- **Performance Engineering**: Optimized for speed and reliability
- **Integration Skills**: Bridging C++ with Unity/C# ecosystem

## Future Enhancements

Potential improvements for future versions:
- Adaptive cooling schedules based on input complexity
- Machine learning to auto-tune SA parameters
- Parallel neighbor exploration for faster convergence
- Add more personalised constraints to better satisfy the military personnel
- Experiment with different neighbour finding approaches and optimize further

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

**Antreas Leonidou**  
📧 leonidou.a24@gmail.com

Feel free to reach out for questions, collaboration opportunities, or discussions about optimization algorithms!
