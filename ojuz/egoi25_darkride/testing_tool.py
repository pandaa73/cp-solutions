#!/usr/bin/env python3

"""
Example usage:

First create an input file, like "sample1.in" with the following contents:
5
2 1 0 3 4

For python programs, say "solution.py" (normally run as "pypy3 solution.py"):

    python3 testing_tool.py pypy3 solution.py < sample1.in

For C++ programs, first compile it
(e.g. with "g++ -g -O2 -std=gnu++20 -static  solution.cpp -o solution.out")
and then run

    python3 testing_tool.py ./solution.out < sample1.in

"""

from fcntl import fcntl
import sys
import os
import signal
from typing import List, Tuple

F_SETPIPE_SZ = 1031

MAX_QUERIES = 30


def error(msg: str) -> None:
    print("ERROR:", msg, file=sys.stderr)
    sys.exit(1)

def wait_for_child(pid: int) -> None:
    pid, status = os.waitpid(pid, 0)
    if os.WIFSIGNALED(status):
        sig = os.WTERMSIG(status)
        error(f"Program terminated with signal {sig} ({signal.Signals(sig).name})")
    ex = os.WEXITSTATUS(status)
    if ex != 0:
        error(f"Program terminated with exit code {ex}")

def read_line(pid: int, file, what: str) -> str:
    line = file.readline()
    if not line:
        wait_for_child(pid)
        error(f"Failed to read {what}: no more output")
    return line.rstrip("\r\n")

def write_line(file, line: str) -> None:
    try:
        file.write(line + "\n")
        file.flush()
    except BrokenPipeError:
        pass

def run_solution(submission: List[str], N: int, perm: List[int], silent: bool):

    c2p_read, c2p_write = os.pipe()
    p2c_read, p2c_write = os.pipe()
    try:
        fcntl(p2c_read, F_SETPIPE_SZ, 1024 * 1024)
    except Exception:
        print("Warning: failed to increase pipe capacity. This may lead to hangs.")
    pid = os.fork()

    if pid == 0:
        os.close(p2c_write)
        os.close(c2p_read)

        os.dup2(p2c_read, 0)
        os.dup2(c2p_write, 1)

        try:
            os.execvp(submission[0], submission)
        except Exception as e:
            error(f"Failed to execute program: {e}")
        assert False, "unreachable"
    else:
        os.close(c2p_write)
        os.close(p2c_read)

        with os.fdopen(p2c_write, "w") as fout:
            with os.fdopen(c2p_read, "r") as fin:

                queries = 0
                marked_at_query = [-1]*N
                write_line(fout, f"{N}")
                while True:

                    line = read_line(pid, fin, f"query {queries+1}")
                    tokens = line.split();
                    if len(tokens) < 1 or (tokens[0] != '!' and tokens[0] != '?'):
                        error(f"[Query {queries+1}] Expected line with ? or !, got: \"{line}\"")
                    if tokens[0] == '!':
                        if len(tokens) != 3:
                            error(f"Answer ! should be followed by two integers, got \"{line}\"")
                        if not silent:
                            print(f"[*] Answered: {line}")

                        a, b = int(tokens[1]), int(tokens[2])
                        if a < 0 or b < 0 or a >= N or b >= N:
                            error(f"Answer numbers out of range; got: {line}")

                        a, b = sorted([perm[int(tokens[1])], perm[int(tokens[2])]])
                        if a != 0 or b != N-1:
                            error(f"Wrong Answer: correct answer is ({perm.index(0)}, {perm.index(N-1)}), but got \"{line}\"")
                            break
                        # Wait for program to terminate, and read all its output
                        remainder = fin.read()
                        if remainder.strip():
                            error(f"Unexpected trailing output: {remainder}")
                        wait_for_child(pid)

                        return queries

                    elif tokens[0] == '?':
                        queries = queries + 1

                        s = ''.join(tokens[1:])
                        if not all(c in "01" for c in s):
                            error(f"Unknown character in query string; got: \"{line}\"")
                        if len(s) != N:
                            error(f"Query ? should be followed by N bits; got: \"{line}\"")

                        if not silent:
                            print(f"[*] Query #{queries}: {line}")

                        if queries > MAX_QUERIES: 
                            error(f"Too many queries")

                        todo = []
                        for i in [j for j in range(N) if s[j] == '1']:
                            x = perm[i]
                            marked_at_query[x] = queries
                            todo.extend([x])
                            if x > 0:
                                todo.append(x - 1)
                            if x + 1 < N:
                                todo.append(x + 1)

                        todo = sorted(set(todo))

                        changes = 0
                        for i in range(len(todo) - 1):
                            green1 = marked_at_query[todo[i]] == queries
                            green2 = marked_at_query[todo[i + 1]] == queries
                            if green1 != green2:
                                changes += 1

                        if not silent:
                            print(f"[*] -> {changes}")

                        write_line(fout, f"{changes}")


def main() -> None:
    silent = False
    args = sys.argv[1:]
    if args and args[0] == "--silent":
        args = args[1:]
        silent = True
    if not args:
        print("Usage:", sys.argv[0], '[--silent] program... < inputfile')
        sys.exit(0)

    toks = []
    for line in sys.stdin:
        for tok in line.split():
            toks.append(int(tok))
        if toks and len(toks) >= 2:
            break

    N = toks[0]
    if len(toks[1:]) != N:
        error("input must be integer N followed by N unique numbers in [0,N-1]")

    print(f"[*] Running solution (N = {N})")

    queries = run_solution(args, N, toks[1:], silent)

    query_text = "queries" if queries != 1 else "query"
    print("[*] Finished running solution")
    print(f"[*] Correctly solved test case using {queries} {query_text}")

if __name__ == "__main__":
    main()

