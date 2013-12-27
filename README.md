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
