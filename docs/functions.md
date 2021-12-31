## Functionalities
__NOTE__: the following commands will be run from the directory's __root directory__.
All of the scripts, however, can be called __globally__ with the necessary dependencies. Consider the following example:

```
$ ./PATH/to/daily-dose-lang/foo
```

### Default (timed) run

The entries are __time limited__ by default, as the project's name implies, with `12h = 1 entry`.

```sh
./run.sh $WORDLIST
```

### Unlimited mode

There is no __time limit__, so you can retrieve as many entries as you want:

```sh
./run.sh $WORDLIST -ul, --unlimited-mode
```

\* `$WORDLIST` represents the source from `database` directory and will be used in the following examples for brevity.

#### Listing wordlists

There's a script that can list all supported __word-lists__ from 'database':\*

```sh
$ ./dict_list
```

\* By default, it will display the __keys__ of the supported inputs. They are, however, valid, because `run.sh` has a __parser__ that can comprehend such behavior.

In practice, given by a __pseudo-code__:

```text
FOR file IN DATABASE_DIR
    REMOVE file extension of $file, REMEMBER $file's base name
    IF $file matches $key
        APPEND the relative path to the script
        BREAK
    ELSE 
        RETAIN $key
```

You can optionally - if you prefer so - list the __relative paths__ of the inputs (respective to the root directory):

```sh
$ ./dict_list -f, --full
```

Alternatively, use the __help__ flag:

```sh
$ ./dict_list -h, --help
```

### Displaying entries

Displaying the __latest__ entry:

```sh
$./mount.sh
```

\* If the user is unable to retrieve a new entry owing to a __time limit__, `mount.sh` is automatically invoked (in the default behavior).
