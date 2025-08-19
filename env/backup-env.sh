#!/bin/sh

rm -f /home/bslin/var/backup.ran
rm -f /home/bslin/var/backup.log

echo "Running backup-env.sh ..." > /home/bslin/var/backup.log

# backup env files
cp /home/bslin/.bashrc        /home/bslin/gitwork/adgf/env/current.bashrc
cp /home/bslin/.bash_profile  /home/bslin/gitwork/adgf/env/current.bash_profile
cp /home/bslin/.profile       /home/bslin/gitwork/adgf/env/current.profile

# backup the backup script
cp /home/bslin/bin/backup-env.sh /home/bslin/gitwork/adgf/env/backup-env.sh

# create "i ran" file
touch /home/bslin/var/backup.ran

echo "Done backup.sh" >> /home/bslin/var/backup.log
/usr/bin/unix2dos /home/bslin/var/backup.log

#-- end of backup-env.sh
