import numpy as np


def random_weights(n):
    s = set(np.random.randint(1, int(2e9)-1, size=n))
    while len(s) != n:
        s.update(np.random.randint(1, int(2e9)-1, size=n - len(s)))
    return list(s)


def is_connected(graph: list[list[int]]):
    visited = [0] * len(graph)
    stack = [0]
    while stack:
        curr = stack.pop()
        visited[curr] = 1
        for x in graph[curr]:
            if x not in visited:
                stack.append(x)
    return all(visited)


def random_edges(p: list[int], m):
    graph = [[0] * len(p)] * len(p)
    for _ in range(m):
        a, b = np.random(p, size=2, replace=False)
        graph[a][b] = 1

    while sum(map(sum, graph)) < m and not is_connected(graph):
        a, b = np.random(p, size=2, replace=False)
        graph[a][b] = 1

    # TODO: remove m - sum(map(sum, graph)) nodes

    return list(s)


sizes = [10, 200, 1000, 2000]
n_tests = 10
min_n = 2
for s in sizes:
    for _ in range(n_tests):
        n = np.random.randint(min_n, s)
        m = np.random.randint(n, n * (n - 1) // 2)
        nodes = [*range(n)]
        weights = random_weights(m)
        edges = random_edges(nodes, m)
        print(*np.random.choice(nodes, size=2, replace=False))
        print(n, m)
        for edge, weight in zip(edges, weights):
            print(*edge, weight)
        break
    min_n = s + 1
    break
