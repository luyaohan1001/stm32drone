use warnings;
use strict;

my @videos = <*>;

foreach my $video (@videos) {
	my $videocp = $video;
	$videocp =~ s/.mp4//;
	my $gif = $videocp .".gif";
	`ffmpeg -i $video $gif`;

}
