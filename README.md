# KeePassStealer

Dump KeePass passwords for fun and educational purposes.
<br><br>
**Admin privileges required to write to the KeePass directory.**
<br>
`Wer.dll` can be sideloaded in `C:\Program Files\KeePass Password Safe 2` and does not intrupt normal operation of KeePass.
<br>

* Rename `KeePassStealer.dll` to `Wer.dll` and place in `KeePass Password Safe 2` directory.
* Launch KeePass.
* After master password is entered, `KeePass.loot` will be created in `C:\Temp` which contains all the passwords. The master password being the first entry.

<br>
Tested on KeePass 2.5.9
