MyNotes
=======

Start subl from terminal
---
ln -s /Applications/Sublime\ Text.app/Contents/SharedSupport/bin/subl /usr/local/bin/subl

Remove dependencies for homebrew formula
---
brew rm FORMULA
brew rm $(join <(brew leaves) <(brew deps FORMULA))
