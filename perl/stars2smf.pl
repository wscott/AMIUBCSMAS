#! /usr/bin/perl -w

$_ = <>;

if (/^Planet Name\tOwner\tStarbase Type/) {
    # planetary report

    if (!/GateMass/) {
	# old-style report
	print STDERR "Old-style planetary report found....bleargh....";

	while (<>) {
	    @f = split('\t');

	    # clean whitespace
	    for $i (0..$#f) {
		$f[$i] =~ s/(^\s+|\s+$)//g;
	    }

	    # 2 possibilities: owned planet or non-owned planet
	    if ($#f == 19) {
		# owned (report_age assumed to be 0)

		$pla_table{$f[0]} = { 'owner' =>    $f[1],
				      'population' => $f[4],
				      'habitability' => "$f[5]/-100%",
				      'installations' => "$f[7] $f[8] -1",
				      'def_coverage' => "$f[9]",
				      'minerals' => "$f[10] $f[11] $f[12]",
				      'mineral_conc' => "$f[16] $f[17] $f[18]" };
	    } else {
		# not owned
		if ($f[1]) { # someone owns it
		    # paranoia check for non-scanned world
		    $f[5] = "0%" if !$f[5];
		    $f[4] = 0 if !$f[4];

		    $pla_table{$f[0]} = { 'owner' =>    $f[1],
					  'population' => $f[4],
					  'habitability' => "$f[5]/-100%" };
		    
		} else {
		    $f[5] = "0%" if !$f[5];
		    $pla_table{$f[0]} = { 'habitability' => "$f[5]/-100%" };
		}

		$pla_table{$f[0]}->{'report_age'} = $f[3] if $f[3];
	    }

	    $pla_table{$f[0]}->{'starbase'} = "\"$f[2]\" 0% 0 0 \"\" 0" if $f[2];
	}

    } else { # NEW style report!
	print STDERR "NEW-style planetary report found! Yeah!\n";

	# generate field->column associations
	@f = split('\t');

	for $i (0..$#f) {
	    # clean whitespace
	    $f[$i] =~ s/(^\s+|\s+$)//g;

	    $field_table[$i] = $f[$i];
	    $field_assoc{$f[$i]} = $i;
	}

	print STDERR "Slurping planets: ";

	while (<>) {
	    @f = split('\t');

	    # clean whitespace
	    for $i (0..$#f) {
		$f[$i] =~ s/(^\s+|\s+$)//g;
	    }
	    
	    print STDERR ".";

	    $ph = { () };
	    # add in the various data
	    if ($f[$field_assoc{'Owner'}]) {
		$ph->{'owner'} = $f[$field_assoc{'Owner'}];
	    }

	    if ($f[$field_assoc{'Starbase Type'}]) {
		if ($f[$field_assoc{'PctDmg'}]) {
		    $ph->{'starbase'} = "\"$f[$field_assoc{'Starbase Type'}]\" $f[$field_assoc{'PctDmg'}]%";
		} else {
		    $ph->{'starbase'} = "\"$f[$field_assoc{'Starbase Type'}]\" 0%";
		}

		if ($f[$field_assoc{'GateRange'}]) {
		    $ph->{'starbase'} .= " $f[$field_assoc{'GateRange'}] $f[$field_assoc{'GateMass'}]";
		} else {
		    $ph->{'starbase'} .= " 0 0";
		}

		if ($f[$field_assoc{'Driver'}]) {
		    $f[$field_assoc{'Warp'}] += 4;
		    $ph->{'starbase'} .= " \"$f[$field_assoc{'Driver'}]\" $f[$field_assoc{'Warp'}]";
		} else {
		    $ph->{'starbase'} .= " \"\" 0";
		}
	    }

	    if ($f[$field_assoc{'Report Age'}]) {
		$ph->{'report_age'} = $f[$field_assoc{'Report Age'}];
	    }

	    if ($f[$field_assoc{'Population'}]) {
		$ph->{'population'} = $f[$field_assoc{'Population'}];
	    }

	    if ($f[$field_assoc{'Value'}]) {
		$ph->{'habitability'} = "$f[$field_assoc{'Value'}]/$f[$field_assoc{'Terra'}]";
	    }

	    if ($f[$field_assoc{'Mines'}]) {
		$ph->{'installations'} = "$f[$field_assoc{'Mines'}] $f[$field_assoc{'Factories'}] -1";
	    }

	    if ($f[$field_assoc{'Def %'}]) {
		$ph->{'def_coverage'} = "$f[$field_assoc{'Def %'}]";
	    }

	    if ($f[$field_assoc{'S Iron'}]) {
		$ph->{'minerals'} = "$f[$field_assoc{'S Iron'}] $f[$field_assoc{'S Bora'}] $f[$field_assoc{'S Germ'}]";
	    }

	    if ($f[$field_assoc{'Iron MC'}]) {
		$ph->{'mineral_conc'} = "$f[$field_assoc{'Iron MC'}] $f[$field_assoc{'Bora MC'}] $f[$field_assoc{'Germ MC'}]";
	    }

	    if ($f[$field_assoc{'Grav'}]) {
		# clean them up
		$f[$field_assoc{'Grav'}] =~ s/g$//;
		$f[$field_assoc{'Temp'}] =~ s/.C$//;
		$f[$field_assoc{'Rad'}] =~ s/mR$//;

		$ph->{'stats'} = "$f[$field_assoc{'Grav'}] $f[$field_assoc{'Temp'}] $f[$field_assoc{'Rad'}]";
	    }

	    if ($f[$field_assoc{'GravOrig'}]) {
		# clean them up
		$f[$field_assoc{'GravOrig'}] =~ s/g$//;
		$f[$field_assoc{'TempOrig'}] =~ s/.C$//;
		$f[$field_assoc{'RadOrig'}] =~ s/mR$//;

		$ph->{'original_stats'} = "$f[$field_assoc{'GravOrig'}] $f[$field_assoc{'TempOrig'}] $f[$field_assoc{'RadOrig'}]";
	    }

	    if ($f[$field_assoc{'Scan'}]) {
		$ph->{'scanning'} = "$f[$field_assoc{'Scan'}] $f[$field_assoc{'Pen'}]";
	    }

	    if ($f[$field_assoc{'Route'}]) {
		$ph->{'routing'} = "\"$f[$field_assoc{'Route'}]\"";
	    }

	    $pla_table{$f[$field_assoc{'Planet Name'}]} = $ph;
	}
    }

    print STDERR "\nDumping .smf to stdout....\n";

    write_hash('planet', \%pla_table);

} elsif (/^Fleet Name\tX\tY/) {
    # fleet report

    if (!/Laying/) {
	# old-style report
	print STDERR "Old-style fleet report found....bleargh....";

	while (<>) {
	    @f = split('\t');

	    # clean whitespace
	    for $i (0..$#f) {
		$f[$i] =~ s/(^\s+|\s+$)//g;
	    }

	    # paranoia check for " in race name
	    $f[0] =~ s/"/'/g;

	    # 2 possibilities: owned or "someone else's"
	    if (!$f[3] || $f[3] =~ /^[0-9]+$/) { # not orbiting planet
		$f[3] = "$f[1] $f[2]";
	    } else {
		$f[3] = "\"$f[3]\"";
	    }

	    if ($f[5]) { # if I know battle plan...
		# add in some random warp (8 is reasonable...)
		$fle_table{$f[0]} = { 'position' => $f[3],
				      'ships' => "$f[6] 0",
				      'warp' => "8",
				      'fuel' => $f[11] };

		if ($f[7] || $f[8] || $f[9] || $f[10]) {
		    $fle_table{$f[0]}->{'cargo'} = "$f[7] $f[8] $f[9] $f[10]";
		}
	
		if ($f[4] ne '--' && $f[4] ne '(Delayed)') {
		    if ($f[4] =~ /Space \(([0-9]+), ([0-9]+)\)/) {
			$fle_table{$f[0]}->{'destination'} = "$1 $2";
		    } else {
			$fle_table{$f[0]}->{'destination'} = "\"$f[4]\"";
		    }
		}
	    } else {
		# not owned
		$fle_table{$f[0]} = { 'position' => $f[3],
				      'ships' => "$f[6] 0" };
	    }
	}

    } else { # NEW style report!
	print STDERR "NEW-style fleet report found! Yeah!\n";

	# generate field->column associations
	@f = split('\t');

	for $i (0..$#f) {
	    # clean whitespace
	    $f[$i] =~ s/(^\s+|\s+$)//g;

	    $field_table[$i] = $f[$i];
	    $field_assoc{$f[$i]} = $i;
	}

	# paranoia check for " in race name
	$f[0] =~ s/"/'/g;

	print STDERR "Slurping fleets: ";

	while (<>) {
	    @f = split('\t');

	    # clean whitespace
	    for $i (0..$#f) {
		$f[$i] =~ s/(^\s+|\s+$)//g;
	    }
	    
	    print STDERR ".";

	    $fh = { };

	    # put in all the stuff which is ALWAYS present
	    if ($f[$field_assoc{'Planet'}]) {
		# planet overrides X/Y position
		$fh->{'position'} = "\"$f[$field_assoc{'Planet'}]\"";
	    } else {
		$fh->{'position'} = "$f[$field_assoc{'X'}] $f[$field_assoc{'Y'}]";
	    }

            # destination (if ship is not halted)
	    $dest = $f[$field_assoc{'Destination'}];
	    if ($dest) {
		if ($dest =~ /([0-9]+)\.([0-9]+)/) {
		    $fh->{'destination'} = ($1-127) . " " . ($2-127);		    
		} elsif ($dest ne '--' && $dest ne '(Delayed)') {
		    if ($dest =~ /Space \(([0-9]+), ([0-9]+)\)/) {
			$fh->{'destination'} = "$1 $2";
		    } else {
			$fh->{'destination'} = "\"$f[4]\"";
		    }
		}
	    }
	
	    $fh->{'ships'} = "$f[$field_assoc{'Ship Cnt'}] $f[$field_assoc{'Mass'}]";

	    # fleet composition
	    $fh->{'composition'} = "$f[$field_assoc{'Unarmed'}] $f[$field_assoc{'Scout'}] $f[$field_assoc{'Warship'}] $f[$field_assoc{'Utility'}] $f[$field_assoc{'Bomber'}]";

            # now check (and add) any additional info
	    if ($f[$field_assoc{'Iron'}] || $f[$field_assoc{'Bora'}] ||
		$f[$field_assoc{'Germ'}] || $f[$field_assoc{'Col'}]) {

		$fh->{'cargo'} = "$f[$field_assoc{'Iron'}] $f[$field_assoc{'Bora'}] $f[$field_assoc{'Germ'}] $f[$field_assoc{'Col'}]";
	    }

	    if ($f[$field_assoc{'Fuel'}]) {
		$fh->{'fuel'} = "$f[$field_assoc{'Fuel'}]";
	    }

	    if ($f[$field_assoc{'Warp'}]) {
		$fh->{'warp'} = "$f[$field_assoc{'Warp'}]";
	    }

	    # this is only included for cross-checks
	    if ($f[$field_assoc{'ETA'}]) {
		if ($f[$field_assoc{'ETA'}] =~ /[0-9]+y/) {
		    chop $f[$field_assoc{'ETA'}];

		    $fh->{'starsETA'} = "$f[$field_assoc{'ETA'}]";
		}
	    }

	    if ($f[$field_assoc{'Cloak'}]) {
		$fh->{'cloaking'} = "$f[$field_assoc{'Cloak'}]";
	    }

	    if ($f[$field_assoc{'Scan'}]) {
		$fh->{'scanning'} = "$f[$field_assoc{'Scan'}] $f[$field_assoc{'Pen'}]";
	    }

	    # not clear if I'll ever use these
	    if ($f[$field_assoc{'Battle Plan'}]) {
		$fh->{'battleplan'} = "\"$f[$field_assoc{'Battle Plan'}]\"";
	    }

	    if ($f[$field_assoc{'Task'}]) {
		$fh->{'wp_task'} = "\"$f[$field_assoc{'Task'}]\"";
	    }

	    if ($f[$field_assoc{'Mining'}]) {
		$fh->{'mining'} = "$f[$field_assoc{'Mining'}]";
	    }

	    if ($f[$field_assoc{'Sweep'}] || $f[$field_assoc{'Laying'}]) {
		$fh->{'minefield_ls'} = "$f[$field_assoc{'Laying'}] $f[$field_assoc{'Sweep'}]";
	    }

	    if ($f[$field_assoc{'Terra'}]) {
		$fh->{'terraforming'} = "$f[$field_assoc{'Terra'}]";
	    }

            $fle_table{$f[$field_assoc{'Fleet Name'}]} = $fh;
	}
    }

    print STDERR "\nDumping .smf to stdout....\n";

    write_hash('fleet', \%fle_table);

} elsif (/^#\tX\tY\tName/) {
    # universe map

    if (!/Name\w+$/) {
	print STDERR "Screwed-style universe report found....\n";

        # handle 1st line (which is buggy :(
	$_ = substr($_, 11);

	@f = split('\t');

	# clean whitespace
	for $i (0..$#f) {
	    $f[$i] =~ s/(^\s+|\s+$)//g;
	}

	$pla_table{$f[3]} = { 'starsid' => "$f[0]",
			      'position' => "$f[1] $f[2]" };

    } else {
	print STDERR "Sane universe report found....\n";
    }

    while (<>) {
	@f = split('\t');

	# clean whitespace
	for $i (0..$#f) {
	    $f[$i] =~ s/(^\s+|\s+$)//g;
	}

	$pla_table{$f[3]} = { 'starsid' => "$f[0]",
			      'position' => "$f[1] $f[2]" };
    }
	
    write_hash('planet', \%pla_table);

} else {
    print STDERR "If this is a Stars! report, I'm unable to understand it.\n";
}

exit(0);


sub write_hash {
    my ($prefix) = shift;
    my (%tab) = (%{$_[0]});

    while (($k, $d) = each %tab) {
	if (%$d) {
	    print "$prefix \"$k\" {\n";

	    if ($d->{'owner'}) {
		print "\towner \"$d->{'owner'}\"\n";
		delete $d->{'owner'};
	    }

	    while (($ik, $id) = each %{$d}) {
		print "\t$ik $id\n";
	    }

	    print "}\n\n";
	}
    }
}

