scripts
=======

Here are some utils for url encoding strings.

- src/int2utf8.c: Take numeric (integer) arguments and prints its UTF-8 characters.
- src/utf8table.c: Prints the entire UTF-8 table (from 0 to 255).
- src/urlencode.c: Encode or decode urls.

All of them are plain C code ready to compile with something like gcc &lt;source&gt; -o &lt;executable&gt;

There are also a bash script intended to sync a remote directory (in a USB drive or something like that) whith a local numbered backup:

- bksync: Make numbered backups based on the timestamps.
