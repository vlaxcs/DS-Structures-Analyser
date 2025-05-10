import random
import time
import numpy as np
import os

def alternating_insert_delete(n, startingInserts, value_range):
    commands = []
    inserted = set()

    n = n - startingInserts
    startingInserts = startingInserts + 1

    if n <= 0: return []

    n = n // 2

    for _ in range(startingInserts):
        val_insert = random.randint(*value_range)
        commands.append(f"insert {val_insert}")
        inserted.add(val_insert)

    for _ in range(n):
        val_insert = random.randint(*value_range)
        commands.append(f"insert {val_insert}")
        inserted.add(val_insert)

        if inserted:
            val_delete = random.choice(list(inserted))
            commands.append(f"delete {val_delete}")
            inserted.discard(val_delete)
    return commands

def sorted_insert(n, descending=False):
    numbers = list(range(1, n + 1))
    if descending:
        numbers.reverse()
    return [f"insert {x}" for x in numbers]

def random_insert_only(n, value_range=(1, 100)):
    return [f"insert {random.randint(*value_range)}" for _ in range(n)]

def random_insert_and_contains(n_insert, n_contains, value_range):
    commands = []
    inserted = set()

    for _ in range(n_insert):
        val = random.randint(*value_range)
        commands.append(f"insert {val}")
        inserted.add(val)

    for _ in range(n_contains):
        # 50% chance to saerch for searching for an element that wasnt inserted
        if inserted and random.random() < 0.5:
            val = random.choice(list(inserted))
        else:
            val = random.randint(*value_range)
        commands.append(f"contains {val}")

    return commands

def full_random_mixed(n_ops, insert_prob=0.4, contains_prob=0.4, delete_prob=0.2, value_range=(1, 100)):
    commands = []
    inserted = set()

    for _ in range(n_ops):
        op_choice = random.random()
        if op_choice < insert_prob:
            val = random.randint(*value_range)
            commands.append(f"insert {val}")
            inserted.add(val)
        elif op_choice < insert_prob + contains_prob:
            if inserted and random.random() < 0.5:
                val = random.choice(list(inserted))
            else:
                val = random.randint(*value_range)
            commands.append(f"contains {val}")
        else:
            if inserted and random.random() < 0.7:
                val = random.choice(list(inserted))
                inserted.discard(val)
            else:
                val = random.randint(*value_range)
            commands.append(f"delete {val}")
    return commands

def zipfian_access_test(n_ops, n_keys, insert_prob=0.4, contains_prob=0.4, delete_prob=0.2, zipf_param=1.5):
    commands = []
    inserted = set()

    # Generate a pool of keys (1..n_keys) with Zipfian weighting
    zipf_keys = np.random.zipf(zipf_param, size=n_ops * 2)
    zipf_keys = [k for k in zipf_keys if k <= n_keys][:n_ops]
    if len(zipf_keys) < n_ops:
        return []

    for i in range(n_ops):
        val = zipf_keys[i]

        op_choice = random.random()
        if op_choice < insert_prob:
            commands.append(f"insert {val}")
            inserted.add(val)
        elif op_choice < insert_prob + contains_prob:
            if inserted and random.random() < 0.7:
                val = random.choice(list(inserted))
            commands.append(f"contains {val}")
        else:
            if inserted and val in inserted:
                inserted.discard(val)
            commands.append(f"delete {val}")

    return commands





def save_to_file(filename, commands):
    with open(filename, "w") as f:
        for cmd in commands:
            f.write(cmd + "\n")
    print(f"Saved {filename}")


random.seed(42)

n = 100_000
value_range = (1, 10000000)

save_to_file(f"Tests/random_I_{n}.txt", random_insert_only(n, value_range))
save_to_file(f"Tests/alternating_ID_{n}.txt", alternating_insert_delete(n, n // 4, value_range))
save_to_file(f"Tests/sortedAscending_I_{n}.txt", sorted_insert(n, False))
save_to_file(f"Tests/sortedDescending_I_{n}.txt", sorted_insert(n, True))
save_to_file(f"Tests/random_IC_{n}.txt", random_insert_and_contains(n // 2, n // 2, value_range))
save_to_file(f"Tests/random_ICD_{n}.txt", full_random_mixed(n, 0.4, 0.4, 0.2, value_range))
save_to_file(f"Tests/zipfian_ICD_{n}.txt", zipfian_access_test(n, n // 2, 0.4, 0.4, 0.2, 1.5))


# save_to_file("test_sorted_ascending.txt", sorted_insert(n, descending=False))
# save_to_file("test_sorted_descending.txt", sorted_insert(n, descending=True))

# save_to_file("test_random_insert_and_contains.txt", random_insert_and_contains(n_insert=30, n_contains=30, value_range=value_range))
# save_to_file("test_random_full_mixed.txt", full_random_mixed(n_ops=60, insert_prob=0.4, contains_prob=0.4, delete_prob=0.2, value_range=value_range))
# save_to_file("zipfian.txt", zipfian_access_test(n_ops=100, n_keys=50, insert_prob=0.4, contains_prob=0.4, delete_prob=0.2, zipf_param=1.5))