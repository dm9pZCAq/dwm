# patches
all patches is branches

```
$ git branch  # to see it
```

branch with merged patches is **patched**

### my patches
* autostart
* xrdb-colors
* bartagindicator
* disabletitle
* center


# compile

```
$ git checkout patched
$ make
# make install
```

if you don't have [tcc](https://bellard.org/tcc/) then:

```
$ make CC=c99
```

## other

dwm *README* without .md
