class Module
  # This method defines attribute reader and writer methods for named
  # attributes, but expects a hash argument mapping attribute names to
  # default values. The generated attribute reader methods return the
  # default value if the instance variable has not yet been defined.
  def attributes(hash)
    hash.each_pair do |symbol, default|   # For each attribute/default pair
      getter = symbol                     # Name of the getter method
      setter = :"#{symbol}="              # Name of the setter method
      variable = :"@#{symbol}"            # Name of the instance variable
      define_method getter do             # Define the getter method
        if instance_variable_defined? variable
          instance_variable_get variable  # Return variable, if defined
        else
          default                         # Otherwise return default
        end
      end

      define_method setter do |value|     # Define setter method
        instance_variable_set variable,   # Set the instance variable
                              value       # To the argument value
      end
    end
  end

  # This method works like attributes, but defines class methods instead
  # by invoking attributes on the eigenclass instead of on self.
  # Note that the defined methods use class instance variables
  # instead of regular class variables.  
  def class_attrs(hash)
    eigenclass = class << self; self; end
    eigenclass.class_eval { attributes(hash) }
  end

  # Both methods are private
  private :attributes, :class_attrs
end
