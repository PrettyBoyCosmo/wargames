#!/usr/bin/env python3

from pwn import *

elf = context.binary = ELF("./just_do_it")
p = process(elf.path)

payload = b"P@SSW0RD\x00"

p.sendline(payload)
p.interactive()
