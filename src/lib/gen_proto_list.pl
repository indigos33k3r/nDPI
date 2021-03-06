#!/usr/bin/perl -w
use English;

my @P;
my %N;
my $m=0;
my ($n,$p);

die "BUG1" if !open(F,'<../include/ndpi_protocol_ids.h');

while(<F>) {
	next if !/^\s*(NDPI_PROTOCOL_\S+)\s+=\s*(\d+)\s*,/;
	($p,$n) = ($1,$2);
	#	print "$1 $2\n";
	if(defined $P[$n]) {
		print STDERR "BUG! $p ($n) redefined $P[$n]. Skip it!\n"
			if !($p eq 'PROTOCOL_UNKNOWN' && !$n);
		next;
	}
	$P[$n]=$p;
	$N{$p}=$n;
	$m = $n if $n > $m;
}
close(F);
if(open(F,'>ndpi_network_list_compile.h')) {
	print F "const char *proto_def[NDPI_LAST_IMPLEMENTED_PROTOCOL+1] = {\n\n";

	for(my $i=0; $i <= $m; $i++) {
		print F "_P($P[$i])",$i == $m ? '':',',"\n";
	}
	print F "\n};\n";
	close(F);
}
exit(0);
