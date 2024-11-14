MAX_VARS = 100
MAX_FUNCS = 100
MAX_LINES = 1000


variables = {}
functions = {}

def assign_variable(line):
    parts = line.split(" ")
    if len(parts) >= 4 and parts[0] == "va" and parts[2] == "to":
        var_name = parts[1]
        
        value = line.split("to ", 1)[1].strip()
        if value.startswith('"') and value.endswith('"'):
            value = value[1:-1]  
        
        variables[var_name] = value
    else:
        print("Error in variable assignment.")

def show(line):
    parts = line.split(" ")
    if len(parts) >= 2 and parts[0] == "show":
        var_name = parts[1]
        if var_name in variables:
            
            print(variables[var_name])
        else:
            print(f"Variable {var_name} not found.")
    else:
        print("Error in show command.")

def define_function(lines, i):
    parts = lines[i].split(" ")
    if len(parts) >= 2 and parts[0] == "func":
        func_name = parts[1]
        i += 1
        func_body = []
        while i < len(lines) and lines[i] != "end":
            func_body.append(lines[i])
            i += 1
        functions[func_name] = func_body
    else:
        print("Error in function definition.")
    return i

def handle_if(lines, i):
    parts = lines[i].split(" ")
    if len(parts) >= 2 and parts[0] == "if":
        condition = parts[1]
        
        i += 1
        while i < len(lines) and lines[i] != "end":
            interpret([lines[i]])
            i += 1
    else:
        print("Error in if statement.")
    return i

def handle_for(lines, i):
    parts = lines[i].split(" ")
    if len(parts) >= 5 and parts[0] == "for" and parts[2] == "in" and parts[3].startswith("range("):
        var_name = parts[1]
        range_values = parts[3][6:-1].split(",")
        start, end = int(range_values[0]), int(range_values[1])
        for j in range(start, end + 1):
            variables[var_name] = str(j)
            i += 1
            while i < len(lines) and lines[i] != "end":
                interpret([lines[i]])
                i += 1
    else:
        print("Error in for loop.")
    return i

def handle_while(lines, i):
    parts = lines[i].split(" ")
    if len(parts) >= 2 and parts[0] == "while":
        condition = parts[1]
        
        i += 1
        while i < len(lines) and lines[i] != "end":
            interpret([lines[i]])
            i += 1
    else:
        print("Error in while loop.")
    return i

def input_variable(line):
    parts = line.split(" ")
    if len(parts) >= 2 and parts[0] == "input":
        var_name = parts[1]
        value = input(f"Enter value for {var_name}: ")
        variables[var_name] = value
    else:
        print("Error in input command.")

def print_value(line):
    parts = line.split(" ")
    if len(parts) >= 2 and parts[0] == "print":
        value = " ".join(parts[1:])
        print(value)
    else:
        print("Error in print command.")

def call_function(line):
    parts = line.split(" ")
    if len(parts) >= 1:
        func_name = parts[0]
        if func_name in functions:
            interpret(functions[func_name])
        else:
            print(f"Function {func_name} not found.")
    else:
        print("Error in function call.")

def interpret(lines):
    i = 0
    while i < len(lines):
        line = lines[i]
        if line.startswith("va "):
            assign_variable(line)
        elif line.startswith("show "):
            show(line)
        elif line.startswith("func "):
            i = define_function(lines, i)
        elif line.startswith("if "):
            i = handle_if(lines, i)
        elif line.startswith("for "):
            i = handle_for(lines, i)
        elif line.startswith("while "):
            i = handle_while(lines, i)
        elif line.startswith("input "):
            input_variable(line)
        elif line.startswith("print "):
            print_value(line)
        else:
            call_function(line)
        i += 1

def run_sky_code(file_path):
    with open(file_path, "r") as file:
        lines = file.read().splitlines()
    interpret(lines)

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python sky_interpreter.py <sky_code_file>")
    else:
        run_sky_code(sys.argv[1])
