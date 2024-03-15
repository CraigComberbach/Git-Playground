require 'ceedling/constants'
require 'ceedling/defaults'
require 'ceedling/exceptions'

class PluginReportinator
  
  constructor :plugin_reportinator_helper, :plugin_manager, :reportinator

  def setup
    @test_results_template = nil
  end
  
  def register_test_results_template(template)
    @test_results_template = template
  end

  def set_system_objects(system_objects)
    @plugin_reportinator_helper.ceedling = system_objects
  end
  
  def fetch_results(results_path, test, options={:boom => false})
    return @plugin_reportinator_helper.fetch_results( File.join(results_path, test), options )
  end

  def generate_banner(message)
    return @reportinator.generate_banner(message)
  end

  def generate_heading(message)
    return @reportinator.generate_heading(message)
  end

  def assemble_test_results(results_list, options={:boom => false})
    aggregated_results = new_results()

    results_list.each do |result_path| 
      results = @plugin_reportinator_helper.fetch_results( result_path, options )
      @plugin_reportinator_helper.process_results(aggregated_results, results)
    end

    return aggregated_results
  end
      
  def run_test_results_report(hash, verbosity=Verbosity::NORMAL, &block)
    if @test_results_template.nil?
      raise CeedlingException.new("No test results report template has been set.")
    end

    run_report( $stdout,
                @test_results_template,
                hash,
                verbosity,
                &block
    )
  end
  
  def run_report(stream, template, hash=nil, verbosity=Verbosity::NORMAL)
    failure = nil
    failure = yield() if block_given?
  
    @plugin_manager.register_build_failure( failure )
    
    @plugin_reportinator_helper.run_report( stream, template, hash, verbosity )
  end
  
  #
  # Private
  #

  private
  
  def new_results()
    return {
      :times       => {},
      :successes   => [],
      :failures    => [],
      :ignores     => [],
      :stdout      => [],
      :counts      => {:total => 0, :passed => 0, :failed => 0, :ignored  => 0, :stdout => 0},
      :total_time  => 0.0
      }
  end
 
end