FILE = "test_storms/hard_pic.txt"

with open(FILE) as f:
    lines = [line.strip() for line in f if line.strip()]

for line in lines:
    print(line.count("#"))

for column in zip(*lines):
    print(column.count("#"))