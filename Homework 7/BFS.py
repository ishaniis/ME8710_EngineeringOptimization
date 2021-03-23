# for convenience
matrix = [
    ["0", "0", "0", "0", "1", "0", "0", "0"],
    ["0", "1", "1", "0", "1", "0", "1", "0"],
    ["0", "1", "0", "0", "1", "0", "1", "0"],
    ["0", "0", "0", "1", "0", "0", "1", "0"],
    ["0", "1", "0", "1", "0", "1", "1", "0"],
    ["0", "0", "1", "1", "0", "1", "0", "0"],
    ["1", "0", "0", "0", "0", "1", "1", "0"],
    ["0", "0", "1", "1", "1", "1", "0", "0"]
]
num_rows = len(matrix)
num_cols = len(matrix[0])

# just to be a bit more flexible, could also be passed as a function argument
goal_state = (num_rows - 1, num_cols - 1)


def dfs(current_path):
    # anchor
    row, col = current_path[-1]
    if (row, col) == goal_state:
        return True

    # try all directions one after the other
    for direction in [(row, col + 1), (row, col - 1), (row + 1, col), (row - 1, col)]:
        new_row, new_col = direction
        if (0 <= new_row < num_rows and 0 <= new_col < num_cols and  # stay in matrix borders
                matrix[new_row][new_col] == "0" and                  # don't run in walls
                (new_row, new_col) not in current_path):             # don't run in circles
            # try new direction
            current_path.append((new_row, new_col))
            if dfs(current_path):  # recursive call
                return True
            else:
                current_path.pop()  # backtrack


# result a list of coordinates which should be taken in order to reach the goal
result = [(0, 0)]
if dfs(result):
    print("Success!")
    print(result)
else:
    print("Failure!")