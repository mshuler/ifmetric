# $Id: Makefile.am 17 2004-01-23 23:25:07Z lennart $

# This file is part of ifmetric.
#
# ifmetric is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# ifmetric is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with ifmetric; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.

EXTRA_DIST=bootstrap.sh README LICENSE
SUBDIRS=src man doc

MAINTAINERCLEANFILES = README
noinst_DATA = README

README:
	rm -f README
	$(MAKE) -C doc README
	ln -s doc/README README

homepage:
	test -d $$HOME/homepage/lennart
	mkdir -p $$HOME/homepage/lennart/projects/ifmetric
	cp *.tar.gz $$HOME/homepage/lennart/projects/ifmetric
	cp man/ifmetric.8.xml man/xmltoman.css man/xmltoman.xsl man/xmltoman.dtd doc/README.html doc/style.css $$HOME/homepage/lennart/projects/ifmetric
	cp $$HOME/homepage/lennart/projects/ifmetric/README.html $$HOME/homepage/lennart/projects/ifmetric/index.html
