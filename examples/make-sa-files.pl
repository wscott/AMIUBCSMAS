#! /usr/bin/perl -w
print "Creating Starana testbed files...\n";
system '../perl/stars2smf.pl < starana.map > sa-map.smf';
system '../perl/stars2smf.pl < starana1.pla > sa-pla1.smf';
system '../perl/stars2smf.pl < starana2.pla > sa-pla2.smf';
system '../perl/stars2smf.pl < starana3.pla > sa-pla3.smf';
system '../perl/stars2smf.pl < starana1.fle > sa-fle1.smf';
system '../perl/stars2smf.pl < starana2.fle > sa-fle2.smf';
system '../perl/stars2smf.pl < starana3.fle > sa-fle3.smf';
