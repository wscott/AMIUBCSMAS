#! /usr/bin/perl -w
$r = $ARGV[0] || 160;
b = $ARGV[1] || 3;

$a = 100000 * $b * ($b + $r) / (2*$b + $r);
$c = - $a / ($b + $r);

print "Range=$r  B=$b  A=$a  C=$c\n";

