#!/usr/bin/perl -w
#tck13: Tyler Kelly
use strict;
use warnings;
my @arr = ();
#grab contents of wordlist from STDIN and place into @arr
while(<>){
  chomp;
  push @arr, $_;
}
my @sort_arr = sort {&len_lex} @arr;

print join("\n",@sort_arr);
print "\n";
sub len_lex(){
  #if length is same then compare lexcially else compare by size
  if(length $a == length $b){return $a cmp $b;}
  return length $a <=> length $b;
}
