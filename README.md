MyNotes
=======

Change vm root password
---
First mount the disk somewhere on the host. I created a directory called a, and mounted it there.
```bash
qemu-nbd -c /dev/nbd0 *.qcow2 
mount /dev/nbd0p1 a
```

Change directory to a, and change the root password by modifying /etc/shadow:

```bash
perl -pe 's|(?<=root:)[^:]*|crypt("my_new_password","\$6\$some_salt\$")|e' etc/shadow > root/shadow
cp root/shadow etc/
rm root/shadow
```

Then unmount it:
```bash
umount /dev/nbd0p1
qemu-nbd -d /dev/nbd0
```

Start subl from terminal
---
`ln -s /Applications/Sublime\ Text.app/Contents/SharedSupport/bin/subl /usr/local/bin/subl`

Remove dependencies for homebrew formula
---
```
brew rm FORMULA
brew rm $(join <(brew leaves) <(brew deps FORMULA))
```
Run `brew rm $(join <(brew leaves) <(brew deps FORMULA))` multiple times until it says `This command requires a keg argument`. Then run `brew doctor` to check dependencies missing. Finally run `brew cleanup`.

Install go from homebrew
---
`brew install go --cross-compile-all`

Build go project for many platforms
---
```
GOOS=windows GOARCH=386 go install
GOOS=windows GOARCH=amd64 go install

GOOS=linux GOARCH=386 go install
GOOS=linux GOARCH=amd64 go install
GOOS=linux GOARCH=arm go install

GOOS=darwin GOARCH=386 go install
GOOS=darwin GOARCH=amd64 go install

GOOS=freebsd GOARCH=386 go install
GOOS=freebsd GOARCH=amd64 go install

GOOS=netbsd GOARCH=386 go install
GOOS=netbsd GOARCH=amd64 go install

GOOS=openbsd GOARCH=386 go install
GOOS=openbsd GOARCH=amd64 go install
```

Disconnect from svn
---
`find . -name .svn | xargs rm -Rf`

Show all files
---
```
defaults write com.apple.finder AppleShowAllFiles TRUE
killall Finder
```

Disable dashboard
---
```
defaults write com.apple.dashboard mcx-disabled -boolean YES
killall Dock
```

Iframe to talk to parent
---
```
child -> parent: 
window.parent.document.getDocumentById('dom_id');  

parent -> child: 
var ifrm = document.getElementById('my_iframe');  
ifrm = (ifrm.contentWindow) ? ifrm.contentWindow : (ifrm.contentDocument.document) ? ifrm.contentDocument.document : ifrm.contentDocument;  
var my_dom = ifrm.document.getDocumentById('dom_id');  
```

Generate RSA key pair
---
`ssh-keygen -t rsa`

Login ssh without password
---
```
target_host="root@192.168.0.1"
ssh ${target_host} mkdir -p .ssh
cat ~/.ssh/id_rsa.pub | ssh ${target_host} "cat >> .ssh/authorized_keys"
ssh ${target_host} chmod 700 .ssh
ssh ${target_host} chmod 640 .ssh/authorized_keys
```

Sync Postfix user mapping table (Ubuntu)
---
`cp -p /etc/passwd /var/spool/postfix/etc/passwd`

Enable Roundcube password plugin to use chpasswd driver
---
Edit the file `/etc/sudoers`, then add this line:
`www-data ALL=NOPASSWD: /usr/sbin/chpasswd` under:
`root    ALL=(ALL:ALL) ALL`

Persist iptable configurations on Ubuntu
---
`apt-get install iptables-persistent`

Adding and deleting zone using rndc
---
to enable rndc to add new zones, add the following code to /etc/bind/named.conf.option:
```
allow-new-zones yes;
```
to add a new zone
```
rndc addzone mydomain.com  '{type master; file "/etc/bind/db/mydomain.com";};'
rndc addzone mydomain.com ‘{ type slave; masters { master_ip; }; };’
```
to add the reserve zone
```
rndc addzone 0.168.192.in-addr.arpa  '{type master; file "/etc/bind/db/db.192.168.0";};'
rndc addzone 0.168.192.in-addr.arpa '{ type slave; masters { master_ip; }; };'
```

to reload modified zone
```
rndc reload mydomain.com
rndc reload 0.168.192.in-addr.arpa
```

to remove a zone
```
rndc delzone mydomain.com
```

Ultimate way to install node/npm with homebrew
---
```
$ brew install node --without-npm
$ curl -L https://npmjs.org/install.sh | sh
```
Please note `sudo` is NOT used anywhere in the above commands. The reason why I want to install `node` and `npm` separately is that `homebrew` does not like `npm` to update `npm` iteslf. `homebrew` has a philosophy that everything is inside it's `Cellar`. I personally appreeciate `homebrew`'s clean way of doing things. However `npm` is just yet another package manager, which is not aware of `homebrew`'s cellars philosophy. Therefore, I prefer to get `homebrew` to manager `node`, and let `npm` manage itself. 

Extend logic volume
---
```
# lvextend -l +100%FREE /dev/ubuntu0-vg/root
# resize2fs /dev/ubuntu0-vg/root 
```

Detect java executable
---
```bash
#!/bin/bash

if [[ $(which ${JAVA_HOME}/bin/java) ]]; then
	exe="${JAVA_HOME}/bin/java"
elif [[ $(which java) ]]; then
	exe="java"
else 
	echo "Java environment is not detected."
	exit 1
fi

${exe} -version
```

$ in shell
---
```bash
#$(xxx) execute the output of xxx
$(which "$JAVA_HOME/bin/java") -version

#${xxx} evaluate xxx
${JAVA_HOME}/bin/java -version
```

iptables for port forwarding
---
Edit this file `/etc/sysctl.conf`，and change the value from `0` to `1`:
```
net.ipv4.ip_forward = 1
```
Run `sysctl -p` to make the change effective 

```
iptables -t nat -A PREROUTING -p tcp -i eth0 --dport <localPort> -j DNAT --to <remoteIp>:<remotePort>
iptables -t nat -A PREROUTING -p tcp -i eth0 --dport <localPort> -j DNAT --to <remoteIp>:<remotePort>
iptables -t nat -A PREROUTING -p tcp -i eth0 --dport <localPort> -j DNAT --to <remoteIp>:<remotePort>
iptables -t nat -A PREROUTING -p tcp -i eth0 --dport <localPort> -j DNAT --to <remoteIp>:<remotePort>
iptables -t nat -A POSTROUTING -j MASQUERADE
```
