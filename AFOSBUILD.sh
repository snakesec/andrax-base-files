cp -Rf os-release /etc/os-release

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Copy os-release... PASS!"
else
  # houston we have a problem
  exit 1
fi

chmod 644 /etc/os-release

cp -Rf os-release /usr/lib/os-release

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Copy lib os-release... PASS!"
else
  # houston we have a problem
  exit 1
fi

chmod 644 /usr/lib/os-release

cp -Rf 10-uname /etc/update-motd.d/10-uname

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Copy motd... PASS!"
else
  # houston we have a problem
  exit 1
fi

chmod 755 /etc/update-motd.d/10-uname

cp -Rf preferences /etc/apt/preferences

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Copy apt preferences... PASS!"
else
  # houston we have a problem
  exit 1
fi

chmod 644 /etc/apt/preferences

cp -Rf dumpkeys /opt/ANDRAX/bin

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Copy dumpkeys... PASS!"
else
  # houston we have a problem
  exit 1
fi

mkdir -p /opt/ANDRAX/dumpkeys

cp -Rf keymap-full.map keymap-keys-only.map keymap-long-info.map /opt/ANDRAX/dumpkeys

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Copy keymaps... PASS!"
else
  # houston we have a problem
  exit 1
fi

cp -Rf andrax-ng-default.png /usr/share/images/fluxbox/andrax-ng-default.png

chmod 755 /usr/share/images/fluxbox/andrax-ng-default.png

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Setup default wallpaper... PASS!"
else
  # houston we have a problem
  exit 1
fi

cp -Rf andrax-ng-style /usr/share/fluxbox/styles/andrax-ng

chmod 755 /usr/share/fluxbox/styles/andrax-ng

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Setup default STYLE... PASS!"
else
  # houston we have a problem
  exit 1
fi

cp -Rf .fluxbox /home/andrax/

chown -R andrax:andrax /home/andrax/.fluxbox

chmod -R 755 /home/andrax/.fluxbox

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Setup FLUXBOX... PASS!"
else
  # houston we have a problem
  exit 1
fi

cp -Rf vnc /etc/init.d/vnc

chown root:root /etc/init.d/vnc

chmod 755 /etc/init.d/vnc

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Setup VNC... PASS!"
else
  # houston we have a problem
  exit 1
fi


chown -R andrax:andrax /opt/ANDRAX/
chmod -R 755 /opt/ANDRAX/
