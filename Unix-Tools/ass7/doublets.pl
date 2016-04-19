#!/usr/bin/perl
#Tyler Kelly : tck13
use strict;
use warnings;
if($#ARGV != 1){
  print STDERR "Invalid command syntax\n";
  exit;
}
my $begin = $ARGV[0];
my $end = $ARGV[1];
if(length $begin != length $end){
  print STDERR "Invalid args, lengths do not match\n";
  exit;
}
exit if $begin eq $end;
my @allWords = ();
my $filename = 'wordlist.txt';
open (my $fh, '<:encoding(UTF-8)', $filename)
 or die "Could not open file '$filename' $!";

while(<$fh>){
  chomp;
  push @allWords, $_;
}
close $fh;
if (grep {$_ eq $begin} @allWords){
  ;
}
else{
  print "$begin not in list\n";
  exit;
}
if (grep {$_ eq $end} @allWords){
  ;
}
else{
  print "$end not in list\n";
  exit;
}
my @sameLength = grep {length $_ == length $begin} @allWords;
my @queue = ([$begin]);
my $flag = 0;
while(@queue){#while queue is not empty
  #pop off @queue and store in @ladder
  my @ladder = @{shift @queue};
  if ($ladder[-1] eq $end){
    print join(" --> ", @ladder), "\n";
    $flag = 1;
    last;
  }
  #store last word of ladder in in $last
  my $last = $ladder[-1];
  my @oneDiffer;
  my $index = 0;
  #after this loop, @oneDiffer will hold words within one charachter of $last
  foreach my $candidate (@sameLength){
    my $diff_chars = 0;
    my $i = 0;
    foreach my $char (split //, $candidate){
      if ($char ne substr $last, $i, 1){
        $diff_chars++;
      }
      $i++;
    } 
    if($diff_chars == 1){
      splice @sameLength, $index, 1;
      push @oneDiffer, $candidate;
    }
    $index++;
  }
  #loop over @oneDiffer and add $word to end of @copy,
  # and add @copy to our queue
  foreach my $word (@oneDiffer){
    my @copy = @ladder;
    push @copy, $word;
    push @queue, [@copy];  
  }
}
print "no word ladder found\n" if $flag == 0;
