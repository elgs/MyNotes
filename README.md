MyNotes
=======

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
`brew install go --cross-compile-all --cc=gcc-4.9`

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
ssh user@server mkdir -p .ssh
cat ~/.ssh/id_rsa.pub | ssh user@server "cat >> .ssh/authorized_keys"
ssh user@server chmod 700 .ssh
ssh user@server chmod 640 .ssh/authorized_key
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
to add a new zone
```
rndc addzone mydomain.com  '{type master; file "/etc/bind/rndc_zones/mydomain.com";};'
rndc reconfig
```

to reload modified zone
```
rndc reload <zone>
```

to remove a zone
```
rndc delzone mydomain.com
```

Ultimate way to install node/npm with homebrew
---
```
$ brew install node --without-npm
$ curl https://npmjs.org/install.sh | sh
```
Please note `sudo` is NOT used anywhere in the above commands. The reason why I want to install `node` and `npm` separately is that `homebrew` does not like `npm` to update `npm` iteslf. `homebrew` has a philosophy that everything is inside it's `Cellar`. I personally appreeciate `homebrew`'s clean way of doing things. However `npm` is just yet another package manager, which is not aware of `homebrew`'s cellars philosophy. Therefore, I prefer to get `homebrew` to manager `node`, and let `npm` to manage itself. 

Extend logic volume
---
```
# lvextend -l +100%FREE /dev/ubuntu0-vg/root
# resize2fs /dev/ubuntu0-vg/root 
```
