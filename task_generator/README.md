1. Language: C++  
2. Compiler: Linux GNU g++

3. Compilation Instructions:
    If a Makefile is available, run the following command inside the task_generator/ directory:

        make

4. Execution and Usage Instructions:
    Input and parameter settings can be adjusted in the config file.  
    After compilation, the task_generator.exe file will be located in task_generator/.  
    To execute, simply run the program in the terminal.  
    The generated results will be saved in result.txt, formatted according to the example in the course materials.  
    For better readability, the terminal output might be more intuitive and straightforward than the result file.  

5. File Structure and Descriptions:
    task_generator/   
     │─ config.txt                      # Configuration file for input parameters  
     │─ constraint.c                    # Implementation of constraint, including set and get function  
     │─ constraint.h                    # Header file for constraint definitions  
     │─ main.c                          # Main entry point of the program, including writing result  
     │─ Makefile                        # Build script for compiling the project   
     │─ readConfig.c                    # Functions to read and parse the config file   
     │─ readConfig.h                    # Header file for readConfig.c   
     │─ README.md                       # Documentation for the project   
     │─ result.txt                      # Output file containing generated results   
     │─ task.c                          # Implementation of task-related functions   
     │─ task.h                          # Header file for task definitions  
		