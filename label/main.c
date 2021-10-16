/*
	main.c (20.01.11)
	Prints or changes exFAT volume label.

	Free exFAT implementation.
	Copyright (C) 2011-2018  Andrew Nayenko

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <exfat.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char** pp;
	struct exfat ef;
	struct exfat_dev* dev;
	int rc = 0;

	for (pp = argv + 1; *pp; pp++)
		if (strcmp(*pp, "-V") == 0)
		{
			printf("exfatlabel %s\n", VERSION);
			puts("Copyright (C) 2011-2018  Andrew Nayenko");
			return 0;
		}

	if (argc != 2 && argc != 3)
	{
		fprintf(stderr, "Usage: %s [-V] <device> [label]\n", argv[0]);
		return 1;
	}

	if (argv[2])
	{
		dev = exfat_open(argv[1], EXFAT_MODE_RW);
		if (dev == NULL)
			return 1;
		if (exfat_mount(&ef, dev, "") != 0)
			return 1;
		rc = (exfat_set_label(&ef, argv[2]) != 0);
	}
	else
	{
		dev = exfat_open(argv[1], EXFAT_MODE_RO);
		if (dev == NULL)
			return 1;
		if (exfat_mount(&ef, dev, "ro") != 0)
			return 1;
		puts(exfat_get_label(&ef));
	}

	exfat_unmount(&ef);
	return rc;
}
