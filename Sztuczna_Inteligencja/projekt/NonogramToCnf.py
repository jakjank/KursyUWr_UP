import itertools
import pprint

class CNFEncoder: #check
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

    def write_definitions(self):
        pprint.pprint(self.var_map)

    def write_cells_nums(self, filename):
        with open(filename, 'w') as f:
            for key in self.var_map:
                if 'x' in key:
                    f.write(f"{key} {self.var_map[key]}\n")

def parse_input_file(filename): #check
    with open(filename) as f:
        lines = [line.strip() for line in f if line.strip()]
    n_rows, n_cols = map(int, lines[0].split())
    row_clues = [list(map(int, line.split())) for line in lines[1:1 + n_rows]]
    col_clues = [list(map(int, line.split())) for line in lines[1 + n_rows:]]
    return n_rows, n_cols, row_clues, col_clues

def generate_block_positions(length, blocks):
    if not blocks:
        yield [0] * length
        return

    total_blocks = sum(blocks)
    min_spaces = len(blocks) - 1
    free_space = length - total_blocks - min_spaces

    def place_block(start_idx, block_idx, row):
        if block_idx == len(blocks):
            yield row
            return

        block_len = blocks[block_idx]
        max_start = length - (sum(blocks[block_idx:]) + (len(blocks) - block_idx - 1))
        for i in range(start_idx, max_start + 1):
            new_row = row[:]
            for j in range(i, i + block_len):
                new_row[j] = 1
            next_start = i + block_len + 1
            yield from place_block(next_start, block_idx + 1, new_row)

    yield from place_block(0, 0, [0] * length)


def encode_line(encoder, cells, clues, prefix):
    valid_layouts = list(get_sequences(len(cells), clues))
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

    # 🔵 Wymagamy: przynajmniej jeden layout (OR)
    encoder.add_clause(layout_vars)

    # 🔴 Wymagamy: najwyżej jeden (mutual exclusion)
    for a, b in itertools.combinations(layout_vars, 2):
        encoder.add_clause([-a, -b])


def encode_nonogram(n_rows, n_cols, row_clues, col_clues): #check
    encoder = CNFEncoder()

    # Wiersze
    for i in range(n_rows):
        cells = [f"x_{i}_{j}" for j in range(n_cols)]
        encode_line(encoder, cells, row_clues[i], f"r{i}")

    # Kolumny
    for j in range(n_cols):
        cells = [f"x_{i}_{j}" for i in range(n_rows)]
        encode_line(encoder, cells, col_clues[j], f"c{j}")

    return encoder

def get_sequences(n: int, clues: list[int]): #check
    def backtrack(pos: int, clue_idx: int, current: list[int]):
        if clue_idx == len(clues):
            # Fill the rest with 0s if needed
            result.append(current + [0] * (n - len(current)))
            return

        block_len = clues[clue_idx]

        # Try placing the block at all valid positions starting from 'pos'
        for start in range(pos, n - block_len + 1):
            # Ensure there is enough space after this block
            new_seq = current + [0] * (start - len(current)) + [1] * block_len
            if len(new_seq) < n:
                new_seq.append(0)  # Add space after block (except at the end)
            backtrack(len(new_seq), clue_idx + 1, new_seq)

    result = []
    if clues:
        backtrack(0, 0, [])
    else:
        result.append([0] * n)
    return result

if __name__ == "__main__":
    input_file = "nonogram.txt"
    output_file = "nonogram.cnf"

    n_rows, n_cols, row_clues, col_clues = parse_input_file(input_file)

    encoder = encode_nonogram(n_rows, n_cols, row_clues, col_clues)

    encoder.write_dimacs(output_file)

    # encoder.write_definitions()
    encoder.write_cells_nums("cells_def.txt")
    # print(f"CNF zapisany do {output_file}. Liczba zmiennych: {encoder.var_counter - 1}, klauzul: {len(encoder.clauses)}")
