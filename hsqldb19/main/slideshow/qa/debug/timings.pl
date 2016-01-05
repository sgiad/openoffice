:
eval 'exec perl -wS $0 ${1+"$@"}'
    if 0;
# *************************************************************
#  
#  Licensed to the Apache Software Foundation (ASF) under one
#  or more contributor license agreements.  See the NOTICE file
#  distributed with this work for additional information
#  regarding copyright ownership.  The ASF licenses this file
#  to you under the Apache License, Version 2.0 (the
#  "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#  
#    http://www.apache.org/licenses/LICENSE-2.0
#  
#  Unless required by applicable law or agreed to in writing,
#  software distributed under the License is distributed on an
#  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#  KIND, either express or implied.  See the License for the
#  specific language governing permissions and limitations
#  under the License.
#  
# *************************************************************
# POD Documentation

=head1 PROGRAM NAME AND AUTHOR

Timings - $Revision: 1.2 $
Last changes: $Author: rt $ $Date: 2004-11-26 18:43:32 $

=head1 WHAT IT IS

Extract move effect timings from a verbose trace log of the
presentation engine. Generated is a gnuplot data file, which can be
displayed issuing a 'gnuplot <filename>' or at a gnuplot prompt, via
'load <filename>'.

To generate such a verbose log file, rebuild module canvas and module
slideshow with VERBOSE=t defined in the environment, and debug=t at
the build tool command line. Then run the presentation, and redirect
stdout to your log file.

Call me like this: timings.pl < trace-file > gnuplot-target

The whole point in doing this is to detect jerks in shape movements,
which manifest themselves clearly in the graphed gnuplot output. Note
that there's some heuristic to recognize when one effect ends and
another has started: If the time difference between two subsequent
page flipping times is more than one second, a new effect is assumed
and a new gnuplot data record is generated.

=head1 REQUIREMENTS

Perl 5

=cut

##############################################################################
#

print "# Autogenerated by timings.pl, do not change\n",
      "set ylabel \"position\"\n",
	  "set xlabel \"time\"\n",
      "plot '-' index 0 using (\$1):(\$2) title \"Move effect position\" with lp\n",
	  "#0\n";

$state = 0;
$last_time = 0;
$record = 1;

while( <> )
{
	if( $state == 0 && m|next position will be| )
	{		
		($posX) = m|.*\(([0-9]+.[0-9]+),|;
		($posY) = m|.*,([0-9]+.[0-9]+)\)|;
		$state = 1;
	}
	elsif( $state == 1 && m|output pos is| )
	{
		$state = 2;
	}
	elsif( $state == 2 && m|flip done at| )
	{
		$state = 0;
		($flippingTime) = m|.*at ([0-9]+.[0-9]+)|;

		if( $last_time != 0 )
		{
			if( $last_time + 1.0 < $flippingTime )
			{
				# new record
				print "\n\n#", $record, "\n";
				$record++;
			}
		}

		$last_time = $flippingTime;
		print $flippingTime, " ", $posX, " ", $posY, "\n";
	}
}
