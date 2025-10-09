#!/usr/bin/env python3

# Title:        foo.py
# Description:  foo
# Author:       bluecosmo

def direction(line):
    return ((line[0] - line[1]) * -1)

def main():

    count = 0;
    direction = 0;
    lines_read = open("./input", "r").readlines()

    for line in lines_read:

        line = line.strip().split(" ")
        line_len = len(line)

if __name__ == "__main__":
main()
