dpkg-divert --local --rename --add /etc/os-release
dpkg-divert --local --rename --add /etc/update-motd.d/10-uname

chmod 777 /etc/os-release

NEW_VERSION=$(grep -o '[0-9]\+' /version | head -n 1)
CODENAME=$(grep -o -m 1 '[A-Z]\+' /codename | tr -d '\n')

# Fallback in case /version invalid
if [[ -z "$NEW_VERSION" ]]; then
	NEW_VERSION=2001
  echo -n "2001" > /version
fi

# Fallback in case /codename is invalid
if [[ -z "$CODENAME" ]]; then
	CODENAME="AFTERSHOCK"
  echo -n "AFTERSHOCK" > /codename
fi

cat > /etc/os-release <<EOF
PRETTY_NAME="ANDRAX-NG $NEW_VERSION ($CODENAME)"
NAME="ANDRAX-NG"
VERSION_ID="$NEW_VERSION"
VERSION="$NEW_VERSION ($CODENAME)"
VERSION_CODENAME=$CODENAME
ID=andrax
HOME_URL="https://snakesecurity.org/andrax"
SUPPORT_URL="https://snakesecurity.org/contact"
BUG_REPORT_URL="https://snakesecurity.org/contact"
EOF

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Copy os-release... PASS!"
else
  # houston we have a problem
  exit 1
fi

chmod 644 /etc/os-release

chmod 777 /usr/lib/os-release

cat > /usr/lib/os-release <<EOF
PRETTY_NAME="ANDRAX-NG $NEW_VERSION ($CODENAME)"
NAME="ANDRAX-NG"
VERSION_ID="$NEW_VERSION"
VERSION="$NEW_VERSION ($CODENAME)"
VERSION_CODENAME=$CODENAME
ID=andrax
HOME_URL="https://snakesecurity.org/andrax"
SUPPORT_URL="https://snakesecurity.org/contact"
BUG_REPORT_URL="https://snakesecurity.org/contact"
EOF

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

if [ $(uname -m | grep 'x86_64') ]; then
  #
  echo "Bypass Graphical Environment Setup..."
else
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
    echo "Setup default FLUXBOX STYLE... PASS!"
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

  mkdir -p /opt/ANDRAX/terminator

  cp -Rf terminator-config /opt/ANDRAX/terminator/.config

  if [ $? -eq 0 ]
  then
    # Result is OK! Just continue...
    echo "Copy terminator config... PASS!"
  else
    # houston we have a problem
    exit 1
  fi

fi

cp -Rf sudoers /etc/sudoers

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Copy sudoers file... PASS!"
else
  # houston we have a problem
  exit 1
fi

chown root:root /etc/sudoers

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Set sudoers file owner... PASS!"
else
  # houston we have a problem
  exit 1
fi

chmod 440 /etc/sudoers

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Set sudoers file permissions... PASS!"
else
  # houston we have a problem
  exit 1
fi

clang -o andrax-fetch andrax-fetch.c -s

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Compile ANDRAX-FETCH... PASS!"
else
  # houston we have a problem
  exit 1
fi

cp -Rf andrax-fetch /opt/ANDRAX/bin/andrax

if [ $? -eq 0 ]
then
  # Result is OK! Just continue...
  echo "Install ANDRAX-FETCH... PASS!"
else
  # houston we have a problem
  exit 1
fi








###########################################
#                                         #
# Any command below that is a hot-fix...  #
#                                         #
###########################################

if [ $(uname -m | grep 'x86_64') ]; then
  echo "Bypass HOTFIX VNC..."
else
  sudo service vnc stop
  sudo apt update
  sudo apt remove --purge tightvncserver tightvncpasswd -y
  sudo apt install tigervnc-standalone-server -y --no-install-recommends
fi

