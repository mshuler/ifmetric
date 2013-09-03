# $Id: Makefile.am 16 2004-01-23 23:20:25Z lennart $

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

man_MANS = ifmetric.8

noinst_DATA = ifmetric.8.xml

EXTRA_DIST = $(man_MANS) ifmetric.8.xml.in xmltoman.css xmltoman.xsl xmltoman.dtd

CLEANFILES = ifmetric.8.xml

ifmetric.8.xml: ifmetric.8.xml.in Makefile
	sed -e 's,@sysconfdir\@,$(sysconfdir),g' -e 's,@sbindir\@,$(sbindir),g' -e 's,@PACKAGE_URL\@,$(PACKAGE_URL),g' -e 's,@PACKAGE_BUGREPORT\@,$(PACKAGE_BUGREPORT),g' $< > $@

if USE_XMLTOMAN

CLEANFILES += $(man_MANS)

ifmetric.8: ifmetric.8.xml Makefile
	 xmltoman $< > $@

endif
