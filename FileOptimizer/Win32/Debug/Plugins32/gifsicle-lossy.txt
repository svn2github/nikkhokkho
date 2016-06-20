
Lossy
=====

https://github.com/pornel/giflossy/releases/tag/lossy-1.80
https://pornel.net/lossygif

./gifsicle --lossy=80 -O3 -o lossy-compressed.gif input.gif


Gifsicle
========

Gifsicle manipulates GIF image files. Depending on command line
options, it can merge several GIFs into a GIF animation; explode an
animation into its component frames; change individual frames in an
animation; turn interlacing on and off; add transparency; add delays,
disposals, and looping to animations; add and remove comments; flip
and rotate; optimize animations for space; change images' colormaps;
and other things.


Copyright/License
-----------------

Source code is Copyright (C) 1997-2013 Eddie Kohler.

IF YOU PLAN TO USE GIFSICLE ONLY TO CREATE OR MODIFY GIF IMAGES, DON'T
WORRY ABOUT THE REST OF THIS SECTION. Anyone can use Gifsicle however
they wish; the license applies only to those who plan to copy,
distribute, or alter its code. If you use Gifsicle for an
organizational or commercial Web site, I would appreciate a link to
the Gifsicle home page on any 'About This Server' page, but it's not
required.

This code is distributed under the GNU General Public License, Version
2 (and only Version 2). The GNU General Public License is available
via the Web at <http://www.gnu.org/licenses/gpl.html> or in the
'COPYING' file in this directory.

The following alternative license may be used at your discretion.

Permission is granted to copy, distribute, or alter Gifsicle, whole or
in part, as long as source code copyright notices are kept intact,
with the following restriction: Developers or distributors who plan to
use Gifsicle code, whole or in part, in a product whose source code
will not be made available to the end user -- more precisely, in a
context which would violate the GPL -- MUST contact the author and
obtain permission before doing so.


Authors
-------

Kornel Lesiński <kornel@pngquant.org>
ata4 <barracuda415@yahoo.de>
Lossy compression.
http://pornel.net/lossygif

Eddie Kohler <ekohler@gmail.com>
http://www.read.seas.harvard.edu/~kohler/
He wrote it.

Anne Dudfield <anne@mazunetworks.com>
http://www.frii.com/~annied/
She named it.

David Hedbor <david@hedbor.org>
Many bug reports and constructive whining about the optimizer.

Emil Mikulic <darkmoon@connexus.net.au>
Win32 port help.

Hans Dinsen-Hansen <dino@danbbs.dk>
http://www.danbbs.dk/~dino/
Adaptive tree method for GIF writing.
