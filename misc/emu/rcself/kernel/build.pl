#!/usr/bin/perl -w

use strict;

open INF,"<build.num";
my $line = <INF>;
chomp;
my $num = $line;
$num += 1;
close INF;

print "build:     dw      $num\n";

open OUTF,">build.num";
print OUTF "$num\n";
close OUTF;

