#**************************************************************
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
#**************************************************************



use lib ("$ENV{SOLARENV}/bin/modules");

use Cwd;
use par2script::check;
use par2script::files;
use par2script::globals;
use par2script::parameter;
use par2script::module;
use par2script::undefine;
use par2script::work;

####################################
# Main program
####################################

par2script::parameter::getparameter();
par2script::parameter::control_parameter();
par2script::parameter::outputparameter();

my $includes = par2script::work::setincludes($par2script::globals::includepathlist);
my $parfiles = par2script::work::setparfiles($par2script::globals::parfilelist);

par2script::work::make_complete_pathes_for_parfiles($parfiles, $includes);

print "Reading par files\n";
my $parfilecontent = par2script::work::read_all_parfiles($parfiles);

print "Collecting items\n";
par2script::work::collect_definitions($parfilecontent);

print "Collecting assigned items\n";
par2script::work::collect_assigned_gids();

# print "First control of multiple assignments\n";
# par2script::check::check_multiple_assignments();

print "Searching for Undefinitions\n";
par2script::undefine::undefine_gids($parfilecontent);
par2script::undefine::remove_complete_item("Directory", $parfilecontent);
par2script::undefine::remove_complete_item("Profile", $parfilecontent);

print "Removing assigned GIDs without definitions\n";
par2script::module::remove_undefined_gids_from_modules();

print "Adding definitions without assignment to the root\n";
par2script::module::add_to_root_module();

print "Control of multiple assignments\n";
par2script::check::check_multiple_assignments();

print "Control of definitions with missing assignments\n";
par2script::check::check_missing_assignments();

# checking the setup script
print "Checking directory definitions ...\n";
par2script::check::check_needed_directories();
par2script::check::check_directories_in_item_definitions();
print "Checking module definitions ...\n";
par2script::check::check_module_existence();
print "Checking module assignments ...\n";
par2script::check::check_moduleid_at_items();
print "Checking Root Module ...";
par2script::check::check_rootmodule();
print "Checking Shortcut assignments ...\n";
par2script::check::check_shortcut_assignments();
print "Checking missing parents ...\n";
par2script::check::check_missing_parents();

print "Shorten lines at modules\n";
par2script::module::shorten_lines_at_modules();

# Now the script can be created
print "Creating setup script\n";
my $setupscript = par2script::work::create_script();

print "Saving script\n";
par2script::files::save_file($par2script::globals::scriptname, $setupscript);

# logging, if set
if ($par2script::globals::logging)
{
	par2script::files::save_file($par2script::globals::logfilename, \@par2script::globals::logfileinfo);
	print "Log file written: $par2script::globals::logfilename\n";
}

####################################
# End main program
####################################
