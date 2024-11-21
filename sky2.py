MAX_VARS = 100
MAX_FUNCS = 100
MAX_LINES = 1000

variables = {}
functions = {}

def parse_value(value):
   
    try:
        if value.isdigit():
            return int(value)
        elif value.replace(".", "", 1).isdigit():
            return float(value)
        elif value.lower() == "true":
            return True
        elif value.lower() == "false":
            return False
        elif value.startswith("[") and value.endswith("]"):
            return eval(value)  
        elif value.startswith("{") and value.endswith("}"):
            return eval(value) 
        return value  
    except:
        print(f"Error: Invalid value '{value}'.")
        return None

def assign_variable(line):
    parts = line.split(" ")
    if len(parts) >= 4 and parts[0] == "va" and parts[2] == "to":
        var_name = parts[1]
        value = line.split("to ", 1)[1].strip()
        variables[var_name] = parse_value(value)
        if len(variables) > MAX_VARS:
            print("Error: Maximum variable limit reached.")
            del variables[var_name]
    else:
        print("Error in variable assignment.")

def show(line):
    parts = line.split(" ")
    if len(parts) >= 2 and parts[0] == "show":
        var_name = parts[1]
        if var_name in variables:
            print(variables[var_name])
        else:
            print(f"Error: Variable {var_name} not found.")
    else:
        print("Error in show command.")

def list_append(line):
    
    parts = line.split(" ")
    if len(parts) >= 4 and parts[0] == "add" and parts[2] == "to":
        value = parse_value(parts[1])
        var_name = parts[3]
        if var_name in variables and isinstance(variables[var_name], list):
            variables[var_name].append(value)
        else:
            print(f"Error: {var_name} is not a list or does not exist.")
    else:
        print("Error in add command.")

def handle_len(line):
   
    parts = line.split(" ")
    if len(parts) == 2 and parts[0] == "len":
        var_name = parts[1]
        if var_name in variables:
            print(len(variables[var_name]))
        else:
            print(f"Error: Variable {var_name} not found.")
    else:
        print("Error in len command.")

def import_module(line):
    
    parts = line.split(" ")
    if len(parts) >= 2 and parts[0] == "excuse":
        module_name = parts[1]
        try:
            globals()[module_name] = __import__(module_name)
            print(f"Module {module_name} imported.")
        except ImportError:
            print(f"Error: Module {module_name} not found.")
    else:
        print("Error in excuse command.")

def evaluate_condition(condition):
    
    try:
        return eval(condition, {}, variables)
    except Exception:
        print(f"Error: Invalid condition '{condition}'.")
        return False

def handle_if(lines, i):
    parts = lines[i].split(" ", 1)
    if len(parts) >= 2 and parts[0] == "if":
        condition = parts[1]
        if evaluate_condition(condition):
            i += 1
            while i < len(lines) and lines[i] != "end":
                interpret([lines[i]])
                i += 1
        else:
            while i < len(lines) and lines[i] != "end":
                i += 1
    else:
        print("Error in if command.")
    return i

def interpret(lines):
    i = 0
    while i < len(lines):
        line = lines[i]
        if line.startswith("va "):
            assign_variable(line)
        elif line.startswith("show "):
            show(line)
        elif line.startswith("add "):
            list_append(line)
        elif line.startswith("len "):
            handle_len(line)
        elif line.startswith("excuse "):
            import_module(line)
        elif line.startswith("if "):
            i = handle_if(lines, i)
        elif line.startswith("print "):
            print_value(line)
        else:
            print(f"Error: Unknown command '{line.split(' ')[0]}'.")
        i += 1

def run_sky_code(file_path):
    with open(file_path, "r") as file:
        lines = file.read().splitlines()
    if len(lines) > MAX_LINES:
        print("Error: Code exceeds maximum allowed lines.")
        return
    interpret(lines)

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python sky2.py <sky_code_file>")
    else:
        run_sky_code(sys.argv[1])
