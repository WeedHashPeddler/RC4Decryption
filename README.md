tlscsp.dll — Ghosted Microsoft RC4 LOLBin (BYOK encrypt/decrypt primitive)

A Microsoft-signed, never-loaded DLL that ships a hardcoded RC4 key.
Call LsCsp_EncryptHwid -> get RC4 encrypt/decrypt running inside trusted
Windows code, with zero crypto in your own binary.

# tlscsp.dll — Ghosted Microsoft RC4 LOLBin

`tlscsp.dll` ("Microsoft Remote Desktop Services Cryptographic Utility") is a
Microsoft-signed DLL in System32 that is **unloaded by default**. Its export
`LsCsp_EncryptHwid` performs **RC4 with a 16-byte key hardcoded in `.rdata`.


## Tested on

Windows 11 latest build (25H2). Older Windows builds ship a slightly different
`tlscsp.dll`, so the key offset may need a small tweak — not covered here.
