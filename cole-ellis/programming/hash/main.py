#!/usr/bin/env python3

# Title:        main.py
# Description:  Hash Solution (Cole Ellis)
# Author:       bluecosmo

import hashlib

def main():
    n = 1
    key = "ckczppom"

    while True:
        hash_object = hashlib.md5((key + str(n)).encode("utf-8"))
        hash = hash_object.hexdigest()

        print(f"[*] N: {n}")
        print(f"[*] Hash: {hash}")

        if (str(hash)[0:6] == '000000'):
            print(f"Cosmo: flag{ {n} }")
            break

        n += 1

    print("Ellis: flag{3938038}")

if __name__ == "__main__":
    main()
