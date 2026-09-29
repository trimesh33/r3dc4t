#!/usr/bin/env python3

from pathlib import Path
import sys

STORAGE_OFFSET = 0x100000
SECTOR_SIZE = 512
SECTOR_COUNT = 2048
MASK32 = 0xFFFFFFFF


def decrypt_sector(encrypted, lba):
    sector = bytearray(encrypted)
    state = (0x9E37A9EA + lba * 0x38C9CDA0) & MASK32

    for block in range(0, SECTOR_SIZE, 16):
        for i in range(16):
            value = (state + (i - 1) * 0x9E3779B1) & MASK32
            sector[block + i] ^= value >> 24
        state = (state + 0x41C64E6D) & MASK32

    return bytes(sector)


def decrypt_firmware(firmware):
    res = bytearray()
    for lba in range(SECTOR_COUNT):
        start = STORAGE_OFFSET + lba * SECTOR_SIZE
        res += decrypt_sector(firmware[start:start + SECTOR_SIZE], lba)
    return bytes(res)


src, dest = map(Path, [sys.argv[1], "drive.img"])
dest.write_bytes(decrypt_firmware(src.read_bytes()))
print(f"written {dest} ({dest.stat().st_size} bytes)")
