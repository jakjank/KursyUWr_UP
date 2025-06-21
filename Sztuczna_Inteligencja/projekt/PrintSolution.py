import argparse

def load_cell_mapping(filename):
    mapping = {}
    with open(filename) as f:
        for line in f:
            name, var = line.strip().split()
            mapping[int(var)] = name
    return mapping

def load_solution(filename):
    result = set()
    with open(filename) as f:
        for line in f:
            if line.startswith('SAT'):
                continue
            result = result.union(set(int(x) for x in line.strip().split() if int(x) > 0))
    return result

def build_grid(mapping, solution):
    # Extract coordinates and determine grid size
    coords = [tuple(map(int, name.split('_')[1:])) for name in mapping.values()]
    max_row = max(r for r, c in coords)
    max_col = max(c for r, c in coords)
    
    # Build reverse mapping from var -> (row, col)
    var_to_pos = {var: tuple(map(int, name.split('_')[1:])) for var, name in mapping.items()}
    
    # Initialize grid
    grid = [['.' for _ in range(max_col + 1)] for _ in range(max_row + 1)]
    
    for var in solution:
        if var in var_to_pos:
            row, col = var_to_pos[var]
            grid[row][col] = '#'
    
    return grid

def print_grid(grid):
    for row in grid:
        print(''.join(row))

# ==== Main ====
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process SAT solution and variable mapping.")
    parser.add_argument("cell_file", help="Path to the cell definitions file (e.g., cells_def.txt)")
    parser.add_argument("solution_file", help="Path to the SAT solver output file (e.g., solution.txt)")
    args = parser.parse_args()
    
    mapping = load_cell_mapping(args.cell_file)
    solution = load_solution(args.solution_file)
    grid = build_grid(mapping, solution)
    print_grid(grid)
