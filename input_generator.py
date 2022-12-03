import random

random.seed(42)

sizes = [10, 50, 100, 150]

for size in sizes:
    tuple_numbers = [(random.uniform(0, 100), random.uniform(0, 100)) for _ in range(size)]

    with open(f'inputs/input-{size}.txt', 'w') as file:
        file.write(f"{size} \n")
        for tuple_number in tuple_numbers:
            file.write(f"{tuple_number[0]} {tuple_number[1]}\n")
