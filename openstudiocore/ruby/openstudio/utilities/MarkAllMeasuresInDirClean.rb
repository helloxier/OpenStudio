########################################################################################################################
#  OpenStudio(R), Copyright (c) 2008-2016, Alliance for Sustainable Energy, LLC. All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
#  following conditions are met:
#
#  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
#  disclaimer.
#
#  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
#  following disclaimer in the documentation and/or other materials provided with the distribution.
#
#  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote
#  products derived from this software without specific prior written permission from the respective party.
#
#  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative
#  works may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without
#  specific prior written permission from Alliance for Sustainable Energy, LLC.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
#  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER, THE UNITED STATES GOVERNMENT, OR ANY CONTRIBUTORS BE LIABLE FOR
#  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
#  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
########################################################################################################################

######################################################################
# == Synopsis
#
#   Marks all measures found in a directory as clean.
#
# == Usage
#
#  ruby MarkAllMeasuresInDirClean.rb ARGV[0]
#
#  ARGV[0] - Path to directory containing measures
#
# == Examples
#
#   ruby MarkAllMeasuresInDirClean.rb 'C:\path\to\measures\' 
#
######################################################################

require 'openstudio'

dir = ARGV[0].gsub("\\", "/")

if not dir or not File.directory?(dir)
  puts "Script requires argument which is path to directory containing measures"
  exit(false)
end

puts "Marking measures found in '#{dir}' as clean"

num_measures = 0
Dir.glob("#{dir}/*/") do |measure_dir|
  puts measure_dir
  if File.directory?("#{measure_dir}")
    measure = OpenStudio::BCLMeasure::load(OpenStudio::Path.new("#{measure_dir}"))
    if measure.empty?
      puts "Directory #{measure_dir} is not a measure"
    else
      measure = measure.get
      
      # update file checksums
      measure.checkForUpdatesFiles
      
      # try to load the ruby measure
      begin
        info = OpenStudio::Ruleset.getInfo(measure)
        info.update(measure)
      rescue Exception => e  
        # failed to get info, put error into the measure's xml
        info = OpenStudio::Ruleset::RubyUserScriptInfo.new(e.message)
        info.update(measure)
      end

      # check for xml updates
      measure.checkForUpdatesXML

      measure.save
    end
  end
end