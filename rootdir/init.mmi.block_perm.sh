#!/system/bin/sh

block_by_name=/dev/block/platform/soc.0/by-name
utags=${block_by_name}/utags
utags_backup=${block_by_name}/utagsBackup
cid=${block_by_name}/cid

# Set correct permissions for UTAGS
/system/bin/chown -L mot_tcmd:system $utags
/system/bin/chown -L mot_tcmd:system $utags_backup
/system/bin/chmod -L 0660 $utags
/system/bin/chmod -L 0660 $utags_backup

# Set correct permissions for CID
/system/bin/chown -L root:mot_dbvc $cid
/system/bin/chmod -L 0660 $cid

# HOB/DHOB
hob=${block_by_name}/hob
dhob=${block_by_name}/dhob
/system/bin/chown -L radio:radio $hob
/system/bin/chown -L radio:radio $dhob
/system/bin/chmod -L 0660 $hob
/system/bin/chmod -L 0660 $dhob

