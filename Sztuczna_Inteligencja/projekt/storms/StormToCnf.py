import itertools
import argparse

class CNFEncoder:
    def __init__(self):
        self.var_map = {}
        self.var_counter = 1
        self.clauses = []

    def get_var(self, name):
        if name not in self.var_map:
            self.var_map[name] = self.var_counter
            self.var_counter += 1
        return self.var_map[name]

    def add_clause(self, literals):
        self.clauses.append(literals)

    def write_dimacs(self, filename):
        with open(filename, 'w') as f:
            f.write(f"p cnf {self.var_counter - 1} {len(self.clauses)}\n")
            for clause in self.clauses:
                f.write(" ".join(str(lit) for lit in clause) + " 0\n")

    def write_cells_nums(self, filename):
        with open(filename, 'w') as f:
            for key in self.var_map:
                if 'x' in key:
                    f.write(f"{key} {self.var_map[key]}\n")

# all lists of length n of 1s and 0s
# where there are exactly clue 1s
def get_sequences(n, clue):
    result = []
    for ones_positions in itertools.combinations(range(n), clue):
        lst = [0] * n
        for pos in ones_positions:
            lst[pos] = 1
        result.append(lst)
    return result

def encode_line(encoder, cells, clue, prefix):
    valid_layouts = get_sequences(len(cells), clue)
    layout_vars = []

    for idx, layout in enumerate(valid_layouts):
        layout_var = encoder.get_var(f"{prefix}_{idx}")
        layout_vars.append(layout_var)
        for cell_val, cell in zip(layout, cells):
            x = encoder.get_var(cell)
            if cell_val:
                encoder.add_clause([-layout_var, x])
            else:
                encoder.add_clause([-layout_var, -x])

    encoder.add_clause(layout_vars)

    for a, b in itertools.combinations(layout_vars, 2):
        encoder.add_clause([-a, -b])

def encode_square_requirements(encoder, n_rows, n_cols):
    for i in range(n_rows - 1):
        for j in range(n_cols - 1):
            a = encoder.get_var(f"x_{i}_{j}")
            b = encoder.get_var(f"x_{i}_{j+1}")
            c = encoder.get_var(f"x_{i+1}_{j}")
            d = encoder.get_var(f"x_{i+1}_{j+1}")

            encoder.add_clause([ a, -b, -c, -d ])
            encoder.add_clause([-a,  b, -c, -d ])
            encoder.add_clause([-a, -b,  c, -d ])
            encoder.add_clause([-a, -b, -c,  d ])

            encoder.add_clause([-a, b, c, -d])
            encoder.add_clause([a, -b, -c, d])

def encode_line_requirements(encoder, n_rows, n_cols):
    for i in range(n_rows):
        for j in range(n_cols - 2):
            x = encoder.get_var(f"x_{i}_{j}")
            y = encoder.get_var(f"x_{i}_{j+1}")
            z = encoder.get_var(f"x_{i}_{j+2}")
            encoder.add_clause([x, -y, z])

        y = encoder.get_var(f"x_{i}_0")
        z = encoder.get_var(f"x_{i}_1")
        encoder.add_clause([-y, z])

        x = encoder.get_var(f"x_{i}_{n_cols - 2}")
        y = encoder.get_var(f"x_{i}_{n_cols - 1}")
        encoder.add_clause([x, -y])

    for j in range(n_cols):
        for i in range(n_rows - 2):
            x = encoder.get_var(f"x_{i}_{j}")
            y = encoder.get_var(f"x_{i+1}_{j}")
            z = encoder.get_var(f"x_{i+2}_{j}")
            encoder.add_clause([x, -y, z])

        # Top border: row 0 and 1
        y = encoder.get_var(f"x_{0}_{j}")
        z = encoder.get_var(f"x_{1}_{j}")
        encoder.add_clause([-y, z])

        # Bottom border: rows n-2 and n-1
        x = encoder.get_var(f"x_{n_rows - 2}_{j}")
        y = encoder.get_var(f"x_{n_rows - 1}_{j}")
        encoder.add_clause([x, -y])


def encode_storm(n_rows, n_cols, row_clues, col_clues):
    encoder = CNFEncoder()

    for i in range(n_rows):
        cells = [f"x_{i}_{j}" for j in range(n_cols)]
        encode_line(encoder, cells, row_clues[i], f"r{i}")

    for j in range(n_cols):
        cells = [f"x_{i}_{j}" for i in range(n_rows)]
        encode_line(encoder, cells, col_clues[j], f"c{j}")
    
    encode_square_requirements(encoder,n_rows,n_cols)

    encode_line_requirements(encoder,n_rows,n_cols)

    return encoder

def parse_input_file(filename):
    with open(filename) as f:
        lines = [line.strip() for line in f if line.strip()]
    n_rows, n_cols = map(int, lines[0].split())
    row_clues = [int(line.split()[0]) for line in lines[1:1 + n_rows]]
    col_clues = [int(line.split()[0]) for line in lines[1 + n_rows:]]
    return n_rows, n_cols, row_clues, col_clues

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process SAT solution and variable mapping.")
    parser.add_argument("input_file", help="Path to the cell definitions file (e.g., cells_def.txt)")
    parser.add_argument("solution", help="Path to the SAT solver output file (e.g., solution.txt)")
    args = parser.parse_args()

    n_rows, n_cols, row_clues, col_clues = parse_input_file(args.input_file)

    encoder = encode_storm(n_rows, n_cols, row_clues, col_clues)

    encoder.write_dimacs(args.solution)
    encoder.write_cells_nums("cells_def.txt")